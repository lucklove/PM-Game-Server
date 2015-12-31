#pragma once
/**
 * \need:
 *      LuaRef.hh for class LuaRef
 *      stack.hh for stack operations
 *      Registry.hh for class Registry
 *      utils.hh for function make_lua_ref
 *      StackGuard for class StackGuard 
 */

namespace nua
{
    class Selector
    {
    private:
        lua_State* l_;
        std::string name_;
        Registry* registry_;
        LuaRefPtr key_;

        std::vector<LuaRefPtr> functor_arguments_;
        bool functor_active_ = false;

        void evaluate_retrieve(int num_results)
        {
            lua_pushglobaltable(l_);
            key_->push();
            lua_gettable(l_, -2);
            lua_remove(l_, lua_absindex(l_, -2));
            evaluate_function_call(num_results);
        }
        
        void evaluate_function_call(int num_results)
        {
            if(!functor_active_)
                return;
            functor_active_ = false;
    
            int handler_index = ErrorHandler::set_error_handler(l_);
            int func_index = handler_index - 1;
            lua_pushvalue(l_, func_index);
            lua_copy(l_, handler_index, func_index);
            lua_replace(l_, handler_index);
            
            for(const LuaRefPtr& arg : functor_arguments_)
                arg->push();

            int status = lua_pcall(l_, functor_arguments_.size(), num_results, handler_index - 1);
            lua_remove(l_, handler_index - 1);

            if(status != LUA_OK)
                ErrorHandler::handle(l_, status);
        }

        template <typename FuncT>
        void evaluate_store(FuncT&& push_func)
        {
            StackGuard sg{l_};
            lua_pushglobaltable(l_);
            key_->push();
            push_func();
            lua_settable(l_, -3);
            lua_pop(l_, 1);
        }

        template <typename L>
        struct lambda_traits;

        template <typename Ret, typename Class, typename... Args>
        struct lambda_traits<Ret(Class::*)(Args...) const>
        {
            using stl_function_type = std::function<Ret(Args...)>;
        };

        template <typename L>
        struct lambda_traits : lambda_traits<decltype(&L::operator())>
        {
        };

        template <typename T>
        struct is_lambda
        {
        private:
            template <typename L>
            static auto check(...) -> std::false_type;

            template <typename L>
            static auto check(int) -> decltype(std::declval<decltype(&L::operator())>(), std::true_type());

        public:
            using type = decltype(check<T>(0));
            enum { value = decltype(check<T>(0))::value };
        };

    public:
        Selector(lua_State* l, Registry* registry, const std::string& name)
            : l_{l}, name_{name}, registry_{registry}, key_{utils::make_lua_ref(l, name)}
        {}

        Selector(const Selector& other) = default;

        ~Selector() noexcept(false)
        {
            if(functor_active_)
                get();
        }

        template <typename... Args>
        Selector operator()(Args... args)
        {
            Selector copy{*this};
            copy.functor_arguments_ = utils::make_lua_refs(l_, args...);
            copy.functor_active_ = true;
            return copy;
        }

        template <typename T>
        typename std::enable_if<!is_lambda<T>::value, void>::type
        operator=(T v)
        {
            evaluate_store([this, v]
            {
                stack::push(l_, v);
            });
        }

        template <typename Ret, typename... Args>
        void operator=(std::function<Ret(Args...)> func)
        {
            evaluate_store([this, func]
            {
                registry_->registerFunction(l_, func);
            });
        }

        template <typename Ret, typename... Args>
        void operator=(Ret(*func)(Args...))
        {
            operator=(std::function<Ret(Args...)>(func));
        }

        template <typename L, typename = typename std::enable_if<is_lambda<L>::value>::type>
        void operator=(const L& lambda)
        {
            operator=(typename lambda_traits<L>::stl_function_type(lambda));
        }

        void get()
        {
            StackGuard sg{l_};
            evaluate_retrieve(0);
        }

        template <typename T>
        T get()
        {
            StackGuard sg{l_};
            evaluate_retrieve(1);
            return stack::pop<T>(l_);
        }

        template <typename T1, typename T2, typename... Args>
        std::tuple<T1, T2, Args...> get()
        {
            StackGuard sg{l_};
            evaluate_retrieve(sizeof...(Args) + 2);
            return utils::get_n<T1, T2, Args...>(l_, std::make_index_sequence<sizeof...(Args) + 2>());
        }
    };
}

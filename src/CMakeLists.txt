SET(POCKET_MONSTER_SRCS
    main.cc
    script/ClassRegister.cc
    script/FunctionRegister.cc
)

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/inc 
    ${CMAKE_SOURCE_DIR}/3rdparty/inc
    /usr/include/mysql
)
LINK_DIRECTORIES(/usr/local/lib64)
ADD_EXECUTABLE(pm_server ${POCKET_MONSTER_SRCS})
TARGET_LINK_LIBRARIES(pm_server boost_system pthread redox ev hiredis soci_core soci_mysql lua atomic)

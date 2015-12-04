#include "crow/crow.h"
#include "utils/Random.hh"
#include "battle/Battle.hh"

int main()
{
    crow::SimpleApp app;

    Battle::route(app);
    
    CROW_ROUTE(app, "/")([]
    {
        return std::to_string(Random::get(0.0, 1.0));
    });
    
    app.port(8080).multithreaded().run();
}

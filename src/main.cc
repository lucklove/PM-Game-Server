#include "crow/crow.h"
#include "storage/BattleDB.hh"
#include "cereal/cereal.hpp"
#include "cereal/archives/xml.hpp"

/*
int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/battle/<int>/<int>")([](int p_pm_id, int s_pm_id)
    {
        crow::json::wvalue result;
        auto battle_opt = Battle::launch(p_pm_id, s_pm_id);
        if(!battle_opt)
        {
            result["result"] = "false";
            result["error"] = "invalid pm id";
        }
        else
        {
            const Battle& b = *battle_opt;
            result["result"] = "true";
            result["battle_id"] = std::to_string(b.id);
            BattleDB::set(b.id, b);
        }
        return result;
    });

    app.port(8080).multithreaded().run();
}
*/
    struct MyData
{
  bool   b;
  double d;

  template <class Archive>
  void serialize( Archive & ar )
  {
    ar( b, d );
  }
};

int main()
{
  int i1, i2, i3, i4;
  MyData md;

  {
    std::ifstream is("data.xml");
    cereal::XMLInputArchive ar(is);

    // NVP doesn't match expected value, perform a search
    ar( cereal::make_nvp("myData", md) );

    ar( i4 );                           // cereal continues from node it found using search
    ar( cereal::make_nvp("var1", i1) ); // new search re-positions at node var1
    ar( i2, i3 );                       // continue from location of last search

                                                // next value read would be 'myData'
    ar( cereal::make_nvp("doesNotExist", i1) ); // throws an exception: NVP not found
  }

  return 0;
}

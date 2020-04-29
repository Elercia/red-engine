#include <RedEngine/Core/Configuration/Configuration.hpp>
#include <catch2/catch.hpp>
#include <RedEngine/Core/Configuration/IniReader.hpp>
#include <iostream>
#include <string>
#include <RedEngine/Core/Configuration/CVar.hpp>

TEST_CASE("INI file parsing", "[Configuration]")
{
    SECTION("Reading from ini file")
    {
        auto catKeyValues = red::utils::IniReader::ReadFromFile("resources/config.ini");

        REQUIRE(std::find_if(catKeyValues.begin(), catKeyValues.end(), [](auto tuple) {
                    return std::get<0>(tuple) == "default" && std::get<1>(tuple) == "ouioui" &&
                           std::get<2>(tuple) == "son beau taxi";
                }) != catKeyValues.end());

        REQUIRE(std::find_if(catKeyValues.begin(), catKeyValues.end(), [](auto tuple) {
                    return std::get<0>(tuple) == "cage" && std::get<1>(tuple) == "nicolas" &&
                           std::get<2>(tuple) == "in a";
                }) != catKeyValues.end());
    }
}

TEST_CASE("Cvar", "[Configuration]")
{
    SECTION("Config variable are loaded when declared before")
    {
        red::CVar<bool> testBool1{"bool1", false, "cat1"};
        red::CVar<bool> testBool2{"bool2", false, "cat1"};
        red::CVar<double> double1{"double1", 0.0, "cat1"};
        red::CVar<int> intVar{"int", 1, "cat1"};
        red::CVar<std::string> str{"str", "non", "cat1"};

        red::Configuration::GetInstance().LoadConfigFile("resources/config.ini");

        REQUIRE(testBool1.GetValue() == true);
        REQUIRE(testBool2.GetValue() == false);
        REQUIRE(std::abs(double1.GetValue() - 0.5) < 0.001);
        REQUIRE(intVar.GetValue() == 1000);
        REQUIRE(str.GetValue() == "je suis un string");
    }

    SECTION("Config variable are loaded when declared after")
    {
        red::Configuration::GetInstance().LoadConfigFile("resources/config.ini");

        red::CVar<bool> testBool1{"bool1", false, "cat1"};
        red::CVar<bool> testBool2{"bool2", true, "cat1"};
        red::CVar<double> double1{"double1", 0.0, "cat1"};
        red::CVar<int> intVar{"int", 1, "cat1"};
        red::CVar<std::string> str{"str", "non", "cat1"};

        REQUIRE(testBool1.GetValue() == true);
        REQUIRE(testBool2.GetValue() == false);
        REQUIRE(std::abs(double1.GetValue() - 0.5) < 0.001);
        REQUIRE(intVar.GetValue() == 1000);
        REQUIRE(str.GetValue() == "je suis un string");
    }
}
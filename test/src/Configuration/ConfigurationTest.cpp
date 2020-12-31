#include "RedEngine/Core/Configuration/CVar.hpp"
#include "RedEngine/Core/Configuration/Configuration.hpp"
#include "RedEngine/Core/Configuration/IniReader.hpp"

#include <catch2/catch.hpp>
#include <filesystem>
#include <iostream>
#include <string>

TEST_CASE("INI file parsing", "[Configuration]")
{
    using namespace std::filesystem;

    path p = current_path();
    std::cout << "current path : " << absolute(p) << std::endl;

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

TEST_CASE("Config variable are loaded when declared before", "[Configuration]")
{
    red::CVar<bool> testBool1{"bool1", "cat1", false};
    red::CVar<bool> testBool2{"bool2", "cat1", false};
    red::CVar<double> double1{"double1", "cat1", 0.0};
    red::CVar<int> intVar{"int", "cat1", 1};
    red::CVar<std::string> str{"str", "cat1", "non"};

    red::Configuration::LoadConfigFile("resources/config.ini");

    REQUIRE(testBool1.GetValue() == true);
    REQUIRE(testBool2.GetValue() == false);
    REQUIRE(std::abs(double1.GetValue() - 0.5) < 0.001);
    REQUIRE(intVar.GetValue() == 1000);
    REQUIRE(str.GetValue() == "je suis un string");
}

TEST_CASE("Config variable are loaded when declared after", "[Configuration]")
{
    red::Configuration::LoadConfigFile("resources/config.ini");

    red::CVar<bool> testBool1{"bool1", "cat1", false};
    red::CVar<bool> testBool2{"bool2", "cat1", true};
    red::CVar<double> double1{"double1", "cat1", 0.0};
    red::CVar<int> intVar{"int", "cat1", 1};
    red::CVar<std::string> str{"str", "cat1", "non"};

    REQUIRE(testBool1.GetValue() == true);
    REQUIRE(testBool2.GetValue() == false);
    REQUIRE(std::abs(double1.GetValue() - 0.5) < 0.001);
    REQUIRE(intVar.GetValue() == 1000);
    REQUIRE(str.GetValue() == "je suis un string");
}

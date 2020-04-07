#include <RedEngine/Core/Configuration/Configuration.hpp>
#include <catch2/catch.hpp>
#include <RedEngine/Core/Configuration/IniReader.hpp>

TEST_CASE("Configuration file", "[Configuration]")
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

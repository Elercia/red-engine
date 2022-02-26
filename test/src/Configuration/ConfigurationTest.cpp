#include "RedEngine/Core/Configuration/CVar.hpp"
#include "RedEngine/Core/Configuration/CVarManager.hpp"
#include "RedEngine/Core/Configuration/IniReader.hpp"
#include "RedEngine/Core/SerializationFunction.hpp"
#include "RedEngine/Filesystem/Path.hpp"

#include <catch2/catch.hpp>
#include <iostream>
#include <string>

#include "TestModule.hpp"

TEST_CASE("INI file parsing", "[Configuration]")
{
    auto catKeyValues = red::utils::IniReader::ReadFromFile(red::Path::Resource("config.ini"));

    REQUIRE(std::find_if(catKeyValues.begin(), catKeyValues.end(),
                         [](auto &tuple)
                         {
                             return std::get<0>(tuple) == "default" && std::get<1>(tuple) == "ouioui" &&
                                    std::get<2>(tuple) == "son beau taxi";
                         }) != catKeyValues.end());

    REQUIRE(std::find_if(catKeyValues.begin(), catKeyValues.end(),
                         [](auto tuple) {
                             return std::get<0>(tuple) == "cage" && std::get<1>(tuple) == "nicolas" &&
                                    std::get<2>(tuple) == "in a";
                         }) != catKeyValues.end());
}

TEST_CASE("Config variable are loaded when declared before", "[Configuration]")
{
    red::CVar<bool> testBool1{"bool1", "cat1", false};
    red::CVar<bool> testBool2{"bool2", "cat1", false};
    red::CVar<double> double1{"double1", "cat1", 0.0};
    red::CVar<int> intVar{"int", "cat1", 1};
    red::CVar<std::string> str{"str", "cat1", "non"};

    red::CVarManager::LoadConfigFile(red::Path::Resource("config.ini"));

    REQUIRE(testBool1.GetValue() == true);
    REQUIRE(testBool2.GetValue() == false);
    REQUIRE(std::abs(double1.GetValue() - 0.5) < 0.001);
    REQUIRE(intVar.GetValue() == 1000);
    REQUIRE(str.GetValue() == "je suis un string");
}

enum class TestEnumCVar
{
    ONE,
    TWO
};

namespace red
{
template <>
bool Deserialize(TestEnumCVar &value, const std::string &str)
{
    if (str == "ONE")
    {
        value = TestEnumCVar::ONE;
        return true;
    }
    if (str == "TWO")
    {
        value = TestEnumCVar::TWO;
        return true;
    }

    return false;
}

template <>
std::string Serialize(const TestEnumCVar &value)
{
    return value == TestEnumCVar::ONE ? "ONE" : "TWO";
}
}  // namespace red

TEST_CASE("Custom CVar type", "[Configuration]")
{
    red::CVar<TestEnumCVar> testValue{"value", "custom", TestEnumCVar::ONE};

    REQUIRE(testValue.GetValue() == TestEnumCVar::ONE);

    red::CVarManager::LoadConfigFile(red::Path::Resource("config.ini"));

    REQUIRE(testValue.GetValue() == TestEnumCVar::TWO);
}
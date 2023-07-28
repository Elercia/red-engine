#include "RedEngine/Math/Math.hpp"
#include "RedEngine/Utils/StringUtils.hpp"

#include <algorithm>
#include <catch2/catch.hpp>

#include "TestModule.hpp"

TEST_CASE("Trim", "[StringUtils]")
{
    String s = "    OUI  ddede  OUI      ";
    red::utils::Trim(s);
    REQUIRE(s == "OUI  ddede  OUI");

    s = "OUI  ddede  OUI      ";
    red::utils::Trim(s);
    REQUIRE(s == "OUI  ddede  OUI");

    s = "    OUI  ddede  OUI";
    red::utils::Trim(s);
    REQUIRE(s == "OUI  ddede  OUI");

    s = "    OUI  ddede  OUI";
    red::utils::Trim(s);
    REQUIRE(s == "OUI  ddede  OUI");

    s = "          ";
    red::utils::Trim(s);
    REQUIRE(s.empty());

    s = "";
    red::utils::Trim(s);
    REQUIRE(s.empty());
}

TEST_CASE("Split", "[StringUtils]")
{
    String myStr = "bla-bli-blo-blu\nbly-blv-blw";
    auto splited = red::utils::Split(myStr, '-');

    REQUIRE(std::find(splited.begin(), splited.end(), "bla") != splited.end());
    REQUIRE(std::find(splited.begin(), splited.end(), "bli") != splited.end());
    REQUIRE(std::find(splited.begin(), splited.end(), "blo") != splited.end());
    REQUIRE(std::find(splited.begin(), splited.end(), "blu\nbly") != splited.end());
    REQUIRE(std::find(splited.begin(), splited.end(), "blw") != splited.end());

    myStr = "azertyuiop";
    splited = red::utils::Split(myStr, '-');

    REQUIRE(splited.size() == 1);
    REQUIRE(splited[0] == myStr);
}

TEST_CASE("StringParser", "[StringUtils]")
{
    using namespace red::utils;

    String str = "[0.5;1.6;2.7;-1]";
    const char* it = str.data();
    const char* end = (&str.back()) + 1;

    float data1 = 0.f;
    float data2 = 0.f;
    float data3 = 0.f;
    int data4 = 0;

    REQUIRE(StringParser::Expect(&it, end, '['));
    REQUIRE(StringParser::ReadFloat(&it, end, data1));
    REQUIRE(StringParser::Expect(&it, end, ';'));
    REQUIRE(StringParser::ReadFloat(&it, end, data2));
    REQUIRE(StringParser::Expect(&it, end, ';'));
    REQUIRE(StringParser::ReadFloat(&it, end, data3));
    REQUIRE(StringParser::Expect(&it, end, ';'));
    REQUIRE(StringParser::ReadInt(&it, end, data4));
    REQUIRE(StringParser::Expect(&it, end, ']'));

    float nothing = 0.f;
    REQUIRE(StringParser::Expect(&it, end, ']') == false);
    REQUIRE(StringParser::ReadFloat(&it, end, nothing) == false);

    REQUIRE(Math::EqualsEpsilon(data1, 0.5f, 0.001f));
    REQUIRE(Math::EqualsEpsilon(data2, 1.6f, 0.001f));
    REQUIRE(Math::EqualsEpsilon(data3, 2.7f, 0.001f));
    REQUIRE(data4 == -1);
}
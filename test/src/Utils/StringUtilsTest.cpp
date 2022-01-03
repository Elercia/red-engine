#include "TestModule.hpp"

#include "RedEngine/Utils/StringUtils.hpp"
#include <catch2/catch.hpp>
#include <algorithm>

TEST_CASE("StringUtils", "[Utils]")
{
    SECTION("Trim")
    {
        std::string s = "    OUI  ddede  OUI      ";
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

    SECTION("Split")
    {
        std::string myStr = "bla-bli-blo-blu\nbly-blv-blw";
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
}
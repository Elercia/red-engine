#include "TestModule.hpp"

#include <LoggerTest.hpp>
#include <catch2/catch.hpp>

TEST_CASE("Logger", "[Debug]")
{
    Logger4Test logger;

    SECTION("Logging trace")
    {
        logger.SetLogLevel(red::LogLevel::LEVEL_TRACE);
        logger.LogInternal(red::LogLevel::LEVEL_TRACE, 10, "LoggerTest.cpp", "Doing stuff with {}, {} times",
                           "my bicycle", 10);

        REQUIRE(logger.lastLog.find("Doing stuff with my bicycle, 10 times") != std::string::npos);
        REQUIRE(logger.lastLog.find("TRACE") != std::string::npos);
    }
}
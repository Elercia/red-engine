#include <catch2/catch.hpp>
#include <logger_test.hpp>

TEST_CASE("Logger", "[Logger]")
{
    LoggerTest logger;

    SECTION("Logging trace")
    {
        logger.SetLogLevel(red::LogLevel::TRACE);
        logger.LogInternal(red::LogLevel::TRACE, "Doing stuff with {}, {d} times", "my bicycle",
                           10);
        std::cout << logger.lastLog << std::endl;

        REQUIRE(logger.lastLog.find("Doing stuff with my bicycle, 10 times") != std::string::npos);
        REQUIRE(logger.lastLog.find("TRACE") != std::string::npos);
    }
}
#include <app/timer.hpp>
#include <catch2/catch_all.hpp>
#include <iostream>
#include <sstream>
#include <streambuf>

// A utility to capture stdout
class CoutRedirect {
  public:
    CoutRedirect(std::streambuf* new_buffer) : old(std::cout.rdbuf(new_buffer)) {}
    ~CoutRedirect() { std::cout.rdbuf(old); }

  private:
    std::streambuf* old;
};

TEST_CASE("Countdown Timer - Quiet Mode", "[timer]") {
    std::stringstream buffer;
    CoutRedirect redirect(buffer.rdbuf());

    app::eggtimer::countdown(1, true);

    std::string output = buffer.str();
    REQUIRE(output.find("Time remaining:") == std::string::npos);
    REQUIRE(output.find("Starting egg timer for") == std::string::npos);
}

TEST_CASE("Countdown Timer - Verbose Mode", "[timer]") {
    std::stringstream buffer;
    CoutRedirect redirect(buffer.rdbuf());

    app::eggtimer::countdown(1, false);

    std::string output = buffer.str();
    REQUIRE(output.find("Starting egg timer for") != std::string::npos);
    REQUIRE(output.find(".") != std::string::npos);
    REQUIRE(output.find("Time's up!") != std::string::npos);
}

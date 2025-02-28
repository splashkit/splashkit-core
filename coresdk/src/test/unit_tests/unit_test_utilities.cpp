#include "catch.hpp"

#include "utils.h"
#include "basics.h"
#include "random.h"
#include <chrono>

using namespace splashkit_lib;

TEST_CASE("substring contained within string is detected", "[contains]")
{
    SECTION("substring is at the start of the string")
    {
        REQUIRE(contains("splashkit library", "splashkit"));
    }
    SECTION("substring is at the end of the string")
    {
        REQUIRE(contains("splashkit library", "library"));
    }
    SECTION("substring is in the middle of the string")
    {
        REQUIRE(contains("splashkit library", "it lib"));
    }
    SECTION("substring is empty")
    {
        REQUIRE(contains("splashkit library", ""));
    }
    SECTION("substring is the same as the string")
    {
        REQUIRE(contains("splashkit library", "splashkit library"));
    }
    SECTION("both string and substring are empty")
    {
        REQUIRE(contains("", ""));
    }
    SECTION("substring is not in the string")
    {
        REQUIRE_FALSE(contains("splashkit library", "unreal"));
    }
    SECTION("substring is larger than the string")
    {
        REQUIRE_FALSE(contains("splashkit library", "splashkit library is the best"));
    }
    SECTION("string is empty")
    {
        REQUIRE_FALSE(contains("", "splashkit"));
    }
}
TEST_CASE("string is converted to double", "[covert_to_double]")
{
    SECTION("string is an integer")
    {
        REQUIRE(convert_to_double("123") == 123.0);
    }
    SECTION("string is a decimal number")
    {
        REQUIRE(convert_to_double("123.456") == 123.456);
    }
    SECTION("string is a negative integer")
    {
        REQUIRE(convert_to_double("-123") == -123.0);
    }
    SECTION("string is a negative decimal number")
    {
        REQUIRE(convert_to_double("-123.456") == -123.456);
    }
    SECTION("string is a decimal number with no integer part")
    {
        REQUIRE(convert_to_double(".456") == 0.456);
    }
    SECTION("string is a decimal number with no decimal part")
    {
        REQUIRE(convert_to_double("123.") == 123.0);
    }
    SECTION ("string is a decimal number with multiple zeroes before the decimal point")
    {
        REQUIRE(convert_to_double("000123.456") == 123.456);
    }
    SECTION ("string is a decimal number with multiple zeroes after the decimal point")
    {
        REQUIRE(convert_to_double("123.456000") == 123.456);
    }
    SECTION("string is a decimal number with multiple zeroes before and after the decimal point")
    {
        REQUIRE(convert_to_double("000123.456000") == 123.456);
    }
    SECTION("string is a decimal number with multiple zeroes before the decimal point and no decimal part")
    {
        REQUIRE(convert_to_double("000123.") == 123.0);
    }
    SECTION("string is a decimal number with no integer part and multiple zeroes after the decimal point")
    {
        REQUIRE(convert_to_double(".456000") == 0.456);
    }
    SECTION("string has leading whitespace")
    {
        REQUIRE(convert_to_double(" 123") == 123.0);
    }
    SECTION("string has trailing whitespace")
    {
        REQUIRE(convert_to_double("123 ") == 123.0);
    }
    SECTION("string has leading and trailing whitespace")
    {
        REQUIRE(convert_to_double(" 123 ") == 123.0);
    }
    SECTION("string is a negative decimal number with leading whitespace")
    {
        REQUIRE(convert_to_double(" -123.456") == -123.456);
    }
    SECTION("string is a negative decimal number with trailing whitespace")
    {
        REQUIRE(convert_to_double("-123.456 ") == -123.456);
    }
    SECTION("string is a negative decimal number with leading and trailing whitespace")
    {
        REQUIRE(convert_to_double(" -123.456 ") == -123.456);
    }
    SECTION("string has multiple decimal points")
    {
        REQUIRE(convert_to_double("123.456.789") == 123.456);
    }
    SECTION("string is infinite")
    {
        REQUIRE(convert_to_double("inf") == INFINITY);
    }
    SECTION("string is negative infinite")
    {
        REQUIRE(convert_to_double("-inf") == -INFINITY);
    }
    SECTION("string is scientific notation")
    {
        REQUIRE(convert_to_double("1.23e2") == 123.0);
    }
    SECTION("string is negative scientific notation")
    {
        REQUIRE(convert_to_double("-1.23e2") == -123.0);
    }
    SECTION("string is a decimal number with no integer or decimal part")
    {
        REQUIRE_THROWS(convert_to_double("."));
    }
    SECTION("string is not a number")
    {
        REQUIRE_THROWS(convert_to_double("SplashKit"));
    }
    SECTION("string is empty")
    {
        REQUIRE_THROWS(convert_to_double(""));
    }
}
TEST_CASE("string is converted to integer", "[covert_to_integer]")
{
    SECTION("string is an integer")
    {
        REQUIRE(convert_to_integer("123") == 123);
    }
    SECTION("string is a decimal number")
    {
        REQUIRE(convert_to_integer("123.456") == 123);
    }
    SECTION("string is a negative integer")
    {
        REQUIRE(convert_to_integer("-123") == -123);
    }
    SECTION("string is a negative decimal number")
    {
        REQUIRE(convert_to_integer("-123.456") == -123);
    }
    SECTION("string is a decimal number with no decimal part")
    {
        REQUIRE(convert_to_integer("123.") == 123);
    }
    SECTION ("string is a decimal number with multiple zeroes before the decimal point")
    {
        REQUIRE(convert_to_integer("000123.456") == 123);
    }
    SECTION ("string is a decimal number with multiple zeroes after the decimal point")
    {
        REQUIRE(convert_to_integer("123.456000") == 123);
    }
    SECTION("string is a decimal number with multiple zeroes before and after the decimal point")
    {
        REQUIRE(convert_to_integer("000123.456000") == 123);
    }
    SECTION("string is a decimal number with multiple zeroes before the decimal point and no decimal part")
    {
        REQUIRE(convert_to_integer("000123.") == 123);
    }
    SECTION("string has leading whitespace")
    {
        REQUIRE(convert_to_integer(" 123") == 123);
    }
    SECTION("string has trailing whitespace")
    {
        REQUIRE(convert_to_integer("123 ") == 123);
    }
    SECTION("string has leading and trailing whitespace")
    {
        REQUIRE(convert_to_integer(" 123 ") == 123);
    }
    SECTION("string is a negative decimal number with leading whitespace")
    {
        REQUIRE(convert_to_integer(" -123.456") == -123);
    }
    SECTION("string is a negative decimal number with trailing whitespace")
    {
        REQUIRE(convert_to_integer("-123.456 ") == -123);
    }
    SECTION("string is a negative decimal number with leading and trailing whitespace")
    {
        REQUIRE(convert_to_integer(" -123.456 ") == -123);
    }
    SECTION("string has multiple decimal points")
    {
        REQUIRE(convert_to_integer("123.456.789") == 123);
    }
    SECTION("string is a decimal number with no integer part and multiple zeroes after the decimal point")
    {
        REQUIRE_THROWS(convert_to_integer(".456000"));
    }
    SECTION("string is a decimal number with no integer part")
    {
        REQUIRE_THROWS(convert_to_integer(".456"));
    }
    SECTION("string is a decimal number with no integer or decimal part")
    {
        REQUIRE_THROWS(convert_to_integer("."));
    }
    SECTION("string is not a number")
    {
        REQUIRE_THROWS(convert_to_integer("SplashKit"));
    }
    SECTION("string is empty")
    {
        REQUIRE_THROWS(convert_to_integer(""));
    }
}
TEST_CASE("substring's index is found in the string", "[index_of]")
{
    SECTION("substring is at the start of the string")
    {
        REQUIRE(index_of("splashkit library", "splashkit") == 0);
    }
    SECTION("substring is at the end of the string")
    {
        REQUIRE(index_of("splashkit library", "library") == 10);
    }
    SECTION("substring is in the middle of the string")
    {
        REQUIRE(index_of("splashkit library", "it lib") == 7);
    }
    SECTION("substring is not in the string")
    {
        REQUIRE(index_of("splashkit library", "unreal") == -1);
    }
    SECTION("substring is the same as the string")
    {
        REQUIRE(index_of("splashkit library", "splashkit library") == 0);
    }
    SECTION("substring is larger than the string")
    {
        REQUIRE(index_of("splashkit library", "splashkit library is the best") == -1);
    }
    SECTION("substring is empty")
    {
        REQUIRE(index_of("splashkit library", "") == 0);
    }
    SECTION("string is empty")
    {
        REQUIRE(index_of("", "splashkit") == -1);
    }
    SECTION("both string and substring are empty")
    {
        REQUIRE(index_of("", "") == 0);
    }
}
TEST_CASE("verify that string is double", "[is_double]")
{
    SECTION("string is a decimal number")
    {
        REQUIRE(is_double("123.456"));
    }
    SECTION("string is an integer")
    {
        REQUIRE(is_double("123"));
    }
    SECTION("string is a negative decimal number")
    {
        REQUIRE(is_double("-123.456"));
    }
    SECTION("string is a negative integer")
    {
        REQUIRE(is_double("-123"));
    }
    SECTION("string is a decimal number with no decimal part")
    {
        REQUIRE(is_double("123."));
    }
    SECTION("string is a decimal number with multiple zeroes before the decimal point")
    {
        REQUIRE(is_double("000123.456"));
    }
    SECTION("string is a decimal number with multiple zeroes after the decimal point")
    {
        REQUIRE(is_double("123.456000"));
    }
    SECTION("string is a decimal number with multiple zeroes before and after the decimal point")
    {
        REQUIRE(is_double("000123.456000"));
    }
    SECTION("string is a decimal number with multiple zeroes before the decimal point and no decimal part")
    {
        REQUIRE(is_double("000123."));
    }
    SECTION("string is a decimal number with no integer part")
    {
        REQUIRE_FALSE(is_double(".456"));
    }
    SECTION("string is a decimal number with no integer or decimal part")
    {
        REQUIRE_FALSE(is_double("."));
    }
    SECTION("string is not a number")
    {
        REQUIRE_FALSE(is_double("SplashKit"));
    }
    SECTION("string is empty")
    {
        REQUIRE_FALSE(is_double(""));
    }
}
TEST_CASE("verify that string is integer", "[is_integer]")
{
    SECTION("string is an integer")
    {
        REQUIRE(is_integer("123"));
    }
    SECTION("string is a negative integer")
    {
        REQUIRE(is_integer("-123"));
    }
    SECTION("string is a decimal number")
    {
        REQUIRE_FALSE(is_integer("123.456"));
    }
    SECTION("string is a negative decimal number")
    {
        REQUIRE_FALSE(is_integer("-123.456"));
    }
    SECTION("string is a decimal number with no decimal part")
    {
        REQUIRE_FALSE(is_integer("123."));
    }
    SECTION("string is a decimal number with multiple zeroes before the decimal point")
    {
        REQUIRE_FALSE(is_integer("000123.456"));
    }
    SECTION("string is a decimal number with multiple zeroes after the decimal point")
    {
        REQUIRE_FALSE(is_integer("123.456000"));
    }
    SECTION("string is a decimal number with multiple zeroes before and after the decimal point")
    {
        REQUIRE_FALSE(is_integer("000123.456000"));
    }
    SECTION("string is a double with multiple zeroes before the decimal point and no decimal part")
    {
        REQUIRE_FALSE(is_integer("000123."));
    }
    SECTION("string is a double with no integer part and multiple zeroes after the decimal point")
    {
        REQUIRE_FALSE(is_integer(".456000"));
    }
    SECTION("string is a double with no integer part")
    {
        REQUIRE_FALSE(is_integer(".456"));
    }
    SECTION("string is a double with no integer or decimal part")
    {
        REQUIRE_FALSE(is_integer("."));
    }
    SECTION("string is not a number")
    {
        REQUIRE_FALSE(is_integer("SplashKit"));
    }
    SECTION("string is empty")
    {
        REQUIRE_FALSE(is_integer(""));
    }
}
TEST_CASE("verify that string is number", "[is_number]")
{
    SECTION("string is a double")
    {
        REQUIRE(is_number("123.456"));
    }
    SECTION("string is an integer")
    {
        REQUIRE(is_number("123"));
    }
    SECTION("string is a negative double")
    {
        REQUIRE(is_number("-123.456"));
    }
    SECTION("string is a negative integer")
    {
        REQUIRE(is_number("-123"));
    }
    SECTION("string is a double with no integer part")
    {
        REQUIRE_FALSE(is_number(".456"));
    }
    SECTION("string is a double with no decimal part")
    {
        REQUIRE(is_number("123."));
    }
    SECTION("string is a double with multiple zeroes before the decimal point")
    {
        REQUIRE(is_number("000123.456"));
    }
    SECTION("string is a double with multiple zeroes after the decimal point")
    {
        REQUIRE(is_number("123.456000"));
    }
    SECTION("string is a double with multiple zeroes before and after the decimal point")
    {
        REQUIRE(is_number("000123.456000"));
    }
    SECTION("string is a double with multiple zeroes before the decimal point and no decimal part")
    {
        REQUIRE(is_number("000123."));
    }
    SECTION("string is a double with no integer part and multiple zeroes after the decimal point")
    {
        REQUIRE_FALSE(is_number(".456000"));
    }
    SECTION("string is a double with no integer part")
    {
        REQUIRE_FALSE(is_number(".456"));
    }
    SECTION("string is a double with no integer or decimal part")
    {
        REQUIRE_FALSE(is_number("."));
    }
    SECTION("string is not a number")
    {
        REQUIRE_FALSE(is_number("SplashKit"));
    }
    SECTION("string is empty")
    {
        REQUIRE_FALSE(is_number(""));
    }
}
TEST_CASE("length of string is calculated", "[length_of]")
{
    SECTION("string is not empty")
    {
        REQUIRE(length_of("splashkit") == 9);
    }
    SECTION("string is empty")
    {
        REQUIRE(length_of("") == 0);
    }
}
TEST_CASE("replace all occurrences of a substring in a string with another string", "[replace_all]")
{
    SECTION("substring is at the start of the string")
    {
        REQUIRE(replace_all("splashkit library", "splashkit", "SK") == "SK library");
    }
    SECTION("substring is at the end of the string")
    {
        REQUIRE(replace_all("splashkit library", "library", "lib") == "splashkit lib");
    }
    SECTION("substring is in the middle of the string")
    {
        REQUIRE(replace_all("splashkit library", "it lib", "itlib") == "splashkitlibrary");
    }
    SECTION("substring is not in the string")
    {
        REQUIRE(replace_all("splashkit library", "unreal", "tournament") == "splashkit library");
    }
    SECTION("substring is the same as the string")
    {
        REQUIRE(replace_all("splashkit library", "splashkit library", "SK") == "SK");
    }
    SECTION("substring is larger than the string")
    {
        REQUIRE(replace_all("splashkit library", "splashkit library is the best", "SK") == "splashkit library");
    }
    SECTION("string is empty")
    {
        REQUIRE(replace_all("", "splashkit", "SK") == "");
    }
    SECTION("replacement is empty")
    {
        REQUIRE(replace_all("splashkit library", "splashkit", "") == " library");
    }
    SECTION("substring is empty")
    {
        REQUIRE(replace_all("splashkit library", "", "SK") == "splashkit library");
    }
    SECTION("both string and substring are empty")
    {
        REQUIRE(replace_all("", "", "SK") == "");
    }
}
TEST_CASE("can split a string into an array of strings based on a delimiter")
{
    SECTION("string is not empty")
    {
        vector<string> result = split("splashkit library", ' ');
        vector<string> expected = { "splashkit", "library" };
        REQUIRE(result == expected);
    }
    SECTION("string is empty")
    {
        vector<string> result = split("", ' ');
        vector<string> expected = { "" };
        REQUIRE(result == expected);
    }
    SECTION("delimiter is not in the string")
    {
        vector<string> result = split("splashkit library", ',');
        vector<string> expected = { "splashkit library" };
        REQUIRE(result == expected);
    }
    SECTION("delimiter is at the start of the string")
    {
        vector<string> result = split(",splashkit library", ',');
        vector<string> expected = { "", "splashkit library" };
        REQUIRE(result == expected);
    }
    SECTION("delimiter is at the end of the string")
    {
        vector<string> result = split("splashkit library,", ',');
        vector<string> expected = { "splashkit library", "" };
        REQUIRE(result == expected);
    }
    SECTION("delimiter is at the start and end of the string")
    {
        vector<string> result = split(",splashkit library,", ',');
        vector<string> expected = { "", "splashkit library", "" };
        REQUIRE(result == expected);
    }
    SECTION("delimiter is repeated")
    {
        vector<string> result = split("splashkit,,library", ',');
        vector<string> expected = { "splashkit", "", "library" };
        REQUIRE(result == expected);
    }
    SECTION("delimiter is a space")
    {
        vector<string> result = split("splashkit library", ' ');
        vector<string> expected = { "splashkit", "library" };
        REQUIRE(result == expected);
    }
    SECTION("delimiter is a tab")
    {
        vector<string> result = split("splashkit\tlibrary", '\t');
        vector<string> expected = { "splashkit", "library" };
        REQUIRE(result == expected);
    }
    SECTION("delimiter is a newline")
    {
        vector<string> result = split("splashkit\nlibrary", '\n');
        vector<string> expected = { "splashkit", "library" };
        REQUIRE(result == expected);
    }
    SECTION("delimiter is a carriage return")
    {
        vector<string> result = split("splashkit\rlibrary", '\r');
        vector<string> expected = { "splashkit", "library" };
        REQUIRE(result == expected);
    }
    SECTION("delimiter is a space, newline, and carriage return")
    {
        vector<string> result = split("splashkit \n\rlibrary", ' ');
        vector<string> expected = { "splashkit", "\n\rlibrary" };
        REQUIRE(result == expected);
    }
}
TEST_CASE("string is converted to lowercase", "[to_lowercase]")
{
    SECTION("string is not empty")
    {
        REQUIRE(to_lowercase("SPLASHKIT") == "splashkit");
    }
    SECTION("string is empty")
    {
        REQUIRE(to_lowercase("") == "");
    }
    SECTION("string is already lowercase")
    {
        REQUIRE(to_lowercase("splashkit") == "splashkit");
    }
    SECTION("string is mixed case")
    {
        REQUIRE(to_lowercase("SpLaShKiT") == "splashkit");
    }
}
TEST_CASE("string is converted to uppercase", "[to_uppercase]")
{
    SECTION("string is not empty")
    {
        REQUIRE(to_uppercase("splashkit") == "SPLASHKIT");
    }
    SECTION("string is empty")
    {
        REQUIRE(to_uppercase("") == "");
    }
    SECTION("string is already uppercase")
    {
        REQUIRE(to_uppercase("SPLASHKIT") == "SPLASHKIT");
    }
    SECTION("string is mixed case")
    {
        REQUIRE(to_uppercase("SpLaShKiT") == "SPLASHKIT");
    }
}
TEST_CASE("string is trimmed", "[trim]")
{
    SECTION("string is empty")
    {
        REQUIRE(trim("") == "");
    }
    SECTION("string has leading whitespace")
    {
        REQUIRE(trim("  splashkit") == "splashkit");
    }
    SECTION("string has trailing whitespace")
    {
        REQUIRE(trim("splashkit  ") == "splashkit");
    }
    SECTION("string has leading and trailing whitespace")
    {
        REQUIRE(trim("  splashkit  ") == "splashkit");
    }
    SECTION("string has no leading or trailing whitespace")
    {
        REQUIRE(trim("splashkit") == "splashkit");
    }
}
TEST_CASE("random number float between 0 and 1 is generated", "[rnd]")
{
    float result = rnd();
    REQUIRE(result >= 0);
    REQUIRE(result <= 1);
}
TEST_CASE("random number int between 0 and ubound is generated", "[rnd(int ubound)]")
{
    SECTION("ubound is 1")
    {
        int result = rnd(1);
        REQUIRE(result >= 0);
        REQUIRE(result <= 1);
    }
    SECTION("ubound is 10")
    {
        int result = rnd(10);
        REQUIRE(result >= 0);
        REQUIRE(result <= 10);
    }
    SECTION("ubound is -1")
    {
        int result = rnd(-1);
        REQUIRE(result == 0);
    }
    SECTION("ubound is 0")
    {
        int result = rnd(0);
        REQUIRE(result == 0);
    }
}
TEST_CASE("random number int between min and max is generated", "[rnd(int min, int max)]")
{
    SECTION("min is 0 and max is 1")
    {
        int result = rnd(0, 1);
        REQUIRE(result >= 0);
        REQUIRE(result <= 1);
    }
    SECTION("min is 0 and max is 10")
    {
        int result = rnd(0, 10);
        REQUIRE(result >= 0);
        REQUIRE(result <= 10);
    }
    SECTION("min is -1 and max is 1")
    {
        int result = rnd(-1, 1);
        REQUIRE(result >= -1);
        REQUIRE(result <= 1);
    }
    SECTION("min is 1 and max is 0")
    {
        int result = rnd(1, 0);
        REQUIRE(result >= 0);
        REQUIRE(result <= 1);
    }
    SECTION("min is 1 and max is 1")
    {
        int result = rnd(1, 1);
        REQUIRE(result == 1);
    }
}
TEST_CASE("gets the number of milliseconds that have passed since the program was started", "[current_ticks]")
{
    unsigned int result = current_ticks();
    REQUIRE(result >= 0);
}
TEST_CASE("program is put to sleep for a specified number of milliseconds", "[delay]")
{
    constexpr long long DELAY_THRESHOLD = 80;
    
    SECTION("milliseconds is 0")
    {
        auto start = std::chrono::steady_clock::now();
        delay(0);
        auto end = std::chrono::steady_clock::now();
        REQUIRE(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() < DELAY_THRESHOLD);
    }
    SECTION("milliseconds is 200")
    {
        constexpr int DELAY = 200;
        auto start = std::chrono::steady_clock::now();
        delay(DELAY);
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        REQUIRE(duration >= (DELAY - DELAY_THRESHOLD));
        #if defined(__APPLE__) || defined(__MACH__)
            // found to be unreliable during macOS CI tests, so for now we don't enforce it
            // perhaps it can be made more reliable later
            CHECK_NOFAIL(duration <= (DELAY + DELAY_THRESHOLD));
            INFO("[SKIPPING TEST] Delay known to take longer than needed during macOS CI");
        #else
            REQUIRE(duration <= (DELAY + DELAY_THRESHOLD));
        #endif
    }
}
TEST_CASE("return a SplashKit resource of resource_kind with name filename as a string", "[file_as_string]")
{
    const resource_kind RESOURCE = resource_kind::BUNDLE_RESOURCE;
    const string RESOURCE_PATH = "blah.txt";
    
    SECTION("filename is a valid file")
    {
        string result = file_as_string(RESOURCE_PATH, RESOURCE);
        string expected = "BITMAP,ufo,ufo.png\n";
        REQUIRE(result == expected);
    }
    SECTION("filename is an empty string")
    {
        string result = file_as_string("", RESOURCE);
        string expected = "";
        REQUIRE(result == expected);
    }
    SECTION("filename is an invalid file")
    {
        string result = file_as_string("invalid.txt", RESOURCE);
        string expected = "";
        REQUIRE(result == expected);
    }
}
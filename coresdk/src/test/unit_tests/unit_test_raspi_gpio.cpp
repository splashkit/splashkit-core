/**
 * Raspi GPIO Unit Tests
 */

#include "catch.hpp"

#include "types.h"
#include "raspi_gpio.h"

using namespace splashkit_lib;

TEST_CASE("can convert from gpio_pin_value to integer", "[to_int][gpio_pin_value]")
{
    gpio_pin_value pin_value;

    SECTION("GPIO_HIGH is 1")
    {
        pin_value = GPIO_HIGH;
        REQUIRE(to_int(pin_value) == 1);
    }
    SECTION("GPIO_LOW is 0")
    {
        pin_value = GPIO_LOW;
        REQUIRE(to_int(pin_value) == 0);
    }
    SECTION("GPIO_DEFAULT_VALUE is -1")
    {
        pin_value = GPIO_DEFAULT_VALUE;
        REQUIRE(to_int(pin_value) == -1);
    }
}

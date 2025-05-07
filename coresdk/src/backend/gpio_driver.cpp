// gpio_driver.cpp
// This file is part of the SplashKit Core Library.
// Copyright (©) 2024 Aditya Parmar. All Rights Reserved.

#include "network_driver.h"
#include "gpio_driver.h"
#include "easylogging++.h"

#include <string>
#include <iostream>
#include <cstdlib> // Add this line to include the necessary header for the exit() function

#include <cstring>
#ifdef RASPBERRY_PI
#include "pigpiod_if2.h"
#endif


using namespace std;
// Use https://abyz.me.uk/rpi/pigpio/pdif2.html for local command reference
//   Archive Link: https://web.archive.org/web/20240423160241/https://abyz.me.uk/rpi/pigpio/pdif2.html
//
// Use https://abyz.me.uk/rpi/pigpio/sif.html for remote command reference
//   Archive Link: https://web.archive.org/web/20240423160319/https://abyz.me.uk/rpi/pigpio/sif.html
namespace splashkit_lib
{
    #ifdef RASPBERRY_PI
    int pi = -1;

    // Check if pigpio_init() has been called before any other GPIO functions
    bool check_pi()
    {
        if (pi < 0)
        {
            LOG(ERROR) << sk_gpio_error_message(pi);
            return false;
        }
        else return true;
    }

    // Initialize the GPIO library
    int sk_gpio_init()
    {
        pi = pigpio_start(0, 0);
        return pi;
    }

    // Read the value of a GPIO pin
    int sk_gpio_read(int pin)
    {
        if (check_pi())
        {
            int result = gpio_read(pi, pin);
            if (result < 0)
            {
                LOG(ERROR) << sk_gpio_error_message(result);
            }
            return result;
        }
        else
        {
            return GPIO_DEFAULT_VALUE;
        }
    }

    // Write a value to a GPIO pin
    void sk_gpio_write(int pin, int value)
    {
        if (check_pi())
        {
            int result = gpio_write(pi, pin, value);
            if(result < 0)
            {
                LOG(ERROR) << sk_gpio_error_message(result);
            }
        }
    }

    // Set the mode of a GPIO pin
    void sk_gpio_set_mode(int pin, int mode)
    {
        if(check_pi())
        {
            int result = set_mode(pi, pin, mode);
            if(result < 0)
            {
                LOG(ERROR) << sk_gpio_error_message(result);
            }
        }
    }

    int sk_gpio_get_mode(int pin)
    {
        if(check_pi())
        {
            int result = get_mode(pi, pin);
            if(result < 0)
            {
                LOG(ERROR) << sk_gpio_error_message(result);
            }
            return result;
        }
        else
        {
            return PI_BAD_GPIO; 
        }
    }
    void sk_gpio_set_pull_up_down(int pin, int pud)
    {
        if(check_pi())
        {
            int result = set_pull_up_down(pi, pin, pud);
            if(result < 0)
            {
                LOG(ERROR) << sk_gpio_error_message(result);
            }
        }
    }

    // PWM Functions
    void sk_set_pwm_range(int pin, int range)
    {
        if(check_pi())
        {
            int result = set_PWM_range(pi, pin, range);
            if(result < 0)
            {
                LOG(ERROR) << sk_gpio_error_message(result);
            }
        }
    }
    void sk_set_pwm_frequency(int pin, int frequency)
    {
        if(check_pi())
        {
            int result = set_PWM_frequency(pi, pin, frequency);
            if(result < 0)
            {
                LOG(ERROR) << sk_gpio_error_message(result);
            }
        }
    }

    void sk_set_pwm_dutycycle(int pin, int dutycycle)
    {
        if(check_pi())
        {
            int result = set_PWM_dutycycle(pi, pin, dutycycle);
            if(result < 0)
            {
                LOG(ERROR) << sk_gpio_error_message(result);
            }
        }
    }

    void sk_gpio_clear_bank_1()
    {
        if(check_pi())
        {
            clear_bank_1(pi, PI4B_GPIO_BITMASK);
        }
    }

    // I2C Functions
    int sk_i2c_open(int bus, int address, int flags)
    {
        if (check_pi())
        {
            int result = ::i2c_open(pi, bus, address, flags);
            if (result < 0)
            {
                LOG(ERROR) << sk_gpio_error_message(result);
            }
            return result;
        }
        else
        {
            return -1;
        }
    }
    void sk_i2c_close(int handle)
    {
        if (check_pi())
        {
            int result = ::i2c_close(pi, handle);
            if (result < 0)
            {
                LOG(ERROR) << sk_gpio_error_message(result);
            }
        }
    }
    int sk_i2c_read_byte(int handle)
    {
        if (check_pi())
        {
            int result = ::i2c_read_byte(pi, handle);
            if (result < 0)
            {
                LOG(ERROR) << sk_gpio_error_message(result);
            }
            return result;
        }
        else
        {
            return -1;
        }
    }
    int sk_i2c_write_byte(int handle, int data)
    {
        if (check_pi())
        {
            int result = ::i2c_write_byte(pi, handle, data);
            if (result < 0)
            {
                LOG(ERROR) << sk_gpio_error_message(result);
            }
            return result;
        }
        else
        {
            return -1;
        }
    }
    int sk_i2c_read_device(int handle, char *buf, int count)
    {
        if (check_pi())
        {
            int result = ::i2c_read_device(pi, handle, buf, count);
            if (result < 0)
            {
                LOG(ERROR) << sk_gpio_error_message(result);
            }
            return result;
        }
        else
        {
            return -1;
        }
    }
    void sk_i2c_write_device(int handle, char *buf, int count)
    {
        if (check_pi())
        {
            int result = ::i2c_write_device(pi, handle, buf, count);
            if (result < 0)
            {
                LOG(ERROR) << sk_gpio_error_message(result);
            }
        }
    }

    // Additional I2C Functions (new)
    int sk_i2c_read_byte_data(int handle, int reg)
    {
        if (check_pi())
        {
            int result = ::i2c_read_byte_data(pi, handle, reg);
            if (result < 0)
            {
                LOG(ERROR) << sk_gpio_error_message(result);
            }
            return result;
        }
        else
        {
            return -1;
        }
    }

    void sk_i2c_write_byte_data(int handle, int reg, int data)
    {
        if (check_pi())
        {
            int result = ::i2c_write_byte_data(pi, handle, reg, data);
            if (result < 0)
            {
                LOG(ERROR) << sk_gpio_error_message(result);
            }
        }
    }

    int sk_i2c_read_word_data(int handle, int reg)
    {
        if (check_pi())
        {
            int result = ::i2c_read_word_data(pi, handle, reg);
            if (result < 0)
            {
                LOG(ERROR) << sk_gpio_error_message(result);
            }
            return result;
        }
        else
        {
            return -1;
        }
    }

    void sk_i2c_write_word_data(int handle, int reg, int data)
    {
        if (check_pi())
        {
            int result = ::i2c_write_word_data(pi, handle, reg, data);
            if (result < 0)
            {
                LOG(ERROR) << sk_gpio_error_message(result);
            }
        }
    }

    // Cleanup the GPIO library
    void sk_gpio_cleanup()
    {
        if(check_pi())
        {
            pigpio_stop(pi);
        }
    }
    
    int sk_spi_open(int channel, int speed, int spi_flags)
    {
        if(check_pi())
            return spi_open(pi, channel, speed, spi_flags);
        else
            return -1;
    }

    int sk_spi_close(int handle)
    {
        if(check_pi())
            return spi_close(pi, handle);
        else
            return -1;
    }

    int sk_spi_transfer(int handle, char *send_buf, char *recv_buf, int count)
    {
        if(check_pi())
            return spi_xfer(pi, handle, send_buf, recv_buf, count);
        else
            return -1;
    }	

    #endif

    // Remote GPIO Functions
    connection sk_remote_gpio_init(std::string name, const std::string &host, unsigned short int port)
    {
        return open_connection(name, host, port);
    }

    void sk_remote_gpio_set_mode(connection pi, int pin, int mode)
    {
        sk_pigpio_cmd_t set_cmd;
        set_cmd.cmd_code = GPIO_CMD_SET_MODE;
        set_cmd.param1 = pin;
        set_cmd.param2 = mode;

        sk_gpio_send_cmd(pi, set_cmd);
    }

    int sk_remote_gpio_get_mode(connection pi, int pin)
    {
        sk_pigpio_cmd_t get_cmd;
        get_cmd.cmd_code = GPIO_CMD_GET_MODE;
        get_cmd.param1 = pin;

        return sk_gpio_send_cmd(pi, get_cmd);
    }

    void sk_remote_gpio_set_pull_up_down(connection pi, int pin, int pud)
    {
        sk_pigpio_cmd_t set_pud_cmd;
        set_pud_cmd.cmd_code = GPIO_CMD_SET_PUD;
        set_pud_cmd.param1 = pin;
        set_pud_cmd.param2 = pud;

        sk_gpio_send_cmd(pi, set_pud_cmd);
    }

    int sk_remote_gpio_read(connection pi, int pin)
    {
        sk_pigpio_cmd_t read_cmd;
        read_cmd.cmd_code = GPIO_CMD_READ;
        read_cmd.param1 = pin;

        return sk_gpio_send_cmd(pi, read_cmd);
    }

    void sk_remote_gpio_write(connection pi, int pin, int value)
    {
        sk_pigpio_cmd_t write_cmd;
        write_cmd.cmd_code = GPIO_CMD_WRITE;
        write_cmd.param1 = pin;
        write_cmd.param2 = value;

        sk_gpio_send_cmd(pi, write_cmd);
    }

    void sk_remote_set_pwm_range(connection pi, int pin, int range)
    {
        sk_pigpio_cmd_t set_range_cmd;
        set_range_cmd.cmd_code = GPIO_CMD_SET_PWM_RANGE;
        set_range_cmd.param1 = pin;
        set_range_cmd.param2 = range;

        sk_gpio_send_cmd(pi, set_range_cmd);
    }

    void sk_remote_set_pwm_frequency(connection pi, int pin, int frequency)
    {
        sk_pigpio_cmd_t set_freq_cmd;
        set_freq_cmd.cmd_code = GPIO_CMD_SET_PWM_FREQ;
        set_freq_cmd.param1 = pin;
        set_freq_cmd.param2 = frequency;

        sk_gpio_send_cmd(pi, set_freq_cmd);
    }

    void sk_remote_set_pwm_dutycycle(connection pi, int pin, int dutycycle)
    {
        sk_pigpio_cmd_t set_dutycycle_cmd;
        set_dutycycle_cmd.cmd_code = GPIO_CMD_SET_PWM_DUTYCYCLE;
        set_dutycycle_cmd.param1 = pin;
        set_dutycycle_cmd.param2 = dutycycle;

        sk_gpio_send_cmd(pi, set_dutycycle_cmd);
    }

    void sk_remote_clear_bank_1(connection pi)
    {
        sk_pigpio_cmd_t clear_bank_cmd;
        clear_bank_cmd.cmd_code = GPIO_CMD_CLEAR_BANK_1;
        clear_bank_cmd.param1 = PI4B_GPIO_BITMASK;

        sk_gpio_send_cmd(pi, clear_bank_cmd);
    }

    bool sk_remote_gpio_cleanup(connection pi)
    {
        if(!is_connection_open(pi))
        {
            LOG(ERROR) << "Remote GPIO: Connection not open.";
            return false;
        }
        LOG(INFO) << "Cleaning Pins on Remote Pi Named: " << pi->name << endl;
        sk_remote_clear_bank_1(pi);
        return close_connection(pi);
    }

    int sk_gpio_send_cmd(connection pi, sk_pigpio_cmd_t &cmd)
    {
        if(!is_connection_open(pi))
        {
            LOG(ERROR) << sk_gpio_error_message(PI_PIGIF_BAD_CONNECT); 
            return PI_PIGIF_BAD_CONNECT;
        }

        if(pi->protocol == TCP)
        {
            int num_send_bytes = sizeof(cmd);

            std::vector<char> buffer(num_send_bytes);
            memcpy(buffer.data(), &cmd, num_send_bytes);

            if(sk_send_bytes(&pi->socket, buffer.data(), num_send_bytes)) 
            {
                int num_bytes_recv = sk_read_bytes(&pi->socket, buffer.data(), num_send_bytes); 
                if(num_bytes_recv == num_send_bytes) 
                {
                    sk_pigpio_cmd_t resp;
                    memcpy(&resp, buffer.data(), num_send_bytes);
                    
                    // We cast it back to a signed type so we can get the negative error codes.
                    int32_t result = static_cast<int32_t>(resp.result);

                    if (result < 0)
                    {
                        LOG(ERROR) << sk_gpio_error_message(result);
                    }

                    return result;
                }
                else
                {
                    LOG(ERROR) << sk_gpio_error_message(PI_PIGIF_BAD_RECV);
                    return PI_PIGIF_BAD_RECV;
                }
            }
            else
            {
                LOG(ERROR) << sk_gpio_error_message(PI_PIGIF_BAD_SEND);
                return PI_PIGIF_BAD_SEND;
            }
        }
        else
        {
            LOG(ERROR) << "Remote GPIO: Connection has UDP Protocol";
            return -1;
        }
    }
    
   #include <string>
#include <cstdlib>

// The following error code constants should be defined elsewhere in your project.
// For example:
// #define PI_INIT_FAILED       -1
// #define PI_BAD_USER_GPIO     -2
// #define PI_BAD_GPIO          -3
// ... (all the way through the last definitions)
// #define PI_CUSTOM_ERR_999    -3999

std::string sk_gpio_error_message(int error_code)
{
    switch (error_code)
    {
        case PI_INIT_FAILED:
            return "GPIO initialization failed. Please check your setup and try again.";
            
        case PI_BAD_USER_GPIO:
        case PI_BAD_GPIO:
            return "Invalid GPIO pin number.";
            
        case PI_BAD_MODE:
            return "Invalid GPIO mode. Valid modes are 0-7.";
            
        case PI_BAD_LEVEL:
            return "Invalid GPIO level. Valid levels are 0 (LOW) or 1 (HIGH).";
            
        case PI_BAD_PUD:
            return "Invalid pull-up/down mode. Valid options are 0 (off), 1 (pull-down), 2 (pull-up).";
            
        case PI_BAD_PULSEWIDTH:
            return "Invalid pulse width. Must be 0 or between 500 and 2500.";
            
        case PI_BAD_DUTYCYCLE:
            return "Invalid PWM duty cycle. Duty cycle out of range.";
            
        case PI_BAD_TIMER:
            return "Invalid timer. Valid timers are 0-9.";
            
        case PI_BAD_MS:
            return "Invalid milliseconds value. Must be between 10 and 60000.";
            
        case PI_BAD_TIMETYPE:
            return "Invalid timetype. Valid values are 0 or 1.";
            
        case PI_BAD_SECONDS:
            return "Invalid seconds. Must be non-negative.";
            
        case PI_BAD_MICROS:
            return "Invalid microseconds. Must be between 0 and 999999.";
            
        case PI_TIMER_FAILED:
            return "Timer function failed (gpioSetTimerFunc error).";
            
        case PI_BAD_WDOG_TIMEOUT:
            return "Invalid watchdog timeout. Must be between 0 and 60000.";
            
        case PI_NO_ALERT_FUNC:
            return "No alert function defined (deprecated).";
            
        case PI_BAD_CLK_PERIPH:
            return "Invalid clock peripheral. Valid values: 0 or 1.";
            
        case PI_BAD_CLK_SOURCE:
            return "Invalid clock source (deprecated).";
            
        case PI_BAD_CLK_MICROS:
            return "Invalid clock micros. Valid values: 1, 2, 4, 5, 8, or 10.";
            
        case PI_BAD_BUF_MILLIS:
            return "Invalid buffer milliseconds. Must be between 100 and 10000.";
            
        case PI_BAD_DUTYRANGE:
            return "Invalid PWM range. Range must be between 25 and 40000.";
            
        case PI_BAD_SIGNUM:
            return "Invalid signal number. Must be between 0 and 63.";
            
        case PI_BAD_PATHNAME:
            return "Invalid pathname. Unable to open file.";
            
        case PI_NO_HANDLE:
            return "No handle available.";
            
        case PI_BAD_HANDLE:
            return "Invalid or unknown handle.";
            
        case PI_BAD_IF_FLAGS:
            return "Invalid interface flags (value must be 4 or less).";
            
        case PI_BAD_CHANNEL:
            return "Invalid DMA channel. Must be between 0 and 15.";
            
        case PI_BAD_SOCKET_PORT:
            return "Invalid socket port. Valid ports are 1024-32000.";
            
        case PI_BAD_FIFO_COMMAND:
            return "Invalid FIFO command.";
            
        case PI_BAD_SECO_CHANNEL:
            return "Invalid DMA secondary channel. Must be between 0 and 15.";
            
        case PI_NOT_INITIALISED:
            return "GPIO not initialised. Function called before gpioInitialise.";
            
        case PI_INITIALISED:
            return "GPIO already initialised. Function called after gpioInitialise.";
            
        case PI_BAD_WAVE_MODE:
            return "Invalid waveform mode. Valid modes are 0-3.";
            
        case PI_BAD_CFG_INTERNAL:
            return "Invalid parameter in gpioCfgInternals call.";
            
        case PI_BAD_WAVE_BAUD:
            return "Invalid waveform baud rate. RX must be 50-250K; TX must be 50-1M.";
            
        case PI_TOO_MANY_PULSES:
            return "Waveform has too many pulses.";
            
        case PI_TOO_MANY_CHARS:
            return "Waveform has too many characters.";
            
        case PI_NOT_SERIAL_GPIO:
            return "No bit bang serial read supported on this GPIO.";
            
        case PI_BAD_SERIAL_STRUC:
            return "Invalid serial structure (NULL).";
            
        case PI_BAD_SERIAL_BUF:
            return "Invalid serial buffer (NULL).";
            
        case PI_NOT_PERMITTED:
            return "GPIO operation not permitted.";
            
        case PI_SOME_PERMITTED:
            return "One or more GPIO operations not permitted.";
            
        case PI_BAD_WVSC_COMMND:
            return "Invalid WVSC subcommand.";
            
        case PI_BAD_WVSM_COMMND:
            return "Invalid WVSM subcommand.";
            
        case PI_BAD_WVSP_COMMND:
            return "Invalid WVSP subcommand.";
            
        case PI_BAD_PULSELEN:
            return "Invalid trigger pulse length. Must be between 1 and 100.";
            
        case PI_BAD_SCRIPT:
            return "Invalid script.";
            
        case PI_BAD_SCRIPT_ID:
            return "Unknown script ID.";
            
        case PI_BAD_SER_OFFSET:
            return "Invalid serial data offset. Must not exceed 30 minutes.";
            
        case PI_GPIO_IN_USE:
            return "GPIO already in use.";
            
        case PI_BAD_SERIAL_COUNT:
            return "Invalid serial count. Must read at least one byte.";
            
        case PI_BAD_PARAM_NUM:
            return "Invalid script parameter number. Valid IDs: 0-9.";
            
        case PI_DUP_TAG:
            return "Duplicate tag found in script.";
            
        case PI_TOO_MANY_TAGS:
            return "Too many tags in script.";
            
        case PI_BAD_SCRIPT_CMD:
            return "Illegal script command.";
            
        case PI_BAD_VAR_NUM:
            return "Invalid script variable number. Valid range: 0-149.";
            
        case PI_NO_SCRIPT_ROOM:
            return "No room available for additional scripts.";
            
        case PI_NO_MEMORY:
            return "Memory allocation failed.";
            
        case PI_SOCK_READ_FAILED:
            return "Socket read failed.";
            
        case PI_SOCK_WRIT_FAILED:
            return "Socket write failed.";
            
        case PI_TOO_MANY_PARAM:
            return "Too many script parameters (maximum is 10).";
            
        case PI_NOT_HALTED:
            return "Script not ready (still initializing or not halted).";
            
        case PI_BAD_TAG:
            return "Script contains an unresolved tag.";
            
        case PI_BAD_MICS_DELAY:
            return "Invalid microsecond delay (too large).";
            
        case PI_BAD_MILS_DELAY:
            return "Invalid millisecond delay (too large).";
            
        case PI_BAD_WAVE_ID:
            return "Invalid waveform ID (non-existent).";
            
        case PI_TOO_MANY_CBS:
            return "Too many control blocks for waveform.";
            
        case PI_TOO_MANY_OOL:
            return "Too many out-of-limit characters in waveform.";
            
        case PI_EMPTY_WAVEFORM:
            return "Empty waveform: no pulses defined.";
            
        case PI_NO_WAVEFORM_ID:
            return "No waveform IDs available.";
            
        case PI_I2C_OPEN_FAILED:
            return "Failed to open I2C device.";
            
        case PI_SER_OPEN_FAILED:
            return "Failed to open serial device.";
            
        case PI_SPI_OPEN_FAILED:
            return "Failed to open SPI device.";
            
        case PI_BAD_I2C_BUS:
            return "Invalid I2C bus.";
            
        case PI_BAD_I2C_ADDR:
            return "Invalid I2C address.";
            
        case PI_BAD_SPI_CHANNEL:
            return "Invalid SPI channel.";
            
        case PI_BAD_FLAGS:
            return "Invalid flags for open operation (I2C/SPI/serial).";
            
        case PI_BAD_SPI_SPEED:
            return "Invalid SPI speed.";
            
        case PI_BAD_SER_DEVICE:
            return "Invalid serial device name.";
            
        case PI_BAD_SER_SPEED:
            return "Invalid serial baud rate.";
            
        case PI_BAD_PARAM:
            return "Invalid parameter for I2C/SPI/serial operation.";
            
        case PI_I2C_WRITE_FAILED:
            return "I2C write failed.";
            
        case PI_I2C_READ_FAILED:
            return "I2C read failed.";
            
        case PI_BAD_SPI_COUNT:
            return "Invalid SPI transfer count.";
            
        case PI_SER_WRITE_FAILED:
            return "Serial write failed.";
            
        case PI_SER_READ_FAILED:
            return "Serial read failed.";
            
        case PI_SER_READ_NO_DATA:
            return "No data available from serial read.";
            
        case PI_UNKNOWN_COMMAND:
            return "Unknown command.";
            
        case PI_SPI_XFER_FAILED:
            return "SPI transfer failed.";
            
        case PI_BAD_POINTER:
            return "Invalid pointer (NULL).";
            
        case PI_NO_AUX_SPI:
            return "No auxiliary SPI available on this model.";
            
        case PI_NOT_PWM_GPIO:
            return "GPIO not configured for PWM.";
            
        case PI_NOT_SERVO_GPIO:
            return "GPIO not configured for servo pulses.";
            
        case PI_NOT_HCLK_GPIO:
            return "GPIO does not support hardware clock.";
            
        case PI_NOT_HPWM_GPIO:
            return "GPIO does not support hardware PWM.";
            
        case PI_BAD_HPWM_FREQ:
            return "Invalid hardware PWM frequency.";
            
        case PI_BAD_HPWM_DUTY:
            return "Invalid hardware PWM duty cycle. Must be between 0 and 1000000.";
            
        case PI_BAD_HCLK_FREQ:
            return "Invalid hardware clock frequency.";
            
        case PI_BAD_HCLK_PASS:
            return "Password required for hardware clock 1.";
            
        case PI_HPWM_ILLEGAL:
            return "Illegal hardware PWM operation. PWM is used for the main clock.";
            
        case PI_BAD_DATABITS:
            return "Invalid serial data bits. Valid range is 1-32.";
            
        case PI_BAD_STOPBITS:
            return "Invalid serial stop bits. Valid range is 2-8.";
            
        case PI_MSG_TOOBIG:
            return "Socket/pipe message too big.";
            
        case PI_BAD_MALLOC_MODE:
            return "Invalid memory allocation mode.";
            
        case PI_TOO_MANY_SEGS:
            return "Too many I2C transaction segments.";
            
        case PI_BAD_I2C_SEG:
            return "Invalid I2C transaction segment.";
            
        case PI_BAD_SMBUS_CMD:
            return "Unsupported SMBus command.";
            
        case PI_NOT_I2C_GPIO:
            return "No bit bang I2C operation on this GPIO.";
            
        case PI_BAD_I2C_WLEN:
            return "Invalid I2C write length.";
            
        case PI_BAD_I2C_RLEN:
            return "Invalid I2C read length.";
            
        case PI_BAD_I2C_CMD:
            return "Invalid I2C command.";
            
        case PI_BAD_I2C_BAUD:
            return "Invalid I2C baud rate. Must be between 50 and 500k.";
            
        case PI_CHAIN_LOOP_CNT:
            return "Invalid chain loop count.";
            
        case PI_BAD_CHAIN_LOOP:
            return "Empty chain loop.";
            
        case PI_CHAIN_COUNTER:
            return "Too many chain counters.";
            
        case PI_BAD_CHAIN_CMD:
            return "Invalid chain command.";
            
        case PI_BAD_CHAIN_DELAY:
            return "Invalid chain delay (in microseconds).";
            
        case PI_CHAIN_NESTING:
            return "Chain counters nested too deeply.";
            
        case PI_CHAIN_TOO_BIG:
            return "Chain is too long.";
            
        case PI_DEPRECATED:
            return "Deprecated function removed.";
            
        case PI_BAD_SER_INVERT:
            return "Invalid serial invert value. Valid values are 0 or 1.";
            
        case PI_BAD_EDGE:
            return "Invalid ISR edge value. Valid values are between 0 and 2.";
            
        case PI_BAD_ISR_INIT:
            return "ISR initialization failed.";
            
        case PI_BAD_FOREVER:
            return "Invalid use of 'loop forever'. Must be the last command.";
            
        case PI_BAD_FILTER:
            return "Invalid filter parameter.";
            
        case PI_BAD_PAD:
            return "Invalid pad number.";
            
        case PI_BAD_STRENGTH:
            return "Invalid pad drive strength.";
            
        case PI_FIL_OPEN_FAILED:
            return "File open failed.";
            
        case PI_BAD_FILE_MODE:
            return "Invalid file mode.";
            
        case PI_BAD_FILE_FLAG:
            return "Invalid file flag.";
            
        case PI_BAD_FILE_READ:
            return "File read error.";
            
        case PI_BAD_FILE_WRITE:
            return "File write error.";
            
        case PI_FILE_NOT_ROPEN:
            return "File not open for reading.";
            
        case PI_FILE_NOT_WOPEN:
            return "File not open for writing.";
            
        case PI_BAD_FILE_SEEK:
            return "Invalid file seek.";
            
        case PI_NO_FILE_MATCH:
            return "No files match the given pattern.";
            
        case PI_NO_FILE_ACCESS:
            return "Insufficient permission to access file.";
            
        case PI_FILE_IS_A_DIR:
            return "Specified file is a directory.";
            
        case PI_BAD_SHELL_STATUS:
            return "Bad shell status.";
            
        case PI_BAD_SCRIPT_NAME:
            return "Invalid script name.";
            
        case PI_BAD_SPI_BAUD:
            return "Invalid SPI baud rate. Must be between 50 and 500k.";
            
        case PI_NOT_SPI_GPIO:
            return "No SPI bit bang operation in progress on this GPIO.";
            
        case PI_BAD_EVENT_ID:
            return "Invalid event ID.";
            
        case PI_CMD_INTERRUPTED:
            return "Command interrupted (used by Python).";
            
        case PI_NOT_ON_BCM2711:
            return "Operation not available on BCM2711.";
            
        case PI_ONLY_ON_BCM2711:
            return "Operation only available on BCM2711.";
        case PI_PIGIF_BAD_SEND:
            return "Pigpio error: base error code.";
        case PI_PIGIF_BAD_RECV:
            return "Pigpio error: bad receive.";
        case PI_PIGIF_BAD_GETADDRINFO:
            return "Pigpio error: bad getaddrinfo.";
        case PI_PIGIF_BAD_CONNECT:
            return "Pigpio error: bad connect.";
        case PI_PIGIF_BAD_SOCKET:
            return "Pigpio error: bad socket.";
        case PI_PIGIF_BAD_NOIB:
            return "Pigpio error: bad noib.";
        case PI_PIGIF_DUPLICATE_CALLBACK:
            return "Pigpio error: duplicate callback.";
        case PI_PIGIF_BAD_MALLOC:
            return "Pigpio error: bad malloc.";
        case PI_PIGIF_BAD_CALLBACK:
            return "Pigpio error: bad callback.";
        case PI_PIGIF_NOTIFY_FAILED:
            return "Pigpio error: notify failed.";
        case PI_PIGIF_CALLBACK_NOT_FOUND:
            return "Pigpio error: callback not found.";
        case PI_PIGIF_UNCONNECTED_PI:
            return "Pigpio error: unconnected Pi.";
        case PI_PIGIF_TOO_MANY_PIS:
            return "Pigpio error: too many Pis.";

        case PI_PIGIF_ERR_99:
            return "Pigpio error: maximum error code.";
            
        case PI_CUSTOM_ERR_0:
            return "Custom error: base error code.";
            
        case PI_CUSTOM_ERR_999:
            return "Custom error: maximum error code.";
            
        default:
            return "Unknown error code " + std::to_string(error_code);
    }
}

}

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define diode 15
#define speaker 16

int main() {
    stdio_init_all();

    // Init uart
    gpio_init(0);
    gpio_init(1);

    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);

    uart_init(uart0, 9600);

    int period = 500;
    int cycle = 250;

    // pwm A
    gpio_set_function(diode, GPIO_FUNC_PWM);
    uint sliceA = pwm_gpio_to_slice_num(diode);
    uint channelA = pwm_gpio_to_channel(diode);
    pwm_set_enabled(sliceA, true);
    pwm_set_wrap(sliceA, period);

    // pwm B
    gpio_set_function(speaker, GPIO_FUNC_PWM);
    uint sliceB = pwm_gpio_to_slice_num(speaker);
    uint channelB = pwm_gpio_to_channel(speaker);
    pwm_set_enabled(sliceB, true);
    pwm_set_wrap(sliceB, period);

    while(true) {
        pwm_set_chan_level(sliceA, channelA, cycle);
        pwm_set_chan_level(sliceB, channelB, cycle);

        cycle += 10;
        sleep_ms(100);
        
        if (cycle >= 500) {
            cycle = 0;
        }
    }

    return 0;
}

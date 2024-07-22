#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#include "PWM.h"

#define diode 15
#define speaker 16

void read_line_from_uart(uart_inst_t *uart, char *buffer, size_t max_length) {
    size_t index = 0;

    while (index < max_length - 1) {
        char letter;

        uart_read_blocking(uart, (uint8_t*)&letter, 1);
        buffer[index++] = letter;

        if (letter == '\n') {
            break;
        }
    }

    buffer[index] = '\0';
}

int main() {
    stdio_init_all();

    // Init uart
    gpio_init(0);
    gpio_init(1);

    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);

    uart_init(uart0, 9600);

    float voltage = 3.3f;

    PWM_Ports pwm_a = PWM_config(diode);
    PWM_Ports pwm_b = PWM_config(speaker);

    int note = 244;
    const int volume = PWM_calc_volume(50);
    const float tone_duration = 0.2; 
    const float rest_duration = 0.025; 

    char line[256];

    while(true) {
        if(uart_is_readable(uart0)){
            read_line_from_uart(uart0, line, sizeof(line));

            note = atoi(line);
        }

        PWM_play_note(&pwm_b, note, tone_duration, volume);
        PWM_play_break(&pwm_b, rest_duration);        
    }

    return 0;
}

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#include "PWM.h"

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

    float voltage = 3.3f;

    PWM_Ports pwm_a = PWM_config(diode);
    PWM_Ports pwm_b = PWM_config(speaker);

    const int notes[] = {267, 277, 294, 311, 330, 349, 370, 392, 410, 440, 466, 494};
    const int volume = PWM_calc_volume(50);
    const float tone_duration = 0.2; 
    const float rest_duration = 0.025; 

    while(true) {
        for (auto note : notes) {
            PWM_play_note(&pwm_b, note, tone_duration, volume);
            PWM_play_note(&pwm_a, note, tone_duration, volume);
            PWM_play_break(&pwm_b, rest_duration);
            PWM_play_break(&pwm_a, rest_duration);
        }
    }

    return 0;
}

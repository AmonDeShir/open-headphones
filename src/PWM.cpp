#include "PWM.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

PWM_Ports PWM_config(int gpio) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);

    PWM_Ports ports;
    ports.channel = pwm_gpio_to_channel(gpio);
    ports.slice = pwm_gpio_to_slice_num(gpio);

    pwm_set_enabled(ports.slice, true);

    return ports;
}

void PWM_generate(PWM_Ports* pwm, float target_voltage) {
    float cycle = target_voltage * 500.0f / PWM_VOLTAGE;
    pwm_set_wrap(pwm->slice, 500);
    pwm_set_chan_level(pwm->slice, pwm->channel, (uint)cycle);
}

void PWM_play_note(PWM_Ports* pwm, uint16_t freq, float duration, int volume) {
    pwm_set_gpio_level(pwm->slice, volume);
    pwm_set_clkdiv(pwm->slice, (float)clock_get_hz(clk_sys) / (freq * 65536));
    sleep_ms(duration * 1000);
}

void PWM_play_break(PWM_Ports* pwm, float duration) {  
    pwm_set_gpio_level(pwm->slice, 0);
    sleep_ms(duration * 1000);
}

int PWM_calc_volume(int percent) {
    return percent * 65535 / 100;
}
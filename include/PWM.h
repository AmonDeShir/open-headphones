#ifndef PWM_H
#define PWM_H

#ifndef PWM_VOLTAGE
#define PWM_VOLTAGE 3.0f
#endif

#include "pico/stdlib.h"

struct PWM_Ports {
    uint slice;
    uint channel;
};

PWM_Ports PWM_config(int gpio);
void PWM_generate(PWM_Ports* pwm, float target_voltage);
void PWM_play_note(PWM_Ports* pwm, uint16_t freq, float duration, int volume);
void PWM_play_break(PWM_Ports* pwm, float duration);
int PWM_calc_volume(int percent);

#endif
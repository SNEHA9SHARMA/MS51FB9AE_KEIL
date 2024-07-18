#ifndef PWM_H
#define PWM_H

/********* PWM Module **********/

/**
 * @brief Sets the PWM duty cycle and frequency.
 * 
 * @param dutyCycle The desired duty cycle of the PWM signal.
 * @param frequency The desired frequency of the PWM signal.
 * @return int Status code (e.g., 0 for success, non-zero for error).
 */
void pw(float );

/**
 * @brief Configures the PWM settings.
 */


/**
 * @brief Initializes the PWM hardware and settings.
 */
void initPwm(void);

#endif // PWM_H

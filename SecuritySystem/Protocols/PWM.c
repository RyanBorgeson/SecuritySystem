#include "PWM.h"

void PWM_Init(void) {

    //GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN6);
   // GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN6);
   // GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P6, GPIO_PIN6, GPIO_TERTIARY_MODULE_FUNCTION);


    Timer_A_PWMConfig pwmConfig =
        {
            TIMER_A_CLOCKSOURCE_SMCLK,
			TIMER_A_CLOCKSOURCE_DIVIDER_1,
			300,
			TIMER_A_CAPTURECOMPARE_REGISTER_0,
			TIMER_A_OUTPUTMODE_RESET_SET,
			150
        };

        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P6, GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);
        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
}

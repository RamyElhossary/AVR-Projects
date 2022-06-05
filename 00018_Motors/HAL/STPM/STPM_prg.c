/*
 * STPM_prg.c
 *
 *  Created on: May 31, 2022
 *      Author: Hossary
 */

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "STPM_int.h"
#include <util/delay.h>

extern volatile u8 G_u8MenuFlag;
void STPM_vInit(void) {
	DIO_vSetPinDir(STPM_YELLOW_PORT, STPM_YELLOW_PIN, DIO_OUTPUT);
	DIO_vSetPinDir(STPM_BLUE_PORT, STPM_BLUE_PIN, DIO_OUTPUT);
	DIO_vSetPinDir(STPM_PINK_PORT, STPM_PINK_PIN, DIO_OUTPUT);
	DIO_vSetPinDir(STPM_ORANGE_PORT, STPM_ORANGE_PIN, DIO_OUTPUT);

	DIO_vSetPinVal(STPM_YELLOW_PORT, STPM_YELLOW_PIN, DIO_HIGH);
	DIO_vSetPinVal(STPM_BLUE_PORT, STPM_BLUE_PIN, DIO_HIGH);
	DIO_vSetPinVal(STPM_PINK_PORT, STPM_PINK_PIN, DIO_HIGH);
	DIO_vSetPinVal(STPM_ORANGE_PORT, STPM_PINK_PIN, DIO_HIGH);
}

void STPM_vRCW(u16 A_u16Angle) {
	u16 L_u16I;
	u16 L_u16Iterations = A_u16Angle / 0.17578125 / 4 + 1;
	for(L_u16I = 0; L_u16I < L_u16Iterations; L_u16I++) {
		DIO_vSetPinVal(STPM_BLUE_PORT, STPM_BLUE_PIN, DIO_LOW);
		DIO_vSetPinVal(STPM_PINK_PORT, STPM_PINK_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_YELLOW_PORT, STPM_YELLOW_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_ORANGE_PORT, STPM_ORANGE_PIN, DIO_HIGH);
		_delay_ms(STEPER_DELAY);

		/* for second Activation */
		DIO_vSetPinVal(STPM_BLUE_PORT, STPM_BLUE_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_PINK_PORT, STPM_PINK_PIN, DIO_LOW);
		DIO_vSetPinVal(STPM_YELLOW_PORT, STPM_YELLOW_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_ORANGE_PORT, STPM_ORANGE_PIN, DIO_HIGH);
		_delay_ms(STEPER_DELAY);

		/* for third Activation */
		DIO_vSetPinVal(STPM_BLUE_PORT, STPM_BLUE_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_PINK_PORT, STPM_PINK_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_YELLOW_PORT, STPM_YELLOW_PIN, DIO_LOW);
		DIO_vSetPinVal(STPM_ORANGE_PORT, STPM_ORANGE_PIN, DIO_HIGH);
		_delay_ms(STEPER_DELAY);

		/* for fourth Activation */
		DIO_vSetPinVal(STPM_BLUE_PORT, STPM_BLUE_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_PINK_PORT, STPM_PINK_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_YELLOW_PORT, STPM_YELLOW_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_ORANGE_PORT, STPM_ORANGE_PIN, DIO_LOW);
		_delay_ms(STEPER_DELAY);
	}
}
void STPM_vRCCW(u16 A_u16Angle) {
	u16 L_u16I;
	u16 L_u16Iterations = A_u16Angle / 0.17578125 / 4 + 1;
	for(L_u16I = 0; L_u16I < L_u16Iterations; L_u16I++) {
		DIO_vSetPinVal(STPM_BLUE_PORT, STPM_BLUE_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_PINK_PORT, STPM_PINK_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_YELLOW_PORT, STPM_YELLOW_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_ORANGE_PORT, STPM_ORANGE_PIN, DIO_LOW);
		_delay_ms(STEPER_DELAY);

		/* for second Activation */
		DIO_vSetPinVal(STPM_BLUE_PORT, STPM_BLUE_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_PINK_PORT, STPM_PINK_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_YELLOW_PORT, STPM_YELLOW_PIN, DIO_LOW);
		DIO_vSetPinVal(STPM_ORANGE_PORT, STPM_ORANGE_PIN, DIO_HIGH);
		_delay_ms(STEPER_DELAY);

		/* for third Activation */
		DIO_vSetPinVal(STPM_BLUE_PORT, STPM_BLUE_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_PINK_PORT, STPM_PINK_PIN, DIO_LOW);
		DIO_vSetPinVal(STPM_YELLOW_PORT, STPM_YELLOW_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_ORANGE_PORT, STPM_ORANGE_PIN, DIO_HIGH);
		_delay_ms(STEPER_DELAY);

		/* for fourth Activation */
		DIO_vSetPinVal(STPM_BLUE_PORT, STPM_BLUE_PIN, DIO_LOW);
		DIO_vSetPinVal(STPM_PINK_PORT, STPM_PINK_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_YELLOW_PORT, STPM_YELLOW_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_ORANGE_PORT, STPM_ORANGE_PIN, DIO_HIGH);
		_delay_ms(STEPER_DELAY);
	}
}

void STPM_vRotateSteps(u16 A_u16Steps) {
	u16 i;
	for(i = 0; i <= A_u16Steps; i++) {
		DIO_vSetPinVal(STPM_BLUE_PORT, STPM_BLUE_PIN, DIO_LOW);
		DIO_vSetPinVal(STPM_PINK_PORT, STPM_PINK_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_YELLOW_PORT, STPM_YELLOW_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_ORANGE_PORT, STPM_ORANGE_PIN, DIO_HIGH);
		_delay_ms(STEPER_DELAY);

		/* for second Activation */
		DIO_vSetPinVal(STPM_BLUE_PORT, STPM_BLUE_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_PINK_PORT, STPM_PINK_PIN, DIO_LOW);
		DIO_vSetPinVal(STPM_YELLOW_PORT, STPM_YELLOW_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_ORANGE_PORT, STPM_ORANGE_PIN, DIO_HIGH);
		_delay_ms(STEPER_DELAY);

		/* for third Activation */
		DIO_vSetPinVal(STPM_BLUE_PORT, STPM_BLUE_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_PINK_PORT, STPM_PINK_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_YELLOW_PORT, STPM_YELLOW_PIN, DIO_LOW);
		DIO_vSetPinVal(STPM_ORANGE_PORT, STPM_ORANGE_PIN, DIO_HIGH);
		_delay_ms(STEPER_DELAY);

		/* for fourth Activation */
		DIO_vSetPinVal(STPM_BLUE_PORT, STPM_BLUE_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_PINK_PORT, STPM_PINK_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_YELLOW_PORT, STPM_YELLOW_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_ORANGE_PORT, STPM_ORANGE_PIN, DIO_LOW);
		_delay_ms(STEPER_DELAY);

		/***************************************************************
		 **** These lines violating the Layered Architecture Rules. ****
		 **** 			We will solve that using RTOS.			    ****
		 ***************************************************************/
		if(G_u8MenuFlag == 1) {
			break;
		}

		HLCD_vClearScreen();
		HLCD_vItoS(i);
	}
}

void STPM_vRotateCSteps(u16 A_u16Steps) {
	u16 L_u16I;
	for(L_u16I = 0; L_u16I < A_u16Steps; L_u16I++) {
		DIO_vSetPinVal(STPM_BLUE_PORT, STPM_BLUE_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_PINK_PORT, STPM_PINK_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_YELLOW_PORT, STPM_YELLOW_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_ORANGE_PORT, STPM_ORANGE_PIN, DIO_LOW);
		_delay_ms(STEPER_DELAY);

		/* for second Activation */
		DIO_vSetPinVal(STPM_BLUE_PORT, STPM_BLUE_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_PINK_PORT, STPM_PINK_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_YELLOW_PORT, STPM_YELLOW_PIN, DIO_LOW);
		DIO_vSetPinVal(STPM_ORANGE_PORT, STPM_ORANGE_PIN, DIO_HIGH);
		_delay_ms(STEPER_DELAY);

		/* for third Activation */
		DIO_vSetPinVal(STPM_BLUE_PORT, STPM_BLUE_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_PINK_PORT, STPM_PINK_PIN, DIO_LOW);
		DIO_vSetPinVal(STPM_YELLOW_PORT, STPM_YELLOW_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_ORANGE_PORT, STPM_ORANGE_PIN, DIO_HIGH);
		_delay_ms(STEPER_DELAY);

		/* for fourth Activation */
		DIO_vSetPinVal(STPM_BLUE_PORT, STPM_BLUE_PIN, DIO_LOW);
		DIO_vSetPinVal(STPM_PINK_PORT, STPM_PINK_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_YELLOW_PORT, STPM_YELLOW_PIN, DIO_HIGH);
		DIO_vSetPinVal(STPM_ORANGE_PORT, STPM_ORANGE_PIN, DIO_HIGH);
		_delay_ms(STEPER_DELAY);

		/***************************************************************
		 **** These lines violating the Layered Architecture Rules. ****
		 **** 			We will solve that using RTOS.			    ****
		 ***************************************************************/
		if(G_u8MenuFlag == 1) {
			break;
		}

		HLCD_vClearScreen();
		HLCD_vItoS(L_u16I);
	}
}





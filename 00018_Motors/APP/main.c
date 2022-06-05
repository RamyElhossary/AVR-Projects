/*
 * main.c
 *
 *  Created on: Jun 3, 2022
 *      Author: Hossary
 */

#include "../LIB/STD_TYPES.h"
#include "../HAL/LCD/LCD_int.h"
#include "../HAL/STPM/STPM_int.h"
#include "../HAL/KPD/KPD_int.h"
#include "../HAL/DCM/DCM_int.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/EXT/EXT_int.h"

#include <util/delay.h>
#include <avr/interrupt.h>

volatile u8 G_u8MenuFlag = 1;	// volatile variable to till the complier that the hardware may overwrite on it.

int main(void) {
	u8 LA_KeyMap[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 0, 0, 0}, {'!', 0, 0, 0}};
	u8 L_keyRow;		// to get the row of the key pressed from the keypad.
	u8 L_keyCol;		// to get the col of the key pressed from the keypad.
	u8 L_Key = 0;		// to hold the value from the keypad.
	u16 L_Digits = 0;	// to hold more than one digit from the keypad.
	u8 L_u8I;			// a counter for our loops.
	u8 L_DCM_Flag;		// flag to indicate the state of the DC Motor.
	u8 L_STPM_Flag;		// flag to indicate the state of the Stepper Motor.

	/* initialization for our hardware components */
	STPM_vInit();
	HLCD_vInit();
	KPD_vInit();
	HDCM_vInit();

	/* Enable the EXTI0 */
	MEXTI_vInit(MEXTI0);
	MEXTI_vControlSense(MEXTI0, MEXTI_FALLING);
	MEXTI_vEnable(MEXTI0);

	DIO_vSetPinVal(DIO_PORTD, DIO_PIN2, DIO_HIGH); // activate pull up for our button connected to EXTI0.

	/* Set Directions for the LEDs! */
	DIO_vSetPinDir(DIO_PORTD, DIO_PIN0, DIO_OUTPUT);
	DIO_vSetPinDir(DIO_PORTD, DIO_PIN1, DIO_OUTPUT);
	DIO_vSetPinDir(DIO_PORTD, DIO_PIN3, DIO_OUTPUT);

	while(1) {
		/* Menu Window:- we control that window with the ISR, and when finishing the steps of the Stepper Motor.*/
		if(G_u8MenuFlag == 1) {
			HDCM_vStop(); 		// stopping the DC Motor when we are the Menu Window.

			/* Displaying info for the Menu Window */
			HLCD_vClearScreen();
			HLCD_vSendString("Menu: 1-DCM");
			HLCD_vGoToRowCol(1, 0);
			HLCD_vSendString("2-STPM, 3-ESC");


			while(!KPD_u8GetPressedKey(&L_keyRow, &L_keyCol)); // waiting to get a key from the user.
			L_Key = LA_KeyMap[L_keyRow][L_keyCol];				// holding the value of the key pressed on L_Key variable.

			/* Setting the state of the Motors */
			if(L_Key == 1) {
				L_DCM_Flag = 1;
				L_STPM_Flag = 0;
			}
			else if(L_Key == 2) {
				L_DCM_Flag = 0;
				L_STPM_Flag = 1;
			}
			else {
				break;	// if the value of the key is not 1 or 2, it will exit from the big while loop.
			}

			G_u8MenuFlag = 0;	// To make sure that it will not enter the Menu Window in the next iterations without altering it using ISR or Finising the Stepper Motor.
		}



		/* Operating the DC Motor */
		if(L_DCM_Flag == 1) {

			/* Displaying modes of the DCM */
			HLCD_vClearScreen();
			HLCD_vSendString("1-RCW");
			HLCD_vGoToRowCol(1, 0);
			HLCD_vSendString("2-RCCW");

			while(!KPD_u8GetPressedKey(&L_keyRow, &L_keyCol)); // waiting to get a key from the user.
			L_Key = LA_KeyMap[L_keyRow][L_keyCol];				// holding the value of the key pressed on L_Key variable.

			/* Rotate the DC Motor Clock Wise */
			if(L_Key == 1) {
				HLCD_vClearScreen();
				HLCD_vSendString("Rotating CW");
				HDCM_vRCW();
			}
			/* Rotate the DC Motor Counter Clock Wise */
			else if(L_Key == 2) {
				HLCD_vClearScreen();
				HLCD_vSendString("Rotating CCW");
				HDCM_vRCCW();
			}

			L_DCM_Flag = 0; // to make sure that it will enter the DC Motor Section in the next iterations.

		}	// end of the DC Motor if statement.

		/* Operate the Stepper Motor. */
		if(L_STPM_Flag == 1) {
			/*Displaying modes of the Stepper Motor. */
			HLCD_vClearScreen();
			HLCD_vSendString("1-RCW");
			HLCD_vGoToRowCol(1, 0);
			HLCD_vSendString("2-RCCW");

			while(!KPD_u8GetPressedKey(&L_keyRow, &L_keyCol)); // waiting to get a key from the user.
			L_Key = LA_KeyMap[L_keyRow][L_keyCol];			   // holding the value of the key pressed in the L_Key variable.

			/* Rotate the Stepper Motor Clock Wise. */
			if(L_Key == 1) {
				/* Getting the number of the steps. */
				HLCD_vClearScreen();
				HLCD_vSendString("EnterSteps:");
				L_Key = 0;
				L_Digits = 0;
				while(L_Key != '!') {	// it will iterate till the user hit enter key.
					if(KPD_u8GetPressedKey(&L_keyRow, &L_keyCol)) {
						L_Digits = L_Digits * 10 + L_Key;			// shifting L_Digits one place to the left to hold the value of the key pressed in the ones place.
						L_Key = LA_KeyMap[L_keyRow][L_keyCol];

						if(L_Key == '!') {
							break;
						}

						HLCD_vSendData(L_Key + '0'); // displaying the key pressed on the LCD.
					}

				}

				STPM_vRotateSteps(L_Digits);
				HLCD_vClearScreen();
				HLCD_vSendString("Finished!");
				/* Flashing the LEDs. */
				for(L_u8I = 0; L_u8I < 5; L_u8I++) {
					DIO_vSetPinVal(DIO_PORTD, DIO_PIN0, DIO_HIGH);
					DIO_vSetPinVal(DIO_PORTD, DIO_PIN1, DIO_HIGH);
					DIO_vSetPinVal(DIO_PORTD, DIO_PIN3, DIO_HIGH);
					_delay_ms(200);

					DIO_vSetPinVal(DIO_PORTD, DIO_PIN0, DIO_LOW);
					DIO_vSetPinVal(DIO_PORTD, DIO_PIN1, DIO_LOW);
					DIO_vSetPinVal(DIO_PORTD, DIO_PIN3, DIO_LOW);
					_delay_ms(200);

				}

				G_u8MenuFlag = 1; // Setting the Menu Flag to enter the Menu Window in the second iteration.
			}
			/* Rotate the Stepper Motor Counter Clock Wise */
			else if(L_Key == 2) {
				/* Getting the number of steps. */
				HLCD_vClearScreen();
				HLCD_vSendString("EnterSteps:");
				L_Key = 0;
				L_Digits = 0;
				while(L_Key != '!') { // it will iterate till the user hit the enter key.
					if(KPD_u8GetPressedKey(&L_keyRow, &L_keyCol)) {
						L_Digits = L_Digits * 10 + L_Key;			// shifting L_Digits one place to the left to hold the value of the key pressed in the ones place.
						L_Key = LA_KeyMap[L_keyRow][L_keyCol];

						if(L_Key == '!') {
							break;
						}

						HLCD_vSendData(L_Key + '0');	// displaying the key pressed on the LCD.
					}
				}

				STPM_vRotateCSteps(L_Digits);
				HLCD_vClearScreen();
				HLCD_vSendString("Finished!");
				/* Flashing the LEDs. */
				for(L_u8I = 0; L_u8I < 5; L_u8I++) {
					DIO_vSetPinVal(DIO_PORTD, DIO_PIN0, DIO_HIGH);
					DIO_vSetPinVal(DIO_PORTD, DIO_PIN1, DIO_HIGH);
					DIO_vSetPinVal(DIO_PORTD, DIO_PIN3, DIO_HIGH);
					_delay_ms(200);

					DIO_vSetPinVal(DIO_PORTD, DIO_PIN0, DIO_LOW);
					DIO_vSetPinVal(DIO_PORTD, DIO_PIN1, DIO_LOW);
					DIO_vSetPinVal(DIO_PORTD, DIO_PIN3, DIO_LOW);
					_delay_ms(200);
				}

				G_u8MenuFlag = 1;	// Setting the Menu Flag to enter the Menu Window in the second iteration.
			}

		}

	}


	/* When Exit */
	HLCD_vClearScreen();
	HLCD_vSendString("Thank You!");

	while(1);

	return 0;
}

ISR(INT0_vect) {
	G_u8MenuFlag = 1;
}


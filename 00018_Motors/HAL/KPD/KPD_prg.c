/*
 * KPD_prg.c
 *
 *  Created on: May 17, 2022
 *      Author: Hossary
 */

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "KPD_int.h"
#include <util/delay.h>


void KPD_vInit(void) {
	DIO_vSetPortDir(KPD_PORT, 0x0f);
	DIO_vSetPortVal(KPD_PORT, 0xff);
}

u8 KPD_u8GetPressedKey(u8 *AP_u8Row, u8 *AP_u8Col) {
	u8 L_u8PressedStatus = 0;
	for(u8 col = 0; col < 4; col++) {
		DIO_vSetPinVal(KPD_PORT, col, DIO_LOW);
		for(u8 row = 4; row < 8; row++) {
			if(DIO_u8GetPinVal(KPD_PORT, row) == 0) {
				while(DIO_u8GetPinVal(KPD_PORT, row) == 0) {
					// it will loop till the key released.
				}
				_delay_ms(40);
				*AP_u8Row = row - 4;
				*AP_u8Col = col;
				L_u8PressedStatus = 1;
			}
		}
		DIO_vSetPinVal(KPD_PORT, col, DIO_HIGH);
	}

	return L_u8PressedStatus;
}

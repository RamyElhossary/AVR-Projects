/*
 * DCM_prg.c
 *
 *  Created on: May 29, 2022
 *      Author: Hossary
 */

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "DCM_int.h"

void HDCM_vInit(void) {
	DIO_vSetPinDir(DCM_CWPort, DCM_CWPin, DIO_OUTPUT);
	DIO_vSetPinDir(DCM_CCWPort, DCM_CCWPin, DIO_OUTPUT);
}

void HDCM_vRCW(void) {
	DIO_vSetPinVal(DCM_CCWPort, DCM_CCWPin, DIO_LOW);
	DIO_vSetPinVal(DCM_CWPort, DCM_CWPin, DIO_HIGH);
}

void HDCM_vRCCW(void) {
	DIO_vSetPinVal(DCM_CWPort, DCM_CWPin, DIO_LOW);
	DIO_vSetPinVal(DCM_CCWPort, DCM_CCWPin, DIO_HIGH);
}

void HDCM_vStop(void) {
	DIO_vSetPinVal(DCM_CWPort, DCM_CWPin, DIO_LOW);
	DIO_vSetPinVal(DCM_CCWPort, DCM_CCWPin, DIO_LOW);
}

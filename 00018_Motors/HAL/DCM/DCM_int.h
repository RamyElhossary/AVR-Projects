/*
 * DCM_int.h
 *
 *  Created on: May 29, 2022
 *      Author: Hossary
 */

#ifndef HAL_DCM_DCM_INT_H_
#define HAL_DCM_DCM_INT_H_


#define DCM_CWPort 		DIO_PORTB
#define DCM_CCWPort		DIO_PORTB

#define DCM_CWPin		DIO_PIN0
#define DCM_CCWPin		DIO_PIN1

void HDCM_vInit(void);
void HDCM_vRCW(void);
void HDCM_vRCCW(void);
void HDCM_vStop(void);

#endif /* HAL_DCM_DCM_INT_H_ */

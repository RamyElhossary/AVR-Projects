/*
 * STPM_int.h
 *
 *  Created on: May 31, 2022
 *      Author: Hossary
 */

#ifndef HAL_STPM_STPM_INT_H_
#define HAL_STPM_STPM_INT_H_

#define STPM_YELLOW_PORT 	 DIO_PORTB
#define STPM_BLUE_PORT 		 DIO_PORTB
#define STPM_PINK_PORT 		 DIO_PORTB
#define STPM_ORANGE_PORT	 DIO_PORTB

#define STPM_BLUE_PIN		 DIO_PIN2
#define STPM_PINK_PIN		 DIO_PIN3
#define STPM_YELLOW_PIN		 DIO_PIN4
#define STPM_ORANGE_PIN		 DIO_PIN5

#define STEPER_DELAY 20

void STPM_vInit(void);
void STPM_vRCW(u16 A_u16Angle);
void STPM_vRCCW(u16 A_u16Angle);
void STPM_vRotateSteps(u16 A_u16Steps);
void STPM_vRotateCSteps(u16 A_u16Steps);


#endif /* HAL_STPM_STPM_INT_H_ */

/*
 * KPD_int.h
 *
 *  Created on: May 17, 2022
 *      Author: Hossary
 */

#ifndef HAL_KPD_KPD_INT_H_
#define HAL_KPD_KPD_INT_H_

#define KPD_PORT DIO_PORTA

void KPD_vInit(void);
u8 KPD_u8GetPressedKey(u8 *AP_u8Row, u8 *AP_u8Col);

#endif /* HAL_KPD_KPD_INT_H_ */

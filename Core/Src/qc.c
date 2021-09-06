/*
 * Quick Charge 2.0 implementation
 */

#include "qc.h"
#include "adc.h"
#include "gpio.h"

void QC_Dp600mV() {
	HAL_GPIO_WritePin(DUSB_PD_P_L_GPIO_Port, DUSB_PD_P_L_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DUSB_PD_P_H_GPIO_Port, DUSB_PD_P_H_Pin, GPIO_PIN_SET);
}
void QC_Dp3300mV() {
	HAL_GPIO_WritePin(DUSB_PD_P_L_GPIO_Port, DUSB_PD_P_L_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DUSB_PD_P_H_GPIO_Port, DUSB_PD_P_H_Pin, GPIO_PIN_SET);
}
void QC_DnHiZ() {
	GPIO_InitTypeDef GPIO_Init = { 0 };
	GPIO_Init.Pin = DUSB_PD_N_L_Pin | DUSB_PD_N_H_Pin;
	GPIO_Init.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(DUSB_PD_N_L_GPIO_Port, &GPIO_Init);
}
void QC_DnOut() {
	GPIO_InitTypeDef GPIO_Init = { 0 };
	GPIO_Init.Pin = DUSB_PD_N_L_Pin | DUSB_PD_N_H_Pin;
	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(DUSB_PD_N_L_GPIO_Port, &GPIO_Init);
}
void QC_Dn0V() {
	HAL_GPIO_WritePin(DUSB_PD_N_L_GPIO_Port, DUSB_PD_N_L_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DUSB_PD_N_H_GPIO_Port, DUSB_PD_N_H_Pin, GPIO_PIN_RESET);
	QC_DnOut();
}
void QC_Dn600mV() {
	HAL_GPIO_WritePin(DUSB_PD_N_L_GPIO_Port, DUSB_PD_N_L_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DUSB_PD_N_H_GPIO_Port, DUSB_PD_N_H_Pin, GPIO_PIN_SET);
	QC_DnOut();
}
void QC_Dn3300mV() {
	HAL_GPIO_WritePin(DUSB_PD_N_L_GPIO_Port, DUSB_PD_N_L_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DUSB_PD_N_H_GPIO_Port, DUSB_PD_N_H_Pin, GPIO_PIN_SET);
	QC_DnOut();
}

void QC_Init() {
	QC_Dp600mV();
	QC_DnHiZ();
}
void QC_Handshake() {
	QC_Init();
	HAL_Delay(QC_HANDSHAKE_DELAY_MS);
}

void QC_Set5V() {
	QC_Dp600mV();
	QC_Dn0V();
	HAL_Delay(QC_V_CHANGE_DELAY_MS);
}
void QC_Set9V() {
	QC_Dp3300mV();
	QC_Dn600mV();
	HAL_Delay(QC_V_CHANGE_DELAY_MS);
}
void QC_Set12V() {
	QC_Dp600mV();
	QC_Dn600mV();
	HAL_Delay(QC_V_CHANGE_DELAY_MS);
}



 /*
 * ADXL357.h
 *
 * Created on: Feb 03, 2025
 * Author: Nathan Netzel
 *
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Nathan Netzel
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the conditions of the MIT License.
 */
 
 

#ifndef INC_ADXL357_H_
#define INC_ADXL357_H_


#include "stm32h5xx_hal.h"

// --- Registers ---
// Register addresses for ADXL357 sensor
#define ADXL_ANALOG_DEVICES_ID_REG			0x00
#define ADXL_ANALOG_DEVICES_MEMS_ID_REG		0x01
#define ADXL_DEVICE_ID_REG					0x02
#define ADXL_PRODUCT_REVISION_ID_REG		0x03
#define ADXL_STATUS							0x04
#define ADXL_FIFO_ENTRIES					0x05
#define ADXL_TEMP2							0x06
#define ADXL_TEMP1							0x07
#define ADXL_DATA_ADDRESS_INIT				0x08
#define ADXL_XDATA3							0x08
#define ADXL_XDATA2							0x09
#define ADXL_XDATA1							0x0A
#define ADXL_YDATA3							0x0B
#define ADXL_YDATA2							0x0C
#define ADXL_YDATA1							0x0D
#define ADXL_ZDATA3							0x0E
#define ADXL_ZDATA2							0x0F
#define ADXL_ZDATA1							0x10
#define ADXL_FIFO_DATA						0x11
#define ADXL_OFFSET_X_H						0x1E
#define ADXL_OFFSET_X_L						0x1F
#define ADXL_OFFSET_Y_H						0x20
#define ADXL_OFFSET_Y_L						0x21
#define ADXL_OFFSET_Z_H						0x22
#define ADXL_OFFSET_Z_L						0x23
#define ADXL_ACT_EN							0x24
#define ADXL_ACT_THRESH_H					0x25
#define ADXL_ACT_THRESH_L					0x26
#define ADXL_ACT_COUNT 						0x27
#define ADXL_FILTER							0x28
#define ADXL_FIFO_SAMPLES					0x29
#define ADXL_INT_MAP						0x2A
#define ADXL_SYNC							0x2B
#define ADXL_RANGE							0x2C
#define ADXL_POWER_CTL						0x2D
#define ADXL_SELF_TEST 						0x2E
#define ADXL_RESET_REG						0x2F

// --- Device IDs ---
#define ADXL_ANALOG_DEVICES_ID				0xAD
#define ADXL_ANALOG_DEVICES_MEMS_ID			0x1D
#define ADXL_Device_ID						0xED
#define ADXL_PRODUCT_REVISION_ID		   	0x01

// --- Output Data Rates (ODR) and LPF Corner --- 
#define ADXL_ODR_4000		0x00
#define ADXL_ODR_2000		0x01
#define ADXL_ODR_1000		0x02
#define ADXL_ODR_0500		0x03
#define ADXL_ODR_0250		0x04
#define ADXL_ODR_0125		0x05
#define ADXL_ODR_0062		0x06
#define ADXL_ODR_0031		0x07
#define ADXL_ODR_0015		0x08
#define ADXL_ODR_0007		0x09
#define ADXL_ODR_0004		0x0A

// --- Measurement Ranges ---
#define ADXL_RANGE_10		0x01
#define ADXL_RANGE_20		0x02
#define ADXL_RANGE_40		0x03

// --- Interrupt Polarity ---
#define ADXL_INT_ACTIVEHIGH		0
#define ADXL_INT_ACTIVELOW  	1

// --- Operating Modes ---
#define ADXL_MEASUREMODE 	0x00
#define ADXL_STANDBYMODE 	0x01

// --- Reset Command ---
#define ADXL_RESET			0x52

// --- Interrupt Map ---
#define ADXL_INT1_DATA_READY	0x00
#define ADXL_INT2_DATA_READY	0x10
#define ADXL_INT1_ACT_DET		0x08
#define ADXL_INT2_ACT_DET		0x80

// --- SPI Commands ---
#define ADXL_Read_Command			0x01
#define ADXL_Write_command			0x00

// --- SPI Timeout (ms) ---
#define ADXL_Timeout	10

// --- Error Status Enum ---
typedef enum {
	ADXL_NO_ERROR 			=	0x00U, 	/**< No error */
	ADXL_ERROR	  			=	0x01U, 	/**< Generic error */
	ADXL_HAL_ERROR			= 	0x02U, 	/**< HAL communication error */
	ADXL_INV_REG_DATA_READ	= 	0x03U, 	/**< Invalid data read from register */
	ADXL_ID_VERIFY_ERROR	=	0x04U, 	/**< Device ID verification failed */

} ADXL357_Error_TypeDef;

// --- Hardware Initialization Structure ---
typedef struct {
	SPI_HandleTypeDef *SPIhandler; 	/**< Pointer to SPI handler */
	GPIO_TypeDef *CS_GPIOport;     	/**< GPIO port for chip select */
	uint16_t CS_GPIOpin;			/**< GPIO pin number for chip select */ 			
	uint8_t	SPI_Timeout;			/**< SPI timeout in milliseconds */
}ADXL357_HW_InitTypeDef;


/**
 * @brief Accelerometer axis data structure
 * 
 * Contains signed 20-bit values stored as int32_t for each axis
 */
typedef struct ADXL357_AXES{
	int32_t DX;
	int32_t DY;
	int32_t DZ;
} ADXL357_Data_TypeDef;


// Functions

/**
 * @brief  Set the ADXL357 output data rate
 * @param  ADXL357_Handler Pointer to the ADXL357_HW_InitTypeDef structure
 * @param  ADXL357_Rate 8-bit value of the DataRate (see datasheet)
 * @retval ADXL357_Error_TypeDef
 */
ADXL357_Error_TypeDef ADXL357_Set_Output_DataRate(ADXL357_HW_InitTypeDef *, uint8_t);

/**
 * @brief  Set the ADXL357 to continuous measurement mode
 * @param  ADXL357_Handler Pointer to the ADXL357_HW_InitTypeDef structure
 * @retval ADXL357_Error_TypeDef
 */
ADXL357_Error_TypeDef ADXL357_Set_Continuous_Measurement(ADXL357_HW_InitTypeDef *);

/**
 * @brief  Set the ADXL357 measurement range
 * @param  ADXL357_Handler Pointer to the ADXL357_HW_InitTypeDef structure
 * @param  ADXL357_Range 8-bit value of the measurement range (see datasheet)
 * @retval ADXL357_Error_TypeDef
 */
ADXL357_Error_TypeDef ADXL357_Set_Range(ADXL357_HW_InitTypeDef *, uint8_t);

/**
 * @brief  Verify the device ID of the ADXL357 sensor
 * @param  ADXL357_Handler Pointer to the ADXL357_HW_InitTypeDef structure
 * @retval ADXL357_Error_TypeDef
 */
ADXL357_Error_TypeDef ADXL357_ID_Verify(ADXL357_HW_InitTypeDef *);

/**
 * @brief  Read the accelerometer data from X, Y, Z axes
 * @param  ADXL357_Handler Pointer to the ADXL357_HW_InitTypeDef structure
 * @param  ADXL357_Data Pointer to ADXL357_Data_TypeDef structure to store the data
 * @retval ADXL357_Error_TypeDef
 */
ADXL357_Error_TypeDef ADXL357_Data_Read(ADXL357_HW_InitTypeDef *, ADXL357_Data_TypeDef *);

/**
 * @brief  Read a single register from the ADXL357 sensor
 * @param  ADXL357_Handler Pointer to the ADXL357_HW_InitTypeDef structure
 * @param  ADXL357_Register_Addr Register address to read
 * @param  pData Pointer to uint8_t variable to store read data
 * @retval ADXL357_Error_TypeDef
 */
ADXL357_Error_TypeDef ADXL357_SingleRegister_Read(ADXL357_HW_InitTypeDef *, uint8_t, uint8_t *);

/**
 * @brief  Write a single register in the ADXL357 sensor
 * @param  ADXL357_Handler Pointer to the ADXL357_HW_InitTypeDef structure
 * @param  ADXL357_Register_Addr Register address to write
 * @param  ADXL357_Write_Data 8-bit value to write in the register
 * @retval ADXL357_Error_TypeDef
 */
ADXL357_Error_TypeDef ADXL357_SingleRegister_Write(ADXL357_HW_InitTypeDef *, uint8_t, uint8_t);

/**
 * @brief  Enable the chip select (CS) pin for SPI communication
 * @param  CS_GPIOport GPIO port of the CS pin
 * @param  CS_GPIOpin GPIO pin number of the CS pin
 */
void enableCS_ADXL357(GPIO_TypeDef *, uint16_t);

/**
 * @brief  Disable the chip select (CS) pin for SPI communication
 * @param  CS_GPIOport GPIO port of the CS pin
 * @param  CS_GPIOpin GPIO pin number of the CS pin
 */
void disableCS_ADXL357(GPIO_TypeDef *, uint16_t);


#endif /* INC_ADXL357_H_ */


/*
 * ADXL357.c
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


#include <ADXL357.h>


/* Private SPI Handler */



/**
 * @brief  Read the ADXL ID register and checks its content
 * @note   Returns ADXL_NO_ERROR only if content matches the expected value
 * @param  ADXL357_Handler Pointer to the ADXL357_HW_InitTypeDef structure
 * @retval ADXL357_Error_TypeDef
 */
ADXL357_Error_TypeDef ADXL357_ID_Verify(ADXL357_HW_InitTypeDef *ADXL357_Handler){
	uint8_t ID_Receive=0;

	// Fazer a função de enviar o comando
	ADXL357_Error_TypeDef Verify_Status = ADXL357_SingleRegister_Read(ADXL357_Handler, ADXL_DEVICE_ID_REG, &ID_Receive);
	/*enableCS_ADXL357(ADXL357_Handler->CS_GPIOport, ADXL357_Handler->CS_GPIOpin);
	HAL_SPI_Transmit(ADXL357_Handler->SPIhandler, &SPITransmitData_ADXL, 1, ADXL357_Handler->SPI_Timeout);
	HAL_SPI_Receive(ADXL357_Handler->SPIhandler, &ID_Receive, 1, ADXL357_Handler->SPI_Timeout);
	disableCS_ADXL357(ADXL357_Handler->CS_GPIOport, ADXL357_Handler->CS_GPIOpin);*/
	if ( (ID_Receive==ADXL_Device_ID) && (Verify_Status==ADXL_NO_ERROR) )
		return ADXL_NO_ERROR;
	else
		return ADXL_ID_VERIFY_ERROR;
}

/**
 * @brief  Set the ADXL357 output data rate
 * @note   Uses the ADXL357_SingleRegister_Write function directly to write the specified
 *         value into ADXL_FILTER register
 * @param  ADXL357_Handler Pointer to the ADXL357_HW_InitTypeDef structure
 * @param  ADXL357_Rate 8-bit value of the DataRate (see datasheet)
 * @retval ADXL357_Error_TypeDef
 */
ADXL357_Error_TypeDef ADXL357_Set_Output_DataRate(ADXL357_HW_InitTypeDef *ADXL357_Handler, uint8_t ADXL357_Rate)
{
	uint8_t ADXL_RateReg_Return = 0;
	ADXL357_SingleRegister_Write(ADXL357_Handler, ADXL_FILTER, ADXL357_Rate);
	ADXL357_SingleRegister_Read(ADXL357_Handler, ADXL_FILTER, &ADXL_RateReg_Return);

	if( ADXL_RateReg_Return != ADXL357_Rate)
		return ADXL_INV_REG_DATA_READ;
	else
		return ADXL_NO_ERROR;
}

/**
 * @brief  Set the ADXL357 range
 * @note   Uses the ADXL357_SingleRegister_Write function directly to write the specified
 *         value into ADXL_RANGE register
 * @param  ADXL357_Handler Pointer to the ADXL357_HW_InitTypeDef structure
 * @param  ADXL357_Range 8-bit value of the range (see datasheet)
 * @retval ADXL357_Error_TypeDef
 */
ADXL357_Error_TypeDef ADXL357_Set_Range(ADXL357_HW_InitTypeDef *ADXL357_Handler, uint8_t ADXL357_Range)
{
	uint8_t ADXL_RangeReg_Return = 0;
	ADXL357_SingleRegister_Write(ADXL357_Handler, ADXL_RANGE, ADXL357_Range);
	ADXL357_SingleRegister_Read(ADXL357_Handler, ADXL_RANGE, &ADXL_RangeReg_Return);

	if( ADXL_RangeReg_Return != ADXL357_Range)
		return ADXL_INV_REG_DATA_READ;
	else
		return ADXL_NO_ERROR;
}

/**
 * @brief  Set the ADXL357 to continuous Measurement mode
 * @note   Uses the ADXL357_SingleRegister_Write function directly to
 *         write 0x08 content into ADXL_POWER_CTL register
 * @param  ADXL357_Handler Pointer to the ADXL357_HW_InitTypeDef structure
 * @retval ADXL357_Error_TypeDef
 */
ADXL357_Error_TypeDef ADXL357_Set_Continuous_Measurement(ADXL357_HW_InitTypeDef *ADXL357_Handler)
{
	uint8_t ADXL_MeasureReg_Return = 0;
	ADXL357_SingleRegister_Write(ADXL357_Handler, ADXL_POWER_CTL, ADXL_MEASUREMODE);
	ADXL357_SingleRegister_Read(ADXL357_Handler, ADXL_POWER_CTL, &ADXL_MeasureReg_Return);

	if(ADXL_MeasureReg_Return!=ADXL_MEASUREMODE)
		return ADXL_INV_REG_DATA_READ;
	else
		return ADXL_NO_ERROR;
}


/**
 * @brief  Acquire the X, Y and Z registers data from the sensor last conversion
 * @note   The function uses a sequential read using enable and disable chip select functions
 * @param  ADXL357_Handler Pointer to the ADXL357_HW_InitTypeDef structure
 * @param  ADXL357_Data Pointer to the ADXL357_Data_TypeDef structure where data will be stored
 * @retval ADXL357_Error_TypeDef
 */
ADXL357_Error_TypeDef ADXL357_Data_Read(ADXL357_HW_InitTypeDef *ADXL357_Handler, ADXL357_Data_TypeDef *ADXL357_Data){

	uint8_t SPITransmitData_ADXL;
	uint8_t ADXL_Data_Reply[10];

	SPITransmitData_ADXL = (ADXL_Read_Command | (ADXL_DATA_ADDRESS_INIT << 1));

	enableCS_ADXL357(ADXL357_Handler->CS_GPIOport, ADXL357_Handler->CS_GPIOpin);
	if(HAL_SPI_Transmit(ADXL357_Handler->SPIhandler, &SPITransmitData_ADXL, 1, ADXL357_Handler->SPI_Timeout) != HAL_OK)
	{
		disableCS_ADXL357(ADXL357_Handler->CS_GPIOport, ADXL357_Handler->CS_GPIOpin);
		return ADXL_HAL_ERROR;
	}
	if(HAL_SPI_Receive(ADXL357_Handler->SPIhandler, ADXL_Data_Reply, 9, ADXL357_Handler->SPI_Timeout) != HAL_OK)
	{
		disableCS_ADXL357(ADXL357_Handler->CS_GPIOport, ADXL357_Handler->CS_GPIOpin);
		return ADXL_HAL_ERROR;
	}
	disableCS_ADXL357(ADXL357_Handler->CS_GPIOport, ADXL357_Handler->CS_GPIOpin);

	ADXL357_Data->DZ = ((uint32_t)ADXL_Data_Reply[8] >> 4)| ((uint32_t)ADXL_Data_Reply[7] << 4) | ((uint32_t)ADXL_Data_Reply[6] << 12);
	ADXL357_Data->DY = ((uint32_t)ADXL_Data_Reply[5] >> 4)| ((uint32_t)ADXL_Data_Reply[4] << 4) | ((uint32_t)ADXL_Data_Reply[3] << 12);
	ADXL357_Data->DX = ((uint32_t)ADXL_Data_Reply[2] >> 4)| ((uint32_t)ADXL_Data_Reply[1] << 4) | ((uint32_t)ADXL_Data_Reply[0] << 12);

	// Check if number is negative
    if(ADXL357_Data->DX & 0x80000) ADXL357_Data->DX = (ADXL357_Data->DX & 0x7FFFF) - 0x80000;
    if(ADXL357_Data->DY & 0x80000) ADXL357_Data->DY = (ADXL357_Data->DY & 0x7FFFF) - 0x80000;
    if(ADXL357_Data->DZ & 0x80000) ADXL357_Data->DZ = (ADXL357_Data->DZ & 0x7FFFF) - 0x80000;

	return ADXL_NO_ERROR;
}

/**
 * @brief  Perform a single register write in the specified register
 * @note   None
 * @param  ADXL357_Handler Pointer to the ADXL357_HW_InitTypeDef structure
 * @param  ADXL357_Register_Addr Register address to be written
 * @param  ADXL357_Write_Data 8-bit value to be written
 * @retval ADXL357_Error_TypeDef
 */
ADXL357_Error_TypeDef ADXL357_SingleRegister_Write(ADXL357_HW_InitTypeDef *ADXL357_Handler, uint8_t ADXL357_Register_Addr, uint8_t ADXL357_Write_Data)
{
	uint8_t SPITransmitData_ADXL;
	SPITransmitData_ADXL = (ADXL_Write_command | (ADXL357_Register_Addr << 1));

	enableCS_ADXL357(ADXL357_Handler->CS_GPIOport, ADXL357_Handler->CS_GPIOpin);
	if(HAL_SPI_Transmit(ADXL357_Handler->SPIhandler, &SPITransmitData_ADXL, 1, ADXL357_Handler->SPI_Timeout) != HAL_OK)
	{
		disableCS_ADXL357(ADXL357_Handler->CS_GPIOport, ADXL357_Handler->CS_GPIOpin);
		return ADXL_HAL_ERROR;
	}
	if(HAL_SPI_Transmit(ADXL357_Handler->SPIhandler, &ADXL357_Write_Data, 1, ADXL357_Handler->SPI_Timeout) != HAL_OK)
	{
		disableCS_ADXL357(ADXL357_Handler->CS_GPIOport, ADXL357_Handler->CS_GPIOpin);
		return ADXL_HAL_ERROR;
	}
	disableCS_ADXL357(ADXL357_Handler->CS_GPIOport, ADXL357_Handler->CS_GPIOpin);

	return ADXL_NO_ERROR;
}

/**
 * @brief  Perform a single register read in the specified register
 * @param  ADXL357_Handler Pointer to the ADXL357_HW_InitTypeDef structure
 * @param  ADXL357_Register_Addr Register address 8-bit value
 * @param  pData Pointer to the uint8_t variable where read data will be stored
 * @retval ADXL357_Error_TypeDef
 */
ADXL357_Error_TypeDef ADXL357_SingleRegister_Read(ADXL357_HW_InitTypeDef *ADXL357_Handler, uint8_t ADXL357_Register_Addr, uint8_t *pData)
{
	uint8_t SPITransmitData_ADXL;
	SPITransmitData_ADXL = (ADXL_Read_Command | (ADXL357_Register_Addr << 1));

	enableCS_ADXL357(ADXL357_Handler->CS_GPIOport, ADXL357_Handler->CS_GPIOpin);
	if(HAL_SPI_Transmit(ADXL357_Handler->SPIhandler, &SPITransmitData_ADXL, 1, ADXL357_Handler->SPI_Timeout) != HAL_OK)
	{
		disableCS_ADXL357(ADXL357_Handler->CS_GPIOport, ADXL357_Handler->CS_GPIOpin);
		return ADXL_HAL_ERROR;
	}
	if(HAL_SPI_Receive(ADXL357_Handler->SPIhandler, pData, 1, ADXL357_Handler->SPI_Timeout) != HAL_OK)
	{
		disableCS_ADXL357(ADXL357_Handler->CS_GPIOport, ADXL357_Handler->CS_GPIOpin);
		return ADXL_HAL_ERROR;
	}
	disableCS_ADXL357(ADXL357_Handler->CS_GPIOport, ADXL357_Handler->CS_GPIOpin);

	return ADXL_NO_ERROR;
}

/**
 * @brief  Enables the chip select pin for the specified SPI Chip Select
 * @param  CS_GPIOport Chip select GPIO port address
 * @param  CS_GPIOpin Chip select GPIO pin number
 * @retval None
 */
void enableCS_ADXL357(GPIO_TypeDef *CS_GPIOport, uint16_t CS_GPIOpin){
  HAL_GPIO_WritePin(CS_GPIOport, CS_GPIOpin, GPIO_PIN_RESET);
}

/**
 * @brief  Disables the chip select pin for the specified SPI Chip Select
 * @param  CS_GPIOport Chip select GPIO port address
 * @param  CS_GPIOpin Chip select GPIO pin number
 * @retval None
 */
void disableCS_ADXL357(GPIO_TypeDef *CS_GPIOport, uint16_t CS_GPIOpin){
  HAL_GPIO_WritePin(CS_GPIOport, CS_GPIOpin, GPIO_PIN_SET);
  //CS_GPIOport->BSRR = CS_GPIOpin;
}


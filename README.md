# ADXL357 STM32 HAL Driver

C driver library for the ADXL357 low-noise, low-drift 3-axis accelerometer sensor.  
Designed for STM32 microcontrollers using the STM32 HAL library and SPI interface.

---

## **Features**

- Verify device ID  
- Configure output data rate and measurement range  
- Enable continuous measurement mode  
- Read acceleration data from X, Y, Z axes  
- SPI communication with chip select control  
- Basic error handling  

---

## **Requirements**

- STM32 MCU with STM32 HAL library  
- SPI hardware interface connected to ADXL357 sensor  
- Basic experience with embedded C and STM32CubeIDE or similar  

---

## **Quick Start**

1. Add driver files to your project

Include `ADXL357.c` and `ADXL357.h` in your STM32 project source folder.

2. Configure your hardware

Set up SPI peripheral and GPIO pins for SPI and Chip Select (CS) according to your board schematic.

3. Initialize driver handle structure

```c
ADXL357_HW_InitTypeDef ADXL357_Handle = {
    .SPIhandler = &hspi1,             // Your SPI handle configured in your project
    .CS_GPIOport = GPIOA,             // GPIO port of CS pin
    .CS_GPIOpin = GPIO_PIN_4,         // GPIO pin of CS
    .SPI_Timeout = 100                // SPI timeout in milliseconds
};
```

4. Verify sensor connection

```c
if (ADXL357_ID_Verify(&ADXL357_Handle) != ADXL_NO_ERROR) {
    // Handle error: sensor not detected
}
```

5. Configure sensor settings

```c
ADXL357_Set_Output_DataRate(&ADXL357_Handle, ADXL_RATE_100HZ);
ADXL357_Set_Range(&ADXL357_Handle, ADXL_RANGE_40G);
ADXL357_Set_Continuous_Measurement(&ADXL357_Handle);
```

6. Read acceleration data

```c
ADXL357_Data_TypeDef accel_data;
if (ADXL357_Data_Read(&ADXL357_Handle, &accel_data) == ADXL_NO_ERROR) {
    int32_t x = accel_data.DX;
    int32_t y = accel_data.DY;
    int32_t z = accel_data.DZ;
    // Process acceleration data
}
```

---

## **API Overview**

- `ADXL357_ID_Verify()` — Verify sensor presence  
- `ADXL357_Set_Output_DataRate()` — Set output data rate  
- `ADXL357_Set_Range()` — Set measurement range  
- `ADXL357_Set_Continuous_Measurement()` — Enable continuous measurement  
- `ADXL357_Data_Read()` — Read acceleration data X, Y, Z  
- `ADXL357_SingleRegister_Read()` and `Write()` — Low-level register access  

---

## **License**

This project is licensed under the MIT License. See the LICENSE file for details.

---

## **Author**

Nathan Netzel  
Electrical Engineering Student - Londrina State University

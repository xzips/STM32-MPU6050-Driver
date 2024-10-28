#ifndef __MPU6050_DRIVER_H
#define __MPU6050_DRIVER_H


#include "stm32l4xx_hal.h"

/*
---Resources Used---

(1) Offical Datasheet from Manufacterer: https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
(2) Example Code for Arduino: https://arduino.stackexchange.com/questions/85287/mpu6050-does-not-give-output


*/



// MPU-6050 I2C address (shifted for HAL since first bit is R/W)
#define MPU_ADDR 0x68  << 1


/*---REGISTERS SECTION---*/


// WHO_AM_I register, used to verify the device is connected
#define WHO_AM_I_ADDR 0x75 

// Power Management 1 register, important for reset/initilization
#define PWR_MGMT_1 0x6B

// Signal Path Reset register, important for reset/initilization
#define SIGNAL_PATH_RESET 0x68   


// Register used to set the accelerometer range, and also do self test on the accelerometer
/*
Register (Hex) Register (Decimal) Bit7  Bit6  Bit5  Bit4 Bit3      Bit2 Bit1 Bit0
1C             28                 XA_ST YA_ST ZA_ST AFS_SEL[1:0]      UNUSED

AFS_SEL[1:0] Full Scale Range mapping:
0 +/- 2g
1 +/- 4g
2 +/- 8g
3 +/- 16g
*/
#define ACCEL_CONFIG 1C


/*
Register(Hex) Register (Decimal)    Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
3B            59                               ACCEL_XOUT[15:8]
3C            60                               ACCEL_XOUT[7:0]
3D            61                               ACCEL_YOUT[15:8]
3E            62                               ACCEL_YOUT[7:0]
3F            63                               ACCEL_ZOUT[15:8]
40            64                               ACCEL_ZOUT[7:0]

ACCEL_XOUT 16-bit 2’s complement value. Stores the most recent X axis accelerometer measurement.
ACCEL_YOUT 16-bit 2’s complement value. Stores the most recent Y axis accelerometer measurement.
ACCEL_ZOUT 16-bit 2’s complement value. Stores the most recent Z axis accelerometer measurement.

*/

#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40

/*
Register(Hex) Register (Decimal)    Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
41            59                               TEMP_OUT[15:8]
42            60                               TEMP_OUT[7:0]  

Temperature in degrees C = (TEMP_OUT Register Value as a signed quantity)/340 + 36.53

*/

#define TEMP_OUT_H 0x41
#define TEMP_OUT_L 0x42

extern I2C_HandleTypeDef* MPU6050_hi2c;


/*---DRIVER FUNCTIONS SECTION---*/

// Initialize the MPU6050 on a particular I2C bus, returns 0 if successful, 1 if failed
int MPU6050_Init(I2C_HandleTypeDef *hi2c);

// Checks if the MPU6050 is connected to the I2C bus, returns 0 if successful, 1 if failed
int MPU6050_CheckConnection();

// Reads X acceleration from the MPU6050, returns the value in m/s^2
float MPU6050_ReadAccelX();

// Reads Y acceleration from the MPU6050, returns the value in m/s^2
float MPU6050_ReadAccelY();

// Reads Z acceleration from the MPU6050, returns the value in m/s^2
float MPU6050_ReadAccelZ();

// Reads the temperature from the MPU6050, returns the value in degrees C
float MPU6050_ReadTemp();




#endif /* __MPU6050_DRIVER_H */
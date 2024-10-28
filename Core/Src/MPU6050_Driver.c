 
 
#include "MPU6050_Driver.h"
 



I2C_HandleTypeDef* MPU6050_hi2c;




// Initialize the MPU6050 on a particular I2C bus, returns 0 if successful, 1 if failed
int MPU6050_Init(I2C_HandleTypeDef *hi2c)
{

    MPU6050_hi2c = hi2c;
    
    uint8_t data;
    HAL_StatusTypeDef status;

    // Step 1: Full reset (DEVICE_RESET, TEMP_DIS in PWR_MGMT_1 register)
    data = 0b10001000;  //temp sense disabled
    status = HAL_I2C_Mem_Write(MPU6050_hi2c, MPU_ADDR, PWR_MGMT_1, I2C_MEMADD_SIZE_8BIT, &data, 1, 1000);
    if (status != HAL_OK) return 1;


    HAL_Delay(100);  // Delay to allow reset to complete, this is recommended in the datasheet, should be non-blocking in an RTOS context

    // Step 2: Reset gyro, accel, and temperature sensor paths
    data = 0b00000111;
    status = HAL_I2C_Mem_Write(MPU6050_hi2c, MPU_ADDR, SIGNAL_PATH_RESET, I2C_MEMADD_SIZE_8BIT, &data, 1, 1000);
    if (status != HAL_OK) return 1;

    HAL_Delay(100); // Delay to allow reset to complete, this is recommended in the datasheet, should be non-blocking in an RTOS context

    // Step 3: Wake up device (disable SLEEP mode)
    data = 0b00000000;  // Clear SLEEP and enable temp
    status = HAL_I2C_Mem_Write(MPU6050_hi2c, MPU_ADDR, PWR_MGMT_1, I2C_MEMADD_SIZE_8BIT, &data, 1, 1000);
    if (status != HAL_OK) return 1;

    // Step 4: Read the WHO_AM_I register from the MPU-6050
    uint8_t who_am_i = 0;
    status = HAL_I2C_Mem_Read(MPU6050_hi2c, MPU_ADDR, WHO_AM_I_ADDR, I2C_MEMADD_SIZE_8BIT, &who_am_i, 1, 1000);
    if (status != HAL_OK) return 1;

    if (who_am_i != 0x68) return 1;
    return 0;


}

// Checks if the MPU6050 is connected to the I2C bus, returns 0 if successful, 1 if failed
int MPU6050_CheckConnection()
{
    uint8_t who_am_i = 0;
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(MPU6050_hi2c, MPU_ADDR, WHO_AM_I_ADDR, I2C_MEMADD_SIZE_8BIT, &who_am_i, 1, 1000);
    if (status != HAL_OK) return 1;

    if (who_am_i != 0x68) return 1;
    return 0;
}

// Reads X acceleration from the MPU6050, returns the value in m/s^2
float MPU6050_ReadAccelX()
{
    //For our purposes, we will assume that the senstitivty is not modified from its default value of 0 = +/- 2g = 16384 LSB/g

    uint8_t data[2];
    HAL_StatusTypeDef status;

    // Read the high byte
    status = HAL_I2C_Mem_Read(MPU6050_hi2c, MPU_ADDR, ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT, data, 2, 1000);
    if (status != HAL_OK) return 0;

    // Combine the high and low bytes
    int16_t raw_accel = (int16_t)(data[0] << 8 | data[1]);

    // Convert to m/s^2
    return (float)raw_accel / 16384.0f * 9.81f;



}

// Reads Y acceleration from the MPU6050, returns the value in m/s^2
float MPU6050_ReadAccelY()
{
    uint8_t data[2];
    HAL_StatusTypeDef status;

    // Read the high byte
    status = HAL_I2C_Mem_Read(MPU6050_hi2c, MPU_ADDR, ACCEL_YOUT_H, I2C_MEMADD_SIZE_8BIT, data, 2, 1000);
    if (status != HAL_OK) return 0;

    // Combine the high and low bytes
    int16_t raw_accel = (int16_t)(data[0] << 8 | data[1]);

    // Convert to m/s^2
    return (float)raw_accel / 16384.0f * 9.81f;

}

// Reads Z acceleration from the MPU6050, returns the value in m/s^2
float MPU6050_ReadAccelZ()
{
    uint8_t data[2];
    HAL_StatusTypeDef status;

    // Read the high byte
    status = HAL_I2C_Mem_Read(MPU6050_hi2c, MPU_ADDR, ACCEL_ZOUT_H, I2C_MEMADD_SIZE_8BIT, data, 2, 1000);
    if (status != HAL_OK) return 0;

    // Combine the high and low bytes
    int16_t raw_accel = (int16_t)(data[0] << 8 | data[1]);

    // Convert to m/s^2
    return (float)raw_accel / 16384.0f * 9.81f;



}


// Reads the temperature from the MPU6050, returns the value in degrees C
float MPU6050_ReadTemp()
{
    uint8_t data[2];
    HAL_StatusTypeDef status;

    // Read the high byte
    status = HAL_I2C_Mem_Read(MPU6050_hi2c, MPU_ADDR, TEMP_OUT_H, I2C_MEMADD_SIZE_8BIT, data, 2, 1000);
    if (status != HAL_OK) return 0;

    // Combine the high and low bytes
    int16_t raw_temp = (int16_t)(data[0] << 8 | data[1]);

    // Convert to degrees C
    return (float)raw_temp / 340.0f + 36.53f;
}

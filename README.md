## Overview
As part of my lead position in the University of Toronto Aerospace Team (UTAT) rocketry division, I am responsible for educating and distributing tasks for the hardware and firmware system of the rocket avionics system. Since firmware drivers can be daunting, especially in the context of an STM32 embedded environment, I decided to write this very basic example driver for the MPU6050 Accelerometer/Gyroscope as a reference/example for firmware members to learn from. This is a relatively small project purely for internal education purposes, but I have also uploaded it here in case anyone finds it useful.

## Demo
Below is a demo video of the driver running on an STM32 NUCLEO-L4R5ZI development board, sending the data over UART/serial to my desktop computer, where a serial plotting program displays the sensor outputs over time.

https://github.com/user-attachments/assets/2aa90332-7b03-4e4a-a117-abae79cce78d


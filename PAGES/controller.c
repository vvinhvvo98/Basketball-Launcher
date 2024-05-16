/**
 * @file controller.c
 * @brief Controller Component Documentation
 */

/**
 * @page controller_detail CONTROLLER
 * 
 * @section overview FINAL DESIGN
 * The controller will use an STM32 BlackPill microcontroller with an IMU sensor attached to the user's hand. 
 * It will send signals via Bluetooth to the launcher, allowing the launcher to receive the data and rotate according to the IMU sensor's input. 
 * The data transfer includes the velocity of the angles, and the communication uses a UART connection between the HC-05 Bluetooth module. 
 * The controller also features buttons and an indicator LED, all mounted on a 3D-printed handle bracket.   
 * 
 * <img src="control.png" width="1200" height="1000">
 * 
 * PICTURE UPDATE NEEDED
 * 
* @section schematic SCHEMATICS
 * The PDF of this schematic is also attached with higher solution can be found in [PDF SCHEMATIC](schematic1.pdf)
 * Moreover, everything about PCBA design for this project can be found in the repositor link that is mentioned in the mainpage
 * Below are the overall schematic and footprint of the PCBA that is used to integrate the STM32 BlackPill, mpu6050 IMU, HC-05, and LEDs together. 
 * 
 * <img src="PCBCONTROLLER.png" width="1200" height="800">
 * 
 * <img src="PCBCONTROLLERLAYOUT.png" width="1200" height="1500">
 * 
 * @section fsm FINITE STATE MACHINE
 * | State       | Description                                                                                   | Actions                                                                                          | Transitions                                                                                                                                                  |
 * |-------------|-----------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------|
 * | STATE0      | INIT - Attempt to connect, read IMU data, and turn on LED1 if the connection is successful    | - Attempt to connect<br>- Read IMU data<br>- Turn on LED1 if successful                          | - If unsuccessful, transition to **STATE 0A: BLINK LED**<br>- If successful, transition to **STATE 1: IMU READING**                                          |
 * | STATE0A     | BLINK LED - Blink three LEDs to indicate unsuccessful connection                              | - Blink three LEDs                                                                               | - After blinking LEDs, transition back to **STATE 0: INIT**                                                                                                  |
 * | STATE1      | IMU READING - Continuously read IMU data                                                      | - Continuously read IMU data                                                                     | - Always transition to **STATE 2: CHECK BUTTONS STATUS**                                                                                                     |
 * | STATE2      | CHECK BUTTONS STATUS - Check the status of the buttons                                        | - Check buttons status                                                                           | - If button is pushed, transition to **STATE 3: BLUETOOTH TRANSFER**<br>- If button 2 is pushed, turn on LED2 and LED3, and transition to **STATE 2A**<br>- Always transition to **STATE 1: IMU READING** |
 * | STATE2A     | CHECK BUTTONS STATUS - Check the status of the buttons and transfer data continuously         | - Check buttons status<br>- Transfer data                                                        | - Always transition to **STATE 1: IMU READING**                                                                                                              |
 * | STATE3      | BLUETOOTH TRANSFER - Transfer data via Bluetooth                                              | - Transfer data via Bluetooth                                                                    | - Always transition back to **STATE 1: IMU READING**                                                                                                         | 
 *
 * <img src="FSM1.png" width="1200" height="1200"> 
 * 
 * PICTURE UPDATE NEEDED
 * 
 * @section bom BILL OF MATERIAL
 * <div align="center">
 * | Component| Description                                       | Image                                          |
 * | -------- | ------------------------------------------------- | ---------------------------------------------- |
 * | PCBA     | Customized PCBA on top of the handle              | <img src="pcb1.png"   width="200" height="200">|
 * | Handle   | 3D printed handle with thread                     | <img src="brk.png"    width="200" height="200">|
 * | MCU      | STM32 BlackPill microcontroller                   | <img src="bp.png"     width="200" height="200">|
 * | IMU      | mpu6050 6 DOF motion sensor                       | <img src="imu.png"    width="200" height="200">|
 * | Button   | Additional buttons for control the launcher       | <img src="button.png" width="200" height="200">|
 * | Bluetooth| Bluetooth module using UART communication         | <img src="hc05.png"   width="200" height="200">|
 * | LED      | Indicator LED for bluetooth, IMU and ESC status.  | <img src="led.png"    width="200" height="200">|
 * | Resistor | Resistor for LED                                  | <img src="r.png"      width="200" height="200">|
 * </div>
 *
 */

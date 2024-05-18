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
 *  
 * @section schematic CONTROLLER PCBA
 * The PDF of this schematic is also attached with higher solution can be found in [PDF SCHEMATIC](ControllerSchematic.pdf).
 * Moreover, everything about PCBA design for this project can be found in the repositor link that is mentioned in the mainpage, or here for convinient: 
 * https://github.com/vvinhvvo98/Basketball-Launcher/tree/main/Ball_Launcher_Controller
 * Below are the overall schematic and footprint of the PCBA that is used to integrate the STM32 BlackPill, mpu6050 IMU, HC-05, and LEDs together. 
 * 
 * <img src="PCBCONTROLLER.png" width="1200" height="800">
 * 
 * <img src="PCBCONTROLLERLAYOUT.png" width="1200" height="400">
 * 
 * <img src="finalpcb1.png" width="1200" height="400">
 * 
 * @section fsm FINITE STATE MACHINE
 * | State       | Description                                        | Actions                                                | Transitions                                                                                    |
 * |-------------|----------------------------------------------------|--------------------------------------------------------|------------------------------------------------------------------------------------------------|
 * | STATE0      | INIT - Attempt to connect to IMU                   | - Attempt to connect<br> - Turn on LED1 if successful  | - If unsuccessful, transition to **STATE 1**<br> - If successful, transition to **STATE 2**    |
 * | STATE1      | ERROR- Failed to connecto IMU                      | - Toggle LED1 if failed to connect to the IMU          | - Always transition to **STATE 0**                                                             |
 * | STATE2      | IMU  - Read data from the IMU                      | - Continuosly read the data from the IMU               | - Always transition to **STATE 3**                                                             |
 * | STATE3      | BUTTON_LED - Read buttons & update LEDs            | - Countinously read the button<br> - Update the LEDs   | - Always transition back to **STATE 4**                                                        | 
 * | STATE4      | TRANSFER   - Send data to UART1 and UART6          | - Send data to UART1 (bluetooth)<br> - UART6 (debug)   | - Always transition back to **STATE 2**                                                        | 
 * 
 * <img src="FSM1.png" width="1200" height="800"> 
 * 
 * 
 * @section bomm5 BILL OF MATERIAL - 3D PRINTED PARTS
 * Most of the 3D printed parts are printed using BambuLab XC1 3D printer. Moreover, and BambuLab filaments. 
 * All the CAD 3D model files can be found here for reference: https://github.com/vvinhvvo98/Basketball-Launcher/tree/main/CAD 
 * 
 * 
 * @section bome2 BILL OF MATERIAL - ELECTRONICS
 * All of the components for electronics are listed in the attached PDF file here: [BOM EXCEL](BILL_OF_MATERIAL.xlsx)
 * 
 */

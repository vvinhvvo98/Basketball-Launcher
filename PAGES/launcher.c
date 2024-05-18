/**
 * @file launcher.c
 * @brief Launcher Component Documentation
 */

/**

 * @page launcher_detail LAUNCHER
 * 
 * @section overview1 FINAL DESIGN
 * The launcher will be the main assembly, receiving data from the controller and moving in 2 degrees of freedom (yaw and pitch angles). 
 * It will then shoot the basketball when the controller sends out signals. The launcher will use a customized PCBA centered around the STM32F401CEU6 chip, which will act as the core component to determine movement.
 * The launcher includes a cycloidal gearbox and stepper motors with a planetary gearbox for precise movement control. 
 * Additionally, the launcher is equipped with brushless motors and 3 limit switches to ensure accurate positioning.
 * 
 * <img src="launcher.png" width="1200" height="1250">
 * PICTURE UPDATE NEEDED
 * 
 * @section schematic1 LAUNCHER PCBA
 * The PDF of this schematic is also attached with higher solution can be found in [PDF SCHEMATIC](LauncherSchematic.pdf).
 * Moreover, everything about PCBA design for this project can be found in the repositor link that is mentioned in the mainpage, or here for convinient: 
 * https://github.com/vvinhvvo98/Basketball-Launcher/tree/main/Ball_Launcher_Launcher.  
 * Below are the all of the PCB schematic contains total of 4 pages describe in the table below 
 * 
 * <div align="center">
 * | Page| Description                                                                                | 
 * | --- | ------------------------------------------------------------------------------------------ | 
 * |  1  | Power source schematic for power the pcb, drivers, mcu, etc                                |
 * |  2  | All connection to power and program for STM32F401CEU6 chip                                 | 
 * |  3  | All connection to power and program for DRV8825 stepper motor driver                       |
 * |  4  | Additional pins + test pads and connectors for limit switches + stepper motors             | 
 * </div>
 * 
 * <img src="p1.png" width="1200" height="800">
 * 
 * <img src="p2.png" width="1200" height="800">
 * 
 * <img src="p3.png" width="1200" height="800">
 * 
 * <img src="p4.png" width="1200" height="800">
 * 
 * <img src="fppf.png" width="1200" height="600">
 * 
 * <img src="finalpcb2.png" width="1200" height="400">
 * 
 * @section fsm1 FINITE STATE MACHINE
 * | State       | Description                                                                                   | Actions                                                                                          | Transitions                                                                                                                                                  |
 * |-------------|-----------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------|
 * | STATE0      | INIT - Attempt to connect, read IMU data, and turn on LED1 if the connection is successful    | - Attempt to connect<br>- Read IMU data<br>- Turn on LED1 if successful                          | - If unsuccessful, transition to **STATE 0A: BLINK LED**<br>- If successful, transition to **STATE 1: IMU READING**                                          |
 * | STATE0A     | BLINK LED - Blink three LEDs to indicate unsuccessful connection                              | - Blink three LEDs                                                                               | - After blinking LEDs, transition back to **STATE 0: INIT**                                                                                                  |
 * | STATE1      | IMU READING - Continuously read IMU data                                                      | - Continuously read IMU data                                                                     | - Always transition to **STATE 2: CHECK BUTTONS STATUS**                                                                                                     |
 * | STATE2      | CHECK BUTTONS STATUS - Check the status of the buttons                                        | - Check buttons status                                                                           | - If button is pushed, transition to **STATE 3: BLUETOOTH TRANSFER**<br>- If button 2 is pushed, turn on LED2 and LED3, and transition to **STATE 2A**<br>- Always transition to **STATE 1: IMU READING** |
 * | STATE2A     | CHECK BUTTONS STATUS - Check the status of the buttons and transfer data continuously         | - Check buttons status<br>- Transfer data                                                        | - Always transition to **STATE 1: IMU READING**                                                                                                              |
 * | STATE3      | BLUETOOTH TRANSFER - Transfer data via Bluetooth                                              | - Transfer data via Bluetooth                                                                    | - Always transition back to **STATE 1: IMU READING**                                                                                                         | 
 * 
 * TABLE UPDATE NEEDED
 * 
 * <img src="FSM2.png" width="1200" height="1000"> 
 * 
 * 
 * @section bomm4 BILL OF MATERIAL - 3D PRINTED PARTS
 * Most of the 3D printed parts are printed using BambuLab XC1 3D printer and BambuLab filaments. 
 * All the CAD 3D model files can be found here for reference: https://github.com/vvinhvvo98/Basketball-Launcher/tree/main/CAD 
 *
 *  
 * @section bome22 BILL OF MATERIAL - ELECTRONICS
 * All of the components for electronics are listed in the attached PDF file here: [BOM EXCEL](BILL_OF_MATERIAL.xlsx)
 * 
 * 
 * @section bomm1 BILL OF MATERIAL - MECHANICAL
 * <div align="center">
 * 
 * | Components              | Description                              | Image                                                  |
 * | ----------------------- | ---------------------------------------- | ------------------------------------------------------ |
 * | NEMA17                  | NEMA17 stepper motor                     | <img src="nema17.png" width="250" height="250">        |
 * | NEMA17 + GEAR BOX       | NEMA17 stepper motor + planetary gearbox | <img src="nema17_gearbox.png" width="250" height="250">|
 * | D4215 BLDC              | D4215 BLDC 650 Kvmotor                   | <img src="d4215_bldc.png" width="250" height="250">    |
 * | UBEC ESC                | Hobby ESC control for BLDC               | <img src="ubec_esc.png" width="250" height="250">      |
 * | O-RING                  | Friction O-Ring                          | <img src="o_ring.png" width="250" height="250">        |
 * | SWITCH                  | Switch for BLDC                          | <img src="switch.png" width="250" height="250">        |
 * | BASKETBALL              | 5 inches basketball                      | <img src="basketball.png" width="250" height="250">    |
 * | LIMIT SWITCH            | Limit switches for safety                | <img src="limit_switch.png" width="250" height="250">  |
 * | BATTERY                 | Lipo battery 11.1 V                      | <img src="battery.png" width="250" height="250">       |
 *
 * </div>
 * 
 * 
 * @section bomm3 BILL OF MATERIAL - CYCLOIDAL GEARBOX
 * <div align="center">
 * <img src="CG.png" width="800" height="800"> 
 * <iframe width="420" height="315" src="https://www.youtube.com/embed/VXcm26m4MQA" frameborder="0" allowfullscreen></iframe>
 * <a href="https://www.youtube.com/watch?v=VXcm26m4MQA&list=PPSV" target="_blank"> Cycloidal GearBox Animation</a>
 * | Components | Description                          | Image                                               |
 * | -----------| -----------------------------------  | ----------------------------------------------------|
 * | Bearing    | OD = 55 mm + ID = 35 mm + t = 10 mm  | <img src="45bearing.png" width="250" height="250">  |
 * | Bearing    | OD = 47 mm + ID = 35 mm + t =  7 mm  | <img src="35bearing.png" width="250" height="250">  |
 * | Bearing    | OD = 37 mm + ID = 25 mm + t =  7 mm  | <img src="25bearing.png" width="250" height="250">  |
 * | Bearing    | OD = 15 mm + ID =  6 mm + t =  5 mm  | <img src="6bearing.png" width="250" height="250">   |
 * | Bolt       | M6         +  L = 70 mm  + Bolt      | <img src="bolt.png" width="250" height="250">       |
 * | Nut        | M6         +  t =  5 mm  + Nut       | <img src="nut.png" width="250" height="250">        |
 * | Nut        | M6         +  t =  5 mm  + Lock Nut  | <img src="locknut.png" width="250" height="250">    |
 * </div>
 * 
 *
 *  
 */

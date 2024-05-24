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
 * <div class="image-frame">
 * <a href=https://vvinhvvo98.github.io/Basketball-Launcher/launcher_detail.html>
 *      <img src="launcher.png" width="1200" height="1250" style="border: 10px solid black; border-radius: 50px;">
 * </a>
 * </div>
 * 
 * --> UPDATE PICTURE
 * 
 * @section schematic1 LAUNCHER PCBA
 * This PCB is the main component of the project, serving as the centerpiece of the launcher. It operates the launcher based on commands received from the controller
 * The PDF of this schematic is also attached with higher solution can be found in <a href="LauncherSchematic.pdf" target="_blank" style="color: blue; font-size: 15px; font-weight: bold; text-decoration: none; padding: 8px; background-color: yellow; border: 1px solid black; border-radius: 5px;">PDF SCHEMATIC</a>. 
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
 * <div class="image-frame">
 *   <a href="LauncherSchematic.pdf" target="_blank">
 *       <img src="p1.png" width="1200" height="800" style="border: 10px solid black; border-radius: 10px;">
 *   </a>
 * </div>
 * 
 * <div class="image-frame">
 *   <a href="LauncherSchematic.pdf" target="_blank">
 *       <img src="p2.png" width="1200" height="800" style="border: 10px solid black; border-radius: 10px;">
 *   </a>
 * </div>
 * 
 *  <div class="image-frame">
 *   <a href="LauncherSchematic.pdf" target="_blank">
 *       <img src="p3.png" width="1200" height="800" style="border: 10px solid black; border-radius: 10px;">
 *   </a>
 * </div>
 * 
 * <div class="image-frame">
 *   <a href="LauncherSchematic.pdf" target="_blank">
 *       <img src="p1.png" width="1200" height="800" style="border: 10px solid black; border-radius: 10px;">
 *   </a>
 * </div>
 * 
 * 
 * <div class="image-frame">
 * <img src="fppf.png" width="1200" height="500" style="border: 10px solid black; border-radius: 50px;">
 * </div>
 * 
 * <div class="image-frame">
 * <img src="finalpcb2.png" width="1200" height="1000" style="border: 10px solid black; border-radius: 50px;">
 * </div>
 * 
 * 
 *@section fsm1 FINITE STATE MACHINE
 *| State       | Description                                     | Actions                                           | Transitions                                                                                                   |
 *|-------------|-------------------------------------------------|---------------------------------------------------|-----------------------------------------------------------------------------------------------------------------|
 *| STATE0      | INIT                                            | - Init all objects in the system                  | - Always transition to **STATE1**                                                                               |
 *| STATE1      | DECISION HUB                                    | - Jump to different state according to condition  | - Move to **STATE3** if MOVE == 1 & SHOT == 0 <br> - Move to **STATE4** if SHOT == 1 & MOVE == 0 <br> - Move to **STATE3** if hit any switches <br> - Move to **STATE2** if ESTOP == 1 |
 *| STATE2      | ESTOP                                           | - Stop all objects in the system & wait for reset | - Move to **STATE1** if dt >= 5000 <br> - Stay in **STATE2** if dt < 5000                                        |
 *| STATE3      | STEPPER RUN                                     | - Running stepper motors                          | - Always move to **STATE1**                                                                                     |
 *| STATE4      | BLDC RUN                                        | - Running BLDC motors                             | - Always move to **STATE1**

 * 
 * <img src="FSM2.png" width="1200" height="500"> 
 * 
 * 
 * 
 * @section bomm3 BILL OF MATERIAL - CYCLOIDAL GEARBOX
 * <div align="center">
 * 
 * <a href="https://www.youtube.com/playlist?list=PLlT9z-PWNXdMvf3wya2C2y9n_Qta7UkEB" target="_blank" style="color: blue; font-size: 20px; font-weight: bold; text-decoration: none; padding: 10px; background-color: yellow; border: 2px solid black; border-radius: 5px;">CYCLOIDAL GEARBOX DEMONSTRATION</a>
 * 
 * 
 * <img src="CG.png" width="800" height="800"> 
 * 
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
 * @section bomm5 BILL OF MATERIAL - 3D PRINTED PARTS
 * Most of the 3D printed parts are printed using BambuLab XC1 3D printer and BambuLab filaments. 
 * All the CAD 3D model files can be found here for reference:
 * <div class="image-frame">
 * <a href=https://github.com/vvinhvvo98/Basketball-Launcher/tree/main/CAD>
 *      <img src="solidworks.png" width="250" height="250" style="border: 10px solid black; border-radius: 50px;">
 * </a>
 * </div>
 * 
 * @section bome2 BILL OF MATERIAL - ELECTRONICS
 * All of the components for electronics are listed in the attached PDF file here below
 * <div class="image-frame">
 *   <a href="BILL_OF_MATERIAL.xlsx" target="_blank">
 *       <img src="bom.png" width="250" height="200" style="border: 10px solid black; border-radius: 10px;">
 *   </a>
 * </div>
 *
 *  
 */

/**
 * @file mainpage.c
 * @brief Main Page Documentation for Project
 */

/**
 * @mainpage MAIN PAGE
 *
 * <div class="image-frame">
 * <img src="FINAL.png" width="1200" height="1200" style="border: 10px solid black; border-radius: 50px;">
 * </div>
 *
 * <br> <!---->
 *
 * @section motivation MOTIVATION
 * The motivation for this project is to build a prototype for a full-scale basketball-playing robot.
 * The project will start with a small-scale version to test the concept and gather insights for future improvements.
 * This approach will provide an opportunity to develop customized PCBAs that can control the robot for its intended purposes.
 * 
 * <br> <!---->
 *
 * @section detail OBJECTIVE
 * The objective of the project includes integrating the mechanical design with PCBA electronic component.
 * This project will primarily use 3D-printed parts, along with shafts and bearings to support the robot's housing.
 * The PCBAs will be designed using Fusion 360 software and manufactured by JLCPCB.
 * The programming for the STM32 microcontroller will be done using the C language.
 *
 * Note: The image below is provided solely for illustrative purposes and does not represent the actual project.
 * 
 * <div class="image-frame">
 * <img src="idea.png" width="1200" height="1000" style="border: 10px solid black; border-radius: 50px;">
 * </div>
 *
 * The project is divided into two main assemblies:
 *
 * - The controller will use an STM32 BlackPill microcontroller with an IMU sensor attached to the user's hand.
 * The controller will send signals via Bluetooth to the launcher, allowing the launcher to receive the data and spin according to the IMU sensor's input.
 * 
 * - The launcher will be the main assembly, receiving data from the controller and moving in 2 degrees of freedom (yaw and pitch angles). 
 * It will then shoot the basketball when the controller send launching flag. 
 * The launcher will use a customized PCBA centered around the STM32F401CEU6 chip, which will act as the core component to determine movement.
 *  
 * <br> <!---->
 *
 * @section design IDEATION DESIGN
 * 
 * The overall design of the two main assemblies in the project is sketched and listed below for reference.
 * The sketch represents a rough idea of how all components are connected and communicate with each other.
 * The PDF of the sketch is also attached with higher solution can be found in by access through the picture below
 * 
 * <div class="image-frame">
 *   <a href="OverallDesign.pdf" target="_blank">
 *       <img src="overall.png" width="1200" height="750" style="border: 10px solid black; border-radius: 50px;">
 *   </a>
 * </div>
 * 
 * <br> <!---->
 *
 * @section cad CAD MODELING
 * The design is inspired by the Peashooter from the Plants vs. Zombies mobile game. 
 * In terms of mechanical design, custom machined parts are limited to facilitate rapid prototyping and maintain focus on electronics and programming. Most custom parts will be 3D printed to save time and effort, except for bearings and shafts, which will be purchased from McMaster-Carr as off-the-shelf components.
 * The CAD modeling phase of the project was completed early to allow the main focus to be on electronics and program implementation. The CAD figure below shows the final design of the launcher. The SolidWorks CAD model can access through the CAD sketch below.
 *
 * <div class="image-frame">
 * <a href=https://github.com/vvinhvvo98/Basketball-Launcher/tree/main/CAD>
 *      <img src="CAD.png" width="1200" height="900" style="border: 10px solid black; border-radius: 50px;">
 * </a>
 * </div>
 * <br> <!---->
 *
 * @section launcher LAUNCHER
 * 
 * The launcher will be the main assembly, receiving data from the controller and moving in 2 degrees of freedom (yaw and pitch angles). 
 * It will then shoot the basketball when the controller sends out signals. The launcher will use a customized PCBA centered around the STM32F401CEU6 chip, which will act as the core component to determine movement.
 * The launcher includes a cycloidal gearbox and stepper motors with a planetary gearbox for precise movement control. 
 * Additionally, the launcher is equipped with brushless motors and 3 limit switches to ensure accurate positioning.
 * More detail about the launcher Bill of Materials, design, source code can be found by access through the launcher picture below:
 *
 * <div class="image-frame">
 * <a href=https://vvinhvvo98.github.io/Basketball-Launcher/launcher_detail.html>
 *      <img src="launcher.png" width="1200" height="600" style="border: 10px solid black; border-radius: 50px;">
 * </a>
 * </div>
 * 
 * <br> <!---->
 * 
 * @section controller CONTROLLER
 * The controller will use an STM32 BlackPill microcontroller with an IMU sensor attached to the user's hand. 
 * It will send signals via Bluetooth to the launcher, allowing the launcher to receive the data and rotate according to the IMU sensor's input. 
 * The data transfer includes the velocity of the angles, and the communication uses a UART connection between the HC-05 Bluetooth module. 
 * The controller also features buttons and an indicator LED, all mounted on a 3D-printed handle bracket.
 * More detail about the controller's Bill of Materials, design, source code can be found by access through the launcher picture below:
 *
 * <div class="image-frame">
 * <a href=https://vvinhvvo98.github.io/Basketball-Launcher/controller_detail.html>
 *      <img src="control.png" width="1200" height="500" style="border: 10px solid black; border-radius: 50px;">
 * </a>
 * </div>
 *
 * <br> <!---->
 *
 * @section improve FUTURE IMPROVEMENT
 * Even though, the project is built and run appropriately according to the project's objectives. The following improvements can be considered for future version.
 * Especially, for the upcoming full scale basketball launcher
 * - Improve the IMU to a 9 DOF sensor that can sense accurate absolute angle
 * - Improve stronger stepper driver that can allow faster and stronger rotation motion
 * - Increase moving angle of the launcher to more than 120°
 * 
 * <br> <!---->
 * 
 * @section demo_day CAL POLY DEMONSTRATION DAY
 * <div class="image-frame">
 * <img src="DSC02620.jpg" width="1200" height="700" style="border: 10px solid black; border-radius: 50px;">
 * </div>
 * 
 * <br> <!---->
 *
 * @section youtube YOUTUBE REFERENCE
 *
 * <div class="image-frame">
 * <a href=https://www.youtube.com/playlist?list=PLlT9z-PWNXdP43BUYpBcqznBU4_-Bkpg8>
 *      <img src="youtube.png" width="250" height="250" style="border: 10px solid black; border-radius: 50px;">
 * </a>
 * </div>
 *
 * <br> <!---->
 *
 * @section repository REPOSITORY REFERENCE
 *
 * You may find it more useful to read through the website exploring the source code.
 * All code that will be referenced in this portfolio relate to project is accessible through:
 *
 *
 * <div class="image-frame">
 * <a href=https://github.com/vvinhvvo98/Basketball-Launcher>
 *      <img src="github.png" width="250" height="250" style="border: 10px solid black; border-radius: 50px;">
 * </a>
 * </div>
 * 
 *
 * NOTE: You may find the Controller's code with a small specification "_C" at the end of the file  that stands for Controller code. 
 * Files' name and the files' header code need to be renamed without that term in case the projects are recreated.
 * The inconvenience is due to the drawback of uploading codes in 2 projects to one GitHub Repository.
 *
 * For example:
 * 
 * - main_C.c means the main code file for the controller. Needs to be changed to main.c before running in any IDE.
 * 
 * <br> <!---->
 *
 * @section info CONTACT INFO
 * 
 * <pre>   
 * <b>Author:</b>         Vinh Vo
 * 
 * <b>Email:</b>          vinhvo.career@gmail.com
 * 
 * <b>LinkedIn:</b>       https://www.linkedin.com/in/vinhvo98/
 * 
 * <b>Youtube:</b>        https://www.youtube.com/channel/UCh_4F4CJVqvAhHmCMTvIb-w   
 * 
 * <b>Major:</b>          MS Mechanical Engineer at Cal Poly San Luis Obispo
 * 
 * <b>Date:</b>           May 15, 2024
 * </pre>
 */

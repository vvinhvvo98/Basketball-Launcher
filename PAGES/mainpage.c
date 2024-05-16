/**
 * @file mainpage.c
 * @brief Main Page Documentation for Project
 */

/**
 * @mainpage MAIN PAGE
 *
 * 
 * @section motivation MOTIVATION
 * The motivation for this project is to build a prototype for a full-scale basketball-playing robot.
 * The project will start with a small-scale version to test the concept and gather insights for future improvements.
 * This approach will provide an opportunity to develop customized PCBAs that can control the robot for its intended purposes.
 * 
 * 
 * @section detail OBJECTIVE
 * The objective of the project includes integrating the mechanical design with PCBA electronic component.
 * This project will primarily use 3D-printed parts, along with shafts and bearings to support the robot's housing.
 * The PCBAs will be designed using Fusion 360 software and manufactured by JLCPCB.
 * The programming for the STM32 microcontroller will be done using the C language.
 * 
 * <img src="idea.png" width="1200" height="1200">
 
 * The project is divided into two main assemblies:
 *
 * - The controller will use an STM32 BlackPill microcontroller with an IMU sensor attached to the user's hand.
 * The controller will send signals via Bluetooth to the launcher, allowing the launcher to receive the data and rotate according to the IMU sensor's input.
 * 
 * - The launcher will be the main assembly, receiving data from the controller and moving in 2 degrees of freedom (yaw and pitch angles). 
 * It will then shoot the basketball when the controller signals it. 
 * The launcher will use a customized PCBA centered around the STM32F401CEU6 chip, which will act as the core component to determine movement.
 *  
 * 
 * @section design DESIGN
 * The design is inspired by the Peashooter from the Plants vs. Zombies mobile game. 
 * The overall design of the two main assemblies in the project is sketched and listed below for reference.
 * The sketch represents a rough idea of how all components are connected and communicate with each other.
 * The PDF of the sketch is also attached with higher solution can be found in [PDF Sketch](overall.pdf)
 * 
 * @image html overall.png
 * 
 * 
 * @section launcher LAUNCHER
 * 
 * The launcher will be the main assembly, receiving data from the controller and moving in 2 degrees of freedom (yaw and pitch angles). 
 * It will then shoot the basketball when the controller sends out signals. The launcher will use a customized PCBA centered around the STM32F401CEU6 chip, which will act as the core component to determine movement.
 * The launcher includes a cycloidal gearbox and stepper motors with a planetary gearbox for precise movement control. 
 * Additionally, the launcher is equipped with brushless motors and 3 limit switches to ensure accurate positioning.
 * More detail about the launcher Bill of Materials, design, source code can be found in:
 * \ref launcher_detail "LAUNCHER"
 * 
 * <img src="launcher.png" width="1200" height="1250">
 * 
 * PICTURE UPDATE NEEDED
 * 
 * 
 * @section controller CONTROLLER
 * The controller will use an STM32 BlackPill microcontroller with an IMU sensor attached to the user's hand. 
 * It will send signals via Bluetooth to the launcher, allowing the launcher to receive the data and rotate according to the IMU sensor's input. 
 * The data transfer includes the velocity of the angles, and the communication uses a UART connection between the HC-05 Bluetooth module. 
 * The controller also features buttons and an indicator LED, all mounted on a 3D-printed handle bracket.
 * More detail about the controller's Bill of Materials, design, source code can be found in:
 * \ref controller_detail "CONTROLLER"
 * 
 * <img src="control.png" width="1200" height="1000">
 * 
 * PICTURE UPDATE NEEDED
 * 
 * 
 * @section improve FUTURE IMPROVEMENT
 * Even though, the project is built and run appropriately according to the project's objectives. The following improvements can be considered for future version.
 * Especially, for the upcoming full scale basketball launcher
 * - Improve the IMU to a 9 DOF sensor that can sense accurate absolute angle
 * - Improve stronger stepper driver that can allow faster and stronger rotation motion
 * - Increase moving angle of the launcher to more than 120°
 * 
 * 
 * @section youtube YOUTUBE REFERENCE
 * YOUTUBE LINK UPDATE NEEDED <---------------------------------------------------
 * 
 * 
 * @section repository REPOSITORY REFERENCE
 * All code that will be referenced in this portfolio relate to project is accessible through https://github.com/vvinhvvo98/Basketball-Launcher
 * 
 * However, you may find it more useful to read through the website exploring the source code.
 * 
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
 * <b>Phone Number:</b>   +1(714)-988-5363    
 * 
 * <b>Major:</b>          Mechanical Engineer at Cal Poly San Luis Obispo
 * 
 * <b>Date:</b>           May 15, 2024
 * </pre>
 */

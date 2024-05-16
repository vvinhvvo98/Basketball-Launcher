/**
 * @file mainpage.c
 * @brief Main Page Documentation for Project
 */

/**
 * @mainpage MAIN PAGE
 *
 * @section motivation MOTIVATION
 * The motivation for this project is to build a prototype for a full-scale basketball-playing robot.
 * The project will start with a small-scale version to test the concept and gather insights for future improvements.
 * This approach will provide an opportunity to develop customized PCBAs that can control the robot for its intended purposes.
 * 
 * @section detail OBJECTIVE
 * The objective of the project includes integrating the mechanical design with PCBA electronic components and programming aspects using the C programming language.
 * This project will primarily use 3D-printed parts, along with shafts and bearings to support the robot's housing. 
 * The PCBAs will be designed using Fusion 360 software and manufactured by JLCPCB. 
 * The programming will be done on an STM32 microcontroller using the C language.
 * 
 * The project is divided into two main assemblies:
 *
 * - The controller will use an STM32 BlackPill microcontroller with an IMU sensor attached to the user's hand.
 * The controller will send signals via Bluetooth to the launcher, allowing the launcher to receive the data and rotate according to the IMU sensor's input.
 * 
 * - The launcher will be the main assembly, receiving data from the controller and moving in 2 degrees of freedom (yaw and pitch angles). 
 * It will then shoot the basketball when the controller signals it. 
 * The launcher will use a customized PCBA centered around the STM32F401CEU6 chip, which will act as the core component to determine movement.
 *  
 * @section design DESIGN
 * The design is inspired by the Peashooter from the Plants vs. Zombies mobile game. 
 * The overall design of the two main assemblies in the project is sketched and listed below for reference.
 * The sketch represents a rough idea of how all components are connected and communicate with each other.
 * The PDF of the sketch is also attached with higher solution can be found in [PDF Sketch](overall.pdf)
 * @image html overall.png
 * 
 * @section controller CONTROLLER
 * More detail about the controller's Bill of Materials and source code can be found in:
 * \ref controller_detail "CONTROLLER"
 * <img src="control.png" width="1200" height="1000">
 * 
 * UPDATE
 * 
 * @section launcher LAUNCHER
 * More detail about the launcher Bill of Materials and source code can be found in:
 * \ref launcher_detail "LAUNCHER"
 * <img src="launcher.png" width="1200" height="1250">
 * 
 * UPDATE
 * 
 * 
 * @section improve FUTURE IMPROVEMENT
 * LIST OF FUTURE IMPROVEMENT <---------------------------------------------------
 * 
 * @section youtube YOUTUBE REFERENCE
 * YOUTUBE LINK <---------------------------------------------------
 * 
 * @section repository REPOSITORY REFERENCE
 * LIST OF FUTURE IMPROVEMENT <---------------------------------------------------
 */

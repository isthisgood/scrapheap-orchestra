/**     ___           ___           ___                         ___           ___     
 *     /__/\         /  /\         /  /\         _____         /  /\         /__/|    
 *    |  |::\       /  /::\       /  /::|       /  /::\       /  /::\       |  |:|    
 *    |  |:|:\     /  /:/\:\     /  /:/:|      /  /:/\:\     /  /:/\:\      |  |:|    
 *  __|__|:|\:\   /  /:/~/::\   /  /:/|:|__   /  /:/~/::\   /  /:/  \:\   __|__|:|    
 * /__/::::| \:\ /__/:/ /:/\:\ /__/:/ |:| /\ /__/:/ /:/\:| /__/:/ \__\:\ /__/::::\____
 * \  \:\~~\__\/ \  \:\/:/__\/ \__\/  |:|/:/ \  \:\/:/~/:/ \  \:\ /  /:/    ~\~~\::::/
 *  \  \:\        \  \::/          |  |:/:/   \  \::/ /:/   \  \:\  /:/      |~~|:|~~ 
 *   \  \:\        \  \:\          |  |::/     \  \:\/:/     \  \:\/:/       |  |:|   
 *    \  \:\        \  \:\         |  |:/       \  \::/       \  \::/        |  |:|   
 *     \__\/         \__\/         |__|/         \__\/         \__\/         |__|/   
 *
 *  Description: 
 *				 
 *  constants.h, created by Marek Bereza on 30/07/2012.
 */

#pragma once

// some pin defs

// the tx pin (digital pin 1)
#define TXD 1


#define STEP1 A1
#define STEP2 A3
#define STEP3 A5
#define STEP4 4

#define DIR1 A0
#define DIR2 A2
#define DIR3 A4
#define DIR4 7



#define FET1 5
#define FET2 6
#define FET3 9
#define FET4 10

// these are on shift register pins
#define EN1 7
#define EN2 6
#define EN3 5
#define EN4 4

// likewise these are shift
#define LED1 15
#define LED2 14
#define LED3 13
#define LED4 12
#define LED5 11
#define LED6 10
#define LED7 9
#define LED8 8

// optoisolators
#define OP1	3
#define OP2	2
#define OP3	1
#define OP4	0
//These are the pins that will talk to the shift register through SPI
#define SDI    11    //Data
#define CLK    13    //Clock
#define LE     12    //Latch

#define LEDEN 8 // active low (activate shift register enble)

#define LIMIT1 2
#define LIMIT2 3
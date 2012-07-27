/// 
/// @mainpage	Brother 
/// @details	<#details#>
/// @n 
/// @n 
/// @n @a	Developed with [embedXcode](http://embedXcode.weebly.com)
/// 
/// @author	Neil Mendoza
/// @author	__MyCompanyName__
/// @date	27/07/2012 11:34
/// @version	<#version#>
/// 
/// @copyright	© Neil Mendoza, 2012
/// @copyright	CC = BY NC SA
///
/// @see	ReadMe.txt for references
///


// Core library - IDE-based
#if defined(WIRING) // Wiring specific
#include "Wiring.h"
#elif defined(MAPLE_IDE) // Maple specific
#include "WProgram.h"   
#elif defined(MPIDE) // chipKIT specific
#include "WProgram.h"
#elif defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#elif defined(ARDUINO) && (ARDUINO >= 100) // Arduino 1.0 specific
#include "Arduino.h"
#elif defined(ARDUINO) && (ARDUINO < 100) // Arduino 23 specific
#include "WProgram.h"
#endif


// Include application, user and local libraries
#include "LocalLibrary.h"


// Define variables and constants
///
/// @brief	Name of the LED
/// @details	Each board has a LED but connected to a different pin
///
uint8_t LED1;


///
/// @brief	Setup
/// @details	Define the pin the LED is connected to
///
// Add setup code 
void setup() {
    // LED1 pin number
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__) // Arduino specific
    LED1 = 13; 
#elif defined(__PIC32MX__) // chipKIT specific
    LED1 = 13;
#elif defined(__AVR_ATmega644P__) // Wiring specific
    LED1 = 15; 
#elif defined(__MSP430G2452__) || defined(__MSP430G2553__) || defined(__MSP430G2231__) // LaunchPad specific
    LED1 = 2; 
#elif defined(MCU_STM32F103RB) || defined(MCU_STM32F103ZE) || defined(MCU_STM32F103CB) || defined(MCU_STM32F103RE) // Maple specific
    LED1 = BOARD_LED_PIN; 
#endif

    pinMode(LED1, OUTPUT);     
}

///
/// @brief	Loop
/// @details	Call blink
///
// Add loop code 
void loop() {
  blink(LED1, 3, 333);
  delay(2000);    
}

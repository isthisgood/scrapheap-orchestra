/// 
/// @mainpage	Brother 
/// @details	<#details#>
/// @n 
/// @n 
/// @n @a	Developed with [embedXcode]( http://embedXcode.weebly.com )
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


#include "Arduino.h"
//#include "EEPROM.h"

// Include application, user and local libraries
#include "LocalLibrary.h"
#include "StepOsc.h"
#include "OscUtils.h"
#include "Osc.h"
#include "Runner.h"
#include "MidiMap.h"
#include "PWMOsc.h"
#include "RandOsc.h"
#include "Midi.h"
#include "VelOsc.h"
#include "Switcher.h"
#include "ShiftRegister.h"
#include "constants.h"
#include "ShiftSwitcher.h"



void setup() {

    
    // addStepOsc(midimap(CHANNEL_1), 8, 9, 10, 11);
    //addVelOsc(midimap(CHANNEL_1), 12);
    //addSwitcher(midimap(CHANNEL_2), 13);
    //addOsc(midimap(CHANNEL_4), 4);
    
    //addSimpleStepperOsc(midimap(CHANNEL_1), );
    
   
    
    initRunner();
	
	
	//addShiftSwitcher(midimap(CHANNEL_1), LED1);
////	addShiftSwitcher(midimap(CHANNEL_2), LED2);
	//addShiftSwitcher(midimap(CHANNEL_3), LED3);
	//addShiftSwitcher(midimap(CHANNEL_4), LED4);

	addShiftSwitcher(midimap(CHANNEL_1), LED1);
	addShiftSwitcher(midimap(CHANNEL_2), LED2);
	addShiftSwitcher(midimap(CHANNEL_3), LED3);
	addShiftSwitcher(midimap(CHANNEL_4), LED4);
	
	
	/*int id = EEPROM.read(0);
    id = 1;
    switch (id)
    {
        case 0:
            break;
		case 1:
			addShiftSwitcher(midimap(CHANNEL_1), LED1);
            addShiftSwitcher(midimap(CHANNEL_2), LED2);
            addShiftSwitcher(midimap(CHANNEL_3), LED3);
            addShiftSwitcher(midimap(CHANNEL_4), LED4);
			break;
        default:
            addOsc(midimap(CHANNEL_1), FET1);
            addOsc(midimap(CHANNEL_2), FET2);
            addOsc(midimap(CHANNEL_3), FET3);
            addOsc(midimap(CHANNEL_4), FET4);
            break;
    }*/
	
	//addStepOsc(midimap(5), , <#int pinB#>, <#int pinC#>, <#int pinD#>)
	
}

void loop() {
    runRunner();
}

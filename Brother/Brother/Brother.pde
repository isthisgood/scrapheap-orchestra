/// 
/// @mainpage	Brother 
/// @details	details
/// @n 
/// @n 
/// @n @a	Developed with [embedXcode]( http://embedXcode.weebly.com )
/// 
/// @author	Neil Mendoza
/// @author	__MyCompanyName__
/// @date	27/07/2012 11:34
/// @version	version
/// 
/// @copyright	© Neil Mendoza, 2012
/// @copyright	CC = BY NC SA
///
/// @see	ReadMe.txt for references
///


#include "Arduino.h"
#include "EEPROM.h"

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
#include "SimpleStepOsc.h"
#include "DirStepOsc.h"
#include "SimpleStepOsc.h"
#include "FloppyOsc.h"
#include "SimpleMotorOsc.h"
#include "DirMotorOsc.h"

void setup()
{
    initRunner();
    
	int id = EEPROM.read(0);
    
    switch (id)
    {
        case 0:
            addSimpleStepOsc(midimap(CHANNEL_7), DIR1, STEP1, EN1, LIMIT1);
            addSimpleStepOsc(midimap(CHANNEL_12), DIR2, STEP2, EN2, LIMIT2);
            addSimpleStepOsc(midimap(CHANNEL_10), DIR4, STEP4, EN4, ANA2);
            //addSimpleStepOsc(midimap(CHANNEL_8), DIR2, STEP2, EN2, LIMIT2);
            addSwitcher(midimap(CHANNEL_10), FET4);
            break;
            
        case 1:
			//addDirStepOsc(midimap(CHANNEL_9), DIR1, STEP1, EN1);
            addFloppyOsc(midimap(CHANNEL_3), FET2, FET3);
            addOsc(midimap(CHANNEL_4), FET1);
            addRandOsc(midimap(CHANNEL_5), FET4);
			break;
            
        case 2:
            addSimpleStepOsc(midimap(CHANNEL_9), DIR1, STEP1, EN1, LIMIT1);
            addSimpleStepOsc(midimap(CHANNEL_11), DIR2, STEP2, EN2, LIMIT2);
            //addSwitcher(midimap(CHANNEL_8), FET4);
            addSimpleStepOsc(midimap(CHANNEL_13), DIR3, STEP3, EN3, ANA1);
            
            break;
		case 58:
			addStepOsc(midimap(CHANNEL_1), DIR1, STEP1, EN1);
			addStepOsc(midimap(CHANNEL_2), DIR2, STEP2, EN2);
			break;
        case 3:
            // addOsc(midimap(CHANNEL_1), FET1);
			addSimpleStepOsc(midimap(CHANNEL_1), DIR1, STEP1, EN1, LIMIT1);
			addSimpleStepOsc(midimap(CHANNEL_2), DIR2, STEP2, EN2, LIMIT2);
            addSimpleMotorOsc(midimap(CHANNEL_6), DIR3, STEP3, EN3);
            
            
			addOsc(midimap(CHANNEL_8), FET1);
			addOsc(midimap(CHANNEL_8), FET2);
			addOsc(midimap(CHANNEL_8), FET3);
			addOsc(midimap(CHANNEL_8), FET4);
            //addOsc(midimap(CHANNEL_1), FET1);
            break;
		case 59:
			addDirMotorOsc(midimap(CHANNEL_1), DIR1, STEP1, EN1, LIMIT1, FET1);
			addSimpleMotorOsc(midimap(CHANNEL_2), DIR2, STEP2, EN2); 
			break;
        case 4:
            //addRandOsc(midimap(CHANNEL_2), FET4);
            addFloppyOsc(midimap(CHANNEL_1), FET3, FET4);
			break;
		case 5:
			addOsc(midimap(CHANNEL_1), FET1);
			addStepOsc(midimap(CHANNEL_2), DIR2, STEP2, EN2);
			addDirMotorOsc(midimap(CHANNEL_3), DIR1, STEP1, EN1, LIMIT1, FET3);
			
			addShiftSwitcher(midimap(CHANNEL_1), LED1);
			addShiftSwitcher(midimap(CHANNEL_1), LED2);
			addShiftSwitcher(midimap(CHANNEL_1), LED3);
			addShiftSwitcher(midimap(CHANNEL_1), LED4);
			
			addShiftSwitcher(midimap(CHANNEL_2), LED5);
			addShiftSwitcher(midimap(CHANNEL_2), LED6);
			addShiftSwitcher(midimap(CHANNEL_2), LED7);
			addShiftSwitcher(midimap(CHANNEL_2), LED8);
			
			
											  
			break;
		case 62:
			addOsc(midimap(CHANNEL_14), FET1);
			addStepOsc(midimap(CHANNEL_15), DIR1, STEP1, EN1);
			addSimpleMotorOsc(midimap(CHANNEL_16), DIR2, STEP2, EN2);
			break;
        default:
            addOsc(midimap(CHANNEL_1), FET1);
            addOsc(midimap(CHANNEL_2), FET2);
            addOsc(midimap(CHANNEL_3), FET3);
            addOsc(midimap(CHANNEL_4), FET4);
            break;
    }
}

void loop()
{
	runRunner();
	
}

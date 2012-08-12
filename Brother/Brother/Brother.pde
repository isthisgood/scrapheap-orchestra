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
#include "FloppyOsc.h"
#include "LimitMotorOsc.h"
#include "LimitStepOsc.h"
#include "ControlMotorOsc.h"
#include "ControlStepOsc.h"
#include "Flapper.h"

void setup()
{
    initRunner();
    
	int id = EEPROM.read(0);
    
    switch (id)
    {
        case 0:
            addLimitStepOsc(midimap(CHANNEL_7), DIR1, STEP1, EN1, LIMIT1);
            addLimitStepOsc(midimap(CHANNEL_12), DIR2, STEP2, EN2, LIMIT2);
            addLimitStepOsc(midimap(CHANNEL_10), DIR4, STEP4, EN4, ANA2);
            addSwitcher(midimap(CHANNEL_10), FET4);
            break;
            
        case 1:
			addFloppyOsc(midimap(CHANNEL_3), FET2, FET3);
            addOsc(midimap(CHANNEL_4), FET1);
            addRandOsc(midimap(CHANNEL_5), FET4);
			break;
            
        case 2:
            addLimitStepOsc(midimap(CHANNEL_9), DIR1, STEP1, EN1, LIMIT1);
            addLimitStepOsc(midimap(CHANNEL_11), DIR2, STEP2, EN2, LIMIT2);
            addControlStepOsc(midimap(CHANNEL_13), DIR4, STEP4, EN4);
            addSwitcher(midimap(CHANNEL_10), FET1);
            break;
		
        case 3:
            addLimitStepOsc(midimap(CHANNEL_1), DIR1, STEP1, EN1, LIMIT1);
			addLimitStepOsc(midimap(CHANNEL_2), DIR2, STEP2, EN2, LIMIT2);
            //addLimitMotorOsc(midimap(CHANNEL_6), DIR3, STEP3, EN3, ANA1);
            
			addOsc(midimap(CHANNEL_8), FET1);
			addOsc(midimap(CHANNEL_8), FET2);
			addOsc(midimap(CHANNEL_8), FET3);
			addOsc(midimap(CHANNEL_8), FET4);
            break;
            
		case 4:
            addFloppyOsc(midimap(CHANNEL_1), FET3, FET4);
			break;
            
        case 5:
			addOsc(midimap(CHANNEL_1), FET1);
			addControlStepOsc(midimap(CHANNEL_2), DIR2, STEP2, EN2);
			addLimitMotorOsc(midimap(CHANNEL_3), DIR1, STEP1, EN1, LIMIT1, FET3);
			
			addShiftSwitcher(midimap(CHANNEL_1), LED1);
			addShiftSwitcher(midimap(CHANNEL_1), LED2);
			addShiftSwitcher(midimap(CHANNEL_1), LED3);
			addShiftSwitcher(midimap(CHANNEL_1), LED4);
			
			addShiftSwitcher(midimap(CHANNEL_2), LED5);
			addShiftSwitcher(midimap(CHANNEL_2), LED6);
			addShiftSwitcher(midimap(CHANNEL_2), LED7);
			addShiftSwitcher(midimap(CHANNEL_2), LED8);
			break;
            
        case 56:
            // design jet
			// formfeed channel 1
			addControlMotorOsc(midimap(CHANNEL_1), FET3, FET4);
			// print head channel 2
			addLimitMotorOsc(midimap(CHANNEL_2), DIR1, STEP1, EN1, LIMIT1, FET2);
            break;
            
		case 58:
			//addControlStepOsc(midimap(CHANNEL_1), DIR1, STEP1, EN1);
			//addControlStepOsc(midimap(CHANNEL_2), DIR2, STEP2, EN2);
			addLimitStepOsc(midimap(CHANNEL_2), DIR1, STEP1, EN1, LIMIT1);
            addFlapper(midimap(CHANNEL_1), FET3, FET2);
            
            addControlStepOsc(midimap(CHANNEL_8), DIR2, STEP2, EN2);
            addControlStepOsc(midimap(CHANNEL_9), DIR3, STEP3, EN3);
            break;
            
        case 59:
			addSwitcher(midimap(CHANNEL_10), FET1);
            break;
        
        case 62:
			addControlStepOsc(midimap(CHANNEL_3), DIR1, STEP1, EN1);
            addShiftSwitcher(midimap(CHANNEL_3), LED1);
            addShiftSwitcher(midimap(CHANNEL_3), LED2);
            addShiftSwitcher(midimap(CHANNEL_3), LED3);
            addShiftSwitcher(midimap(CHANNEL_3), LED4);
            addOsc(midimap(CHANNEL_4), FET1);
			//addControlStepOsc(midimap(CHANNEL_15), DIR1, STEP1, EN1);
			//addLimitMotorOsc(midimap(CHANNEL_16), DIR2, STEP2, EN2, LIMIT2, FET2);
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

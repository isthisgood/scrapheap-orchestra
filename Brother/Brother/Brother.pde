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
#include "DrawerOsc.h"

void setup()
{
    initRunner();
    
	int id = EEPROM.read(0);
    
    switch (id)
    {   
        //////////////////////////////////////////
        // PORT 1
        // oki 3410 group 1
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            // heads
            addLimitMotorOsc(midimap(CHANNEL_1), DIR1, STEP1, EN1, LIMIT1, FET1);
            // pins
            addOsc(midimap(CHANNEL_2), FET2);
            // form feed
            addControlStepOsc(midimap(CHANNEL_3), DIR2, STEP2, EN2);
            break;
            
        //////////////////////////////////////////
        // PORT 2
        // oki 3410 group 2
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
            // heads
            addLimitMotorOsc(midimap(CHANNEL_1), DIR1, STEP1, EN1, LIMIT1, FET1);
            // pins
            addOsc(midimap(CHANNEL_2), FET2);
            // form feed
            addControlStepOsc(midimap(CHANNEL_3), DIR2, STEP2, EN2);
            break;
        
        //////////////////////////////////////////
        // PORT 3
        // manisman tallys
        case 13:
            // heads
            addLimitStepOsc(midimap(CHANNEL_1), DIR1, STEP1, EN1, LIMIT1);
            addLimitStepOsc(midimap(CHANNEL_1), DIR2, STEP2, EN2, LIMIT2);
            
            // form feeds
            addControlStepOsc(midimap(CHANNEL_2), DIR3, STEP3, EN3);
            addControlStepOsc(midimap(CHANNEL_2), DIR4, STEP4, EN4);
            break;
        
        // design jets
        case 14:
        case 15:
            // head
            addLimitMotorOsc(midimap(CHANNEL_3), DIR1, STEP1, EN1, LIMIT1, FET1);
            // form feed
            addControlMotorOsc(midimap(CHANNEL_4), FET1, FET2);
            break;
            
        // dpx group 1
        case 16:
        case 17:
            // solenoid
            // head
            // ff
            break;
            
        // dpx group 2
        case 18:
        case 19:
            // solenoid
            // head
            // ff
            break;
            
        // faxes
        case 20:
            addFlapper(midimap(CHANNEL_11, mC3), FET1, FET2);
            addFlapper(midimap(CHANNEL_11, mD3), FET3, FET4);
            break;
        
        case 21:
            addFlapper(midimap(CHANNEL_11, mE3), FET1, FET2);
            addFlapper(midimap(CHANNEL_11, mF3), FET3, FET4);
            break;
            
        case 22:
            addFlapper(midimap(CHANNEL_11, mG3), FET1, FET2);
            break;
            
        //////////////////////////////////////////
        // PORT 4
        // digital senders
        case 23:
            addFlapper(midimap(CHANNEL_1), FET1, FET2);
            addFlapper(midimap(CHANNEL_1), FET3, FET4);
            break;
        
        // brother lasers
        case 24:
        case 25:
        case 26:
            // clicker
            // flap
            // y
            break;
        
        // HDDs
        case 27:
        case 28:
        case 29:
        case 30:
            //addOsc(midimap(<#int channel#>), <#int pin#>)
            break;
            
        case 62:
            addFlapper(midimap(CHANNEL_1), FET4, FET3);
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

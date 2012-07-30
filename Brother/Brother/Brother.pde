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

#define TXD 1
#define DIR1 A0
#define DIR2 A2
#define DIR3 A4
#define DIR4 7





void setup() {
    
    // addStepOsc(midimap(CHANNEL_1), 8, 9, 10, 11);
    //addVelOsc(midimap(CHANNEL_1), 12);
    //addSwitcher(midimap(CHANNEL_2), 13);
    //addOsc(midimap(CHANNEL_4), 4);
    
    //addSimpleStepperOsc(midimap(CHANNEL_1), );
    
	dipValue = getDipValues();

    initRunner();
	
}





void loop() {
    runRunner();

	
}

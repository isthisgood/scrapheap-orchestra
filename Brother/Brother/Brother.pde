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






void setup() {

    initRunner();
	
	
	addOsc(midimap(CHANNEL_1), FET1);
	addOsc(midimap(CHANNEL_2), FET2);
	addOsc(midimap(CHANNEL_3), FET3);
	addOsc(midimap(CHANNEL_4), FET4);
	
	addStepOsc(midimap(5), , <#int pinB#>, <#int pinC#>, <#int pinD#>)
	
}





void loop() {
    runRunner();

	
}

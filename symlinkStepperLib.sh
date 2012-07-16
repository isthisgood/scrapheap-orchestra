#!/bin/bash
sudo mv /Applications/Arduino.app/Contents/Resources/Java/libraries/Stepper /Applications/Arduino.app/Contents/Resources/Java/libraries/StepperOld
sudo ln -s `pwd`/Stepper /Applications/Arduino.app/Contents/Resources/Java/libraries/Stepper

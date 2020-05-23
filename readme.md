µsini M1D1_36
-------------
An Open Source Midi controller with **36 pads** in a **compact body**.  

Make music on a PC or with open source sound modules.
* 36 capacitives pads  
* 4 Potentiometers    
* 10 buttons    

Based Sparkfun Pro Micro (atmega32u4)
https://www.sparkfun.com/products/12640

![m1d1_36 Photo](/doc/images/m1d1_36.JPG)

# Demo


# USB Midi
Compatible with any music software   
Can also be used as a keyboard / mouse / xbox360 controller...

## Examples
LMMS - Open Source Music Software - https://lmms.io/download#windows
![LMMS](/doc/images/lmms_small.png) 

PatchBox OS - Raspberry Pi synthetiser - https://blokas.io/modep/
![PatchBox OS](/doc/images/patchbox_os.jpg) 

# Serial Midi
Add controls / sound generators using open sources modules
    ![m1d1_36 Photo](/doc/images/m1d1_36_serial.JPG) 
    
## Compatibles Modules
* **µsini zx** [TO BE PUBLISHED] : a AY-3-8910 sound generator (used in zx-spectrum)   
 Based on Ian Harvey design (public domain) : https://www.instructables.com/id/Arduino-MIDI-Chiptune-Synthesizer/

* **µsini opl2** [WAITING FOR COMPONENTS] : A OPL-2 FM sound generator (used in adlib sound card)   
  Based on Maarten Janssen design (MIT licence) : https://hackaday.io/project/18995-opl2-audio-board-for-arduino-raspberry-pi

* **µsini M1d1 Out** [TO MAKE] : A serial pins to Midi output
* **µsini M1d1 WiFi** [TO MAKE] : A serial midi to RtpMidi (WiFi Midi)
* **µsini M1d1 BLE** [TO MAKE] : A serial midi to BLE 

# Make your own
Fast and easy to solder as this midi controller used only modules.

## Send Gerbers to PCB Manufacturer

## Buy component
You can either choose to buy components from a chinese clone manufacturer or the original source.

### Clone links (sponsored)


### Sparkfun links

## Solder it

## Upload code


# Easy to customize code
Easy to use events system

Each times a pad / buttons is pressed or a potentiometers is moved, theses functions are triggered: 
* potsEvent()
* buttonsEvent()
* MPREvent()

 ![m1d1_36 Event based system](/doc/images/event_based.png) 

Developer documentation : LINK

# Easy to customize schematics

noob friendly schematics for Kicad.  
 ![m1d1_36 Schematics](/doc/images/schematic_m1d1_36.png) 

 ![PCB](/doc/images/pcb_m1d1_36.png) 

## 3D models
![m1d1_36 3D Models](/doc/images/kicad_3D_models_m1d1_36.png) 

* pro_micro.step - **Andrew_Witham** - https://grabcad.com/library/arduino-pro-micro-1
* stepdown.STEP - **Hasanain Shuja**   - https://grabcad.com/library/   dd0503ma-ultra-mini-dc-3-7v-4-5v-5v-to-3-3v-dc-dc-step-down-converter-buck-module-2    
* oled.step - **CDMX ELECTRONICA** - https://grabcad.com/library/display-oled-ssd1306-de-0-96-1     
* mpr121.step - **SPARKFUN** - https://www.sparkfun.com/products/retired/9695     
* logic_level.step - **SPARKFUN** - https://www.sparkfun.com/products/12009     
* 12mmx12mm Without cap.step - **Nilton** - https://grabcad.com/library/    
* 12mm-button-without-cap-with-round-square-cap-1
pot.step - **Mirko Ragni** - https://grabcad.com/library/47k-potentiometer-1   

# Open source as its core
## Make your own midi controller and sell it.   
Documentations / Codes and components, everything is licenced so you can make your own controller and sell it.

## Open source modules
Except for the OLED screen / 5v to 3.3v voltage regulator, all modules are licenced Creative Commons Share-alike 3.0 by Sparkfun.   

Eagles Files
* Pro Micro - http://cdn.sparkfun.com/datasheets/Dev/Arduino/Boards/SparkFun_Pro_Micro_v13a.zip

* MPR121 - http://cdn.sparkfun.com/datasheets/BreakoutBoards/MPR121-Breakout-v13.zip

* Logic Level Converter - http://cdn.sparkfun.com/datasheets/BreakoutBoards/Logic_Level_Bidirectional.zip

## Open Source code



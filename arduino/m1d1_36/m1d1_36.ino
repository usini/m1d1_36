/*! 
 * @file m1d1_36.ino
 * 
 * @mainpage µsini M1D1_36 v1.0: A 36 Capacitive Pad Midi Controller
 * 
 * @section intro_sec Introduction
 *
 * µsini M1D1_36 v1.0: A 36 Capacitive Pad Midi Controller \n
 * For more informations go to https://github.com/usini/midi_36
 *
 * @section dependencies Dependencies
 * AceButton        : https://github.com/bxparks/AceButton \n
 * MIDIUSB          : https://www.arduino.cc/en/Reference/MIDIUSB \n
 * Adafruit SSD1306 : https://github.com/adafruit/Adafruit_SSD1306 \n
 * Adafruit MPR121  : https://github.com/adafruit/Adafruit_MPR121 \n 
 * 
 * @section author Author
 * 
 * Written by Rémi Sarrailh for µsini, with 
 * contributions from the open source community
 * 
 * @section licence Licence
 * 
 * MIT Licence
*/

// Libraries
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <AceButton.h>
#include "Adafruit_MPR121.h"
#include "MIDIUSB.h"

// Internal code
#include "settings.h" //Settings
#include "midi.h"
#include "buttons.h" //Buttons
#include "pots.h" //Potentiometers
#include "mpr121.h" // Pads
#include "OLED.h" //Display (OLED)

/*!
 *  @brief Settings all components
*/
void setup() {
  if (SERIAL_ACTIVE) {
    Serial.println("M1D1_36 Startup");
  }

  setupMIDI();
  setupMPR();
  setupButtons();
  setupOLED();
}

/*!
 *  @brief Check all components and generate events
*/
void loop() {
  // To test the buttons / Potentiometers, disable all code but testButtons(); or testPots();
  // testButtons();
  // testPots();

  checkMPR(capE.touched(), 0);
  checkMPR(capF.touched(), 1);
  checkMPR(capG.touched(), 2);
  checkPots();
  checkButtons();
  checkOLED(); //Check if OLED need to be refresh
  MidiUSB.flush();
}

/*!
 *  @brief When a pad is pressed / released
 * 
 *  @param capPos
 *        Pad position (from 0 to 36)
 *  @param note
 *        Notes in capNote (see settings.h)
 *  @param state
 *        Is the pad currently pressed or released
 *  @param mpr_id
 *        Which MPR121 module is used (from 0 to 2)
 *  @param cap_id
 *        Which pad is used on the MPR121 (from 0 to 11)
*/
void MPREvent(int capPos, int note, bool state, int mpr_id, int cap_id) {
  if (state) {
    // NoteON (with transposition)
    noteOn(note + (12 * transpose), 127, channel);
    // Draw pad position on OLED
    drawMPR(mpr_id, cap_id, true);
    // Display Pad pressed on Serial
    serialMPR(capPos, note, true);
  } else {
    // NoteOFF (with transposition)
    noteOff(note + (12 * transpose), 0, channel);
    // Draw pad position on OLED
    drawMPR(mpr_id, cap_id, false);
    // Display Pad release on Serial
    serialMPR(capPos, note, false);
  }
}

/*!
 *  @brief When a potentiometer is used
 * 
 *  @param pot_id
 *        Potentiometer id (from 0 to 3)
*/
void potsEvent(int pot_id) {
  controlChange(pots_cc[pot_id], pots_val[pot_id], channel);
  drawPots();
  serialPots(pot_id, pots_val[pot_id]);
}

/*!
 *  @brief When a button is pressed / released
 * 
 *  @param button
 *        Acebutton object (button->getId() to get ID)
 *  @param eventType
 *        Is the button press / release / double click / long press / repeatly press
 *  @param buttonState 
 *        Is the button was pressed or released
*/
void buttonsEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  uint8_t id = button->getId();
  switch (eventType) {
    //Button is pressed
    case AceButton::kEventPressed:
      //Change buttons state (toggle mode)
      if (id < 6) { // First 6 buttons are used as midi

        btn[id] = !btn[id]; //Invert button state
        //Button ON = 127 / Button OFF = 0
        uint8_t val = 0;
        if (btn[id]) {
          val = 127;
        }

        controlChange(btn_cc[id], val, channel); //Send CC command (cc, value, channel)
        drawButtons(id, btn[id]);
        serialButtons(id, val);
      } else {
        switch (id) { //Last buttons are use to change Channel / Transpose
          case 6:
            if (transpose != 0) {
              transpose--;
              drawTranspose();
            }
            break;
          case 7:
            if (transpose <= 6) {
              transpose++;
              drawTranspose();
            }
            break;
          case 8:
            if (channel != 1) {
              channel--;
              drawChannel();
            }
            break;
          case 9:
            if (channel < 16) {
              channel++;
              drawChannel();
            }
            break;
        }
      }
      break;

      /*
        case AceButton::kEventReleased:
        break;

        case AceButton::kEventDoubleClicked:
        break;

        case AceButton::kEventLongPressed:
        break;

        case AceButton::kEventRepeatPressed:
        break;
      */
  }
}

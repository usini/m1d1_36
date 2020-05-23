/*! 
 * @file mpr121.h
 * 
 * Documentation : https://learn.adafruit.com/adafruit-mpr121-12-key-capacitive-touch-sensor-breakout-tutorial/wiring \n
 * WARNING: You can't use multiples MPR121 clone without this modification: https://electronics.stackexchange.com/questions/325702/how-to-cut-the-add-to-gnd-trace-on-a-mpr121-capacitive-touch-sensor#325714
*/

/* Bitshifting */
#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

Adafruit_MPR121 capE = Adafruit_MPR121(); ///<MPR121 Object for E
Adafruit_MPR121 capF = Adafruit_MPR121(); ///<MPR121 Object for F
Adafruit_MPR121 capG = Adafruit_MPR121(); ///<MPR121 Object for G

bool capState[36] = {false, false, false, false, false, false, false, false, false, false, false, false,
                     false, false, false, false, false, false, false, false, false, false, false, false,
                     false, false, false, false, false, false, false, false, false, false, false, false
                    }; ///<Is pad pressed or not

void MPREvent(int, int, bool, int, int);

/*!
 *  @brief Start I²C communication for all modules, will stop if MPR121 module not founded
*/
void setupMPR() {
  Serial.println("--> MPR Modules....");
  if (!capE.begin(0x5A)) {
    while (1) {
      Serial.println("MPR121 E not found, check wiring?");
    }
  }

  if (!capF.begin(0x5B)) {
    while (1) {
      Serial.println("MPR121 F not found, check wiring?");
    }
  }

  if (!capG.begin(0x5C)) {
    while (1) {
      Serial.println("MPR121 G not found, check wiring?");
    }
  }
}
/*!
 *  @brief check if a pad is pressed and generate event in MPREvent()
 *  @param currtouched
 *         pad id (from 0 to 11)
 *  @param mpr_id
 *         MPR id (from 0 to 3)
*/
void checkMPR(uint16_t currtouched, uint8_t mpr_id) {
  int mpr_pos = 12 * mpr_id;
  for (uint8_t cap_id = 0; cap_id < 12; cap_id++) {
    
    int capPos = cap_id + mpr_pos;

    // it if *is* touched and *wasnt* touched before, trigger event.
    if ((currtouched & _BV(cap_id)) && !(capState[capPos]) ) {
      MPREvent(capPos, capNote[capPos], true, mpr_id, cap_id);
      capState[capPos] = true;
    }

    // if it *was* touched and now *isnt*, trigger event.
    if (!(currtouched & _BV(cap_id)) && (capState[capPos]) ) {
      MPREvent(capPos, capNote[capPos], false, mpr_id, cap_id);
      capState[capPos] = false;
    }
  }
}

/*!
 *  @brief Serial message on pad pressed/released
 *  @param capPos
 *         pad global position (from 0 to 35)
 *  @param note
 *         note assign to pad (see settings.h)
 *  @param state
 *          pressed or release
*/
void serialMPR(int capPos, int note, bool state) {
  if (SERIAL_ACTIVE) {
    Serial.print("U");
    Serial.print(capPos + 1);
    Serial.print(" - ");
    Serial.print(note);
    if (state) {
      Serial.println(" - ON");
    } else {
      Serial.println(" - OFF");
    }
  }
}

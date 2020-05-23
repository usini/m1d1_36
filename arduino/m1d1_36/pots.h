/*! 
 * @file pots.h
 * 
  Documentations : https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives \n
                   https://learn.adafruit.com/monochrome-oled-breakouts/arduino-library-and-examples
*/

uint8_t pots_val[4] = {0, 0, 0, 0}; ///< Potentiometers value (from 0 to 127)

void potsEvent(int);

/*!
 *  @brief Check if value of potentiometers change , translate it from 0 to 1024 to 0 to 127 to generate events
*/
void checkPots() {
  uint8_t new_pots_val[4];
  //Bitshift value from 1024 to 127
  new_pots_val[0] = analogRead(A0) >> 3;
  new_pots_val[1] = analogRead(A1) >> 3;
  new_pots_val[2] = analogRead(A2) >> 3;
  new_pots_val[3] = analogRead(A3) >> 3;

  //For each potentiometers
  for (int pot_id = 0; pot_id < 4; pot_id++) {
    //Check if value change (precision is not great so we discard change if only +1)
    if ((pots_val[pot_id] != new_pots_val[pot_id]) && (pots_val[pot_id] != new_pots_val[pot_id] + 1))
    {
      pots_val[pot_id] = new_pots_val[pot_id]; // Update value of pots
      potsEvent(pot_id);
    }
  }
}

/*!
 *  @brief Display Potentiometers change on serial

 *  @param pot
 *         potentiometer id (from 0 to 3)
 *  @param val
 *         potentiometer value (from 0 to 127)
*/
void serialPots(int pot, int val) {
  if (SERIAL_ACTIVE) {
    Serial.print("POT");
    Serial.print(pot);
    Serial.print(":");
    Serial.println(val);
  }
}

/*!
 *  @brief Test potentiometers
*/
void testPots() {
  Serial.print(analogRead(A0));
  Serial.print(" - ");
  Serial.print(analogRead(A1));
  Serial.print(" - ");
  Serial.print(analogRead(A2));
  Serial.print(" - ");
  Serial.println(analogRead(A3));
}

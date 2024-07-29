/*! 
 * @file buttons.h
 * 
 * Documentations : https://github.com/bxparks/AceButton
*/

using namespace ace_button;

AceButton buttons[10]; ///< AceButton object (for 10 buttons)

void buttonsEvent(AceButton*, uint8_t, uint8_t);

const uint8_t buttons_pins[10] = { 4, 5, 6, 7, 8, 9, 10, 14, 15, 16}; ///< pins of buttons
bool btn[10] = {false, false, false, false, false, false, false, false, false, false}; ///< buttons state

/*!
 *  @brief Setup pins on pullup and create events for AceButtons
*/
void setupButtons() {
  Serial.println("--> Buttons....");

  /* Using PullUp for buttons */
  for (int i = 0; i < 10; i++) {
    pinMode(buttons_pins[i], INPUT_PULLUP);
    buttons[i].init(buttons_pins[i], HIGH, i);
  }

  /* Setup Buttons for events */
  ButtonConfig* buttonConfig = ButtonConfig::getSystemButtonConfig();
  buttonConfig->setEventHandler(buttonsEvent);
  buttonConfig->setFeature(ButtonConfig::kFeatureClick);
  buttonConfig->setFeature(ButtonConfig::kFeatureDoubleClick);
  buttonConfig->setFeature(ButtonConfig::kFeatureLongPress);
  buttonConfig->setFeature(ButtonConfig::kFeatureRepeatPress);
}

/*!
 *  @brief Check for buttons events
*/

void checkButtons() {
  for (uint8_t i = 0; i < 10; i++) {
    buttons[i].check();
  }
}

/*!
 *  @brief Display a message on Serial USB
 * 
 *  @param id
 *         buttons id (from 0 to 9)
 *  @param val
 *         is button was previously pressed or not
*/
void serialButtons(int id, int val) {
  if (SERIAL_ACTIVE) {
    Serial.print("BTN ");
    Serial.print(id);
    Serial.print(":");
    Serial.println(val);
  }
}

/*!
 *  @brief Test buttons
*/
void testButtons() {
  for (int i = 0; i < 10; i++) {
    Serial.print(digitalRead(buttons_pins[i]));
  }
  Serial.println();
}

/*! 
 * @file OLED.h
 * 
  Documentations \n 
  Adafruit GFX : https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives \n
  Monochrome OLED : https://learn.adafruit.com/monochrome-oled-breakouts/arduino-library-and-examples
*/

#define SCREEN_WIDTH 128 ///< OLED display width, in pixels
#define SCREEN_HEIGHT 64 ///< OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 ///< RESET pin (no available on basic OLED module)

/*!
    @brief  Constructor for I2C-interfaced SSD1306 displays.
    @param  w
            Display width in pixels
    @param  h
            Display height in pixels
    @param  twi
            Pointer to an existing TwoWire instance (e.g. &Wire, the
            microcontroller's primary I2C bus).
    @return Adafruit_SSD1306 object.
*/
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool screen_update = false; ///< Refresh screen after instructions

/*!
 *  @brief Start I²C communication for OLED, will stop if not founded
*/
void setupOLED() {
  Serial.println("--> OLED....");
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.display();
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
}

/*!
 *  @brief draw pad pressed on OLED
 *  @param mpr_id
 *         pad id (from 0 to 11)
 *  @param cap_id
 *         MPR id (from 0 to 3)
 *  @param state
 *         is pressed/released
*/
void drawMPR(int mpr_id, int cap_id, bool state) {
  int y = 0;
  //Compute Y position on screen
  switch (mpr_id) {
    case 0:
      y = 48;
      break;
    case 1:
      y = 32;
      break;
    case 2:
      y = 16;
      break;
  }
  //Compute X position on screen
  int x = cap_id * 10;

  if (state) {
    display.drawRect(x, y, 10, 16, SSD1306_WHITE); //Create box
  } else {
    display.drawRect(x, y, 10, 16, SSD1306_BLACK); //Erase box
  }
  screen_update = true; //Tell screen to update at end of loop
}

/*!
 *  @brief draw transpose value on screen
*/

void drawTranspose() {
  display.fillRect(65, 0, 20, 8, SSD1306_BLACK);
  display.setCursor(65, 0);
  String string = "T" + String(transpose);
  display.write(string.c_str());
  screen_update = true;
}

/*!
 *  @brief draw channel value on screen
*/
void drawChannel() {
  display.fillRect(65, 8, 20, 8, SSD1306_BLACK);
  display.setCursor(65, 8);
  String string = "C" + String(channel);
  display.write(string.c_str());
  screen_update = true;
}

/*!
 *  @brief Check if display need to be refresh (after instructions)
*/
void checkOLED() {
  if (screen_update) {
    display.display();
    screen_update = false;
  }
}

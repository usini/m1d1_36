/*! 
 * @file settings.h
 * 
 * Documentations \n
 * Control Change : https://www.midi.org/specifications-old/item/table-3-control-change-messages-data-bytes-2 \n
 * Midi Note      : https://newt.phys.unsw.edu.au/jw/notes.html
*/

uint8_t transpose = 2; ///< Default Transposition (by step of an octave, 12 notes)
uint8_t channel = 2; ///< Default Channel
byte btn_cc[10] = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19}; ///< Buttons Control Change parameters
byte pots_cc[4] = {0x01, 0x02, 0x03, 0x04}; ///< Potentiometers Control Change parameters
uint8_t capNote[36] = {21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
                       33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
                       45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56
                      }; ///< Note from pad (before transposition)
const byte SCREEN_ADDRESS = 0x3C; ///< Screen I²C address
const bool SERIAL_ACTIVE = true; ///< Enable Serial debug

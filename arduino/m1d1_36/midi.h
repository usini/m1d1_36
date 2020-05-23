/*! 
 * @file midi.h
 * 
 * Documentations \n
 * Tutorial on Midi Message : https://www.instructables.com/id/Send-and-Receive-MIDI-with-Arduino/ \n
 * Summary of MIDI Message : https://www.midi.org/specifications-old/item/table-1-summary-of-midi-message \n
 * MIDIUSB : https://www.arduino.cc/en/Reference/MIDIUSB \n
*/

const int NOTEON = 144;  ///<144, note on command
const int NOTEOFF = 128; ///<128, note off command
const int CONTROLCHANGE = 176; ///<176, Control Change command

/*!
 *  @brief Start communication on Serial1 (on pro micro Serial is USB only / Serial1 is TX/RX)
*/
void setupMIDI() {
  Serial1.begin(31250);
}

/*!
 *  @brief Send a MIDI noteOn on USB / Serial
 *  @param pitch
 *         midi note
 *  @param velocity
 *         velocity (force with which a note is played)
 *  @param channel
 *         channel (can be use to change instruments)
*/
void noteOn(byte pitch, byte velocity, byte channel) {
  Serial1.write(NOTEON + (channel - 1));
  Serial1.write(pitch);
  Serial1.write(velocity);
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

/*!
 *  @brief Send a MIDI noteOff on USB / Serial
 *  @param pitch
 *         midi note
 *  @param velocity
 *         velocity (force with which a note is played)
 *  @param channel
 *         channel (can be use to change instruments)
*/

void noteOff(byte pitch, byte velocity, byte channel) {
  Serial1.write(NOTEOFF + (channel - 1));
  Serial1.write(pitch);
  Serial1.write(velocity);
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

/*!
 *  @brief Send a MIDI noteOn on USB / Serial
 *  @param control
 *         Control Change (parameters in hex ex: 0x11)
 *  @param value
 *         Value of the parameters (from 0 to 127)
 *  @param channel
 *         channel
*/

void controlChange(byte control, byte value, byte channel) {
  Serial1.write(CONTROLCHANGE + (channel - 1));
  Serial1.write(value);
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

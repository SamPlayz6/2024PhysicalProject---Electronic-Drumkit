#include <MIDIUSB.h>

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = { 0x09, 0x90 | channel, pitch, velocity };
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = { 0x08, 0x80 | channel, pitch, velocity };
  MidiUSB.sendMIDI(noteOff);
}

void setup() {
  Serial.begin(115200);
}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = { 0x0B, 0xB0 | channel, control, value };
  MidiUSB.sendMIDI(event);
}

void loop() {
  Serial.println("Sending note on");
  noteOn(1, 48, 64);  // Channel 0, middle C, normal velocity
  digitalWrite(LED_BUILTIN, HIGH);
  MidiUSB.flush();
  delay(500);
  Serial.println("Sending note off");
  noteOff(1, 48, 64);  // Channel 0, middle C, normal velocity
  digitalWrite(LED_BUILTIN, LOW);
  MidiUSB.flush();
  delay(1500);

  // controlChange(0, 10, 65); // Set the value of controller 10 on channel 0 to 65
}
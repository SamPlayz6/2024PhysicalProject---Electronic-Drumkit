#include <MIDIUSB.h>

int sensoroutput = A11; // the analog pin connected to the sensor
int THRESHOLD = 500;
// Acoustic Snare on MIDI Channel 10 (internally, Channel 9)
uint8_t channel = 1;  // MIDI channels are 0-15, so Channel 10 is 9
uint8_t pitch = 38;   // Acoustic Snare drum pitch
uint8_t velocity = 127;  // Maximum hit velocity



void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = { 0x0B, 0xB0 | channel, control, value };
  MidiUSB.sendMIDI(event);
}

void loop() {
  int value = analogRead(sensoroutput); 

  Serial.println(analogRead(sensoroutput));

    if (value <= THRESHOLD)                    // function to check voltage level from sensor
    {
      Serial.println("Sending note on");
      noteOn(channel, pitch, velocity);  // Channel 0, middle C, normal velocity
      digitalWrite(LED_BUILTIN, HIGH);
      MidiUSB.flush();
      delay(2000);
    }
    else {
      noteOff(channel, pitch, velocity);  // Channel 0, middle C, normal velocity
      digitalWrite(LED_BUILTIN, LOW);
      MidiUSB.flush();
    }
  }

void noteOn(uint8_t channel, uint8_t pitch, uint8_t velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush(); // Make sure to send the message immediately
}

void noteOff(uint8_t channel, uint8_t pitch, uint8_t velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, 0}; // Velocity should be 0 for noteOff
  MidiUSB.sendMIDI(noteOff);
  MidiUSB.flush(); // Make sure to send the message immediately
}
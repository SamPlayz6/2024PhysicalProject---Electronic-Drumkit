#include <MIDIUSB.h>

// Sensor analog pins
int sensors[4] = {A2, A3, A4, A5};  // List of analog pins for the sensors - Snare1, Snare2, Snare3 , Bass(Floor Drum)
int THRESHOLD = 250;

uint8_t channel = 9;  // MIDI channel 10 for drums (internally 9, correcting the initial channel error)
uint8_t pitches[4] = {38, 40, 42, 46};   // Different pitches for different drum sounds
                                       // 38 - Acoustic Snare, 35 - Bass Drum, 42 - Closed Hi-Hat, 46 - Open Hi-Hat
uint8_t velocity = 127;  // Maximum hit velocity

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(sensors[i], INPUT);  // Set sensor pins as input
  }
}

void loop() {
  for (int i = 0; i < 4; i++) {
    int value = analogRead(sensors[i]);

    if (i == 0) {
      value = 1023 - analogRead(sensors[i]);
      Serial.println(value);
    }

    if (value <= THRESHOLD) {  // Check if sensor exceeds threshold
      Serial.println("Sending note on for sensor " + String(i));
      noteOn(channel, pitches[i], velocity);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(10); // Short delay to simulate drum hit655
      noteOff(channel, pitches[i], velocity);
      digitalWrite(LED_BUILTIN, LOW);
      delay(200); // Prevent rapid re-triggering
    }
  }
  // int valueA1 = analogRead(sensors[0]);
  // int valueA0 = analogRead(sensors[1]);
  // int valueA3 = analogRead(sensors[2]);
  // int valueA4 = analogRead(sensors[3]);


  // Serial.println(valueA1);
  // Serial.println(valueA3);
  // Serial.println(valueA4);


  delay(10); // Loop delay to prevent excessive CPU usage
}

void noteOn(uint8_t channel, uint8_t pitch, uint8_t velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush(); // Ensure the message is sent immediately
}

void noteOff(uint8_t channel, uint8_t pitch, uint8_t velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, 0}; // Velocity should be 0 for noteOff
  MidiUSB.sendMIDI(noteOff);
  MidiUSB.flush(); // Ensure the message is sent immediately
}

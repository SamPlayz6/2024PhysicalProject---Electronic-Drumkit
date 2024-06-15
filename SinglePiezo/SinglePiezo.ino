int sensoroutput = 1; // the analog pin connected to the sensor
int THRESHOLD = 500;
void setup()
{
pinMode(LED_BUILTIN, OUTPUT);
Serial.begin(9600);
}
void loop()
{
int value = analogRead(sensoroutput);  // function to read analog voltage from sensor
Serial.println(value);

if (value <= THRESHOLD)                    // function to check voltage level from sensor
{
digitalWrite(LED_BUILTIN, HIGH);
delay(100); // to make the LED visible
}
else
digitalWrite(LED_BUILTIN, LOW);
}
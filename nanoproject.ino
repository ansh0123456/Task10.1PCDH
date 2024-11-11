const int button1Pin = 2;    // Push button 1 to send GPS and activate red LED
const int button2Pin = 3;    // Push button 2 to turn off red LED
const int redLedPin = 7;     // Red LED

bool button1State = false;
bool button2State = false;
bool previousButton1State = false;
bool previousButton2State = false;
// Static GPS data for Chitkara University
const String latitude = "30.516459";
const String longitude = "76.659210";
const String altitude = "300"; // Assuming altitude in meters

void setup() {
  // Initialize pins
  pinMode(button1Pin, INPUT_PULLUP);  // Use internal pull-up resistor
  pinMode(button2Pin, INPUT_PULLUP);  // Use internal pull-up resistor
  pinMode(redLedPin, OUTPUT);

  // Start Serial communication with Raspberry Pi
  Serial.begin(9600);

  // Ensure the red LED is off at the start
  digitalWrite(redLedPin, LOW);
}

void loop() {
  // Read button states
  button1State = digitalRead(button1Pin) == LOW; // LOW means pressed
  button2State = digitalRead(button2Pin) == LOW; // LOW means pressed

  // If Button 1 is pressed, send GPS data and turn on the red LED
  if (button1State && !previousButton1State) {
    activateRedLED();
    sendGPSDataToPi();
  }

  // If Button 2 is pressed, turn off the red LED
  if (button2State && !previousButton2State) {
    deactivateRedLED();
    // Send message to notify the Pi to turn off the buzzer
    Serial.println("RED_LED_OFF");
  }

  // Store the last button states
  previousButton1State = button1State;
  previousButton2State = button2State;

  delay(50); // Small debounce delay
}

// Function to activate the red LED
void activateRedLED() {
  digitalWrite(redLedPin, HIGH);  // Turn on red LED
}

// Function to deactivate the red LED
void deactivateRedLED() {
  digitalWrite(redLedPin, LOW);   // Turn off red LED
}

// Function to send static GPS data to the Raspberry Pi
void sendGPSDataToPi() {
  // Send formatted GPS data to the Pi
  Serial.println("Latitude: " + latitude);
  Serial.println("Longitude: " + longitude);
  Serial.println("Altitude: " + altitude + " m");
}
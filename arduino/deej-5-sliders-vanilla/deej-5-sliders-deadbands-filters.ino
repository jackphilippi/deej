const int NUM_SLIDERS = 5;
const int analogInputs[NUM_SLIDERS] = {A0, A1, A2, A3, A6};

int analogSliderValues[NUM_SLIDERS];
int previousAnalogSliderValues[NUM_SLIDERS];

const int LOW_DEADBAND_THRESHOLD = 10; 
const int HIGH_DEADBAND_THRESHOLD = 1014;

unsigned long lastSentTime = 0;

const unsigned long SEND_INTERVAL = 10000; // 10 seconds in milliseconds

void setup() { 
  for (int i = 0; i < NUM_SLIDERS; i++) {
    // Set up analog pins to read slider values
    pinMode(analogInputs[i], INPUT);
    // Initialize previous values
    previousAnalogSliderValues[i] = analogRead(analogInputs[i]); 
  }
  lastSentTime = millis();
  Serial.begin(9600);
}

void loop() {
  updateSliderValues();

  if (millis() - lastSentTime >= SEND_INTERVAL) {
    // Send the values even if they haven't changed sufficiently
    sendSliderValues();
    lastSentTime = millis(); // Update the last sent time
  }
  
  delay(10);
}

void updateSliderValues() {
  bool shouldSendValues = false;
  for (int i = 0; i < NUM_SLIDERS; i++) {
    int newValue = analogRead(analogInputs[i]);
    
    // Set deadbands for upper and lower limits
    if (newValue < LOW_DEADBAND_THRESHOLD) {
      newValue = 0;
    } else if (newValue > HIGH_DEADBAND_THRESHOLD) {
      newValue = 1024;
    }

    // Check if the value has changed sufficiently
    if (abs(newValue - previousAnalogSliderValues[i]) >= 5) {
      shouldSendValues = true;
    }

    // Always update the value arrays
    analogSliderValues[i] = newValue;
    previousAnalogSliderValues[i] = newValue;
  }
  
  if (shouldSendValues == true) {
    sendSliderValues();
    lastSentTime = millis();
  }
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    if (i == NUM_SLIDERS - 1) {
      // We need to reverse the value of the non-master sliders as they are reversed
      builtString += String((int)analogSliderValues[i]);
    } else {
      builtString += String(1024 - (int)analogSliderValues[i]);
    }

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}

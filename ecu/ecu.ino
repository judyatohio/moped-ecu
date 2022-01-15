// vars declarations
// outputs
// the headlight and tail light will both just be wired through a mosfet to the battery with the alternator current on the gate
const int LEFT_TURN_SIGNAL = 5;
const int RIGHT_TURN_SIGNAL = 6;
const int BRAKE_LIGHT = 7;
const int HORN = 8;

// inputs
const int FRONT_BRAKE_SWITCH = 9;
const int COASTER_BRAKE_SENSOR = 19;
const int LEFT_SIGNAL_SWITCH = 10;
const int RIGHT_SIGNAL_SWITCH = 11;
const int HORN_SWITCH = 12;

// extra variables
const int THRESHOLD = 512; // this value is the value that will be used for coaster braking detection

// function prototypes

/*
 * Function:        turnSignalOn
 * Brief:           turns on the turn signal and manages the blinking
 * Param pin:       5 for left, 6 for right, 7 for hazards
 * Param milli:     reference variable that contains the millis() from the last time the light was switched. 0 before the first time turnSignalOn was called
 * Param signalOn:  reference bool that tracks whether or not the signal is on        
 * 
 */
void turnSignalOn(int pin, int &milli, bool &signalOn);
void turnSignalOff(int pin);
void hornOn();
void hornOff();
void brakeLightOn();
void brakeLigthOff();


void setup() {
  // put your setup code here, to run once:

  // output pin setups
  pinMode(LEFT_TURN_SIGNAL, OUTPUT);
  pinMode(RIGHT_TURN_SIGNAL, OUTPUT);
  pinMode(BRAKE_LIGHT, OUTPUT);
  pinMode(HORN, OUTPUT);

  // input pin setups
  pinMode(FRONT_BRAKE_SWITCH, INPUT);
  pinMode(COASTER_BRAKE_SENSOR, INPUT);
  pinMode(LEFT_SIGNAL_SWITCH, INPUT);
  pinMode(RIGHT_SIGNAL_SWITCH, INPUT);
  pinMode(HORN_SWITCH, INPUT);
  pinMode(LEFT_SIGNAL_CHECK, INPUT);
  pinMode(RIGHT_SIGNAL_CHECK, INPUT);
  pinMode(BRAKE_LIGHT_CHECK, INPUT);

  // variables
  bool signalOn = false;
}

void loop() {
  // put your main code here, to run repeatedly:

  // check each input, and call necessary function
  if (digitalRead(LEFT_SIGNAL_SWITCH) == HIGH) {
    turnSignalOn(LEFT_TURN_SIGNAL, milli, signalOn);
  } else {
    turnSignalOff(LEFT_TURN_SIGNAL);
  }

  if (digitalRead(RIGHT_SIGNAL_SWITCH) == HIGH) {
    turnSignalOn(RIGHT_TURN_SIGNAL);
  } else {
    turnSignalOff(RIGHT_TURN_SIGNAL);
  }

  if (digitalRead(HORN_SWITCH) == HIGH) {
    hornOn();
  } else {
    hornOff();
  }

  if (digitalRead(HORN_SWITCH) == LOW && analogRead(COASTER_BRAKE_SENSOR) < THRESHOLD) {
    brakeLightOff();
  } else {
    brakeLightOn();
  }

}

// function implementations
int turnSignalOn(int pin, int &milli, bool &signalOn) {
  if (millis() - milli > 333) {
    if (signalOn == true) {
      digitalWrite(pin, LOW);
      milli = millis();
    }
  }
  return 0;
}
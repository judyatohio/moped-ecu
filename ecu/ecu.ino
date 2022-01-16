// vars declarations
// outputs
// the headlight and tail light will both just be wired through a mosfet to the battery with the alternator current on the gate
const int LEFT_TURN_SIGNAL = 2;
const int RIGHT_TURN_SIGNAL = 3;
const int BRAKE_LIGHT = 4;
const int HORN = 5;

// inputs
const int FRONT_BRAKE_SWITCH = 6;
const int COASTER_BRAKE_SENSOR = 16;
const int LEFT_SIGNAL_SWITCH = 7;
const int RIGHT_SIGNAL_SWITCH = 8;
const int HORN_SWITCH = 9;

// extra variables
const int THRESHOLD = 512; // this value is the value that will be used for coaster braking detection
bool leftSignalStatus;
bool rightSignalStatus;    // unfortunately, i have to use global variables.
unsigned long milli;       // i cannot figure out another way to make these work

// function prototypes

/*
 * Function: *signalOn
 * Brief: manages the blinking of said signal using a few global variables that are only accessed in these functioned, and therefore shouldn't get out of hand
 */
void leftSignalOn();
void rightSignalOn();

/*
 * Function: *signalOff
 * Brief: turns said signal off
 */
void leftSignalOff();
void rightSignalOff();


/*
 * Function:  hornOn
 * Brief:     turns on the horn
 */
void hornOn();

/*
 * Function:  hornOff
 * Brief:     turns off the horn
 */
void hornOff();

/*
 * Function:  brakeLightOn
 * Brief:     turns on the brake light
 */
void brakeLightOn();

/*
 * Function:  brakeLightOff
 * Brief:     turns off the brake light
 */
void brakeLigthOff();

void setup()
{
  // put your setup code here, to run once:
  // just to make sure it uploaded correctly
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

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

  // variables
  leftSignalStatus = false;
  rightSignalStatus = false;
  milli = millis();
}

void loop()
{
  // put your main code here, to run repeatedly:

  // check each input, and call necessary function
  if (digitalRead(LEFT_SIGNAL_SWITCH) == HIGH)
  {
    leftSignalOn();
  }
  else
  {
    leftSignalOff();
  }

  if (digitalRead(RIGHT_SIGNAL_SWITCH) == HIGH)
  {
    rightSignalOn();
  }
  else
  {
    rightSignalOff();
  }

  if (digitalRead(HORN_SWITCH) == HIGH)
  {
    hornOn();
  }
  else
  {
    hornOff();
  }

  if (digitalRead(HORN_SWITCH) == LOW && analogRead(COASTER_BRAKE_SENSOR) < THRESHOLD)
  {
    brakeLightOff();
  }
  else
  {
    brakeLightOn();
  }
}

// function implementations
void leftSignalOn() {
    // if it's time to switch, switch and make note of the state of the light and the time.
  if (millis() - milli > 333){

    if (leftSignalStatus == true){
      digitalWrite(LEFT_TURN_SIGNAL, LOW);
      leftSignalStatus = false;
    } else {
      digitalWrite(LEFT_TURN_SIGNAL, HIGH);
      leftSignalStatus = true;
    }

    milli = millis();

  }
}

void rightSignalOn() {
    // if it's time to switch, switch and make note of the state of the light and the time.
  if (millis() - milli > 333){

    if (rightSignalStatus == true){
      digitalWrite(RIGHT_TURN_SIGNAL, LOW);
      rightSignalStatus = false;
    } else {
      digitalWrite(RIGHT_TURN_SIGNAL, HIGH);
      rightSignalStatus = true;
    }

    milli = millis();

  }
}

void leftSignalOff() {
  digitalWrite(LEFT_TURN_SIGNAL, LOW);
  leftSignalStatus = false;
}

void rightSignalOff() {
  digitalWrite(RIGHT_TURN_SIGNAL, LOW);
  rightSignalStatus = false;
}

void hornOn()
{
  digitalWrite(HORN, HIGH);
}

void hornOff()
{
  digitalWrite(HORN, LOW);
}

void brakeLightOn()
{
  digitalWrite(BRAKE_LIGHT, HIGH);
}

void brakeLightOff()
{
  digitalWrite(BRAKE_LIGHT, LOW);
}

#include <CmdMessenger.h>  // CmdMessenger
#include <NS_Rainbow.h>
#define PIN 0
#define N_CELL 12

byte flag_a = 1, flag_b = 0;
unsigned int cnt = 0, seed = 0;  // seed: used to initialize random number generator
const unsigned int maxCycle = 1200;  // go to next state when cnt >= maxCycle
NS_Rainbow ns_strip = NS_Rainbow(N_CELL,PIN);

const int redPin = 8;
const int yellowPin = 10;
const int greenPin = 11;

String color = "";

// Attach a new CmdMessenger object to the default Serial port
CmdMessenger cmdMessenger = CmdMessenger(Serial);

enum
{
  kSetLed, // Command to request led to be set in specific state
};

// Callbacks define on which received commands we take action 
void attachCommandCallbacks()
{
  cmdMessenger.attach(kSetLed, OnSetLed);
}

// Callback function that sets led on or off
void OnSetLed()
{
  // Read led state argument, interpret string as boolean
  //ledState = cmdMessenger.readBoolArg();
  color = cmdMessenger.readStringArg();
  
  if(color == "Busy" || color == "DoNotDisturb"){
    setColor(255, 0, 0);
    ColorSet(0);
  }else if(color == "Away" || color == "TemporarilyAway"){
    setColor(0, 0, 255);
    ColorSet(2);
  }else if (color == "Free"){
    setColor(0, 255, 0);
    ColorSet(1);
  }else{
    setColor(0, 0, 0);
    resetstrip();
  }
}
void ColorSet(uint16_t color){
  resetstrip();
  uint16_t n = ns_strip.numCells();
  uint16_t x=color;
     for(uint16_t i=0; i<n; i++) {
      switch (x) {
      case 0:
        ns_strip.setColor(i, 255,   0,   0);  // red
        break;
      case 1:
        ns_strip.setColor(i,   0, 255,   0);  // green
        break;
      case 2:
        ns_strip.setColor(i, 255, 100,   0);  // orange
        break;
      default:
        ns_strip.setColor(i, 0, 0, 0);  
        break;
      }
        ns_strip.show();        
    }
}
void resetstrip(){
  ns_strip.clear();
  ns_strip.show();
}

void setColor(int red, int green, int yellow)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(yellowPin, yellow);
}

// Setup function
void setup() 
{
  ns_strip.begin();
  ns_strip.clear();
  ns_strip.show();
  ns_strip.setBrightness(128);  // range: 0 ~ 255  55
  // Listen on serial connection for messages from the PC
  // 115200 is the max speed on Arduino Uno, Mega, with AT8u2 USB
  // Use 57600 for the Arduino Duemilanove and others with FTDI Serial
  Serial.begin(115200); 

  // Adds newline to every command
  cmdMessenger.printLfCr();   

  // Attach my application's user-defined callback methods
  attachCommandCallbacks();

  // set pin for blink LED
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

// Loop function
void loop() 
{
  // Process incoming serial data, and perform callbacks
  cmdMessenger.feedinSerialData();
}



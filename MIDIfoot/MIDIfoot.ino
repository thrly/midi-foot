/*
______ _____ _   _ _____ _    ______ ___________ 
| ___ \  ___| | | |  _  | |   |  _  \  ___| ___ \
| |_/ / |__ | |_| | | | | |   | | | | |__ | |_/ /
| ___ \  __||  _  | | | | |   | | | |  __||    / 
| |_/ / |___| | | \ \_/ / |___| |/ /| |___| |\ \ 
\____/\____/\_| |_/\___/\_____/___/ \____/\_| \_|
 / _|          | |                               
| |_ ___   ___ | |_                              
|  _/ _ \ / _ \| __|                             
| || (_) | (_) | |_                              
|_| \___/ \___/ \__|                                               
 
 *  MIDI foot
 *    ~ a Teensy MIDI Foot Controller for the Beholder
 *    ~ oliver thurley, winter 2018 :: http://oliverthurley.co.uk
 *    ~ v0.01a
 * 
 *  info:
 *    - teensy 3.2 board (more Teensy x MIDI info: <https://www.pjrc.com/teensy/td_midi.html>)
 *    - x6 footswitch inputs (momentary buttons), pins 0-5
 *    - x6 LEDs, pins 13-18
 *    - requires Josh Nishikawa's MIDIcontroller library <https://github.com/joshnishikawa/MIDIcontroller>, and is based on the 'buttons' example.
*/

#include <MIDIbutton.h>
#include <MIDIcontroller.h>

byte MIDIchannel = 1; // Set MIDI channel.

//Define any digital pin for buttons
const int pinA = 0; 
const int pinB = 1;
const int pinC = 2;
const int pinD = 3;
const int pinE = 4;
const int pinF = 5;

//Set LED pin (used to show the state of a button)
const int ledA = 18;
const int ledB = 17;
const int ledC = 16;
const int ledD = 15;
const int ledE = 14;
const int ledF = 13;

// Define MOMENTARY buttons (default) and set the Controller Change number.
// Other button types are  LATCH or TRIGGER
// Standard MIDI protocol says CC 20-31 are 'undefined'.
MIDIbutton buttonA(pinA, 20, MOMENTARY); // Control Change #21
MIDIbutton buttonB(pinB, 21, MOMENTARY); // Control Change #22
MIDIbutton buttonC(pinC, 22, MOMENTARY); // Control Change #23
MIDIbutton buttonD(pinD, 23, MOMENTARY); // Control Change #24
MIDIbutton buttonE(pinE, 24, MOMENTARY); // Control Change #23
MIDIbutton buttonF(pinF, 25, MOMENTARY); // Control Change #24

void setup(){
  pinMode(ledA, OUTPUT); // Setup the leds as outputs.
  pinMode(ledB, OUTPUT);
  pinMode(ledC, OUTPUT);
  pinMode(ledD, OUTPUT);
  pinMode(ledE, OUTPUT);
  pinMode(ledF, OUTPUT);
}
void loop(){
  buttonA.send(); // Send the state/value of each button.
  buttonB.send();
  buttonC.send();
  buttonD.send();
  buttonE.send();
  buttonF.send();

  digitalWrite(ledA, buttonA.state);// need to check if state works on buttons that aren't LATCHING
  digitalWrite(ledB, buttonB.state);
  digitalWrite(ledC, buttonC.state);
  digitalWrite(ledD, buttonD.state);
  digitalWrite(ledE, buttonE.state);
  digitalWrite(ledF, buttonF.state);
}

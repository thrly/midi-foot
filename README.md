# Building a Custom MIDI foot pedal
⚠️ ***NOTE: This is an archived post from my blog, written in 2018. The links and libraries may no longer be working. Proceed with caution and hope...*** ⚠️

<img src="https://github.com/thrly/midi-foot/blob/master/images/midi-6-switch-led.JPG" alt="A basic 6-button footswitch USB MIDI controller. LEDs show button state." width="600">
Figure 1: A basic 6-button footswitch USB MIDI controller. LEDs show button state.

## Background
I’m working on some pieces at the moment that require some electronics to be triggered via footpedals in performance. The problem is that I don’t have any MIDI foot pedals, and those that exist are expensive or overkill or both. All I need is a simple, passive MIDI pedal, connectable via USB that can give me a bunch of footswitch triggers (and maybe more features down the road). So, I decided that I’d build my own, and thought that if I documented the (surprisingly easy) process, others might see how easy it is to get custom hardware controllers…  

## The Board
There are a few simple options out there. In the first instance, an [Arduino](https://www.arduino.cc/) would probably cut it. I could use the serial port, or run a MIDI library to get what I need. Arduino is simple to learn, but I didn’t really need all the extras (or the board size). A [Teensy](https://www.pjrc.com/store/teensy32.html) is a smaller, equally affordable, and in some cases, a more versatile microcontroller that gets used a lot in USB MIDI and Music Tech related projects. And there’s a handy [MIDI library](https://github.com/joshnishikawa/MIDIcontroller) already out there. So I opted for a Teensy (v3.2).  

## The Pedal
I sourced a cheap aluminium box here (a nice diecast Hammond box would have been lovely and heavier duty, but they’re expensive. [This](https://uk.rs-online.com/web/p/general-purpose-enclosures/4019698/) (Takachi Electric Industrial, MB-14) was 5 quid). For my current purposes, I only need 4 switches, but I got carried away and cut holes for 6 — not realising that this narrows the footprint considerably, making this a tricky thing to trigger with shoes on. It’s also a real mess of wiring inside as a result. If I’d thought about it before, I would have limited the switches to 4. As they say: _measure twice, cut once._ Lesson learned.  
  
Switches are simple momentary (not-latching) switches, with some LEDs for visual confirmation. Below is a quick breadboard mock-up of the setup:  

<img src="https://github.com/thrly/midi-foot/blob/master/images/midifoot-circuit%20.png" alt="A breadboard mock-up of the circuit" width="600">

Figure 2: A breadboard mock-up of the circuit (in the finished product, I skipped the breadboard and chained the ground on each component) made with Fritzing


<img src="https://github.com/thrly/midi-foot/blob/master/images/midi-side-panel.JPG" alt="Panel-mounted USB port." width="600">

Figure 3: I took the strain off of the Teensy’s USB port by adding a [panel-mount USB cable](https://www.adafruit.com/product/937). It also allows me to use a slightly heavier-duty USB-B-type connector, as opposed to the Teensy’s micro port.

## The Code
The code for the Teensy is simple given Josh Nishikawa’s MIDI controller library available [here](https://github.com/joshnishikawa/MIDIcontroller) (Note, that I'm interested in MIDI _controller numbers/values_, not MIDI _notes_, Teensy can handle regular notes without a library). I’m only using the Pushbutton, assigned as MIDI control numbers (20-25) as they’re typically unassigned. This could also be serial, or MIDI note numbers rather than controller number. The code is simple: when a footswitch is pushed, fire off a MIDI control value of 127, otherwise it’s zero. When the pedal goes down, the LED pin is also lit up. In Max, all I need to read this is a `\[ctlin\]`, `\[pak\]` and a `\[route 20 21 22 23 24 25\]` and I’ve got my pedal triggers into Max (see .maxpat in my git below). Easy.  
  
In the Arduino IDE (Teensy uses the Arduino IDE, just with an additional library. There’s a guide to getting started with it [here](https://www.pjrc.com/teensy/first_use.html)), I wanted the MIDI device to show up with it’s own name, so use the {name.c} file to set that. Set your USB Type to ‘MIDI’ in the Tools menu, and set your Board to 'Teensy 3.2', upload all that to the board and you’re done! A cheap, custom MIDI controller...

## Improvements:
-  _We’re gonna need a bigger boat._ The initial plan was to include jack sockets and a stereo TRS jack so that I could plug in keyboard sustain pedals and an expression pedal to read as MIDI controllers. The code is simple, but since I didn’t leave myself enough space in the box, they won’t fit now.
- _Push-and-hold._ My Max patch takes care of held buttons for flexibility, but this could easily be programmed in at the MIDI device level. Currently, if a button is held for x seconds or more, it clears a buffer.
- Writing in at the Teensy level would let me have LED feedback too (light flashes after x seconds). I suppose I could set this anyway, but without it linking directly to the Max value (via serial?) there’s little point.

### Files:
*   [Teensy MIDIfoot code](https://github.com/thrly/midi-foot/tree/master/MIDIfoot)
*   [Max interface](https://raw.githubusercontent.com/thrly/midi-foot/master/MIDIfoot%20Max%20Interface.maxpat) (copy this and select File > ‘New from Clipboard’ in Max)

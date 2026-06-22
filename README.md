# Smart Lock System (Arduino-Based Project)

## What this is 
This is a simple smart lock system I built using an Arduino.  
It uses a piezo sensor to detect tap patterns and a button to switch into “record mode”.  
If the same pattern is repeated later, it triggers a relay that unlocks a solenoid lock.

Basically, a basic pattern based lock system.

---

## How it works

- You press a button to start recording a pattern  
- You tap a pattern on the sensor  
- When you release the button, that pattern gets saved  
- Later, if you repeat the same tapping pattern, the lock unlocks  

---

## Parts used

- Arduino Uno  
- Piezo sensor (A1)  
- Push button (D2)  
- Relay module (D7)  
- 12V solenoid lock  
- 12V power adapter  
- Breadboard + jumper wires  

---

## What I learned from this
This project was more about understanding real world sensor noise, timing issues, and how unreliable raw analog signals can be without proper filtering.

It also showed how small hardware issues can affect software behavior a lot more than expected.

---

## Limitations
- Sensor can pick up noise sometimes  
- Pattern accuracy depends on how consistently you tap  
- Not fully stable in noisy electrical environments  

---

## Final note
It’s not a perfect system, but it works as a working prototype and helped me understand how real embedded systems behave beyond just code.

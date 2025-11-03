🌟 EnviroAlert System 🌟

Hi! I’m proud to present my EnviroAlert System — an Arduino-based environmental monitoring project I built to detect high temperature 🔥 and low light 🌑 conditions.

Whenever things get too hot or too dark, the system gives a visual alert using an RGB LED, an audible alert using a buzzer, and even switches on a cooling fan using a transistor circuit! This is perfect for simple environmental monitoring setups, especially in DIY or educational projects.

🛠️ What Does It Do?
✅ Measures temperature using a 10kΩ NTC thermistor
✅ Measures light intensity using an LDR (photoresistor)
✅ Signals alerts when:
 🌡️ Temperature > threshold → buzzer + red RGB light + fan ON
 🌤️ Light < threshold → buzzer + blue RGB light
✅ Uses transistor + diode to safely control a 5V fan
✅ Gives clear visual + audible feedback so I always know the system status

🧩 Components I Used
🖥️ Arduino Uno

🌡️ 10kΩ NTC thermistor

🌞 LDR (photoresistor)

🔧 10kΩ resistors (for voltage dividers)

💡 Common cathode RGB LED

🔵 220Ω resistor (for RGB LED)

🎵 Active buzzer

🔌 PN2222 transistor (for fan control)

⚡ 1N4007 diode (flyback protection for fan)

🌀 5V cooling fan

⚙️ Breadboard

🧵 Jumper wires

💻 Laptop/PC (for uploading the code)

🛠️ Wiring Setup (Step by Step)
1️⃣ Thermistor

One leg → 5V

Other leg → A0 + 10kΩ to GND (voltage divider)

2️⃣ LDR (photoresistor)

One leg → 5V

Other leg → A1 + 10kΩ to GND (voltage divider)

3️⃣ RGB LED (common cathode)

Red pin → Pin 11 (with 220Ω resistor)

Green pin → Pin 10 (with 220Ω resistor)

Blue pin → Pin 9 (with 220Ω resistor)

Common cathode → GND

4️⃣ Buzzer

Positive → Pin 7

Negative → GND

5️⃣ Fan + Transistor + Diode

Fan positive → +5V

Fan negative → Collector (C) of PN2222

Emitter (E) → GND

Base (B) → Pin 6 (through 220Ω resistor)

1N4007 diode across fan terminals (cathode to +5V, anode to collector)

💾 Arduino Sketch
cpp
Copy
Edit
// [Insert your final working Arduino code here, cleaned + formatted]
✅ Features included in code:

Reads temperature + light

Compares to thresholds

Controls RGB LED, buzzer, and fan

Uses transistor switching + diode protection




## 📈 Calibration Tips

* Adjust `lightThreshold` based on your room’s lighting.
* Tune `tempThreshold` to match the desired trigger point.

You can monitor real-time readings using the **Serial Monitor** in the Arduino IDE. 🖥️

---

## 🏗️ Improvements & Ideas

* Add an LCD display to show readings.
* Log data to an SD card.
* Connect to Wi-Fi or Bluetooth for remote alerts.
* Add more sensors (humidity, gas, etc.).

---

Thank you for checking out my EnviroAlert System! 🌍💛 Feel free to fork, modify, or improve it. Let’s make the world a little smarter, one project at a time! 💪✨


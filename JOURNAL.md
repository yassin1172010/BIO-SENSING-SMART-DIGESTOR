#  Project Journal: Bio-Sensing Smart Digestor
> **An Automated In-Vitro Systems for Real-Time Drug Dissolution and Photosensitivity Monitoring**
> **Platform:** ESP32 | **Application:** Biopharmaceutics & Pharmaceutical Engineering

---

##  Project Overview & Objective
The **Bio-Sensing Smart Digestor** is an innovative, low-cost scientific simulator designed to monitor the dissolution rate of oral solid dosage forms (capsules/tablets) in a simulated gastric environment. By utilizing non-contact ultrasonic topographic measurement and optical sensors, the system provides real-time data on compound disintegration and light exposure hazards without human intervention.

---

##  Development Log & Milestones

###  Phase 1: Conceptualization & Math Modeling
* **Challenge:** How to measure the dissolution rate of a tablet without physical contact or expensive chemical assays (like UV-Vis Spectroscopy)?
* **The Solution:** We modeled the tablet’s physical decay as a **topographic height variation**. By measuring the distance from a fixed point at the top of a 500mL beaker to the dissolving tablet, we can map this physical erosion to a dissolution percentage ($0\%$ to $100\%$).
* **The Physics of Sound:** Standard speed of sound is $343 \text{ m/s}$ at $20^\circ\text{C}$, but it changes with temperature ($T$). To keep the measurements highly accurate inside a laboratory environment, we integrated the temperature correction formula:
    $$\text{Speed of Sound } (c) = 331.4 + (0.6 \times T) \text{ m/s}$$

---

### Phase 2: Hardware Architecture & Pin Mapping (ESP32)
We migrated the system from Arduino Uno to **ESP32** to utilize its high processing speed and future IoT connectivity. 

#### 🔌 Wiring Topology:
* **Ultrasonic Sensor (HC-SR04):** Trigger $\rightarrow$ `GPIO 12`, Echo $\rightarrow$ `GPIO 13` (Powered by `5V` via VIN).
* **Temperature & Humidity (DHT11/22):** Data $\rightarrow$ `GPIO 4` (Powered by `3.3V`).
* **Light Dependent Resistor (LDR):** Connected to `GPIO 34` (Analog input) using a $10\text{k}\Omega$ pull-down resistor.
    * *Note:* The ESP32 ADC has a **12-bit resolution** (values from $0$ to $4095$), unlike the Arduino's 10-bit ADC ($0$-$1023$). We calibrated our software formulas accordingly.
* **LCD 16x2 (Direct 4-Bit Interface):** * `RS` $\rightarrow$ `GPIO 22` | `E` $\rightarrow$ `GPIO 23`
    * `D4-D7` $\rightarrow$ `GPIO 5, 18, 19, 21`
    * `V0` connected to a fixed $10\text{k}\Omega$ voltage divider for optimal contrast.
* **RGB Status LEDs:**
    * **Green (Safe):** `GPIO 25`
    * **Yellow (Processing):** `GPIO 26`
    * **Red (Danger/Unsafe Light):** `GPIO 27`

---

### Phase 3: Calibration & Experimental Testing
We ran empirical tests using a standard **500mL Beaker** filled with water to simulate gastric fluid.

1.  **Calibration Parameters:**
    * **Empty Beaker Distance (`emptyDistance`):** $12 \text{ cm}$ (Target fully dissolved or empty).
    * **Full Beaker / Initial Tablet Distance (`fullDistance`):** $9 \text{ cm}$ (Tablet placed at the bottom, initial height peak).
2.  **LDR Lux Thresholding:**
    * Under safe dark/filtered laboratory conditions, the ESP32 ADC reads high values ($> 3000$).
    * Under direct light exposure (simulating light-sensitive drug degradation), the ADC value drops below $1500$, triggering the **Red Blinking LED** safety alert.

---

###  Phase 4: Experimental Observations & Results
During our live trial with an effervescent tablet:

| Elapsed Time (s) | Measured Distance (cm) | Calculated Dissolution (%) | LDR Reading | Status LED |
|------------------|------------------------|----------------------------|-------------|------------|
| 0s               | $9.0 \text{ cm}$       | $0\%$                      | 3200 (Safe) | Yellow     |
| 15s              | $9.75 \text{ cm}$      | $25\%$                     | 3150 (Safe) | Yellow     |
| 30s              | $10.5 \text{ cm}$      | $50\%$                     | 3100 (Safe) | Yellow     |
| 45s              | $11.25 \text{ cm}$     | $75\%$                     | 1200 (Light)| Red (Blink)|
| 60s              | $12.0 \text{ cm}$      | $100\%$ (Complete)         | 3100 (Safe) | Green      |

---

## Future Enhancements (Roadmap)
1.  **Mechanical Agitation:** Add a small PWM-controlled DC stirrer to simulate stomach contractions (Peristalsis) and study its effect on dissolution rates.
2.  **IoT Dashboard (Blynk/ThingSpeak):** Stream real-time kinetic curves (Dissolution vs. Time) to a cloud platform for remote pharmaceutical research.
3.  **pH Feedback Loop:** Integrate a pH sensor to monitor changes in acidity as the drug releases its active ingredients.

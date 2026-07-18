title: "Bio-Sensing Smart Digestor"
author: "YASSIN MOHAMED"
description: "An automated laboratory simulator built with ESP32 to monitor pharmaceutical dissolution rates corrected by real-time thermodynamic and environmental variables."
created_at: "2026-07-18"July 18th: Initial System Architecture & Multi-Sensor Integration on ESP32Today, I initiated the engineering phase for the Bio-Sensing Smart Digestor. The core objective was to move away from basic 8-bit microcontrollers and establish a robust 32-bit architecture using the ESP32 to handle multi-sensor arrays, high-resolution ADC processing, and prepare the foundation for future IoT capabilities. What Got DoneDesigned the Multi-Sensor Topology: Mapped out the pinout configurations to safely integrate 5V components (HC-SR04 Ultrasonic Sensor and the Parallel LCD 16x2) alongside 3.3V native components (DHT Sensor and LDR) without causing logic voltage mismatch issues.Assembled the Physical Prototype Circuit: * Mounted the ESP32 on the primary breadboard matrix.Wired the HC-SR04 Ultrasonic sensor over GPIO 12 (Trig) and GPIO 13 (Echo) using the VIN rail for a stable 5V supply line.Set up the DHT Temperature/Humidity sensor on GPIO 4 to capture ambient variables. This will feed into our thermodynamic speed-of-sound correction formula:$$v = 331.4 + 0.6 \times T$$Wired the LDR (Light Dependent Resistor) in a voltage divider configuration with a $10\text{ k}\Omega$ pull-down resistor leading into the analog pin GPIO 34.Connected the Parallel 16x2 LCD Screen directly using data pins GPIO 5, 18, 19, 21 along with control lines RS (GPIO 22) and E (GPIO 23). Added a $10\text{ k}\Omega$ potentiometer to control the liquid crystal contrast dynamic.Placed three status indicators (LEDs: Green, Yellow, Red) on pins GPIO 25, 26, 27 with $220\Omega$ current-limiting resistors for immediate visual telemetry feedback.Calibrated the Beaker Volumetric Environment: Established the physical distance parameters using a standard 500 mL glass laboratory beaker filled up to the 400 mL threshold line.Empty State Baseline (100% Dissolution): Measured exactly 12 cm from the top-mounted sensor frame to the liquid base.Full State Baseline (0% Dissolution): Placed an initial large effervescent test tablet on the submerged platform, bringing the topographic height reading down to 9 cm. Software & Tools UsedFritzing (for schematic mapping and tracing the parallel lines cleanly).Visual Studio Code (VS Code) with the Hackatime extension active for text-based code tracking.Lapse (running on the workbench camera mount to record the circuit assembly, component placements, and initial wire routing).Engineering Artifacts & SchematicsBelow is the exact circuit wiring matrix used to deploy the hardware layout:[ESP32 Pins]            [Target Component & Pin Connections]
5V (VIN) -------------> HC-SR04 VCC  |  LCD Pin 2 (VDD)  |  LCD Pin 15 (A)
GND ------------------> Common Ground Rail (HC-SR04, DHT, LDR Resistor, LEDs, LCD Pins 1, 5, 16)
3.3V -----------------> DHT VCC      |  LDR Pin 1

GPIO 12 --------------> HC-SR04 TRIG
GPIO 13 --------------> HC-SR04 ECHO
GPIO 4 --------------> DHT DATA Pin

GPIO 34 --------------> LDR Pin 2 / 10kΩ Resistor Junction (Analog Input)

GPIO 22 --------------> LCD Pin 4 (RS)
GPIO 23 --------------> LCD Pin 6 (E)
GPIO 5 --------------> LCD Pin 11 (D4)
GPIO 18 --------------> LCD Pin 12 (D5)
GPIO 19 --------------> LCD Pin 13 (D6)
GPIO 21 --------------> LCD Pin 14 (D7)

GPIO 25 --------------> Green LED (+) ---> [220Ω] ---> GND (Safe Status)
GPIO 26 --------------> Yellow LED (+) --> [220Ω] ---> GND (Processing Status)
GPIO 27 --------------> Red LED (+) -----> [220Ω] ---> GND (Photosensitive Danger Alert)

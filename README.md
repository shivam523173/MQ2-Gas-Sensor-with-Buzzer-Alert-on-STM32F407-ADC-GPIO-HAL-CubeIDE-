# STM32F407 + MQ2 Gas Sensor with Buzzer Alert (ADC & GPIO, HAL/CubeIDE)

Reads MQ2 analog output (A0) on **PA0/ADC1_IN0** and turns **ON a buzzer on PD11** if the ADC value exceeds a threshold. Built using **STM32CubeIDE** and HAL drivers.

## 🧩 Components
- STM32F407 Discovery Board
- MQ2 Gas Sensor Module (A0, D0, VCC, GND)
- Active Buzzer
- Breadboard, Jumper Wires, USB Cable

## 🔌 Pin Connections
| Component | Module Pin | STM32 Pin |
|----------|------------|-----------|
| MQ2 VCC  | VCC        | 5V        |
| MQ2 GND  | GND        | GND       |
| MQ2 A0   | Analog Out | **PA0 (ADC1 IN0)** |
| Buzzer + | —          | **PD11 (GPIO Output)** |
| Buzzer – | —          | GND       |

> ⚠️ **ADC limit is 3.3 V.** If your MQ2 A0 can output up to 5 V when powered at 5 V, use a **voltage divider** or condition the signal so **PA0 ≤ 3.3 V**.

## 🛠️ CubeIDE Configuration
1. Create a new project for **STM32F407 Discovery**.
2. Pinout:
   - `PA0` → **ADC1_IN0** (Analog)
   - `PD11` → **GPIO_Output** (Buzzer)
3. Enable **ADC1**.
4. Set system clock to **84 MHz** (PLL from HSI).
5. Generate code and paste the provided **main.c** (unchanged).

## 🧪 How It Works
- MQ2 analog signal is read via ADC.
- If `gas_value > threshold` (default `2000`), buzzer on **PD11** turns **ON**; else **OFF**.
- Polling interval: ~300 ms.

## ▶️ Build & Flash
- Build in STM32CubeIDE → Flash to the board.
- Approach the sensor with a lighter/gas source (no flame on sensor) to test.

## ✅ Expected Readings (example)
- Clean air: **~500–800** ADC counts  
- With gas/smoke: **~2500–3500** ADC counts  
- Above threshold: **Buzzer ON**

## 🔧 Tips
- MQ2 needs **a few minutes of preheat** for stable readings.
- Tune `threshold` in code after observing your sensor’s typical values.
- Ensure **common GND** and solid wiring to avoid noise.

## 🧱 Applications
- Gas leakage detection
- Safety alarms
- Air quality monitoring

## 📄 License
MIT — educational use.

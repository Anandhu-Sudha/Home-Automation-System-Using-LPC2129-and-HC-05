# Home-Automation-System-Using-LPC2129-and-Bluetooth

This project demonstrates a **Home Automation System** using the **LPC2129 microcontroller**, enabling control of household appliances via manual switches or Bluetooth communication. It showcases dual-mode operation with real-time status updates on an LCD and efficient interrupt-driven handling.
![Image](https://github.com/user-attachments/assets/63f20a74-e50b-40aa-addb-116058e1894e)


**Date**: 02-04-2025

---

## 🔍 Overview

The objective of this project is to implement a **dual-mode smart control system** where household appliances (e.g., lights) can be operated using either physical switches or remotely through Bluetooth commands. The system is designed for minimal hardware complexity and fast response time, making it ideal for embedded smart home applications.

## Working Video
https://github.com/user-attachments/assets/902b247d-2811-454f-9bed-fd9aa66161ef

for documentation purposes i did the code for the arduino, this is the system paired with the arduino UNO.

Virtually designed it in proteus and corrected the minor issues that i have faced.

https://github.com/user-attachments/assets/3d22e70f-9140-4b61-bc9f-f76cef86273b

https://github.com/user-attachments/assets/b3e9b092-da59-4548-9787-f48a67c6811e

This is the first time after developing it the proteus, the hex file was flashed to the lpc 2129 board for the first time. 


---

## 🧭 Development Journey

This project was initially simulated in **Proteus** using the **LPC2129** controller to validate the concept and basic functionality.  
After successful simulation:
- The setup was **prototyped using Arduino Uno** for quick testing and hardware debugging.
- Once stable, the final implementation was ported back to **LPC2129**, utilizing its built-in peripherals for real-time embedded control.
- The embedded c code is developed in the Keil Uvision 5.

This iterative development helped validate the system across platforms and ensured a reliable final output.

---

## 🚀 Key Features

- **Dual Mode Operation**: Toggle between **Manual** and **Bluetooth** modes using a dedicated switch.
- **Interrupt-Based Design**: Efficient handling of switch inputs using interrupts.
- **Real-Time Feedback**: 16x2 LCD shows current mode, light status, and pairing info.
- **Bluetooth Control**: Supports serial ASCII commands from a terminal or mobile app.
- **Status LEDs**: Visual feedback for ON/OFF states and active mode.

---

## 🧰 Hardware Components

- 1 × **LPC2129 Microcontroller**
- 1 × **HC-05 Bluetooth Module**
- 1 × **16x2 LCD Display**
- 3 × **LEDs**
  - Mode Indicator 1 (Manual)
  - Mode Indicator 2 (Bluetooth)
  - Light Status Indicator
- 2 × **Push Buttons**
  - SW1 → Mode toggle
  - SW2 → Manual light control
- 1 × **MOC IC + TRIAC setup** for controlling a 230V AC bulb
- 5V power supply (via USB)
- Wires, Breadboard, etc.

---

## 🛠️ Use Case Description

- **Manual Mode**:
  - SW2 controls the light.
  - The LCD displays *Manual Mode* and light status.
  - LEDs indicate mode and light state.

- **Bluetooth Mode**:
  - Control light via Bluetooth terminal using:
    - `'a'` → Turn ON the light
    - `'b'` → Turn OFF the light
  - LCD displays *Bluetooth Mode*, pairing status, and light state.

---

## 📊 Connection Diagram

![Image](https://github.com/user-attachments/assets/8d1c0941-12e7-404d-baed-0f8125071c26)

> Diagram includes LPC2129, HC-05, LCD, switches, LEDs, MOC/TRIAC setup, and bulb.

---

## 🔮 Future Improvements

- Add **RTC module** for time-based automation.
- Design **App-Based UI** for mobile control.
- Integrate **PWM** for light dimming control.
- Expand to control **multiple appliances** (fans, plugs, etc.).
- Include **sensor inputs** (temperature, motion) for smart triggers.

---

## 🧪 Getting Started

To build and test the project:

1. Assemble the LPC2129 with LCD, Bluetooth module, LEDs, and switches.
2. Connect the MOC/TRIAC circuit to safely control a 230V bulb.
3. Create a new project in keil ide, upload all the codes present in the directory , compile and create the hex file.
4. Flash the microcontroller with the appropriate hex file.
5. Power the board using 5V USB input.
6. Press **SW1** to toggle modes, and use **SW2** or Bluetooth commands (`'a'`/`'b'`) to control the light.
7. Observe the system status on the LCD and verify bulb operation.

##  NOTE ** The codes for this and the videos and clips attached are included in the corresponding folders.

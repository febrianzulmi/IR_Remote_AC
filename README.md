# 🌬️ Air Conditioner (AC) Control System via Bluetooth & IR
---

## 🎯 System Overview

**AirLink** is a Bluetooth and InfraRed (IR) based Air Conditioner (AC) control system consisting of two main components:

1. **nRF52840** - A Bluetooth Low Energy (BLE) microcontroller that receives commands from other devices (smartphones, tablets, etc.) and forwards them to the ESP8266 via Serial UART communication.

2. **ESP8266** - A microcontroller that receives commands from the nRF52840 and transmits IR signals to a Daikin AC to control its various functions.

### System Workflow

```text
Device (Master Node / Smartphone / Tablet)
    ↓ [Bluetooth BLE]
nRF52840 (BLE Peripheral)
    ↓ [Serial UART 115200 baud]
ESP8266 (UART Receiver)
    ↓ [InfraRed Signal]
Daikin AC
```

---

## 🔧 Hardware & Software Components

### Hardware
- **nRF52840** - Nordic Semiconductor BLE SoC
- **ESP8266** (NodeMCU) - WiFi module acting as an IR Blaster
- **IR LED** - To transmit IR signals to the AC
- **LED Indicator** - For visual feedback during IR transmission
- **Resistor** - For the IR LED (according to IR LED specifications)

### Software & Libraries
- **nRF5 SDK 17.1.0** - Nordic SDK for the nRF52840
- **Arduino IDE** - For programming the ESP8266
- **IRremoteESP8266 Library** - Library for IR control
- **ir_Daikin Library** - Specific library for Daikin ACs

---

## 📌 Pin Configuration & Wiring

### nRF52840 Pin Configuration

| Pin | Function | Description |
|-----|----------|-------------|
| **P0.13** | TX_NRF | Connected to ESP8266 RX |
| **P0.14** | RX_NRF | Connected to ESP8266 TX |
| **P0.11** | ESP_RESET | Reset pin for the ESP8266 |

### ESP8266 Pin Configuration

| Pin | Function | Description |
|-----|----------|-------------|
| **GPIO2** | LED_PIN | Built-in LED (status indicator) |
| **GPIO4** | IR_SEND_PIN | Pin for IR Blaster (to IR LED) |
| **GPIO5** | IR_INDICATOR_PIN | Indicator LED when sending IR |
| **RX** | Serial RX | Connected to nRF52840 TX |
| **TX** | Serial TX | Connected to nRF52840 RX |

### Wiring Diagram

```text
nRF52840          ESP8266
--------          -------
P0.13 (TX)  --->  RX
P0.14 (RX)  <---  TX
P0.11 (RST) --->  RESET
GND         --->  GND
VCC         --->  3.3V

ESP8266           IR LED
--------          -------
GPIO4      --->  [Resistor] ---> IR LED (+) ---> GND
GPIO5      --->  LED Indicator (+)
```

**Important Notes:**
- Ensure all components share the same ground (Common Ground).
- Use a logic level shifter if necessary, though both the nRF52840 and ESP8266 typically operate at 3.3V.
- The IR LED requires an appropriate resistor (usually 100-220 ohms) to prevent burning out.

---

## ✨ System Features

### 1. **AC Power Control**
   - Turn on the AC with default settings (Cool Mode, 18°C, Auto Fan).
   - Turn off the AC.

### 2. **Temperature Control**
   - Adjust AC temperature.
   - Command format: `TEMP_XX` (e.g., `TEMP_24` for 24°C).

### 3. **Swing Control**
   - Enable vertical and horizontal swing.
   - Disable swing.

### 4. **Bluetooth Low Energy (BLE)**
   - Wireless communication with external devices.
   - Service name: "Nordic_UART".
   - No pairing required (open connection).

### 5. **Auto Reset ESP8266**
   - The nRF52840 automatically resets the ESP8266 before sending commands.
   - Ensures the ESP8266 is in a ready state to receive data.

### 6. **LED Indicators**
   - The built-in ESP8266 LED blinks when receiving a command.
   - The IR Indicator LED lights up when transmitting an IR signal.

---

## 📝 Command List

### Supported Commands

| Command | Description | Example |
|---------|-------------|---------|
| `AC_ON` | Turn on AC (Cool Mode, 18°C, Auto Fan) | `AC_ON` |
| `AC_OFF` | Turn off AC | `AC_OFF` |
| `SWING_ON` | Enable vertical & horizontal swing | `SWING_ON` |
| `SWING_OFF` | Disable swing | `SWING_OFF` |
| `TEMP_XX` | Set temperature (18-30°C) | `TEMP_24` |

### Command Rules

- **Case Insensitive**: Commands can be sent in uppercase or lowercase.
- **Auto Trim**: Leading and trailing spaces are automatically removed.
- **Newline Required**: Every command must end with a `\n` (newline character).
- **Validation**: `TEMP_XX` commands only accept values between 18 and 30.

### Usage Example

```text
ON          → AC turns on (18°C, Cool, Auto Fan)
OFF         → AC turns off
TEMP_24     → Set temperature to 24°C
SWING_ON    → Enable swing
SWING_OFF   → Disable swing
```

---

## 🚀 Usage Guide

### 1. Connecting to the nRF52840

1. **Enable Bluetooth** on your Master Node / Smartphone / Tablet.
2. **Scan** for nearby Bluetooth devices.
3. **Find** the device named **"Nordic_UART"**.
4. **Connect** to the device.
5. The system is ready to use!

### 2. Sending Commands

#### Via Smartphone App (BLE Terminal)
1. Open a BLE Terminal app (e.g., nRF Connect, BLE Scanner).
2. Connect to "Nordic_UART".
3. Select the "Nordic UART Service".
4. Type your command in the text field.
5. Tap **Send** (Make sure your app appends a newline/Enter).

#### Via Serial Monitor (For Testing)
1. Open the Serial Monitor in the Arduino IDE.
2. Set the baud rate to **115200** and line ending to "Newline".
3. Type the command and press Enter.
4. The command will be forwarded to the ESP8266.

### 3. Visual Indicators

- **ESP8266 Built-in LED (GPIO2)**: Blinks when receiving a command.
- **IR Indicator LED (GPIO5)**: Lights up when sending an IR signal to the AC.
- **AC Response**: The AC will beep or react according to the sent command.

---

## ⚙️ Installation & Setup

### nRF52840 Setup

1. **Install nRF5 SDK 17.1.0**
   ```bash
   # Download from the Nordic Semiconductor website
   # Extract to your preferred directory
   ```

2. **Compile & Flash**
   ```bash
   # Use Segger Embedded Studio or nRF Connect SDK
   # To compile the project: move the remote_ac_extension/main.c file to examples/ble_peripheral/ble_app_uart/main.c
   # Compile and flash to the nRF52840
   ```

### ESP8266 Setup

1. **Install Arduino IDE**
   - Download from [arduino.cc](https://www.arduino.cc)

2. **Install ESP8266 Board Support**
   - Go to `File` → `Preferences` → `Additional Board Manager URLs`.
   - Add: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
   - Go to `Tools` → `Board` → `Boards Manager` → Search for "ESP8266" → `Install`.

3. **Install Libraries**
   ```text
   Sketch → Include Library → Manage Libraries
   - Search for: "IRremoteESP8266" → Install
   - Search for: "ir_Daikin" → Install (if listed separately)
   ```

4. **Upload Code**
   - Select Board: `NodeMCU 1.0 (ESP-12E Module)`
   - Set Upload speed: `115200`
   - Upload the `remote_ac_extension.ino` and `feature.ino` files.

---

## 🔍 Troubleshooting

### Issue: AC is not responding

**Possible Causes:**
- IR LED is not connected properly.
- IR LED is broken or does not match specifications.
- Distance is too far from the AC.
- AC does not support the Daikin protocol.

**Solutions:**
- Check the IR LED connection to GPIO4.
- Ensure the IR LED has a clear line of sight to the AC receiver.
- Try moving closer (1-3 meters).
- Verify if your specific AC model supports Daikin remote codes.

### Issue: Bluetooth device not found

**Possible Causes:**
- nRF52840 firmware is not flashed correctly.
- BLE advertising is inactive.
- Device is out of range.

**Solutions:**
- Re-flash the nRF52840 firmware.
- Restart/Reset the nRF52840 board.
- Ensure you are within a 10-meter range.

### Issue: ESP8266 not receiving data

**Possible Causes:**
- Serial UART wiring is incorrect.
- Baud rate mismatch.
- ESP8266 is not being reset correctly.

**Solutions:**
- Check TX/RX wiring between nRF52840 and ESP8266 (it must be crossed: TX to RX, RX to TX).
- Ensure baud rate is set to 115200 on both sides.
- Check if the ESP8266 is properly wired to the Reset pin.
- Check the ESP8266 Serial Monitor for debug output.

### Issue: Commands not recognized

**Possible Causes:**
- Incorrect command format.
- Newline character is missing.

**Solutions:**
- Ensure every command ends with a `\n` (newline).
- Use valid commands (refer to the Command List).

### Issue: Indicator LEDs not working

**Possible Causes:**
- LED is broken.
- Incorrect pin connection.
- LED polarity is reversed.

**Solutions:**
- Check connections to the correct pins (GPIO2 & GPIO5).
- Ensure resistors are properly installed.
- Check LED polarity (Anode to Pin, Cathode to Ground).

---

## 📊 Technical Specifications

### Serial UART Communication
- **Baud Rate**: 115200 bps
- **Data Bits**: 8
- **Stop Bits**: 1
- **Parity**: None
- **Flow Control**: Disabled

### Bluetooth Low Energy (BLE)
- **Standard**: Bluetooth 5.0
- **Service UUID**: Nordic UART Service (NUS)
- **Connection Interval**: 20-75 ms
- **Advertising Interval**: 40 ms
- **Range**: ~10 meters (indoor)

### InfraRed (IR)
- **Protocol**: Daikin AC Protocol
- **Carrier Frequency**: 38 kHz (IRremoteESP8266 default)
- **Range**: 1-5 meters (depends on IR LED power)
- **Transmission**: Double send (for reliability)

### Power Consumption
- **nRF52840**: ~5-10 mA (idle), ~15-20 mA (BLE active)
- **ESP8266**: ~80-170 mA

### Default AC Settings (when turned ON)
- **Mode**: Cool
- **Temperature**: 18°C
- **Fan Speed**: Auto
- **Swing**: Off (can be enabled with `SWING_ON`)

---

## 🔄 Changelog

### Version 1.0
- ✅ AC power control (ON/OFF)
- ✅ Temperature control 
- ✅ Swing control (ON/OFF)
- ✅ Bluetooth BLE communication
- ✅ Serial UART communication setup
- ✅ LED status indicators

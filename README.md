# AirLink - Sistem Kontrol AC via Bluetooth & IR
---

## 🎯 Overview Sistem

**AirLink** adalah sistem kontrol AC (Air Conditioner) berbasis Bluetooth dan InfraRed (IR) yang terdiri dari dua komponen utama:

1. **nRF52840** - Mikrokontroller Bluetooth Low Energy (BLE) yang menerima perintah dari device lain (smartphone, tablet, dll) dan meneruskannya ke ESP8266 melalui komunikasi Serial UART.

2. **ESP8266** - Mikrokontroller yang menerima perintah dari nRF52840 dan mengirimkan sinyal IR ke AC Daikin untuk mengontrol berbagai fungsi.

### Alur Kerja Sistem

```
Device (Master Node/smartphone/tablet)
    ↓ [Bluetooth BLE]
nRF52840 (BLE Peripheral)
    ↓ [Serial UART 115200 baud]
ESP8266 (UART Receiver)
    ↓ [InfraRed Signal]
AC Daikin
```

---

## 🔧 Komponen yang Digunakan

### Hardware
- **nRF52840** - Nordic Semiconductor BLE SoC
- **ESP8266** (NodeMCU) - WiFi module dengan IR Blaster
- **IR LED** - Untuk mengirim sinyal IR ke AC
- **LED Indikator** - Untuk visual feedback saat mengirim IR
- **Resistor** - Untuk IR LED (sesuai spesifikasi IR LED)

### Software & Library
- **nRF5 SDK 17.1.0** - Nordic SDK untuk nRF52840
- **Arduino IDE** - Untuk pemrograman ESP8266
- **IRremoteESP8266 Library** - Library untuk kontrol IR
- **ir_Daikin Library** - Library khusus untuk AC Daikin

---

## 📌 Konfigurasi Pin & Wiring

### nRF52840 Pin Configuration

| Pin | Fungsi | Keterangan |
|-----|--------|------------|
| **P0.13** | TX_NRF | Terhubung ke RX ESP8266 |
| **P0.14** | RX_NRF | Terhubung ke TX ESP8266 |
| **P0.11** | ESP_RESET | Pin reset untuk ESP8266 |

### ESP8266 Pin Configuration

| Pin | Fungsi | Keterangan |
|-----|--------|------------|
| **GPIO2** | LED_PIN | LED Builtin (indikator status) |
| **GPIO4** | IR_SEND_PIN | Pin untuk IR Blaster (ke IR LED) |
| **GPIO5** | IR_INDICATOR_PIN | LED indikator saat mengirim IR |
| **RX** | Serial RX | Terhubung ke TX nRF52840 |
| **TX** | Serial TX | Terhubung ke RX nRF52840 |

### Wiring Diagram

```
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

**Catatan Penting:**
- Pastikan semua komponen menggunakan GND yang sama (common ground)
- Gunakan level shifter jika diperlukan (nRF52840 = 3.3V, ESP8266 = 3.3V)
- IR LED memerlukan resistor sesuai spesifikasi (biasanya 100-220 ohm)

---

## ✨ Fitur-Fitur Sistem

### 1. **Kontrol Power AC**
   - Menyalakan AC dengan pengaturan default (Cool Mode, 18°C, Auto Fan)
   - Mematikan AC

### 2. **Kontrol Suhu**
   - Mengatur suhu AC
   - Format command: `TEMP_XX` (contoh: `TEMP_24` untuk 24°C)

### 3. **Kontrol Swing**
   - Mengaktifkan swing vertikal dan horizontal
   - Menonaktifkan swing

### 4. **Bluetooth Low Energy (BLE)**
   - Komunikasi wireless dengan device lain
   - Service name: "Nordic_UART"
   - Tidak memerlukan pairing (open connection)

### 5. **Auto Reset ESP8266**
   - nRF52840 secara otomatis mereset ESP8266 sebelum mengirim perintah
   - Memastikan ESP8266 dalam kondisi siap menerima data

### 6. **LED Indikator**
   - LED Builtin ESP8266 berkedip saat menerima perintah
   - LED IR Indicator menyala saat mengirim sinyal IR

---

## 📝 Daftar Command

### Command yang Didukung

| Command | Deskripsi | Contoh |
|---------|-----------|--------|
| `AC_ON` | Menyalakan AC (Cool Mode, 18°C, Auto Fan) | `AC_ON` |
| `AC_OFF` | Mematikan AC | `AC_OFF` |
| `SWING_ON` | Mengaktifkan swing vertikal & horizontal | `SWING_ON` |
| `SWING_OFF` | Menonaktifkan swing | `SWING_OFF` |
| `TEMP_XX` | Mengatur suhu (18-30°C) | `TEMP_24` |

### Format Command

- **Case Insensitive**: Command dapat dikirim dalam huruf besar atau kecil
- **Auto Trim**: Spasi di awal/akhir otomatis dihapus
- **Newline Required**: Command harus diakhiri dengan `\n` (newline)
- **Validasi**: Command `TEMP_XX` hanya menerima nilai 18-30

### Contoh Penggunaan

```
ON          → AC menyala (18°C, Cool, Auto Fan)
OFF         → AC mati
TEMP_24     → Set suhu ke 24°C
SWING_ON    → Aktifkan swing
SWING_OFF   → Nonaktifkan swing
```

---

## 🚀 Cara Penggunaan

### 1. Menghubungkan Device ke nRF52840

1. **Aktifkan Bluetooth** pada Master Node/smartphone/tablet Anda
2. **Scan** untuk perangkat Bluetooth di sekitar
3. **Cari** device dengan nama **"Nordic_UART"**
4. **Connect** ke device tersebut
5. Sistem siap digunakan!

### 2. Mengirim Command

#### Via Smartphone App (BLE Terminal)
1. Buka aplikasi BLE Terminal (contoh: nRF Connect, BLE Scanner)
2. Connect ke "Nordic_UART"
3. Pilih service "Nordic UART Service"
4. Ketik command di text field
5. Tekan **Send**

#### Via Serial Monitor (untuk testing)
1. Buka Serial Monitor di Arduino IDE
2. Set baud rate ke **115200**
3. Ketik command dan tekan Enter
4. Command akan diteruskan ke ESP8266

### 3. Indikator Visual

- **LED Builtin ESP8266 (GPIO2)**: Berkedip saat menerima perintah
- **IR Indicator LED (GPIO5)**: Menyala saat mengirim sinyal IR ke AC
- **AC Response**: AC akan merespons sesuai command yang dikirim

---

## ⚙️ Instalasi & Setup

### Setup nRF52840

1. **Install nRF5 SDK 17.1.0**
   ```bash
   # Download dari Nordic Semiconductor website
   # Extract ke folder yang diinginkan
   ```

2. **Compile & Flash**
   ```bash
   # Gunakan Segger Embedded Studio atau nRF Connect SDK
   # Compile project: pindahkan file remote_ac_extension/main.c ke examples/ble_peripheral/ble_app_uart/main.c
   # Flash ke nRF52840
   ```


### Setup ESP8266

1. **Install Arduino IDE**
   - Download dari [arduino.cc](https://www.arduino.cc)

2. **Install ESP8266 Board Support**
   - File → Preferences → Additional Board Manager URLs
   - Tambahkan: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
   - Tools → Board → Boards Manager → Cari "ESP8266" → Install

3. **Install Library**
   ```
   Sketch → Include Library → Manage Libraries
   - Cari: "IRremoteESP8266" → Install
   - Cari: "ir_Daikin" → Install (jika terpisah)
   ```

4. **Upload Code**
   - Pilih Board: NodeMCU 1.0 (ESP-12E Module)
   - Upload speed: 115200
   - Upload file `remote_ac_extension.ino` dan `feature.ino`

---

## 🔍 Troubleshooting

### Masalah: AC Tidak Merespons

**Kemungkinan Penyebab:**
- IR LED tidak terhubung dengan benar
- IR LED rusak atau tidak sesuai spesifikasi
- Jarak terlalu jauh dari AC
- AC tidak mendukung protokol Daikin

**Solusi:**
- Cek koneksi IR LED ke GPIO4
- Pastikan IR LED menghadap ke receiver AC
- Coba jarak lebih dekat (1-3 meter)
- Cek apakah AC Anda mendukung remote Daikin

### Masalah: Bluetooth Tidak Terdeteksi

**Kemungkinan Penyebab:**
- nRF52840 tidak ter-flash dengan benar
- BLE advertising tidak aktif
- Device terlalu jauh

**Solusi:**
- Re-flash firmware nRF52840
- Restart nRF52840
- Pastikan jarak maksimal kurang lebih 10 meter

### Masalah: ESP8266 Tidak Menerima Data

**Kemungkinan Penyebab:**
- Koneksi Serial UART tidak benar
- Baud rate tidak sesuai
- ESP8266 tidak di-reset dengan benar

**Solusi:**
- Cek wiring TX/RX antara nRF52840 dan ESP8266 (harus cross)
- Pastikan baud rate 115200 di kedua sisi
- Cek apakah ESP8266 di-reset sebelum mengirim command
- Cek Serial Monitor ESP8266 untuk debug

### Masalah: Command Tidak Dikenali

**Kemungkinan Penyebab:**
- Format command salah
- Karakter newline tidak terkirim
- Case sensitivity (seharusnya tidak masalah)

**Solusi:**
- Pastikan command diakhiri dengan `\n` (newline)
- Gunakan command yang valid (lihat Daftar Command)
- Cek apakah command dikirim dalam format string yang benar

### Masalah: LED Indikator Tidak Berfungsi

**Kemungkinan Penyebab:**
- LED rusak
- Pin tidak terhubung dengan benar
- Polarity LED salah

**Solusi:**
- Cek koneksi LED ke pin yang benar
- Pastikan resistor terpasang dengan benar
- Cek polarity LED (anode/cathode)

---

## 📊 Spesifikasi Teknis

### Komunikasi Serial UART
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
- **Range**: ~10 meter (indoor)

### InfraRed (IR)
- **Protocol**: Daikin AC Protocol
- **Carrier Frequency**: 38 kHz (default IRremoteESP8266)
- **Range**: 1-5 meter (tergantung IR LED)
- **Transmission**: Double send (untuk reliability)

### Power Consumption
- **nRF52840**: ~5-10 mA (idle), ~15-20 mA (BLE active)
- **ESP8266**: ~80-170 mA

### Default AC Settings (saat ON)
- **Mode**: Cool
- **Temperature**: 18°C
- **Fan Speed**: Auto
- **Swing**: Off (dapat diaktifkan dengan SWING_ON)


## 🔄 Changelog

### Version 1.0
- ✅ Kontrol power AC (ON/OFF)
- ✅ Kontrol suhu 
- ✅ Kontrol swing (ON/OFF)
- ✅ Bluetooth BLE communication
- ✅ Serial UART communication
- ✅ LED indicators

---


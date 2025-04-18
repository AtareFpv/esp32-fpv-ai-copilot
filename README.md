# ESP32 FPV AI Co-Pilot

An onboard AI co-pilot for INAV-powered fixed-wing FPV aircraft. Uses an ESP32 to monitor flight data via MSP and inject intelligent warnings into the OSD displayed in DJI FPV goggles (WTFOS).

### Features
- Reads telemetry data from INAV via MSP
- Injects real-time AI alerts (voltage drop, low altitude, etc.) into DJI OSD
- Easily expandable with external sensors (temperature, baro, etc.)
- Designed for Matek F405-TE + LILYGO T-Display S3

### How It Works
ESP32 connects to a spare UART on the flight controller. It polls INAV via MSP, evaluates conditions, and sends text overlays into the OSD via MSP DisplayPort.

---

## Wiring
| ESP32 (T-Display S3) | Matek F405-TE |
|----------------------|----------------|
| TX (GPIO17)          | RX (e.g. UART3 RX) |
| RX (GPIO18)          | TX (e.g. UART3 TX) |
| GND                  | GND |
| USB-C                | 5V power from BEC or battery pack |

---

## Status: In Development

This is the base code and structure. Expect expansion as we add logic for:
- Stall detection
- Glide estimation
- Custom warning symbols with OSD font patching

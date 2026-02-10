# ESP01 Universal PWM Controller

A simple universal PWM controller based on **ESP-01 (ESP8266)**. The device creates its own WiFi access point and allows you to set the PWM output value directly from a web browser via an HTTP endpoint.

## Features

* Works with ESP-01 (ESP8266)
* Standalone WiFi Access Point (no router required)
* Control PWM output via browser
* Simple HTTP GET interface
* PWM value range: **0 – 1023**

## How It Works

1. Power on the ESP-01.
2. The device creates a WiFi access point.
3. Connect to the ESP-01 WiFi network using your phone or computer.
4. Open a browser and hit the PWM control endpoint.
5. The PWM output is updated instantly.

## Usage

### 1. Connect to ESP-01 WiFi

* SSID: *(defined in firmware)*
* Password: *(defined in firmware, if any)*

Once connected, the ESP-01 will be accessible at:

```
http://192.168.4.1
```

### 2. Set PWM Value

Use the following endpoint in your browser:

```
http://192.168.4.1/set?val=512
```

* `val` = PWM value
* Range: `0` – `1023`

Example:

* `0`     → 0% duty cycle
* `512`   → ~50% duty cycle
* `1023`  → 100% duty cycle

After opening the URL, the PWM output is set immediately.

## Hardware Notes

* ESP-01 has limited GPIOs. Make sure the selected GPIO supports PWM.
* Use appropriate external circuitry (transistor, MOSFET, driver, etc.) when controlling high-current loads.

## Project Status

* Minimal and lightweight
* Designed for simple PWM control applications

## License

This project is released under the MIT License. Feel free to use, modify, and distribute it.

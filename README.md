# Raspberry Pi Pico nRF24L01 Communication Library

A comprehensive library for interfacing the Raspberry Pi Pico with nRF24L01+ wireless transceiver modules. This project enables reliable two-way communication between Pico devices using the popular nRF24L01+ 2.4GHz RF modules.

## Features

- Full-featured nRF24L01+ driver implementation for Raspberry Pi Pico
- Support for both transmitter and receiver modes
- Configurable payload size, channel, and address settings
- Robust error handling and status reporting
- Simple API for sending and receiving data
- Example code demonstrating basic usage
- LED status indicators for transmission and reception events

## Hardware Requirements

- Raspberry Pi Pico (or Pico W)
- nRF24L01+ module (or compatible)
- Jumper wires for connections
- Optional: LEDs and resistors for status indication

## Wiring

Connect your nRF24L01+ module to the Raspberry Pi Pico as follows:

| nRF24L01+ Pin | Raspberry Pi Pico Pin |
|---------------|------------------------|
| VCC           | 3.3V (Pin 36)          |
| GND           | GND (Pin 38)           |
| CE            | GP2 (Pin 4)            |
| CSN           | GP3 (Pin 5)            |
| SCK           | GP18 (Pin 24)          |
| MOSI          | GP19 (Pin 25)          |
| MISO          | GP16 (Pin 21)          |
| IRQ           | Not used               |

Additional connections for status LEDs:
- GP25 (Pico's built-in LED) - TX indicator
- GP15 - RX indicator (connect with a ~330Ω resistor to an external LED)

## Project Structure

```
pico_nrf24l01/
├── CMakeLists.txt          # Main CMake configuration file
├── pico_nrf24l01.cpp       # Main application code
├── pico_sdk_import.cmake   # Pico SDK import script
└── lib/
    └── nRF24L01/           # nRF24L01 library
        ├── CMakeLists.txt  # Library CMake configuration
        ├── nRF24L01.cpp    # Library implementation
        └── nRF24L01.h      # Library header file
```

## Installation and Building

1. Clone or download this repository:
   ```bash
   git clone https://github.com/yourusername/pico_nrf24l01.git
   cd pico_nrf24l01
   ```

2. Make sure you have the Raspberry Pi Pico SDK installed and the `PICO_SDK_PATH` environment variable set correctly.

3. Create a build directory and compile the project:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. Flash the `.uf2` file to your Raspberry Pi Pico:
   - Hold the BOOTSEL button on the Pico while connecting it to your computer
   - Release the button after connecting
   - Drag and drop the `pico_nrf24l01.uf2` file from the `build` directory to the mounted RPI-RP2 drive

## Usage

The example code demonstrates simple communication between two Pico devices. One acts as a transmitter and one as a receiver, determined by the `MODE_TX` define in the code.

### Switching Between Transmitter and Receiver Modes

To configure a Pico as a transmitter, open `pico_nrf24l01.cpp` and set:
```cpp
#define MODE_TX true    // Set to true for transmitter, false for receiver
```

To configure a Pico as a receiver, set:
```cpp
#define MODE_TX false
```

### Serial Output

Connect to the Pico's USB serial port to view debug messages:
- Baud rate: 115200
- You'll see status messages indicating transmission/reception events

## Customization

You can customize the following parameters in `pico_nrf24l01.cpp`:

- RF Channel: `RADIO_CHANNEL` (0-125, default is 76)
- Address: `RADIO_ADDRESS` (5-byte address, default is 0x01, 0x23, 0x45, 0x67, 0x89)
- Payload size: Configured in the `setPayloadSize()` function call (default is 32 bytes)

## Advanced Usage

For more advanced applications, you can integrate this library into your own projects by:

1. Copy the `lib/nRF24L01` directory to your project
2. Include the library in your CMakeLists.txt file
3. Include the header with `#include "lib/nRF24L01/nRF24L01.h"`
4. Initialize the nRF24L01 object with your desired SPI and GPIO settings

## Troubleshooting

Common issues and solutions:

- **No transmission/reception:**
  - Check wiring connections
  - Ensure both devices are using the same channel and address
  - Verify nRF24L01+ module power (should be 3.3V)
  - Check for adequate power supply (some nRF24L01+ modules require a capacitor across VCC/GND)

- **Compilation errors:**
  - Ensure PICO_SDK_PATH is set correctly
  - Check for missing header files
  - Verify CMakeLists.txt configuration

## License

This project is released under the MIT License. See the LICENSE file for details.

## Contributing

Contributions to improve the library are welcome! Please feel free to submit pull requests.

## Acknowledgements

- Based on the Raspberry Pi Pico C/C++ SDK
- Inspired by RF24 and other open-source nRF24L01+ libraries

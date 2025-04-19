#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/spi.h>
#include "lib/nRF24L01/nRF24L01.h"

// Pin definitions
#define SPI_PORT spi0
#define PIN_CE   2
#define PIN_CSN  3
#define PIN_SCK  18
#define PIN_MOSI 19
#define PIN_MISO 16
#define PIN_TX_LED  25 // Built-in LED on Pico
#define PIN_RX_LED  15 // External LED for RX indication

// Define whether this is a transmitter or receiver
#define MODE_TX false  // Set to true for transmitter, false for receiver

// Radio channel and address
#define RADIO_CHANNEL 76
const uint8_t RADIO_ADDRESS[5] = {0x01, 0x23, 0x45, 0x67, 0x89};

int main() {
    // Initialize stdio
    stdio_init_all();
    sleep_ms(2000); // Wait for USB serial connection
    printf("Pico nRF24L01 example starting...\n");

    // Initialize LEDs
    gpio_init(PIN_TX_LED);
    gpio_init(PIN_RX_LED);
    gpio_set_dir(PIN_TX_LED, GPIO_OUT);
    gpio_set_dir(PIN_RX_LED, GPIO_OUT);
    gpio_put(PIN_TX_LED, 0);
    gpio_put(PIN_RX_LED, 0);

    // Initialize the nRF24L01 module
    NRF24L01 radio(SPI_PORT, PIN_CE, PIN_CSN, PIN_SCK, PIN_MOSI, PIN_MISO);
    radio.init();

    // Configure radio settings
    radio.setChannel(RADIO_CHANNEL);
    radio.setPayloadSize(32); // 32 byte payload
    radio.setAddress(RADIO_ADDRESS);
    printf("Radio initialized!\n");

    if (MODE_TX) {
        // Transmitter mode
        printf("Operating in transmitter mode\n");
        uint32_t counter = 0;

        while (true) {
            // Create a message
            char message[32];
            snprintf(message, sizeof(message), "Hello #%lu from Pico!", counter++);

            // Transmit the message
            printf("Sending: %s\n", message);
            gpio_put(PIN_TX_LED, 1); // Turn on TX LED

            bool success = radio.transmit((uint8_t*)message, strlen(message) + 1); // +1 for null terminator

            gpio_put(PIN_TX_LED, 0); // Turn off TX LED

            if (success) {
                printf("Transmission successful!\n");
            } else {
                printf("Transmission failed.\n");
            }

            // Wait befor next transmission
            sleep_ms(1000);
        }
    } else {
        // Receiver mode
        printf("Operating in receiver mode\n");
        radio.setRxMode();

        while (true) {
            uint8_t data[32];
            uint8_t length;

            // Check for received data
            if (radio.receive(data, &length)) {
                // Data received
                gpio_put(PIN_RX_LED, 1); // Turn on RX LED
                
                // Print the received message
                printf("Received: %s\n", (char*)data);

                // Flash the LED briefly
                sleep_ms(50);
                gpio_put(PIN_RX_LED, 0); // Turn off RX LED
            }

            // Small delay to avoid hogging the CPU
            sleep_ms(10);
        }
    }

    return 0;
}
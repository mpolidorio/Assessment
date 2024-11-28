#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define UART_BUFFER_SIZE 256
#define START_BYTE 0x0D
#define CMD_PRINT_HELLO_WORLD 0x01
#define CMD_PRINT_GOODBYE_WORLD 0x02

uint8_t uart_rx_buffer[UART_BUFFER_SIZE];
size_t uart_rx_index = 0;
bool message_received = false;

/*
 * Simulates an interrupt-driven UART handler.
 * Appends received data to a buffer and checks if a complete message has been
 * received.
 */
void uart_interrupt_handler(uint8_t data) {
  uart_rx_buffer[uart_rx_index++] = data;

  if (uart_rx_index > 3 && uart_rx_buffer[0] == START_BYTE) {
    uint8_t expected_length = uart_rx_buffer[3] + 5;
    if (uart_rx_index == expected_length) {
      message_received = true;
      uart_rx_index = 0;
    }
  }

  if (uart_rx_index >= UART_BUFFER_SIZE) {
    uart_rx_index = 0;
  }
}

/*
 * Calculates the checksum of a given data array.
 * XORs checksum.
 */
uint8_t calculate_checksum(const uint8_t *data, size_t length) {
  uint8_t checksum = 0;
  for (size_t i = 0; i < length; i++) {
    checksum ^= data[i];
  }
  return checksum;
}

/*
 * Parses a received message to validate its checksum and execute the command.
 * If the checksum matches, it processes the command and handles unknown
 * commands.
 */
void parse_message(const uint8_t *message) {
  uint8_t command = message[2];
  uint8_t length = message[3];
  const uint8_t *payload = &message[4];
  uint8_t received_checksum = message[4 + length];
  uint8_t calculated_checksum = calculate_checksum(message, 4 + length);

  if (calculated_checksum != received_checksum) {
    printf("Checksum error!\n");
    return;
  }

  switch (command) {
  case CMD_PRINT_HELLO_WORLD:
    printf("Hello, World!\n");
    break;
  case CMD_PRINT_GOODBYE_WORLD:
    printf("Goodbye, World!\n");
    break;
  default:
    printf("Unknown command: 0x%02X\n", command);
  }
}

/*
 * Introduces a blocking delay for the specified number of seconds.
 * Uses the system time to create the delay.
 */
void delay(size_t seconds) {
  time_t start_time = time(NULL);
  while (time(NULL) - start_time < seconds)
    ;
}

int main() {
  // Order of the bytes: Start byte | Address | Command | Length | Payload
  // ( 2 bytes in this case) | Checksum
  uint8_t msg_1[] = {0x0d, 0x01, 0x01, 0x02, 0x34, 0xf3, 0xc8};
  uint8_t size_1 = sizeof(msg_1) / sizeof(uint8_t);

  uint8_t msg_2[] = {0x0d, 0x01, 0x02, 0x02, 0x34, 0xf3, 0xcb};
  uint8_t size_2 = sizeof(msg_2) / sizeof(uint8_t);
  bool flag = true;

  while (1) {
    if (message_received) {
      message_received = false;
      parse_message(uart_rx_buffer);
    }

    for (uint8_t i = 0; i < size_1; i++) {
      if (flag) {
        uart_interrupt_handler(msg_1[i]);
        flag = !flag;
      } else {
        uart_interrupt_handler(msg_2[i]);
        flag = !flag;
      }
    }

    delay(2);
  }

  return 0;
}

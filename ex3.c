#include <stdbool.h>
#include <stdio.h>
#include <time.h>

// States definition
#define OFF 0
#define ON 1
#define PROTECTED 2

/*
 * This function introduces a delay in seconds using the system time.
 */
void delay(size_t seconds) {
  time_t start_time = time(NULL);
  while (time(NULL) - start_time < seconds)
    ;
}

/*
 * The main function simulates a state machine with three states: OFF, ON,
 * and PROTECTED. The states change based on button press and release
 * events, with delays and feedback to simulate a debounce mechanism.
 */
int main(int argc, char *argv[]) {

  size_t current_state = OFF;
  size_t count = 0;
  size_t bt_pressed = false;

  for (;;) {
    if (current_state != PROTECTED) {
      printf(
          "(Simulation): Enter the state of the button\n(1 for Pressed, 0 for "
          "Released)\n");
      scanf("%zu", &bt_pressed);
      delay(1);
      bt_pressed = bt_pressed ? true : false; // simulating a debounce.
    }
    switch (current_state) {
    case OFF:
      if (bt_pressed) {
        printf("Button pressed!\n");
        printf("\a");
        current_state = ON;
      }
      break;

    case ON:
      if (!bt_pressed) {
        printf("Button released!\n");
        printf("\a");
        current_state = PROTECTED;
      }
      break;

    case PROTECTED:
      printf("Protected state!\n Waiting for 10 seconds...\n");
      delay(10);
      current_state = OFF;
      printf("\a");
      break;
    }

    if (bt_pressed) {
      count++;
      printf("Button pressed for %zu (s)\n", count);
    } else
      count = 0;
  }

  return 0;
}

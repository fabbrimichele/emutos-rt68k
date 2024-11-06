#include <stdio.h>
#include <osbind.h> // Include XBIOS functions

// Define bit masks for joystick directions and fire button
#define JOY_UP      0x01
#define JOY_DOWN    0x02
#define JOY_LEFT    0x04
#define JOY_RIGHT   0x08
#define JOY_FIRE    0x10

// Function to read and print joystick status using XBIOS
void read_joystick_xbios(int port) {
    int status = JOYSTICK(port);

    printf("Joystick %d status:\n", port);
    printf("  Up: %s\n", (status & JOY_UP) ? "not pressed" : "pressed");
    printf("  Down: %s\n", (status & JOY_DOWN) ? "not pressed" : "pressed");
    printf("  Left: %s\n", (status & JOY_LEFT) ? "not pressed" : "pressed");
    printf("  Right: %s\n", (status & JOY_RIGHT) ? "not pressed" : "pressed");
    printf("  Fire: %s\n", (status & JOY_FIRE) ? "not pressed" : "pressed");
}

int main() {
    // Example loop: read joystick status repeatedly
    while (1) {
        read_joystick_xbios(0); // Read from joystick port 0
        read_joystick_xbios(1); // Read from joystick port 1

        // Simple delay to avoid overwhelming the output
        for (volatile int i = 0; i < 100000; i++) {}

        // Clear screen between reads for cleaner output
        printf("\033[H\033[J"); // ANSI escape codes to clear screen
    }

    return 0;
}
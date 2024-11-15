#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <mint/osbind.h>


#define IKBD_JOY_UP      0x01
#define IKBD_JOY_DOWN    0x02
#define IKBD_JOY_LEFT    0x04
#define IKBD_JOY_RIGHT   0x08
#define IKBD_JOY_FIRE    0x10

#define IKBD_JOY_EVENT_REPORTING 0x14

void install_joy_vector(void);
void uninstall_joy_vector(void);
void joy_vector(void* status);
void print_joy_status(void);

unsigned short joy_status;

int main() {
    unsigned short old_joy_status;

    Supexec(install_joy_vector);
    Bconout(DEV_IKBD, IKBD_JOY_EVENT_REPORTING);

	while (true) {
        if (joy_status != old_joy_status) {
            print_joy_status();
            old_joy_status = joy_status;
        }
	}

    Supexec(uninstall_joy_vector);
    return 0;
}

void print_joy_status(void) {
    if (joy_status & IKBD_JOY_UP) {
        printf("UP\n");
    } else if (joy_status & IKBD_JOY_DOWN) {
        printf("DOWN\n");
    } else if (joy_status & IKBD_JOY_LEFT) {
        printf("LEFT\n");
    } else if (joy_status & IKBD_JOY_RIGHT) {
        printf("RIGHT\n");
    }

    if (joy_status & IKBD_JOY_FIRE) {
        printf("FIRE\n");
    }
}

void install_joy_vector(void) {
    _KBDVECS* kbd_vectors = Kbdvbase();
    //old_statvec = kbd_vectors->statvec;
    kbd_vectors->joyvec = joy_vector;
}

void uninstall_joy_vector(void) {
    // TODO: restore previous vector
}

void joy_vector(void* status) {
    joy_status = *((unsigned short *)status);
}

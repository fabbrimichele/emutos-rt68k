#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <mint/osbind.h>


#define IKBD_JOY_UP      0x01
#define IKBD_JOY_DOWN    0x02
#define IKBD_JOY_LEFT    0x04
#define IKBD_JOY_RIGHT   0x08
#define IKBD_JOY_FIRE    0x80

#define IKBD_JOY_EVENT_REPORTING 0x14
#define IKBD_JOY_DISABLE         0x08

void install_joy_vector(void);
void uninstall_joy_vector(void);
void joy_vector(void* status);
void print_joy_status(unsigned short status);

_KBDVECS* kbd_vectors;
void* old_joy_vector;

unsigned short joy_status;

int main() {
    unsigned short old_joy_status = 0;
    unsigned short cur_joy_status = 0;

    Supexec(install_joy_vector);
    Bconout(DEV_IKBD, IKBD_JOY_EVENT_REPORTING);

    printf("Move joystick, press FIRE button to exit.\n");

	while (!(cur_joy_status & IKBD_JOY_FIRE)) {
        // Take a snapshot of the joystick status which 
        // continues changing in the interrupt function
        cur_joy_status = joy_status;
        
        if (cur_joy_status != old_joy_status) {
            print_joy_status(cur_joy_status);
            old_joy_status = cur_joy_status;
        }
	}

    Bconout(DEV_IKBD, IKBD_JOY_DISABLE);
    Supexec(uninstall_joy_vector);
    return 0;
}

void print_joy_status(unsigned short status) {
    printf("Status: %04x\n", status);

    if (status & IKBD_JOY_UP) {
        printf("UP\n");
    } else if (status & IKBD_JOY_DOWN) {
        printf("DOWN\n");
    } else if (status & IKBD_JOY_LEFT) {
        printf("LEFT\n");
    } else if (status & IKBD_JOY_RIGHT) {
        printf("RIGHT\n");
    }

    if (status & IKBD_JOY_FIRE) {
        printf("FIRE\n");
    }
}

void install_joy_vector(void) {
    _KBDVECS* kbd_vectors = Kbdvbase();
    old_joy_vector = kbd_vectors->joyvec;
    //old_kbd_vectors->joyvec = kbd_vectors->joyvec;
    kbd_vectors->joyvec = joy_vector;
}

void uninstall_joy_vector(void) {
    //_KBDVECS* kbd_vectors = Kbdvbase();
    //kbd_vectors->joyvec = old_kbd_vectors->joyvec;
    kbd_vectors->joyvec = old_joy_vector;
}

void joy_vector(void* status) {
    joy_status = *((unsigned short *)status);
}

#include <stdio.h>
#include <osbind.h>
#include <mint/ostruct.h>

// The following constants are not defined in ostruct.h
#define GIACCESS_READ  0x00
#define GIACCESS_WRITE 0x80

#define PSG_NOISES_DISABLE       (PSG_NOISEA | PSG_NOISEB | PSG_NOISEC)
#define PSG_TONES_DISABLE        (PSG_ENABLEA | PSG_ENABLEB | PSG_ENABLEC)
#define PSG_ALL_DISABLED         (PSG_NOISES_DISABLE | PSG_TONES_DISABLE)

void pause(long);

int main() {
    printf("\r\nPlaying 440Hz\r\n\r\n");   

    Giaccess(0x0f, PSG_AVOLUME | GIACCESS_WRITE);        // Set volume to max
    Giaccess(~PSG_ENABLEA, PSG_MODE | GIACCESS_WRITE);   // Enable channel A (0 - enable, 1 disable)        
    Giaccess(0x01, PSG_APITCHHIGH | GIACCESS_WRITE);     // 0x11c = 440 Hz at 2MHz
    Giaccess(0x1c, PSG_APITCHLOW | GIACCESS_WRITE);

    pause(100000);

    Giaccess(PSG_ALL_DISABLED, PSG_MODE | GIACCESS_WRITE);    // Disable channel A
    
    return 0;
}


void pause(long length) {
    volatile long i;
    for (i = 0; i < length; i++) {}
}

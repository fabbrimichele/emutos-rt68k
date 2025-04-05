#include <stdio.h>
#include <osbind.h>
#include <mint/ostruct.h>
#include "portab.h"
#include "psg.h"

void pause(long);
void play_pitch(UWORD);
void play_sound(UWORD, UWORD);

static UBYTE snddat[16];        /* read later by interrupt handler */

int main() {
    printf("\r\n");   
    printf("Playing 440Hz with Giaccess\r\n");   
    play_pitch(0x011c);
    pause(100000);

    printf("Playing 440Hz with Dosound\r\n");   
    play_sound(440, 4);
    pause(100000);

    printf("\r\n");   
    return 0;
}

void play_pitch(UWORD pitch) {
    Giaccess(0x0f, PSG_AVOLUME | GIACCESS_WRITE);        // Set volume to max
    Giaccess(~PSG_ENABLEA, PSG_MODE | GIACCESS_WRITE);   // Enable channel A (0 - enable, 1 disable)        
    Giaccess((pitch >> 8) & 0xFF, PSG_APITCHHIGH | GIACCESS_WRITE);     // 0x11c = 440 Hz at 2MHz
    Giaccess(pitch & 0xFF, PSG_APITCHLOW | GIACCESS_WRITE);

    pause(100000);

    Giaccess(PSG_ALL_DISABLED, PSG_MODE | GIACCESS_WRITE);    // Disable all channels
}

/*
 *  play_sound()
 *
 *  This routine plays a sound:
 *      'frequency' is the frequency in Hz; must be > 0
 *      'duration' is the duration in ~250msec units: must be > 0 & < 32
 */
void play_sound(UWORD frequency, UWORD duration) {
    UWORD tp; /* 12 bit oscillation frequency setting value */

    tp = 125000L / frequency;
    snddat[0] = 0;      snddat[1] = LOBYTE(tp);     /* channel A pitch lo */
    snddat[2] = 1;      snddat[3] = HIBYTE(tp);     /* channel A pitch hi */
    snddat[4] = 7;      snddat[5] = 0xFE;
    snddat[6] = 8;      snddat[7] = 0x10;           /* amplitude: envelope */
    snddat[8] = 11;     snddat[9] = 0;              /* envelope lo */
    snddat[10] = 12;    snddat[11] = duration * 8;  /* envelope hi */
    snddat[12] = 13;    snddat[13] = 9;             /* envelope type */
    snddat[14] = 0xFF;  snddat[15] = 0;

    Dosound((LONG)snddat);
}


void pause(long length) {
    volatile long i;
    for (i = 0; i < length; i++) {}
}

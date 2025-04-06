#include <stdio.h>
#include <osbind.h>
#include <mint/ostruct.h>
#include "portab.h"
#include "psg.h"

void pause(long);
void play_pitch(UWORD);
void play_sound(UWORD, UWORD);

/* 
For details about the Dosound format 
see Atari ST Internals page 196
*/
static UBYTE snddat[64] = {
    0x00, 0x1F, // channel A pitch lo
    0x01, 0x01, // channel A pitch hi
    0x07, 0xFE, // enable channel A
    0x08, 0x10, // amplitude: envelope
    0x0B, 0x00, // envelope lo
    0x0C, 0x20, // envelope hi
    0x0D, 0x09, // envelope type
    0xFF, 0x1E, // length (0xFF, value * 20ms)
    // Another note            
    // envelop must be set again, otherwise it continues the previous sound
    0x00, 0x1F, // channel A pitch lo
    0x01, 0x02, // channel A pitch hi
    0x0B, 0x00, // envelope lo 
    0x0C, 0x20, // envelope hi
    0x0D, 0x09, // envelope type
    0xFF, 0x1E, // length (0xFF, value * 20ms)
    0xFF, 0x00  // end script
};

int main() {
    printf("\r\n");   
    printf("Playing 440Hz with Giaccess\r\n");   
    play_pitch(0x011c);
    pause(100000);

    printf("Playing 440Hz with Dosound\r\n");   
    Dosound((LONG)snddat);

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

void pause(long length) {
    volatile long i;
    for (i = 0; i < length; i++) {}
}

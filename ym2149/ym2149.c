#include <stdio.h>
#include <osbind.h>

struct psg {
    unsigned char control;
    unsigned char pad0;
    unsigned char data;
};


// RT68
#define PSG_ADDR 0x0037e400

// Atari ST
//#define PSG_ADDR  0xffff8800

#define PSG ((volatile struct psg *) PSG_ADDR)

#define PSG_A_TONE_PERIOD_FINE   0
#define PSG_A_TONE_PERIOD_COARSE 1
#define PSG_ENABLE               7
#define PSG_A_AMPLITUDE          8

#define MIXER_INPUT_B_DISABLE      0x80
#define MIXER_INPUT_A_DISABLE      0x40
#define MIXER_NOISE_C_DISABLE      0x20
#define MIXER_NOISE_B_DISABLE      0x10
#define MIXER_NOISE_A_DISABLE      0x08
#define MIXER_TONE_C_DISABLE       0x04
#define MIXER_TONE_B_DISABLE       0x02
#define MIXER_TONE_A_DISABLE       0x01
#define MIXER_INPUTS_DISABLE       (MIXER_INPUT_B_DISABLE | MIXER_INPUT_A_DISABLE)
#define MIXER_NOISES_DISABLE       (MIXER_NOISE_C_DISABLE | MIXER_NOISE_B_DISABLE | MIXER_NOISE_A_DISABLE)
#define MIXER_TONES_DISABLE        (MIXER_TONE_C_DISABLE | MIXER_TONE_B_DISABLE | MIXER_TONE_A_DISABLE)
#define MIXER_ALL_DISABLED         (MIXER_INPUTS_DISABLE | MIXER_NOISES_DISABLE | MIXER_TONES_DISABLE)

/*
    ChA_Tone_Period_Fine_Reg   = 0,  // 8 bits
    ChA_Tone_Period_Coarse_Reg = 1,  // 4 bits
    ChB_Tone_Period_Fine_Reg   = 2,  // 8 bits
    ChB_Tone_Period_Coarse_Reg = 3,  // 4 bits
    ChC_Tone_Period_Fine_Reg   = 4,  // 8 bits
    ChC_Tone_Period_Coarse_Reg = 5,  // 4 bits
    Noise_Period_Reg           = 6,  // 5 bits
    Enable_Reg                 = 7,  // 8 bits
    ChA_Amplitude              = 8,  // 5 bits
    ChB_Amplitude              = 9,  // 5 bits
    ChC_Amplitude              = 10, // 5 bits
    Env_Period_Fine_Reg        = 11, // 8 bits
    Env_Period_Coarse_Reg      = 12, // 8 bits
    Env_Shape_Cycle            = 13, // 4 bits
    IO_Port_A_Reg              = 14, // 8 bits
    IO_Port_B_Reg              = 15  // 8 bits
*/

void test_register();
void play_tone();
void pause(long);

void psg_write(unsigned char reg, unsigned char val);
unsigned char psg_read(unsigned char reg);

int main() {
    Super(0);  // Switch to supervisor mode
    printf("\r\nYM2149 tester\r\n\r\n");
    printf("PSG address %x\r\n", PSG_ADDR);

    test_register();
    play_tone();

    Super(1);  // Restore user mode
    return 0;
}

void test_register() {
    unsigned char wr_val = 55;
    unsigned char rd_val;

    printf("\r\nPSG address %x\r\n\r\n", PSG_ADDR);   
    psg_write(PSG_A_TONE_PERIOD_FINE, wr_val);
    printf("Wrote to reg: 0x%x val: 0x%x\r\n", PSG_A_TONE_PERIOD_FINE, wr_val);

    rd_val = psg_read(PSG_A_TONE_PERIOD_FINE);
    printf("Read from reg: 0x%x val: 0x%x\r\n", PSG_A_TONE_PERIOD_FINE, rd_val);
    printf("\r\n");
}

void play_tone() {
    printf("\r\nPlaying Tone...\r\n\r\n", PSG_ADDR);   

    psg_write(PSG_A_AMPLITUDE, 0x0f);
    psg_write(PSG_ENABLE, ~MIXER_TONE_A_DISABLE);
    
    // 0x11c = 440 Hz at 2MHz
    psg_write(PSG_A_TONE_PERIOD_COARSE, 0x01);
    psg_write(PSG_A_TONE_PERIOD_FINE, 0x1c);

    pause(100000);
    psg_write(PSG_ENABLE, MIXER_ALL_DISABLED);
}

void psg_write(unsigned char reg, unsigned char val) {
    // TODO: this is not the proper way, there is a function
    // provided by EmuTOS to read and write to the PSG.
    // The following way should be fine (to be verified):
    // - for low level access use: `giaccess`
    // - to play a sound use `xbios(28, freq, duration, volume)`
    PSG->control = reg;
    PSG->data = val;
}

unsigned char psg_read(unsigned char reg) {
    return PSG->control;
}

void pause(long length) {
    volatile long i;
    for (i = 0; i < length; i++) {}
}

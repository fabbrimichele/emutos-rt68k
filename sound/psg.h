// The following constants are not defined in ostruct.h
#define GIACCESS_READ  0x00
#define GIACCESS_WRITE 0x80

#define PSG_NOISES_DISABLE       (PSG_NOISEA | PSG_NOISEB | PSG_NOISEC)
#define PSG_TONES_DISABLE        (PSG_ENABLEA | PSG_ENABLEB | PSG_ENABLEC)
#define PSG_ALL_DISABLED         (PSG_NOISES_DISABLE | PSG_TONES_DISABLE)
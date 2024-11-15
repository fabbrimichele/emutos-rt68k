NAME=joystick
DEPLOY_HATARI_PATH=/home/michele/hatari/Harddisk/APPS
DEPLOY_CF_PATH=/media/michele/BC6B-3ADA/apps

PREFIX=m68k-atari-mint

CC=$(PREFIX)-gcc
LD=$(PREFIX)-ld
OBJCOPY=$(PREFIX)-objcopy
OBJDUMP=$(PREFIX)-objdump

#  The -Wl,--traditional-format option above is only useful when you want to use a classic Atari debugger like MonST2
#CFLAGS=-O2 -Wl,--traditional-format

CFLAGS=-lgem

build: $(NAME).c
	$(CC) $(NAME).c -o $(NAME).tos -Wa,-S $(CFLAGS) 

clean:
	rm -f $(NAME).tos

deploy-hatari:
	cp $(NAME).tos $(DEPLOY_HATARI_PATH)

deploy-cf:
	cp $(NAME).tos $(DEPLOY_CF_PATH)

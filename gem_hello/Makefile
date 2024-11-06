NAME=g_hello
TYPE=prg
DEPLOY_PATH=/home/michele/hatari/Harddisk/APPS

PREFIX=m68k-atari-mint

CC=$(PREFIX)-gcc
LD=$(PREFIX)-ld
OBJCOPY=$(PREFIX)-objcopy
OBJDUMP=$(PREFIX)-objdump

#  The -Wl,--traditional-format option above is only useful when you want to use a classic Atari debugger like MonST2
#CFLAGS=-O2 -Wl,--traditional-format
#CFLAGS=-lgem

build: $(NAME).c
	m68k-atari-mint-gcc -nostdlib $(LIBCMINI)/crt0.o $(NAME).c -o $(NAME).$(TYPE) -s -L/usr/libcmini/lib -lcmini -lgcc -lgem

clean:
	rm -f $(NAME).prg

deploy:
	cp $(NAME).$(TYPE) $(DEPLOY_PATH)

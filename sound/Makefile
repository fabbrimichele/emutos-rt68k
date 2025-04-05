NAME=sound
DEPLOY_PATH=/home/michele/hatari/Harddisk/APPS

PREFIX=m68k-atari-mint

CC=$(PREFIX)-gcc
LD=$(PREFIX)-ld

#  The -Wl,--traditional-format option above is only useful when you want to use a classic Atari debugger like MonST2
# CFLAGS=-O2 -Wl,--traditional-format
# $(CC) $(NAME).c -o $(NAME).tos $(CFLAGS) 

#CFLAGS=-O2

# The following is supposed to use a smaller libc but it makes the program fail with
# Panic: Illegal Instruction
CFLAGS=-nostdlib /usr/libcmini/lib/crt0.o -s -L/usr/libcmini/lib -lcmini -lgcc

# TODO:
# Note the order of the parameters is important as it is now using CFLAGS doesn't work
# `-nostdlib /usr/libcmini/lib/crt0.o` must be at the beginning and 
# `-s -L/usr/libcmini/lib -lcmini -lgcc` at the end

build: $(NAME).c
	m68k-atari-mint-gcc -nostdlib $(LIBCMINI)/crt0.o $(NAME).c -o $(NAME).tos -s -L/usr/libcmini/lib -lcmini -lgcc

clean:
	rm -f $(NAME).tos

deploy: build
	cp $(NAME).tos $(DEPLOY_PATH)

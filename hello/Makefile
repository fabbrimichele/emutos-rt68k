NAME=hello

PREFIX=m68k-atari-mint

CC=$(PREFIX)-gcc
LD=$(PREFIX)-ld
OBJCOPY=$(PREFIX)-objcopy
OBJDUMP=$(PREFIX)-objdump

#  The -Wl,--traditional-format option above is only useful when you want to use a classic Atari debugger like MonST2
#CFLAGS=-O2 -Wl,--traditional-format

CFLAGS=-O2

build: $(NAME).c
	$(CC) $(CFLAGS) $(NAME).c -o $(NAME).tos

clean:
	rm 	$(NAME).tos

#m68k-atari-mint-gcc hello.c -o hello.tos -O2 -Wl,--traditional-format
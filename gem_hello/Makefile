NAME=g_hello

PREFIX=m68k-atari-mint

CC=$(PREFIX)-gcc
LD=$(PREFIX)-ld
OBJCOPY=$(PREFIX)-objcopy
OBJDUMP=$(PREFIX)-objdump

#  The -Wl,--traditional-format option above is only useful when you want to use a classic Atari debugger like MonST2
#CFLAGS=-O2 -Wl,--traditional-format

CFLAGS=-lgem

build: $(NAME).c
	$(CC) $(NAME).c -o $(NAME).prg $(CFLAGS) 

clean:
	rm 	$(NAME).prg

#m68k-atari-mint-gcc hello.c -o hello.tos -O2 -Wl,--traditional-format
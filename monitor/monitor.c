#include <stdio.h>

// Commands
void help();
void read();
void write();
void set_curr_addr();

// Utils 
int read_addr();

unsigned int curr_addr = 0;

int main() {
   printf("\r\nMonitor v0.1\r\n");
   printf("Press 'h' for help.\r\n\r\n");

   int c = 0;
   while(c != 'q' && c != 'Q') {
    printf("0x%06x> ", curr_addr);
    c = getch();
    printf("%c\r\n", c);

    switch (toupper(c)) {
        case 'S':
            set_curr_addr();
            break;

        case 'R':
            read();
            break;

        case 'W':
            write();
            break;
    
        case 'H':
            help();
            break;

        default:
            break;
    }    
   }

   printf("\r\n");
   return 0;
}

void help() {
    printf("[s]et  : set current address\r\n");
    printf("[r]ead : read memory\r\n");
    printf("[w]rite: write memory\r\n");
    printf("[h]elp : this help\r\n");
    printf("[q]uit : exit program\r\n");
}

void set_curr_addr() {
    unsigned int input_addr;
    
    printf("set addr (hex): ");
    scanf("%x", &input_addr);
    printf("\r\n\r\n");

    curr_addr = input_addr;
}

void read() {
    char* addr;    
    
    printf("read from (hex): ", curr_addr);
    addr = (char*) read_addr_with_default();

    printf("val       (hex): %02x\r\n", (unsigned char)*addr);
    printf("\r\n");
}

void write() {
    char* addr;
    unsigned int val;
    
    printf("write to (hex): ");
    addr = (char*) read_addr_with_default();
    
    printf("byte val (hex): ");
    scanf("%x", &val);
    printf("\r\n\r\n");    
    *addr = (char) val;
}

int read_addr_with_default() {
    char input_addr_str[20];
    unsigned int input_addr;

    fgets(input_addr_str, sizeof(input_addr_str), stdin);
    printf("\r\n");

    // Check if input is empty, use default if so
    if (input_addr_str[0] == '\n' || input_addr_str[0] == '\0') {
        input_addr = curr_addr;
    } else {
        sscanf(input_addr_str, "%x", &input_addr);
    }

    return input_addr;
}


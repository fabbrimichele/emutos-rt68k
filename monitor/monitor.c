#include <stdio.h>

void help();
void read();
void write();

int main() {
   printf("\r\nMonitor v0.1\r\n");
   printf("Press 'h' for help.\r\n\r\n");

   int c = 0;
   while(c != 'q' && c != 'Q') {
    printf("command> ");
    c = getch();
    printf("%c\r\n", c);

    switch (toupper(c)) {
        case 'H':
            help();
            break;

        case 'R':
            read();
            break;

        case 'W':
            write();
            break;
    
        default:
            break;
    }    
   }

   printf("\r\n");
   return 0;
}

void help() {
    printf("[r]ead: read memory\r\n");
    printf("[h]elp: this help\r\n");
    printf("[q]uit: exit program\r\n");
}

void read() {
    unsigned int input_addr;
    char* addr;    
    
    printf("read from (hex): ");
    scanf("%x", &input_addr);
    printf("\r\n");
    addr = (char*) input_addr;

    printf("val       (hex): %02x\r\n", (unsigned char)*addr);
}

void write() {
    unsigned int input_addr;
    char* addr;
    unsigned int val;
    
    printf("write to  (hex): ");
    scanf("%x", &input_addr);
    printf("\r\n");
    addr = (char*) input_addr;

    printf("byte val  (hex): ");
    scanf("%x", &val);
    printf("\r\n");    
    *addr = (char) val;
}


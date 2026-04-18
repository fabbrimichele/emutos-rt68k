#include <osbind.h>
#include <stdio.h>

int main(int argc, char *argv[]) 
{
    int rez;

    switch (argc)
    {
    case 1:
        // Get the current resolution
        rez = Getrez();
        printf("Current resolution %d\r\n\r\n", rez);
        printf("Usage:\r\n");
        printf("set_res [res]\r\n");
        printf("  res 0 low, 1 high\r\n");
        break;
    
    default:
        rez = atoi(argv[1]);
        // We pass -1 for the addresses because we want to keep using
        // the current video memory buffer.
        Setscreen(-1, -1, rez);
        break;
    }
    
    return 0;
}

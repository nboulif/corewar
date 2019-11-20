#include "vm_corewar.h"
#include <signal.h>

void signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        moveTo(10, 0);
        printf("                                                                                                                            ");
        moveTo(10, 10);
        printf("\e[?23l");
        printf("exit\n");
        exit(1);
    }
}
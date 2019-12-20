#include "vm_corewar.h"

void	moveTo(int row, int col)
{
	printf("\x1b[%d;%df", row, col); 
}

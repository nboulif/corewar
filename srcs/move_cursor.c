#include "vm_corewar.h"

void moveUp(int positions)
{
	printf("\x1b[%dA", positions);
}
  
void moveDown(int positions)
{
	printf("\x1b[%dB", positions);
}

void moveRight(int positions)
{
	printf("\x1b[%dC", positions);
}

void moveLeft(int positions)
{
	printf("\x1b[%dD", positions);
}

void moveTo(int row, int col)
{
	printf("\x1b[%d;%df", row, col); 
}

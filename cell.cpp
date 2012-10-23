#include "cell.h"

cell::cell(int row, int col) : row(row), col(col), previous((cell*) 0) {
}

cell::~cell() {
}

/*

cell::~cell(void)
{
auto current = this;
while(current->previous) {
auto temp = current; 
current = current->previous;
delete temp;
temp = 0;
}
}

*/
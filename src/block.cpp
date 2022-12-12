#include "block.h"

void block::Block_initialize(int Block_Name, double w, double h)
 {
	name = Block_Name;
	Height = h;	
	Width = w;
	rotate = 0;	
 }
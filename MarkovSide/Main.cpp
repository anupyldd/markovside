#include "MarkovSide.h"

int main()
{
	MarkovSide msLore("Lore.txt", 2);
	MarkovSide msPatch("Patch Notes.txt", 1);

	msPatch.Generate(30);
	msLore .Generate(30);
	
	return 0;
}
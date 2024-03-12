#include "MarkovSide.h"

int main()
{
	MarkovSide msLore("Lore.txt", 2);
	msLore.Generate(30);

	MarkovSide msPatch("Patch Notes.txt", 2);
	msPatch.Generate(30);

	return 0;
}
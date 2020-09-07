#include "flexible.h"

using namespace std;


// The constructor creates a unique_ptr to a dynamically allocated array of two
// CharacterBlocks using the initialization list syntax. No need to change this
// unless you add fields to the FlexibleCharacterManager.
FlexibleCharacterManager::FlexibleCharacterManager() : blocks(new CharacterBlock[2] {}) {}
size_t size_of_Blocks_Array =2;
char* FlexibleCharacterManager::alloc_chars(size_t n) {
	// TODO: your implementation here
	char* first = this->first_available_address;
	size_t counter = 0;
	bool flag = true;
	for(size_t i =0; i < BUFFER_SIZE; i++)
	{
		if(first[i] == '\0')
		{
			counter++;
			if(counter >=n) //we have a suitable section to check against the blocks[]
			{
				for (size_t x = 0; x < this -> blocks_in_use; x++)
				{
					for(size_t j = i - (n-1); j < i+1; j++)
					{
					if(blocks[x].address == &(first[j])) //signifies that from the blocks there was a part of the memory that was already allocated elsewhere
					{
						flag = false;
						counter = 0;
					}
					}
				}
				if(flag)
				{
					this->blocks_in_use++;
					if(this->blocks_in_use > size_of_Blocks_Array)
					{
						//reallocate an array of size 2n
						int n = this->blocks_in_use;
						size_of_Blocks_Array = n;
						unique_ptr<CharacterBlock[]> blocks2(new CharacterBlock[2*n]);
						blocks2 = move(blocks);
						unique_ptr<CharacterBlock[]> blocks = move(blocks2);
					}
					blocks[this->blocks_in_use].address = first+(i-(n-1));
					blocks[this->blocks_in_use].size = n;

				return first+(i-(n-1));
				}
				else
				{
					flag = true;
				}
			}
		}
		else
		{
			counter = 0;
		}
	}
	return nullptr;
}

void FlexibleCharacterManager::free_chars(char* p) {
	// TODO: your implementation here
	for(size_t i = 0; i < this->blocks_in_use; i++)
	{
		if(blocks[i].address == p)
		{
			for(size_t j = 0; j < blocks[i].size; j++)
			{
				p[j] = '\0';
			}
			blocks[i].address = nullptr;
			blocks[i].size = 0;
		}
	}
}
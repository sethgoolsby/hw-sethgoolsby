#include "simple.h"

using namespace std;


char* SimpleCharacterManager::alloc_chars(size_t size) {
	// TODO: your implementation here
	char* first = this->first_available_address;
	size_t counter = 0;
	for(size_t i =0; i < BUFFER_SIZE; i++)
	{
		if(first[i] == '\0')
		{
			counter++;
			if(counter >=size)
			{
				return first+(i-(size-1));
			}
		}
		else
		{
			counter = 0;
		}
	}
	return nullptr;
}

void SimpleCharacterManager::free_chars(char* address) {
	// TODO: your implementation here
	//We assume that we pass an address with at least one char in it.
	size_t i = 0;
	while(address[i] != '\0')
	{
		address[i] = '\0';
		i++;
	}
}

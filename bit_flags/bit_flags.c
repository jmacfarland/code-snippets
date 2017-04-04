#include <stdlib.h>
#include <math.h>
#include "bit_flags.h"
#include "status.h"

/*********************************************************************
	Author: Jamison MacFarland
	Date: 2/9/2017
	Effort: About an hour
	Purpose: Defines and creates a bit_flags object which can hold a
		given number of bits, and interact with them in several ways.
		When a bit outside of the capacity of storage is requested to 
		be changed, the object automatically resizes to be able to 
		contain the necessary number of bits.
	Interface proposal: 
		1. Add a bit_flags_display function that would display all of
			the bits in the object, so we can see all of the bits at
			once. This is only really useful while testing.
		2. Bit_flags_resize function, so we don't have to repeat
			code in the getter and setter functions.
		3. Bit_flags_encrypt and decrypt, which would XOR the bits with
			a key stored in a second bit_flags object. This would be
			useful for cryptology, and also cause it'd be cool.
		4. Building off of #3, as well as what Doctor Adams mentioned
			in class about steganography, we could add a 
			bit_flags_pad_with_random function that would space each 
			bit of our information out by a certain number of places
			and then fill in the gaps with random bits.
**********************************************************************/

//used double to gain access to ceil function for determining necessary num of integers
double  BITS_PER_INT = sizeof(int) * 8.0;

struct bit_flags
{
	int size;
	int capacity;
	int* data;
};
typedef struct bit_flags Bit_flags;

BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits)
{
	Bit_flags* pBit_flags = (Bit_flags*)malloc(sizeof(Bit_flags));

	if (pBit_flags != NULL)
	{
		int numIntegersNeeded = (int)ceil(number_of_bits / BITS_PER_INT);

		pBit_flags->size = number_of_bits;
		pBit_flags->capacity = numIntegersNeeded * BITS_PER_INT;
		pBit_flags->data = (int*)calloc(numIntegersNeeded, sizeof(int));

		if (pBit_flags->data == NULL)
		{
			free(pBit_flags);
			return NULL;
		}
	}

	return (BIT_FLAGS)pBit_flags;
}

Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;

	//if user wants an out of bounds bit that we don't have already
	if (flag_position > pBit_flags->capacity)
	{
		//I'm not sure if we are allowed to add a function, so I just added the code in here.
		//I realize that it would be a good idea to not repeat myself and just make a function.
		int* temp;
		int i;

		//get new numIntegersNeeded based on where the user wants to put the new bit
		int numIntegersNeeded = (int)ceil(flag_position / BITS_PER_INT);

		temp = (int*)calloc(numIntegersNeeded, sizeof(int));
		if (temp == NULL) return FAILURE;

		//iterates through the ints in the data array
		//if only there was an easier way to iterate through items in an array
		//cough cough python cough
		for (i = 0; i < (pBit_flags->capacity / BITS_PER_INT); i++)
		{
			temp[i] = pBit_flags->data[i];
		}

		free(pBit_flags->data);
		pBit_flags->data = temp;
		pBit_flags->size = flag_position + 1;//the bit the user wanted is now the farthest out we can access (so it's the size)
		pBit_flags->capacity = numIntegersNeeded * BITS_PER_INT;
	}
	else if (flag_position + 1 > pBit_flags->size)//if user wants an out of bounds bit we DO have
	{
		pBit_flags->size = flag_position + 1;
	}

	int arrIndex = flag_position / BITS_PER_INT;//gets num of the index where the int that contains the desired bit resides
	flag_position %= (int)BITS_PER_INT;//gets index of the bit we want within the int

	pBit_flags->data[arrIndex] |= 1 << flag_position;

	return SUCCESS;
}

Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;

	//if user wants an out of bounds bit that we don't have already
	if (flag_position > pBit_flags->capacity)
	{
		//I'm not sure if we are allowed to add a function, so I just added the code in here.
		//I realize that it would be a good idea to not repeat myself and just make a function.
		int* temp;
		int i;

		//get new numIntegersNeeded based on where the user wants to put the new bit
		int numIntegersNeeded = (int)ceil(flag_position / BITS_PER_INT);

		temp = (int*)calloc(numIntegersNeeded, sizeof(int));
		if (temp == NULL) return FAILURE;

		//iterates through the ints in the data array
		//if only there was an easier way to iterate through items in an array
		//cough cough python cough
		for (i = 0; i < (pBit_flags->size/BITS_PER_INT); i++)
		{
			temp[i] = pBit_flags->data[i];
		}

		free(pBit_flags->data);
		pBit_flags->data = temp;
		pBit_flags->size = flag_position + 1;//the bit the user wanted is now the farthest out we can access (so it's the size)
		pBit_flags->capacity = numIntegersNeeded * BITS_PER_INT;
	}
	else if (flag_position + 1 > pBit_flags->size)//if user wants an out of bounds bit we DO have
	{
		pBit_flags->size = flag_position + 1;
	}

	int arrIndex = flag_position / BITS_PER_INT;//gets num of the index where the int that contains the desired bit resides
	flag_position %= (int)BITS_PER_INT;//gets index of the bit we want within the int

	pBit_flags->data[arrIndex] &= ~(1 << flag_position);//creates and ANDs in a full string of 32 1s, with a single zero in the position we want to unset

	return SUCCESS;
}

int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;

	//if out of bounds return -1
	if (flag_position > pBit_flags->size) return -1;

	int arrIndex = flag_position / BITS_PER_INT;//gets num of the index where the int that contains the desired bit resides
	flag_position %= (int)BITS_PER_INT;//gets index of the bit we want within the int
	
	return (pBit_flags->data[arrIndex] >> flag_position) & 1;
}

int bit_flags_get_size(BIT_FLAGS hBit_flags)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;

	return pBit_flags->size;
}

int bit_flags_get_capacity(BIT_FLAGS hBit_flags)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;

	return pBit_flags->capacity;
}

void bit_flags_destroy(BIT_FLAGS* phBit_flags) 
{
	Bit_flags* pBit_flags = (Bit_flags*)*phBit_flags;

	free(pBit_flags->data);//don't orphan the data
	free(pBit_flags);
	*phBit_flags = NULL;//take care of dangling pointer
}
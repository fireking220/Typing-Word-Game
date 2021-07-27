//Scott Patterson
//Mark Morrissey
//Program A1
//This program takes the sentence, "The quick brown fox jumps over the lazy dog" and scrambles it using random numbers
//using the algorithm defined as the Fischer-Yates shuffle and presents it to the user. The user will write the words
//exactly and once they're finished, the computer will tell them their final time in seconds and usecs

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>

//prototypes
int rand_int(int size);
void shuffle(int size, char ** test);

int main()
{
	char * typing_test[] = {"The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
	int size = 9;
	struct timeval tv, start_time, end_time;
	bool is_equal = false;
	char c[51] = "";
	long seconds, mic_seconds;
	
	seconds = mic_seconds = 0;

	//code from Mark
	if(gettimeofday(&tv, 0) != 0)
	{
		printf("ERROR: gettimeofday failed in %s at line %d\n", __func__, __LINE__);
		exit(0);
	}
	
	//seed the random number generator
	srand(tv.tv_usec);
	//shuffle our sentence
	shuffle(size, typing_test);
	//get the start time
	gettimeofday(&start_time, 0);

	//initiate typing test
	for(int i = 0; i < size; ++i)
	{
		do
		{
			printf("The word is: %s\n", typing_test[i]);
			scanf("%50s", c);
			//code to clear our buffer, copied from Mark
			while(getchar() != '\n')
				{
					;
				}
			//code to compare our answer to the word
			if(strncmp(c, typing_test[i], strlen(c) - 1) == 0)
			{
				if(strlen(c) == strlen(typing_test[i]))
				{
					printf("That is correct!\n");
					is_equal = true;
				}
				else
				{
					printf("That is incorrect, try again\n");
				}
			}
			else
			{
				printf("That is incorrect, try again\n");
			}
		}while(!is_equal);
		is_equal = false;
	}

	//get the end time
	gettimeofday(&end_time, 0);
	//figure out seconds and microseconds passes
	seconds = end_time.tv_sec - start_time.tv_sec;
	mic_seconds = (end_time.tv_sec * 1e6 + end_time.tv_usec) - (start_time.tv_sec * 1e6 + start_time.tv_usec);
		
	//prints seconds and leftover microseconds that passes
	printf("%ld seconds and %ld usecs passed...\n", seconds, mic_seconds % 1000000);
	exit(0);
}

//function to produce a random int within the bounds
int rand_int(int size)
{
	return rand() % size;
}

//shuffles our sentence
void shuffle(int size, char ** test)
{
	int j = 0;
	char * tmp = NULL;

	//shuffle the typing_test
	for(int i = 0; i < size; ++i)
	{
		//random number, modding it to fit within the array bounds
		j = rand_int(size);
		//storing a temp
		tmp = test[j];
		//swapping
		test[j] = test[i];
		//point to tmp
		test[i] = tmp;
	}
}

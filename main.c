#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int random_int(int input){
	int result;
	read(input, &result, sizeof(int));
	return result;
}

int main(){
	int  input = open("/dev/urandom", O_RDONLY);
	int write_to = open("data", O_CREAT | O_RDWR);
	int rand_ints[10];
	int i;
	printf("Generating random numbers:\n");
	for (i = 0;  i < 10; i++){
		rand_ints[i] = random_int(input);
	}
	for (i = 0; i < 10; i++){
		printf("\trandom %d: %d\n", i, rand_ints[i]);
	}

	printf("\nWriting numbers to file...\n");
	int bytes = write(write_to, &rand_ints, sizeof(rand_ints));

	printf("\nReading numbers from file...\n");
	int rand_ints_2[10];
	read(write_to, &rand_ints_2, sizeof(rand_ints_2));

	printf("\nVerification that written values were the same:\n");
	for (i = 0; i < 10; i++){
		printf("\tramdom %d: %d\n", i, rand_ints_2[i]);
	}
	return 0;
}

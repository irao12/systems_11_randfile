#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int random_int(int input){
	int result;
	read(input, &result, sizeof(int));
	return result;
}

int main(){
	int  input = open("/dev/random", O_RDONLY);
	if (input == -1)
		printf("opening dev/random error: %s\n", strerror(errno));

	int write_to = open("./output", O_CREAT | O_RDWR, 0777);
	if (write_to == -1)
		printf("creating output error: %s\n", strerror(errno));


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
	int test = write(write_to, rand_ints, sizeof(rand_ints));
	printf("wrote %d bytes\n", test);
	if (test == -1)
		printf("writing error: %s\n",strerror(errno));

	printf("\nReading numbers from file...\n");
	int rand_ints_2[10];
	int fd = open("output", O_RDONLY);

	test = read(fd, rand_ints_2, sizeof(rand_ints_2));

	printf("read %d bytes\n", test);
	if (test == -1)
		printf("reading error: %s\n", strerror(errno));

	printf("\nVerification that written values were the same:\n");
	for (i = 0; i < 10; i++){
		printf("\tramdom %d: %d\n", i, rand_ints_2[i]);
	}

	return 0;
}

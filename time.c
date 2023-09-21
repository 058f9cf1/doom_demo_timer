#include <stdio.h>
#include <stdlib.h>
  
int main(int argc, char* argv[])
{
	// If the file exists and has read permission
	FILE *file = fopen(argv[1], "r");
	
	if(file == NULL)
	{
		return 1;
	}

	//Determine size of the demo
	fseek(file, 0, SEEK_END); //Seek to end of file
	int size = ftell(file); //Get current file pointer
	fseek(file, 0, SEEK_SET); //Seek back to beginning of file

	//Read the contents of the demo to buffer
	signed char buffer[size];
	fread(buffer, size, 1, file);

	//Print out headder information
	printf("Demo name: %s\n", argv[1]);
	printf("Size: %d bytes\n", size);
	printf("Game version: %d\n", buffer[0]);
	printf("Skill: %x\n", buffer[1]+1);
	printf("Episode: %x\n", buffer[2]);
	printf("Map: %x\n", buffer[3]);
	printf("Multiplayer mode: %x\n", buffer[4]);
	printf("-respawn: %x\n", buffer[5]);
	printf("-fast: %x\n", buffer[6]);
	printf("-nomonsters: %x\n", buffer[7]);
	printf("POV: %x\n", buffer[8]);
	printf("P1: %x\n", buffer[9]);
	printf("P2: %x\n", buffer[10]);
	printf("P3: %x\n", buffer[11]);
	printf("P4: %x\n", buffer[12]);

	int count = 0;
	int end = 0;

	//Loop through the rest of the demo
	for(int i = 13; i < size; i++)
	{
		//Determine if the demo has ended
		if(buffer[i] == -128)
		{
			end = 1;
		}

		//Print bytes in groups of 4
		printf("%d ", buffer[i]);
		if(i%4 == 0 & !end)
		{
			printf("\n");
			count++;
		}
	}
	//Display total tics and time
	printf("\nNumber of tics: %d\n", count);
	printf("Final time: %.2f\n", (float)count/35);

	fclose(file);
	return 0;
}

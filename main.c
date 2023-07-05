#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
      	if(argc < 3)
      	{
      		printf("%s <file> <to split in Bytes>\n", argv[0]);

      		return 0;
      	}
   
	int fp1;
	const int max = 1000000;
	int fp[max];
	ssize_t num1;
	ssize_t num2;
	char buffer1[atoi(argv[2])];
	char buffer2[40];
	int i = 0;
	
	if(argc > 1)
	{
		fp1 = open(argv[1], O_RDONLY);
	}

	snprintf(buffer2, 38, "%s.%d", argv[1], i);

	fp[i] = open(buffer2, O_WRONLY | O_CREAT);

	chmod(buffer2, S_IRUSR | S_IWUSR);

	num1 = read(fp1, buffer1, atoi(argv[2]));

	num2 = write(fp[i], buffer1, num1);

	close(fp[i]);

	i++;
	
	while(num1 > 0)
	{
		num1 = read(fp1, buffer1, atoi(argv[2]));
	
		if(num1 == 0)
		{
			break;
		}

		snprintf(buffer2, 38, "%s.%d", argv[1], i);

		fp[i] = open(buffer2, O_WRONLY | O_CREAT);

		chmod(buffer2, S_IRUSR | S_IWUSR);
		
		num2 = write(fp[i], buffer1, num1);

		close(fp[i]);

		i++;
	}

	close(fp1);

	return 0;
}

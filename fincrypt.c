#include <stdio.h>
#include <stdlib.h>
void buffcrypt(signed char* pass)
{
	int buff, i = 0, ms = 0, ks;
	char *buffer = malloc(1);
	while((buff = getchar()) != EOF)
	{
		ms++;
		if(pass[i] == '\0')
		{
			ks = i;
			i = 0;
		}
		buffer = realloc(buffer, ms);
		buffer[ms - 1] = buff + pass[i];
		i++;
	}
	char cache;
	for(i = 0; i < ms; i++)
	{
		cache = buffer[i];
		if(pass[i % ks] > 0)
		{
			for(int j = 0; j < pass[i % ks]; j++)
				buffer[(i + j) % ms] = buffer[(i + j + 1) % ms];
		}
		else
		{
			for(int j = 0; j > pass[i % ks]; j--)
				buffer[(i + j) % ms] = buffer[(i + j - 1) % ms];
		}
		buffer[(i + pass[i % ks]) % ms] = cache;
	}
	for(i = 0; i < ms; i++)
		putchar(buffer[i]);
	free(buffer);
}
int main(int argn, char* args[])
{
	if(argn != 2)
	{
		printf("a messages and small files encryption tool.\nusage:\n%s PASS\nto encrypt the buffer.\n", args[0]);
		return 1;
	}
	buffcrypt((signed char*) args[1]);
	return 0;
}

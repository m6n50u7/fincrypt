#include <stdio.h>
#include <stdlib.h>
int mod(int a, int b)
{
	int c = a % b;
	if(c < 0)
		c += b;
	return c;
}
void buffdecrypt(signed char* pass)
{
	int buff, i = 0, ms = 0, ks;
	char *buffer = malloc(0);
	while((buff = getchar()) != EOF)
	{
		ms++;
		if(pass[i] == '\0')
		{
			ks = i;
			i = 0;
		}
		buffer = realloc(buffer, ms);
		buffer[ms - 1] = buff;
		i++;
	}
	char cache;
	for(i = ms - 1; i >= 0; i--)
	{
		cache = buffer[mod(i + pass[i % ks], ms)];
		if(pass[i % ks] < 0)
		{
			for(int j = pass[i % ks]; j < 0; j++)
				buffer[mod(i + j, ms)] = buffer[mod(i + j + 1, ms)];
		}
		else
		{
			for(int j = pass[i % ks]; j > 0; j--)
				buffer[mod(i + j, ms)] = buffer[mod(i + j - 1, ms)];
		}
		buffer[i % ms] = cache;
	}
	for(i = 0; i < ms; i++)
	{
		putchar((buffer[i] - pass[i % ks]) % 256);
	}
	free(buffer);
}
int main(int argn, char* args[])
{
	if(argn != 2)
	{
		printf("a file encryption tool.\nusage:\n%s PASS\nto encrypt the buffer.", args[0]);
		return 1;
	}
	buffdecrypt((signed char*) args[1]);
	return 0;
}

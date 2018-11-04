#include <stdio.h>
#include "DES.h"

int main(int argc, char **argv)
{
	char *result = "Hi, this's my first repository!";
	result = des_ecb(result, "DevDopax", ENCRYPT);
	result = des_ecb(result, "DevDopax", DECRYPT);
	printf("Result: %s\n", result);
	free(result);
	return 0;
}

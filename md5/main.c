#include <stdio.h>
#include <stdlib.h>
#include "md5.h"

void hexhash(char *str, char *hash);

int main(int argc, char *argv[])
{
	char hash[33];
	hexhash("hello", hash);
	printf("%s", hash);
	getchar();
}

void hexhash(char *str, char *hash)
{
	struct MD5Context mdc;
	unsigned char dg[16];
	MD5Init(&mdc);
	MD5Update(&mdc, str, strlen(str));
	MD5Final(dg, &mdc);
	
	sprintf(hash, "%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x", 
		dg[0], dg[1], dg[2],
 		dg[3], dg[4], dg[5], dg[6], dg[7], dg[8], dg[9], dg[10], dg[11],	
 		dg[12], dg[13], dg[14], dg[15]);
}
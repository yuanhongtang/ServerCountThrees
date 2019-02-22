#include "readInt32BitLE.h"

int readInt32BitLE(FILE *inFile)
{
	int result = 0;
	unsigned char *resultPtr = (unsigned char *) &result;

	if (inFile) {
		int i = 3;

		fread(&resultPtr[i--],1,1,inFile);
		fread(&resultPtr[i--],1,1,inFile);
		fread(&resultPtr[i--],1,1,inFile);
		fread(&resultPtr[i--],1,1,inFile);
	}
	return result;
}

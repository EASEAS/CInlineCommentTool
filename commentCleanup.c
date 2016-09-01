#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int fileFinished;
int charCount(FILE *FP);

int main(int argc, char * argv[]){
	char* returnFile;
	int i,j,total;
	FILE *fp,*op;

	if (argc < 2) return -1; /* a file must be provided to program, throws error if number of args is too small*/
	
	for (i = 1 ; i < argc ; i++) /*loop through all args except the first */
	{

		char character,*line;
		int lineLength;
		
		fp = fopen(argv[i], "r+");
		if (fp == NULL) break;
		
		returnFile = (char*)malloc(strlen( argv[i]) );
		strncpy( returnFile, argv[i], strlen(argv[i]) );
		*(returnFile) = '1';
		
		op = fopen(returnFile, "w+");
		if (op == NULL) break;
		
		fileFinished = 0;
		total = 0;
		while (!fileFinished)
		{

			lineLength = charCount(fp);
			
			line = (char*)malloc(lineLength);

			fgets(line,lineLength,fp);
			total+=lineLength;

			for (j = 0 ; j < lineLength ; j++)
			{	

				if ( *(line + j) == '/')
				{

					if (*(line + j + 1) == '/')
					{
						
						*(line + j + 1) = '*';
						line = (char*)realloc(line, (lineLength + 2));
						*(line + lineLength - 1) = '*';
						*(line + lineLength ) = '/';
						break; /* breaks becuase there is no need to search for more inline comments on this line*/
					}
				}
			}

			fputs(line,op);
			fputc('\n',op);
			free(line);
			fseek(fp, total, SEEK_SET);
		}
	}
	if (fclose(fp)){
		printf("%s\n", "input file close error");
	}
	if (fclose(op)){
		printf("%s\n", "output file close error");
	}
}

int charCount (FILE *FP){
	int c, count;

	c = fgetc(FP);
	count = 0;
	while (c != EOF && c != '\n')
	{
		c = fgetc(FP);
		count++;
	}
	if (c == EOF) fileFinished = 1;
	fseek(FP, -(count+1),SEEK_CUR);
	return ++count;
}
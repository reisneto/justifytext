#include <stdio.h>
#include <stdlib.h>

FILE *open_file(char *filename);
void print_doc(FILE *doc);
	
int main(int argc, char *argv[])
{
	int line_size;
	FILE *doc;
	if(argc != 3)
	{
		fprintf(stderr, "Usage: ./format line_size file\n");
		exit(1);
	}
	
	line_size = atoi(argv[1]);

	doc = open_file(argv[2]);
	print_doc(doc);
	fclose(doc);
	return 0;
}

void print_doc(FILE *doc)
{
	char line[100];
	while(!feof(doc))
	{
		if( fgets(line, 100, doc) == NULL ) break;
		printf("%s",line);
	}
	return;
}

FILE *open_file(char *filename)
{
	FILE *doc;
	doc = fopen(filename, "r");
	if (doc == NULL) 
	{
		perror("Error opening file");
		exit(1);
		return NULL;
	}
	else
	{
		return doc;
	}
}

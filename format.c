#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX 101
FILE *open_file(char *filename, char type[]);
void print_doc(FILE *doc);
	
int main(int argc, char *argv[])
{
	int line_size;
	FILE *doc;
	FILE *doc_out;
	char word[MAX];
	int counter;


	if(argc != 3)
	{
		fprintf(stderr, "Usage: ./format line_size file\n");
		exit(1);
	}
	
	line_size = atoi(argv[1]);

	doc = open_file(argv[2],"r");

	doc_out = open_file(strcat(argv[2],".out"),"w"); 

	/** algorithm
	 handle lines with a variable
	 **/

	/* Assuming that there isn't a word greather than 25 chars */
	fscanf(doc,"%s",word);
	fprintf(doc_out,"%s", word);
	counter = strlen(word);

	while( (fscanf(doc,"%s",word) == 1) )
	{
			if(counter + strlen(word) < line_size)
			{
				fprintf(doc_out," %s",word);
				counter += strlen(word);
			}
			else
			{
				fprintf(doc_out,"\n%s",word);
				counter=0;
			}
	}
	fclose(doc);
	fclose(doc_out);

	doc_out = open_file(argv[2],"r"); 

	print_doc(doc_out); 

	return 0;
}

void print_doc(FILE *doc)
{
	char line[MAX];
	while(!feof(doc))
	{
		if( fgets(line, MAX, doc) == NULL ) break;
		printf("%s",line);
	}
	return;
}

FILE *open_file(char *filename,char type[])
{
	FILE *doc;
	doc = fopen(filename, type);
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

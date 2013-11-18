#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX 101
FILE *open_file(char *filename, char type[]);
void print_doc(FILE *doc);
int compare(const void* a,const void* b);
int wordCount(char ***wordlist, int *numwords, char word[]);

int main(int argc, char *argv[])
{
	int line_size;
	FILE *doc;
	FILE *doc_out;
	char word[MAX];
	int counter;
	int numwords=1;
	int i;
	char **wordlist = malloc(sizeof(char*));

	wordlist[0] = "default";

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

	/*** JUSTIFY TEXT ***/
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
			wordCount(&wordlist, &numwords, word);
	}

	fclose(doc);
	fclose(doc_out);


	/*** PRINT OUT JUSTIFIED TEXT ***/
	doc_out = open_file(argv[2],"r"); 

	print_doc(doc_out); 

	/*qsort((char *) wordlist, numwords, sizeof(wordlist[0]), compare);*/

	printf( "\n\nAdded %d words to the array and they are:\n", numwords );
	for( i = 0; i < numwords; i++ )
		printf( "%s\n", wordlist[ i ] );


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


int wordCount(char ***wordlist, int *numwords, char word[])
/* Put word inside wordlist, even if there's already a copy of it */
{
	/* Expand our array of pointers by one pointer's worth */
	*wordlist = realloc( *wordlist, (*numwords + 1) * sizeof( char * ) );
	if(*wordlist == NULL)
		return 0;
	
	/* Make a duplicate of the word and save the pointer to it */
	(*wordlist)[ *numwords ] = strdup( word);
	(*numwords)++;	
	return 1;
}

int compare(const void* a,const void* b)
{
	return(strcmp( *( (char**)a),*( (char**)b) ) );

}

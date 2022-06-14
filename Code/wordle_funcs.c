#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *create_int_vector(int length){
   return (int*) malloc( (size_t) length*sizeof(int));
}

void destroy_int_vector(int *vector){
   free(vector);
}

int **create_int_array(int dim_x, int dim_y){
	int i;
	int **array;
	array=(int**) malloc(dim_x * sizeof(int*) );
	array[0] = (int *) malloc(dim_x*dim_y * sizeof(int) );
	for(i=1;i< dim_x;i++){
		array[i]=array[0] + i * dim_y;
	}
	return array;
}

void destroy_int_array(int **array){
   free(array[0]);
   free(array);
}

int len_word(char *word){
	int i=0;
	while (word[i] != '\0') i++;
	return i;
}

int **read_word_list(char *filename, int *size){

	FILE *fp = fopen(filename, "r");
	
	if (fp == NULL){
		printf("Error: could not open file %s", filename);
	}
	
	// reading line by line, max 256 bytes;
	int length = 10;
	char line[length];
	
	//count the lines
	int lines = 0;
	while (fgets(line, length, fp)){
		lines++;
	}
	
	*size = lines;

	// printf("lines: %d\n",lines);
	int **word_list = create_int_array(lines,6);
	
	rewind(fp);
	
	int i;
	lines = 0;
	while (fgets(line, length, fp)){
		for(i=0;i<5;i++){
			word_list[lines][i] = (int)line[i];
		}
		// strcpy(word_list[lines],word);
		lines++;
	}

	// printf("1st word: %d%d%d%d%d\n",word_list[0][0],word_list[0][1],word_list[0][2],word_list[0][3],word_list[0][4]);
	// printf("1st word: %c%c%c%c%c\n",(char)word_list[0][0],(char)word_list[0][1],(char)word_list[0][2],(char)word_list[0][3],(char)word_list[0][4]);

	
	// close the file
	fclose(fp);
	
	return word_list;
}

void test_word(int *guess, int *answer, int *response){
/*  ************************************************
	Tests a guess word against an answer and generates
	a response string
	
	input:
	
	guess    :: A 5 letter string containing the guess word
	answer   :: A 5 letter string containing the solution word
	
	returns:
	
	response :: A 5 letter response string containing the information
			    wordle would return. in the string b=black
			    y=yellow, and g=green
	************************************************ */
	
	int i,j;
	int *guess2 = create_int_vector(5);
	int *answer2 = create_int_vector(5);
	
	for(i=0;i<5;i++){
		guess2[i] = guess[i];
		answer2[i] = answer[i];
		// Set default to all black
		response[i] = 0;
		// Check for green matches
		if(guess2[i]==answer2[i]){
			response[i] = 2;
			guess2[i] = -2;
			answer2[i] = -1;
		}
	}
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			if(guess2[i]==answer2[j]){
				response[i] = 1;
				guess2[i]=-2;
				answer2[j]=-1;
			}
		}
	}
	destroy_int_vector(guess2);
	destroy_int_vector(answer2);
}

int check_match(int *word1, int *word2){
	int i;
	int test = 1;
	for(i=0;i<5;i++){
		if(word1[i]!=word2[i]){
			test = 0;
		};
	}
	return test;
}

int **update_list(int *guess, int *response, int *size, int **word_list, int *size_new){
/*  ************************************************
	Takes a list of words and removes all words which
	are not compatible with the guess and response
	
	input:
	
	guess     		:: A 5 letter string containing the guess word
	response		:: A 5 letter response string containing the information
					   wordle would return. in the string b=black
					   y=yellow, and g=green
	word_list		:: A vector of 5 letter strings for each word
	
	returns:
	
	word_list_new	:: returns a new word list which is the subset
					:: of 'word_list' which could be the solution
					:: given the ruess and response
	************************************************ */	
	
	int i,j;	
	int count=0;
	int test;
	int *response_test = create_int_vector(6);
	int *word = create_int_vector(6);
	
	for(i=0;i<*size;i++){
		for(j=0;j<5;j++){
			word[j] = word_list[i][j];
		}
		test_word(guess,word,response_test);
		
		if(check_match(response,response_test)){
			count+=1;
		}
	}
	
	*size_new = count;
	int **word_list_new = create_int_array(count,6);
	
	count = 0;
	for(i=0;i<*size;i++){
		for(j=0;j<5;j++){
			word[j] = word_list[i][j];
		}
		test_word(guess,word,response_test);
		
		if(check_match(response,response_test)){
			for(j=0;j<5;j++){
				word_list_new[count][j] = word[j];
			}
			count+=1;
		}
	}
	return word_list_new;
}





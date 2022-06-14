#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <strings.h>
#include "wordle_funcs.h"


	


int main(){
	
	char filename[128] = "./Data/words_all.txt";
	int i,j,k;
	
	int size_all;
	int **word_list = read_word_list(filename, &size_all);
	
	printf("\ntotal number of words: %d\n",size_all);

	printf("1st word: %c%c%c%c%c\n",(char)word_list[0][0],(char)word_list[0][1],(char)word_list[0][2],(char)word_list[0][3],(char)word_list[0][4]);

	
	// printf("first word: %s\n",word_list[0]);
	
	// Start actual code
	
	printf("***************************************\n");
	printf("*                                     *\n");
	printf("*            Wordle Solver            *\n");
	printf("*                                     *\n");
	printf("***************************************\n");
/*	
	int sample = 1000;
	int **word_list_tmp;
	int *rand_list = create_int_vector(sample);
	
	int test_unique = 1;

	word_list_tmp = create_int_array(sample,5);
	for(i=0;i<sample;i++) {
		while(test_unique){
			test_unique = 0;
			j = rand() % size_all;
			rand_list[i]=j;
			for(k=0;k<i;k++){
				if(j==rand_list[k]){
					test_unique = 1;
				}
			}
		}
		for(k=0;k<5;k++){
			word_list_tmp[i][k] = word_list[j][k];
		}
		test_unique = 1;
	}
	
	
	
	// score list to select best guesses
	// Method is to check for each guess word
	// and each possible answer from the sub sample
	// how many words would be compatible with the 
	// information gained from that guess
*/	
	int score;
	int *guess = create_int_vector(5);
	int *answer = create_int_vector(5);
	int *word = create_int_vector(5);
	int *response = create_int_vector(5);
	int *response_test = create_int_vector(5);
/*	
	for(i=0;i<size_all;i++){
		score = 0;
		guess = word_list[i];
		for(j=0;j<sample;j++){
			answer = word_list_tmp[j];
			test_word(guess,answer,response);
			for(k=0;k<sample;k++){
				word = word_list_tmp[k];
				test_word(guess,word,response_test);
				if(check_match(response_test,response)){
					score += 1;
				}
			}
		}
		word_list[i][5] = score;
	}
	
	int smallest;
	int sml_index;
	for(k=0;k<20;k++){
		sml_index=0;
		smallest = word_list[0][5];
		for(i=1;i<size_all;i++){
			if(smallest>word_list[i][5]){
				smallest = word_list[i][5];
				sml_index = i;
			}
		}
		printf("%d - %c%c%c%c%c\n",word_list[sml_index][5],(char)word_list[sml_index][0],(char)word_list[sml_index][1],(char)word_list[sml_index][2],(char)word_list[sml_index][3],(char)word_list[sml_index][4]);
		word_list[sml_index][5] = sample*sample;
	}
*/		
	printf("Select you first guess. Some suggestions are below.\n");
	printf("22430 - reais\n22616 - lares\n22830 - tares\n22844 - nares\n23054 - rales\n23302 - rates\n23432 - saner\n23744 - soare\n23816 - serai\n24382 - aeros\n\n");
	// printf("[aloes\tsoare\taeros\taeons\tlares]\n\n");
	printf("Enter your guess now:\n");
	
	char text[20];
	fgets(text,20,stdin);
	
	while(len_word(text)!=6){
		printf("\nGuesses must be 5 letters\n");
		fgets(text,20,stdin);
	} 
	
	for(i=0;i<5;i++){
		guess[i] = (int)text[i];
	}
	
	/*
	int *test1 = create_int_vector(5);
	int *test2 = create_int_vector(5);
	int *test3 = create_int_vector(5);
	int *test4 = create_int_vector(5);
	int *test5 = create_int_vector(5);
	int *test6 = create_int_vector(5);
	
	strcpy(text,"abode");
	for(i=0;i<5;i++){
		test1[i] = (int)text[i];
	}

	strcpy(text,"fgooj");
	for(i=0;i<5;i++){
		test2[i] = (int)text[i];
	}
	
	strcpy(text,"koonp");
	for(i=0;i<5;i++){
		test3[i] = (int)text[i];
	}
	
	strcpy(text,"qosou");
	for(i=0;i<5;i++){
		test4[i] = (int)text[i];
	}
	
	strcpy(text,"owoyo");
	for(i=0;i<5;i++){
		test5[i] = (int)text[i];
	}
	
	test6 = test_word(test1, test2);
	printf("12: 00200 - %d%d%d%d%d\n",test6[0],test6[1],test6[2],test6[3],test6[4]);
	test6 = test_word(test1, test3);
	printf("13: 00200 - %d%d%d%d%d\n",test6[0],test6[1],test6[2],test6[3],test6[4]);
	test6 = test_word(test1, test4);
	printf("14: 00100 - %d%d%d%d%d\n",test6[0],test6[1],test6[2],test6[3],test6[4]);
	test6 = test_word(test1, test5);
	printf("15: 00200 - %d%d%d%d%d\n",test6[0],test6[1],test6[2],test6[3],test6[4]);
	
	test6 = test_word(test2, test1);
	printf("21: 00200 - %d%d%d%d%d\n",test6[0],test6[1],test6[2],test6[3],test6[4]);
	test6 = test_word(test2, test3);
	printf("23: 00210 - %d%d%d%d%d\n",test6[0],test6[1],test6[2],test6[3],test6[4]);
	test6 = test_word(test2, test4);
	printf("24: 00120 - %d%d%d%d%d\n",test6[0],test6[1],test6[2],test6[3],test6[4]);
	test6 = test_word(test2, test5);
	printf("25: 00210 - %d%d%d%d%d\n",test6[0],test6[1],test6[2],test6[3],test6[4]);
	
	test6 = test_word(test3, test1);
	printf("31: 00200 - %d%d%d%d%d\n",test6[0],test6[1],test6[2],test6[3],test6[4]);
	test6 = test_word(test3, test2);
	printf("32: 01200 - %d%d%d%d%d\n",test6[0],test6[1],test6[2],test6[3],test6[4]);
	test6 = test_word(test3, test4);
	printf("34: 02100 - %d%d%d%d%d\n",test6[0],test6[1],test6[2],test6[3],test6[4]);
	test6 = test_word(test3, test5);
	printf("35: 01200 - %d%d%d%d%d\n",test6[0],test6[1],test6[2],test6[3],test6[4]);
	
	test6 = test_word(test4, test1);
	printf("41: 01000 - %d%d%d%d%d\n",test6[0],test6[1],test6[2],test6[3],test6[4]);
	test6 = test_word(test4, test2);
	printf("42: 01020 - %d%d%d%d%d\n",test6[0],test6[1],test6[2],test6[3],test6[4]);
	test6 = test_word(test4, test3);
	printf("43: 02010 - %d%d%d%d%d\n",test6[0],test6[1],test6[2],test6[3],test6[4]);
	test6 = test_word(test4, test5);
	printf("45: 01010 - %d%d%d%d%d\n",test6[0],test6[1],test6[2],test6[3],test6[4]);
	
	test6 = test_word(test5, test1);
	printf("51: 00200 - %d%d%d%d%d\n",test6[0],test6[1],test6[2],test6[3],test6[4]);
	test6 = test_word(test5, test2);
	printf("52: 10200 - %d%d%d%d%d\n",test6[0],test6[1],test6[2],test6[3],test6[4]);
	test6 = test_word(test5, test3);
	printf("53: 10200 - %d%d%d%d%d\n",test6[0],test6[1],test6[2],test6[3],test6[4]);
	test6 = test_word(test5, test4);
	printf("54: 10100 - %d%d%d%d%d\n",test6[0],test6[1],test6[2],test6[3],test6[4]);
	*/
	
	printf("\nWhat was the response? Enter a 5 letter sequence\n");
	printf("2=green 1=yellow 0=black\n");
	printf("An answer with a green square in position 2\n");
	printf("and a yellow one in position 5 you would type:\n");
	printf("02001:\n");
	printf("\nEnter response now:\n");

	fgets(text,20,stdin);
	while(len_word(text)!=6){
		printf("\nResponses must be 5 numbers\n");
		fgets(text,20,stdin);
	}
	
	for(i=0;i<5;i++){
		response[i] = text[i]-'0';
	}
	int size_new;
	int size_old;
	int **word_list_new;
	
	int test = 0;
	for(i=0;i<5;i++){
		if(response[i]!=2)test=1;
	}
	
	word_list_new = word_list;
	time_t t;
	srand((unsigned) time(&t));
	
	size_old = size_all;
	
	
	
	while(test){
		// Remove incorrect words from list of possible solutions
		word_list_new = update_list(guess,response,&size_old,word_list_new,&size_new);
		
		printf("\nThere are %d possible remaining guesses\n",size_new);
		if(size_new<20){
			printf("[");
			for(i=0;i<size_new;i++){
				printf("%c%c%c%c%c",(char)word_list_new[i][0],(char)word_list_new[i][1],(char)word_list_new[i][2],(char)word_list_new[i][3],(char)word_list_new[i][4]);
				printf("\t");
			}
			printf("]\n");
		}
		printf("Calculating next best guesses...\n");
		
		int sample = 100;
		int **word_list_tmp;
		int *rand_list = create_int_vector(sample);
		
		int test_unique = 1;
		
		if (sample>size_new){
			sample = size_new;
			word_list_tmp = word_list_new;
		}else{
			word_list_tmp = create_int_array(sample,6);
			for(i=0;i<sample;i++) {
				while(test_unique){
					test_unique = 0;
					j = rand() % size_new;
					rand_list[i]=j;
					for(k=0;k<i;k++){
						if(j==rand_list[k]){
							test_unique = 1;
						}
					}
				}
				for(k=0;k<5;k++){
					word_list_tmp[i][k] = word_list_new[j][k];
				}
				// printf("%d - %c%c%c%c%c\n",rand_list[i],(char)word_list_tmp[i][0],(char)word_list_tmp[i][1],(char)word_list_tmp[i][2],(char)word_list_tmp[i][3],(char)word_list_tmp[i][4]);
				test_unique = 1;
			}
		}
		
		
		// score list to select best guesses
		// Method is to check for each guess word
		// and each possible answer from the sub sample
		// how many words would be compatible with the 
		// information gained from that guess
		
		int score;
		int *answer = create_int_vector(6);
		int *word = create_int_vector(6);
		
		for(i=0;i<size_all;i++){
			score = 0;
			guess = word_list[i];
			for(j=0;j<sample;j++){
				answer = word_list_tmp[j];
				test_word(guess,answer,response);
				for(k=0;k<sample;k++){
					word = word_list_tmp[k];
					test_word(guess,word,response_test);
					if(check_match(response,response_test)){
						score += 1;
					}
				}
			}
			word_list[i][5] = score;
		}
		
		int smallest;
		int sml_index;
		for(k=0;k<20;k++){
			sml_index=0;
			smallest = word_list[0][5];
			for(i=1;i<size_all;i++){
				if(smallest>word_list[i][5]){
					smallest = word_list[i][5];
					sml_index = i;
				}
			}
			printf("%d - %c%c%c%c%c\n",word_list[sml_index][5],(char)word_list[sml_index][0],(char)word_list[sml_index][1],(char)word_list[sml_index][2],(char)word_list[sml_index][3],(char)word_list[sml_index][4]);
			word_list[sml_index][5] = sample*sample;
		}
		
		if(sample == size_new){
			printf("Calculating next best solutions...\n");
			for(i=0;i<sample;i++){
				score = 0;
				guess = word_list_tmp[i];
				for(j=0;j<sample;j++){
					answer = word_list_tmp[j];
					test_word(guess,answer,response);
					for(k=0;k<sample;k++){
						word = word_list_tmp[k];
						test_word(guess,word,response_test);
						if(check_match(response,response_test)){
							score += 1;
						}
					}
				}
				word_list_tmp[i][5] = score;
			}
			
			for(k=0;k<20;k++){
				sml_index=0;
				smallest = word_list_tmp[0][5];
				for(i=1;i<sample;i++){
					if(smallest>word_list_tmp[i][5]){
						smallest = word_list_tmp[i][5];
						sml_index = i;
					}
				}
				printf("%d - %c%c%c%c%c\n",word_list_tmp[sml_index][5],(char)word_list_tmp[sml_index][0],(char)word_list_tmp[sml_index][1],(char)word_list_tmp[sml_index][2],(char)word_list_tmp[sml_index][3],(char)word_list_tmp[sml_index][4]);
				word_list_tmp[sml_index][5] = sample*sample;
			}
		}
		size_old = size_new;
			
		printf("Enter your guess now:\n");
	
		fgets(text,20,stdin);
	
		while(len_word(text)!=6){
			printf("\nGuesses must be 5 letters\n");
			fgets(text,20,stdin);
		} 
		
		for(i=0;i<5;i++){
			guess[i] = (int)text[i];
		}
		
		printf("\nEnter response now:\n");
		
		fgets(text,20,stdin);
		while(len_word(text)!=6){
			printf("\nResponses must be 5 numbers\n");
			fgets(text,20,stdin);
		}
		
		for(i=0;i<5;i++){
			response[i] = text[i]-'0';
		}
		
		test = 0;
		for(i=0;i<5;i++){
			if(response[i]!=2)test=1;
		}
	}

	printf("Yay! You won!!\n");
	
	return 0;
}
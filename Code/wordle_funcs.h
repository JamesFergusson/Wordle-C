#ifndef WORDLE_FUNCS_H
#define WORDLE_FUNCS_H
	
	int *create_int_vector(int length);
	void destroy_int_vector(int *vector);
	int **create_int_array(int dim_x, int dim_y);
	void destroy_int_array(int **array);
	int len_word(char *word);
	
	int **read_word_list(char *filename, int *size);
	
	void test_word(int *guess, int *answer, int *response);
	int check_match(int *word1, int *word2);
	int **update_list(int *guess, int *response, int *size, int **word_list, int *size_new);
	
#endif
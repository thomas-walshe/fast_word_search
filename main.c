#include <stdio.h>
#include <stdlib.h>

int string_length(char* str);
void string_copy(char* target, char* source, int length);
char convert_lower(char c);
void word_search(char* filename, char* search_word, int search_length);
int dict_word_length(char* line);
void string_copy_offset(char* target, char* source, int length, int offset);
int is_subset(char* search_word, int search_length, char* dict_word);

int main(int argc, char* argv[]){
  int length = 0;
  //char filename[7] = "xx.txt\0";
  char filename[13] = "files/xx.txt\0";
  if( argc == 2 ) {
      length = string_length(argv[1]);
      if(length <= 2){
	return -1;
      }
      char* search_word = (char*)malloc((length + 1)*sizeof(char));
      string_copy(search_word, argv[1], length);
      //filename[0] = search_word[0];
      //filename[1] = search_word[1];
      filename[6] = search_word[0];
      filename[7] = search_word[1];
      printf("\n");
      word_search(filename, search_word, length);
      free(search_word);
   }
   else {
      printf("One argument expected.\n");
      return -1;
   }

  return 0;
}

int string_length(char* str){
  int counter = 0;
  char cur_char;

  cur_char = str[counter];
  while(cur_char != '\0'){
    counter++;
    cur_char = str[counter];
  }

  return counter;
}

void string_copy(char* target, char* source, int length){
  for(int i = 0; i < length; i++){
    target[i] = convert_lower(source[i]);
  }
  target[length] = '\0';
}

char convert_lower(char c){
  char ret_c = c;
  if((c >= 65) && (c <= 90)){
    ret_c = c + 32;
  }

  return ret_c;
}

void word_search(char* filename, char* search_word, int search_length){
  char line[256];
  FILE *file = fopen(filename, "r");
  int word_length = 0;
  int total_subsets = 0;

  if(file != NULL){
    while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
    {
      //line now contains both the length of the word and the word | 3 doe
      //fputs(line,stdout); /* write the line */
      word_length = dict_word_length(line); //gets the length of the dictionary word

      //If the dictionary word is of suitable length, continue
      if(word_length >= search_length){
	//The following 2 lines extract the dictionary word
	char dict_word[word_length + 1];
	string_copy_offset(dict_word, line, word_length, 3);
        //dict word now contains the dictionary word

	//Checks for subset of word
	total_subsets += is_subset(search_word, search_length, dict_word);
      }
    }
    fclose (file);
    printf("Total matches: %d\n\n", total_subsets);
  }
  else
   {
      perror(filename); /* why didn't the file open? */
   }
}

int dict_word_length(char* line){
  char tens = line[0];
  char units = line[1];
  int ret_val = 0;

  ret_val = (int)tens - 48;
  ret_val *= 10;
  ret_val += (int)units - 48;

  return ret_val;
}

void string_copy_offset(char* target, char* source, int length, int offset){
  for(int i = 0; i < length; i++){
    target[i] = source[i + offset];
  }
  target[length] = '\0';
}

int is_subset(char* search_word, int search_length, char* dict_word){
  int i = 0;
  int subset = 1;
  while((subset == 1) && (i < search_length)){
    if(search_word[i] != dict_word[i]){
      subset = 0;
    }
    i++;
  }

  if(subset > 0){
    printf("%s\n", dict_word);
  }

  return subset;
}

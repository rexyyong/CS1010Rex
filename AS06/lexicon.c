/**
 * CS1010 Semester 1 AY22/23
 * Assignment 6: Lexicon
 *
 * @file: lexicon.c
 * @author: rex yong (Group c05)
 */
#include "cs1010.h"


/**
 *This function finds the max length from list of arrays
 *@post: number > 1
 *@param[in] array : input array
 *@param [in] number : number of arrays
 *@return : max length excluding new line char 
 */
long max_len (char **array , long number) //function returns max length from the list of arrays
{
  long max_so_far = (long)strlen(array[0]) ; 
  for(long i = 1 ; i < number ; i += 1) {
    if( (long)strlen(array[i]) > max_so_far ) {
      max_so_far = (long)strlen(array[i]) ; 
    }
  }
  return max_so_far - 1 ;  //excludes the new line char
}


/**
 *This function creates padded array, padded with null
 *@post: number > 1
 *@param[in] array : input array
 *@param[in,out] padded : array to be padded 
 *@paran[in] max : max length excluding line char
 *@param[in] number : number of arrays
 */
void padding (char **array , char **padded , long max , long number)
{
  for (long row = 0 ; row < number ; row += 1) {
    padded[row] = array[row] ; //copying occupied spaces from array to padded 

    long length = (long)strlen(array[row]) - 1 ; //minus 1 to remove new line char
    for (long col = length ; col <= max ; col += 1) {
      padded[row][col] = '\0' ; //adding in the null char
    }
  }
}


/**
 *Function prints out the array
 *@post: number > 1
 *@param[in] answer : sorted array 
 *@param[in] number : number of arrays
 */
void print(char **answer , long number)
{
  for (long count = 0 ; count < number ; count += 1) {
    cs1010_println_string(answer[count]);
  }
  free(answer) ; 
}


/**
 *This function carries out the radix sort 
 *@post: number > 1
 *@param[in] padded : padded  array
 *@param[in,out] answer : array to store the final order of arrays
 *@param[in] freq : array to store freq of appearance of chars
 *@paran[in] max : max length excluding line char
 *@param[in] number : number of arrays
 */
void sort (char **padded , char **answer , long *freq , long max , long number)
{
  for (long col = max - 1 ; col >= 0 ; col -= 1) { //loops max amount of times 
    for (long count = 0 ; count < 128 ; count += 1) { //initializes freq array to 0
    freq[count] = 0 ; 
    }

    for (long row = 0 ; row < number ; row += 1) {
      freq[(long)padded[row][col]] += 1 ; //stores frequency 
    }

    for (long index = 1 ; index < 128 ; index += 1) {
      freq[index] += freq[index - 1] ;  //populates the freq array so that ranking can be differentiated
    }

    for (long row = number - 1 ; row >= 0 ; row -= 1) {
      answer[freq[(long)padded[row][col]] - 1] = padded[row] ; //updates the new ranking into answer array
      freq[(long)padded[row][col]] -= 1 ; 
    }
    for (long count = 0 ; count < number ; count += 1) { //updates the padded array new new rank order
      padded[count] = answer[count] ; 
    }
  }
  free(padded) ; 
}


int main()
{
  long number = cs1010_read_long() ;
  char **array = cs1010_read_line_array((size_t)number) ;
  if(array == NULL) {
    cs1010_println_string("array not initialised");
    free(array) ;
    return 1;
  }

  char **padded = calloc((size_t)number , sizeof(char *)) ; 
  if(padded  == NULL) {
    cs1010_println_string("array not initialised");
    free(padded) ;
    return 1;
  }

  char **answer = calloc((size_t)number , sizeof(char *)) ; 
  if(answer  == NULL) {
    cs1010_println_string("array not initialised");
    free(answer) ;
    return 1;
  }

  long *freq = calloc(128 , sizeof(long)) ; 
  if(freq  == NULL) {
    cs1010_println_string("array not initialised");
    free(answer) ;
    return 1;
  }

  long max = max_len(array , number) ; 
  padding (array , padded , max , number) ;
  sort (padded , answer , freq , max , number) ;
  print(answer , number) ; 

  for(long i = 0 ; i < number ; i += 1) {
    free(array[i]) ; 
  }


  free(array) ; 
  free(freq) ; 
}

/*

   long max_len(char **array , long number) //function returns the max length of the list of arrays
   {
   long max_so_far = (long)strlen(array[0]) ; 
   for(long i = 1 ; i < number ; i += 1) {
   if( (long)strlen(array[i]) > max_so_far ) {
   max_so_far = (long)strlen(array[i]) ; 
   }
   }
   return max_so_far - 1 ;  //excludes the new line char
   }


   char** editable_array(long number , long max) //creates the array to edit, incldues space for newline char and null char at back
   {
   char **out; 

   out = calloc( (size_t)number , sizeof(char *) ) ;
   if(out == NULL) {
   cs1010_println_string("array not initialised");
   free(out) ;
   return NULL ;
   }
   long size = max * number ; 

   out[0] = calloc( (size_t)size , sizeof(char) ) ; 
   if(out[0] == NULL) {
   cs1010_println_string("array not initialised");
   free(out[0]) ; 
   free(out) ; 
   return NULL ; 
   }

   for(long i = 1 ; i < number ; i += 1 ) {
   out[i] = out[i-1] + max ; 
   }

   return out ; 
   }


   void padding(char **output , char **array , long max , long number)
   {
   for (long row = 0 ; row < number ; row += 1 ) { //goes downt he array of pointers 
   long length = (long)strlen(array[row]) - 1 ;
   for (long col = 0 ; col < length ; col += 1) {
   output[row][col] = array[row][col] ; //puts occupied chars into output array 
   }

   for ( long col = length  ; col < max ; col += 1 ) { //length - 1 because it contains new line char. 
   output[row][col] = 0 ; //padding occurs to achieve same length as max length
   }
   }
   }


   void print_array(char **array , long number , long max)
   {
   for(long row = 0 ; row < number ; row += 1 ) {
   for(long col = 0 ; col < max ; col += 1 ) {
   putchar(array[row][col]) ; 
   }
   cs1010_println_string("");
   }
   }

   void sort(char **output , char **answer , long number , long max)
   {
   for(long col = max - 1 ; col >= 0 ; col -= 1) { //loops for m times
   long freq[128] = {0} ; //initialize frequency array to zero

for(long row = 0 ; row < number ; row += 1) { //goes down the array pointers 
  freq[(long)output[row][col]] += 1 ;  //counts frequency of appearance of chars
}

for(long index = 1 ; index < 128 ; index += 1) {
  freq[index] += freq[index-1] ; //populates the freq array with the ranking of the frequencies. Purpose is to help main array find the index of the char and do sorting
}

for(long row = number - 1 ; row >= 0 ; row -= 1) { //go from largest row to smallest because of the way freq array is arranged. This will ensure that order of elements in output array is followed
  answer[ freq[(long)output[row][col] ] - 1 ] = output[row] ; //freq[ output[row][col] ] - 1  , -1 because you want to get the index of answer array. Afterwards string at output[row] is stored in answer array
  freq[(long)output[row][col]] -= 1 ; //updates the ranking in the freq array
}

for(long row = 0 ; row < number ; row += 1) {
  output[row] = answer[row] ; //updates output array to new order of strings 
}
}
for(long i = 0 ; i < number ; i += 1) {
  cs1010_println_string(answer[i]);
}
}





int main() 
{
  long number = cs1010_read_long() ;
  char **array = cs1010_read_line_array((size_t)number) ;
  if(array == NULL) {
    cs1010_println_string("array not initialised");
    free(array) ;
    return 1;
  }

  long max = max_len(array , number) ; 

  char **padded_array = editable_array(number , max) ; 

  padding(padded_array , array , max , number) ; 


  char **answer = calloc((size_t)number , sizeof(char *)) ;  //answer array
  if(answer==NULL) {
    cs1010_println_string("array not initialised");
    free(answer) ; 
    return 1;
  }

  sort(padded_array , answer , number , max) ; 

  for(long i = 0 ; i < number ; i += 1) {
    free(array[i]) ; 
  }


  free(padded_array[0]) ; 
  free(padded_array) ; 
  free(array) ; 
  free(answer) ; 
}
*/








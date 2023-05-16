/**
 * CS1010 Semester 1 AY22/23
 * Assignment 4: Mastermind
 *
 * @file: mastermind.c
 * @author: Rex Yong (Group C05)
 */
#include "cs1010.h"


/**
 *This function takes in the array code and array guess which are stored on the heap. The purpose of the function is to find the number of matching colors from guess and code. EG if code = 1 3 5 4 , guess = 6 6 6 1 will return a value of 1 because there is indeed a 1 matching color in code. 
 *@pre: both code and guess has 4 long values which are within 1 to 6 
 *@param[in] code : array pointer code is passed into the function as a const array, it contains the actual code
 *@param[in] guess : array pointer guess is passed into the function, it contains the guess by user 
 *@return : the number of matching colors between guess and code is returned 
 */
long same_color ( const long *code , long *guess ) 
{
  long color_value = 0 ; 
  long colors [7] = { 0 } ; //initialize array which stores color 0-6 and initializes to 0 
  for ( long counter = 0 ; counter < 4 ; counter += 1 ) 
  {
    long number = code [counter] ; 
    colors [number] += 1 ; //updates the colors in stack accordingly
  }

  for ( long i = 0 ; i < 4 ; i += 1 ) 
  {
    for ( long j = 0 ; j < 7 ; j += 1 ) 
    {
      if ( ( guess[i] == j ) && ( colors[j] > 0 ) )  //if colors[j] == 0 , then no point checking already
      {
        colors[j] -= 1 ; 
        color_value += 1 ; 
      }
    }
  }
  return color_value ; 
}


/**
 *This function takes in the array code and then it prints out the pegs with same position and color , and number of matching colors between the code and guess. It however does not double count, which means that if pos and color is 1, matching colors = pos_and_color - matching_colors.  It reads in an array guess which is stored on heap as long as the correct code is not given. 
 *@pre : input code is on heap, and it has 4 long values which are within 1 to 6 
 *@param[in] code : array pointer code is passed 
 */
void number_pegs ( const long *code ) 
{
  long pos_and_color = 0 ; //counter? 
  long color = 0 ;  //counter? 
  while ( pos_and_color < 4 ) // loop continues until pos and color is found
  {
    pos_and_color = 0;
    color = 0 ; 
    long *guess = cs1010_read_long_array( (size_t)4 ) ; //stores the array on heap
    for ( long i = 0 ; i < 4 ; i += 1 ) //loop updates pos and color pegs 
    {
      if ( guess[i] == code [i] ) 
      {
        pos_and_color += 1 ; 
      }
    }
    color = same_color ( code , guess ) ; 
    long second_value = color - pos_and_color ; //minus off to prevent the double count

    cs1010_print_long(pos_and_color);
    cs1010_print_string(" ");
    cs1010_println_long(second_value);
    free(guess) ; 
  }
}


int main()
{
  long *code = cs1010_read_long_array((size_t)4) ; //stores array on heap 

  number_pegs ( code ) ; 

  free(code);
}

/**
 * CS1010 Semester 1 AY22/23
 * Assignment 4: Subtract
 *
 * @file: subtract.c
 * @author: rex yong (Group C05)
 * */

#include "cs1010.h"


/**
 *This function prints out the answer char by char. It includes a bool checker so that the leading zeroes of the answer will not be printed. 
 *@pre : a is an array on heap , the number is more than or equal to zero  
 *@param[in] a : a is the array on heap which contains answer from the sutraction 
 */
void print_chars ( char *a ) 
{
  bool checker = false ; //checker starts with false
  for ( long k = 0 ; a[k] != '\0' ; k += 1 )
  {
    if ( checker == false ) //once checker turns true, this if statement will not be executed, hence only leading zeroes wont be printed. 
    {
      if ( a[k] > '0' )
      {
        checker = true ; 
      }
    }
    
    if ( checker == true )
    {
    putchar(a[k]) ; 
    }
  }
  cs1010_println_string("");
}

/**
 *This function does the char by char subtraction of the arrays a and b. It then updates all the answer into array a which is on the heap. It then passes the array a into the print char function so that the answer of subtraction will be printed out. 
 *@pre : integer form of array a is more than or equal to integer form of array b. 
 *@pre : length_a >= length_b
 *@param[in, out] a : a is the array of characters that gives the number to be subtracted. In this function, a will be updated char by char as it is subtracted by b, the result will then be updated on array a on the heap. 
 *@param[in] b : b is the array of characters that gives the number to subtract with 
 *@param[in] length_a : the length of array a excluding null 
 *@param[in] length_b : the length of array b excluding null 
 *
 */
void find_subtracted_val ( char *a , char *b , size_t length_a , size_t length_b ) 
{
  long i = (long)length_a - 1 ; //initialize i outside the loop
  for ( long k = (long)length_b -1 ; k>= 0 ; k -= 1 ) 
  {
    if( (a[i] < b[k]) && k >= 0 ) //if a is 1xx1 and b is x2, this loop will run
    {
      long j = i - 1; //introduce another counter
      while ( a[j] == '0' ) 
      {
        a[j] = '9' ; 
        j -= 1 ; 
      }

      a[j] = (a[j] - '0') - 1 + '0' ; //will subtract 1 from non zero number and transfer it to a[i]

      a[i] = (a[i] - '0') + 10 + '0' ; //adds 10 to a[i]

      a[i] = ( (a[i] - '0') - (b[k] - '0' ) ) + '0' ; //subtracts the digit and converts back to char
      i -= 1 ; //need to update i  
      //length_b -= 1; //updates length_b after subtracting 
    }

    else 
    {
      a[i] = ( (a[i] - '0') - (b[k] - '0') ) + '0' ; //subtracts the last digit of a and b and updates it back into array as char
      //length_b -= 1; //updates length_b after subtracting
      i -= 1 ; //need to update i 
    }
  }
  print_chars( a ) ; 
}


/**
 * This function calculates the length of number a and number b , it then passes it into function find_subtracted_val
 *@pre : integer form of array a is more than or equal to integer form of array b  
 *@param[in] a : a is the array of characters that gives the number to be subtracted 
 *@param[in] b : b is the array of characters that gives the number to subtract with 
 */
void subtract( char *a , char *b ) 
{
  size_t length_a = strlen( a ) ; //strlen returns length of input, excluding the null value behind
  size_t length_b = strlen( b ) ; 

  find_subtracted_val( a , b , length_a , length_b ) ; 
}


int main()
{
  char *a = cs1010_read_word() ;
  char *b = cs1010_read_word() ;

  subtract( a , b ) ; //function to subtract the numbers 

  free(a) ; 
  free(b) ; 
}

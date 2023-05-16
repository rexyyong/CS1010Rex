/**
 * CS1010 Semester 1 AY22/23
 * Assignment 3: Padovan
 *
 * @file: padovan.c
 * @author: rex yong jin xiang (Group C05)
 */
#include "cs1010.h"


void find_padovan ( long n )
{
  long p [ 161 ] = { 1 , 0 , 0 } ; //storing the padovan numbers into an array

  for ( long i = 3 ; i < n + 1 ; i += 1 ) // this will loop for n + 1 - 3 times 
  {
    p [ i ] = p [ i - 2 ] + p [ i - 3 ] ; // p[3] = p [1] + p [0] 
  }
 
  for ( long i = n ; i >= 0 ; i -= 1 )
  {
    cs1010_println_long(p [i]);
  }
}

int main()
{
  long n = cs1010_read_long() ;

  find_padovan ( n );
}

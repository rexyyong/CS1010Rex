/**
 * CS1010 Semester 1 AY22/23
 * Assignment 2: Collatz 
 *
 * @file: collatz.c
 * @author: rex yong jin xiang (Group C05)
 */
#include "cs1010.h"
#include <math.h>

long stopping_num( long i ) //checks stopping number
{
  long stopping_time_i = 0;
  while ( i != 1)
  {
    stopping_time_i += 1;
    if ( i % 2 == 0 )  //checks if even
    {
      i /= 2; 
    } else //i is odd
    {
      i = i * 3 + 1;
    }
  }
  return stopping_time_i;
}


void max_stopping_num( long m, long n ) //function that checks the max stopping number within range
{
  long i = m; //initialize the number to starting point m
  long max = 0; //initialize max stopping number to 0
  long corresponding_num;

  while( i <= n ) 
  {
    long current_stopping = stopping_num(i); 
    if( current_stopping >=  max )
    {
      max = current_stopping; 
      corresponding_num = i; //stores the number with max stopping number to corresponding_num
      i += 1; //updates i
    } else
    {
      i += 1;  //else block
    }
  }
  cs1010_println_long(max);
  cs1010_println_long(corresponding_num);
}

int main() 
{
  long m = cs1010_read_long() ;
  long n = cs1010_read_long() ;

  max_stopping_num( m, n );
}


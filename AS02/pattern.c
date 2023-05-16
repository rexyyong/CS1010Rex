/**
 * CS1010 Semester 1 AY22/23
 * Assignment 2: Pattern
 *
 * @file: pattern.c
 * @author: rex yong jin xiang (Group C05)
 */
#include "cs1010.h"
#include <math.h>
#include <stdbool.h>

long leading_number ( long m , long row )  //function that gives the leading nuber. Row starts from 0!
{
  long lead = 1;
  for (long i = 1; i < row ; i += 1)
  {
    lead += ( i * m );
  }
  return lead;
}


bool is_prime( long leading )
{
  if ( leading == 1 )
  {
    return false;
  }
  if ( leading == 2 || leading == 3 ) //in the 6k + 1 method, need to single out 2 and 3 and declare it as prime
  {
    return true;
  }

  if ( leading % 2 == 0 || leading % 3 == 0 ) // removing multiples of 2 and 3, this leaves us with 6 n + 1 and 6 n + 5 numbers
  {
    return false;
  }

  //this part onwards checks if 6n + 5 and 6n + 1 is prime 
  long divisor = 5;
  while ( divisor * divisor <= leading ) // while divisor < sqrt(i), is the same as divisor^2 < i
  {
    if ( leading % divisor == 0 ) //divisible by divisor means that it is not prime
    {
      return false;   // checks for divisor = 5 , 11 , 17 and so on
    }
    if ( leading % (divisor + 2) == 0 ) //this may be a redundant step but i have no idea how to eliminate it
      //checks for divisor = 7 , 13 , 19 and so on
    { 
      return false;
    }
    divisor += 6;
  }
  return true;
}


bool is_cell_prime ( long m , long row, long col ) //function checks if cell is prime
{
  long leading = leading_number( m , row );
  long i = 1; //just a counter
  while ( i < col ) //gives the first number of each cell
  {
    leading += 1;
    i += 1;
  }

  long q = 1; // just a counter
  while ( q <= m ) //each cell has m numbers, if m = 5, will check for q = 1,2,3,4,5
  {
    if ( is_prime ( leading ) == true )
    {
      return true;
    }
    leading += row;
    q += 1;
  }
  return false;
}
 

void print_triangle ( long h , long m ) //function that prints a triangle
{
  for ( long row = 1 ; row <= h ; row += 1 ) //eg when h = 4, it will run for row = 1,2,3,4 and stop. 
  {
    for ( long space = 1 ; space <= h - row ; space += 1 ) //at each row, 
    {
      cs1010_print_string(" "); //prints out spaces 
    }

    long k = 0 ; //just a counter
    long col = 1;
    while ( k < 1 + ( row - 1 ) * 2 ) //when row = 1, 0 < 1 loops once , when row = 2, 0 < 3 loops 3 times      
    {
      if ( is_cell_prime ( m , row , col ) == true)
      {
        cs1010_print_string("#");
      }
      else
      {
        cs1010_print_string(".");
      }
      col += 1;
      k += 1;
    }

    for ( long space = 1 ; space <= h - row ; space += 1 ) //at each row, 
    {
      cs1010_print_string(" "); //prints out spaces 
    }
    cs1010_println_string(""); //prints new line
  }
}


int main()
{
  long m = cs1010_read_long() ; //interval
  long h = cs1010_read_long() ; //height
  print_triangle ( h , m );

}

/*
bool is_prime( long leading ) //this function checks if a input is prime, and returns true or false
{
  if ( leading == 1 )
  {
    return false;
  }

  long divisor = 2; //initialize 
  while( divisor < leading )
  {
    if( leading % divisor == 0 ) //means that it is perfectly divisible
    {
      return false;
    }
    divisor += 1;
  }
  return true;
}
*/

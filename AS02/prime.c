/**
* CS1010 Semester 1 AY22/23
 * Assignment 2: Prime
 *
 * @file: prime.c
 * @author: rex yong jin xiang (Group C05)
 */
#include "cs1010.h"
#include <math.h>
#include <stdbool.h>

bool is_prime( long i )
{
  if ( i == 2 || i == 3 ) //in the 6k + 1 method, need to single out 2 and 3 and declare it as prime
  {
    return true;
  }

  if ( i % 2 == 0 || i % 3 == 0 ) // removing multiples of 2 and 3, this leaves us with 6 n + 1 and 6 n + 5 numbers
  {
    return false;
  }

  //this part onwards checks if 6n + 5 and 6n + 1 is prime 
  long divisor = 5;
  while ( divisor * divisor <= i ) // while divisor < sqrt(i), is the same as divisor^2 < i
  {
    if ( i % divisor == 0 ) //divisible by divisor means that it is not prime
    {
      return false;   // checks for divisor = 5 , 11 , 17 and so on
    }
    if ( i % (divisor + 2) == 0 ) //this may be a redundant step but i have no idea how to eliminate it
      //checks for divisor = 7 , 13 , 19 and so on
    { 
      return false;
    }
    divisor += 6;
  }
  return true;
}


void check_prime( long n )
{
  long i = n;
  while( is_prime( i ) == false )
  {
    i -= 1;
  }
  if( is_prime ( i ) == true )
  {
  cs1010_println_long(i);
  }
}


int main()
{
  long n = cs1010_read_long() ;

  check_prime( n );
}

/*
bool is_prime( long i )
{
  long divisor = 2; //initialize 
  while( divisor < i )
  {
    if( i % divisor == 0 ) //means that it is perfectly divisible
    {
      return false;
    } 
    divisor += 1;
  }
  return true;
}


bool is_prime_2 ( long s )
{
  long divisor = 2; //initialize 
  while( divisor < s )
  {
    if( s % divisor == 0 ) //means that it is perfectly divisible
    {
      return false;
    } 
    divisor += 1;
  }
  return true;
}

bool is_prime_3 ( long q )
{
  long divisor = 2; //initialize 
  while( divisor < q )
  {
    if( q % divisor == 0 ) //means that it is perfectly divisible
    {
      return false;
    } 
    divisor += 1;
  }
  return true;
}

void check_prime( long n )
{
  long i = n;
  long s = n - 1;
  while( is_prime( i ) == false && is_prime_2 ( s ) == false )
  {
    i -= 2;
    s -= 2;
  }
  if( is_prime ( i ) == true )
  {
  cs1010_println_long(i);
  } else  
  {
    cs1010_println_long( s );
  } 
}
*/


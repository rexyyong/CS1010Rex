/**
 * CS1010 Semester 1 AY22/23
 * Assignment 3: ID
 *
 * @file: id.c
 * @author: rex yong jin xiang (Group c05)
 */
#include "cs1010.h"


long length ( long number ) //function to find length of number
{
  long len = 1;
  while ( number / 10 > 0 ) //if number is 1359, loop will run 3 times, final len is 4
  {
    len += 1;
    number /= 10;
  }
  return len;
}


long sum_number ( long number , long len )  //function to find the sum of the input
{
  long sum = 0 ; 
  for ( long i = 0 ; i < len ; i += 1 )
    {
      long digit = number % 10 ; //stores last digit of number , eg for 1234567, it stores 7
      sum += digit ; 
      number /= 10 ; //updates number to 1 less digit , from 1234567 to 123456 
    }
  return sum;
}


void print_char ( long sum )
{
  char check_code [ 13 ] = { 'Y' , 'X' , 'W' , 'U' , 'R' , 'N' , 'M' , 'L' , 'J' , 'H' , 'E' , 'A' , 'B' } ;
  long R = sum % 13 ; //takes remainder of sua eg 28 % 13 gives 2

  putchar( check_code [ R ] ) ;
  cs1010_println_string("");

}


int main()
{
  long number = cs1010_read_long() ;

  long len = length ( number ) ;

  long sum = sum_number ( number , len );

  print_char ( sum ) ; //number has 7 digits
}

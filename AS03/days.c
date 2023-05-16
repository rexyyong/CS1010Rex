/**
 * CS1010 Semester 1 AY22/23
 * Assignment 3: Days
 *
 * @file: days.c
 * @author: rex yong jin xiang (Group C05)
 */
#include "cs1010.h"


void print_answer ( long day [ 1 ] , long month [ 1 ] )
{
  long day_months [12] = { 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31 } ; //storing different months into array

  long result = 0;
  for ( long i = 0 ; i < day [ 0 ] ; i += 1 ) //this loop settles the day portion of input
  {
    result += 1 ;
  }

  for ( long i = 0 ; i < month [ 0 ] - 1 ; i += 1 ) // this loop settles the month part, i < month [ 0 ] -1 because if its jan, you only add the days, no need add any for month 
  {
    result += day_months [ i ] ;
  }

  cs1010_println_long(result);
}

int main() 
{
  long month [1] = { cs1010_read_long() } ;
  long day [1] = { cs1010_read_long() } ; 

  print_answer ( day , month );
}

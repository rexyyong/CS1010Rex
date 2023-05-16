/**
 * CS1010 Semester 1 AY22/23
 * Assignment 3: Max
 *
 * Read in a sequence of numbers and recursively find
 * the maximum.
 *
 * @file: max.c
 * @author:rex yong jin xiang (Group c05)
 */
#include "cs1010.h"

long find_max(const long list[], long start, long end)
{
  if ( start == end - 1 ) 
  {
    return list[start] ; //may need to edit this
  }

  long n = ( start + end ) / 2 ;  //finds mid point 
  long max1 = find_max ( list , start , n ) ; // goes from 0 starting point, and n amount of elements 
  long max2 = find_max ( list , n , end ) ; // goes from n starting point to end - n amount of elements
  
  if ( max1 > max2 ) 
  {
    return max1;
  }
  return max2;
}   


int main()
{
  long list[100000];
  long num_of_elems = cs1010_read_long();
  for (long i = 0; i < num_of_elems; i += 1) {
    list[i] = cs1010_read_long();
  }

  cs1010_println_long(find_max(list, 0, num_of_elems));
}

/*
 * CS1010 Semester 1 AY22/23
 * Assignment 4: Kendall
 *
 * Read in a sequence of numbers and find its kendall tau 
 * distance.
 *
 * @file: kendall.c
 * @author: REX YONG (GROUP C05)
 * */
#include "cs1010.h"

/*
 * This function calculates the total number of possible pairs from a given number of items
 *@pre : n > 0
 *@param[in] n : n is the number of items
 *@return : returns the number of possible pairs from list
 */
long all_possible_pairs ( long n ) //function returns number of possible pairs 
{ 
  long i = 0 ; 
  long possible_pairs = 0 ; 
  while ( i < n ) 
  {
    i += 1 ; 
    possible_pairs += (i - 1) * 1 ; // arithmetic series, 1 , 1+2, 1 + 2 + 3 and so on
  }
  return possible_pairs ; 
}
    

/**
 *This function finds the number of pairs ranked in a different order 
 *This occurs when the previous rank is larger than the rank after 
 *
 *@pre : n > 0 
 *@param[in] n : n is number of items 
 *@param[in] rank : passes the pointer rank into function, which allows function to access values on heap
 *@return : returns the number of pairs ranked in a different order 
 */
long pairs_diff_order ( long *rank , long n )  //finds the number of pairs in diff order 
{
  long pairs = 0 ;  //initializes to 0 at the start 
  for ( long i = 0 ; i < n - 1 ; i += 1 ) 
  {
    long first_num = rank [i] ; 

    for ( long j = i + 1 ; j < n ; j += 1 ) 
    {
      long second_num = rank [j] ; 
      if ( first_num > second_num ) //diff order occurs when down the list is smaller than before 
      {
        pairs += 1 ; 
      }
    }
  }
  return pairs ; 
}


int main()
{
  long n = cs1010_read_long() ;
  long possible_pairs = all_possible_pairs( n ) ; 

  long *rank = cs1010_read_long_array((size_t)n) ; // stores the input array into pointer rank on heap 

  if ( rank == NULL ) 
  {
    cs1010_println_string("uninitialised");
    return 1; 
  }
  long pairs_diff = pairs_diff_order ( rank , n )  ; 
  double kendall = (double)pairs_diff/(double)possible_pairs ; //formula for the kendall tau 
  cs1010_println_double(kendall);

  free(rank) ; 
}

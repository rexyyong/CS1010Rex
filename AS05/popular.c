/**
 * CS1010 Semester 1 AY22/23
 * Assignment 5: Popular
 *
 * @file: popular.c
 * @author: rex yong (Group c05)
 */

#include "cs1010.h"

/**
 *This function returns the number of friend a person has if i == j , when we check down the column 
 *@pre:  n >1 
 *@param[in] j is column *@param[in] i : i is row 
 *@param[in] friendlist is the jagged array 
 *@param[in] friend is variable to store number of friends 
 *@param[in] n is the number of people 
 *@return : returns number of friends 
 *
 */
long i_equal_j ( size_t j , size_t i , char **friendlist , long friend , long n ) 
{
  for ( size_t k = i + 1 ; k < (size_t)n ; k += 1 ) //this loop will go down the column
  {
    if ( friendlist[k][j] == '1' ) //counts the numbers of 1s down the column 
    {
      friend += 1 ; 
    }
  }
  return friend ; 
}

/**
 * This function identifies the id of the most popular person, followed by the amount of friends he has 
 *@pre: n >= 1 
 *@param[in,out] check : this array stores the id of most popular person and the max amount of friends that person has. it prefers the popular person with smaller id. 
 *@param[in] n : the number of people 
 *@param[in] friendlist : passes in the jagged array 
 */

void count_friends ( long check[2] , long n , char **friendlist ) 
{
  for ( size_t i = 0 ; i < (size_t)n ; i += 1 ) //loop will continue down the array which has pointers 
  {
    size_t length = strlen(friendlist[i]) ; 
    long friend = 0 ;

    for ( size_t j = 0 ; j < length ; j += 1 ) //loop will continue down the array with char values 
    {
      if ( i == j ) //if i==j , it will check down the column 
      {
        friend = i_equal_j ( j , i , friendlist , friend , n ) ;  //function to find friends if i==j
      }

      else if ( j < i && friendlist[i][j] == '1' ) //counts the number of 1s before last char value of array is reached 
      {
        friend += 1 ; 
      }
    }

    if ( friend > check[0] ) //checks if friend count is more max so far in check array , since condition is more than, when it is equal to the array will not be updated
    {
      check[0] = friend ; //updates value of max so far 
      check[1] = (long)i ; //updates value for person with max friends so far 
    }

  }
}


int main()
{
  long n = cs1010_read_long() ;
  char **friendlist = cs1010_read_line_array( (size_t)n ) ; //command helps to read in a jagged array , reb to free

  long check[2] = {0} ; //initializes a array to check max so far and person i (row) 

  count_friends( check , n , friendlist ) ; //passes in pointer to array

  for ( size_t i = 0 ; i < (size_t)n ; i += 1 ) //loop to free the arrays that store the char 
  {
    free ( friendlist[i] ) ; 
  }
  free(friendlist) ; //line to free the array of pointers 

  cs1010_println_long(check[1]);
  cs1010_println_long(check[0]);



}

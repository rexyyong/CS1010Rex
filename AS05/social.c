/**
 * CS1010 Semester 1 AY22/23
 * Assignment 5: Life
 *
 * @file: life.c
 * @author: rex yong (Group C05)
 */


#include "cs1010.h"

#define FRIEND '1'
#define STRANGER '0'


/**
 *Function checks if 2 people are direct contact
 *@pre : id1 != id2
 *@param [in] contactlist : jagged array
 *@param[in] id1 : person 1 
 *@param[in] id2 : person 2 
 *@return : true (direct contact) or false (not direct contact)
 */

bool direct_contact ( char **contactlist , long id1, long id2 ) 
{
  if ( id1 < id2 ) 
  {
    if ( contactlist[id2][id1] == '1' ) //check for direct contact 
    {
      return true ; 
    }
    return false ; 
  }
  if ( contactlist[id1][id2] == '1' ) //occurs when id2 < id1 
  {
    return true ; 
  }
  return false ; 
}


/**
 *Function checks if 2 people have indirect contact, and returns who the indirect contact is 
 *@pre : n >= 0 
 *@param[in] contactlist : the jagged array 
 *@param[in] id1 : person 1 
 *@param[in] id2 : person 2 
 *@param[in] n : number of people 
 *@return : either the id of indirect contact or -1 which means no indirect contact
 */

long indirect_contact ( char **contactlist , long id1 , long id2 , long n ) 
{
  for ( long i = 0 ; i < n ; i += 1 ) //goes down the column of contactlist[id1][id1]
  {
    if ( direct_contact ( contactlist , id1 , i ) == true && direct_contact( contactlist , id2 , i ) == true ) //this works because if person 0 is direct contact with both 1 and 2, then 1 and 2 are indirect contact through person 0
    {
      return i ; 
    }
  }
  return -1 ; //returning -1 signifies that there is no indirect contact
}

/**
 *Function prints out the jagged array
 *@pre : people >= 0 
 *@param[in] friendlist : jagged array 
 *@param[in] people : number of people 
 */

void print_triangle( char **friendlist , long people ) 
{
  for ( long i = 0 ; i < people ; i += 1 ) //loop that goes down the array of pointers (row) 
  {
    long length = (long)strlen(friendlist[i]) ; //returns the length of array that stores long values (column) 
    for ( long j = 0 ; j < length ; j += 1 ) 
    {
      putchar(friendlist[i][j]) ; 
    }
  }
}

/**
 *Function performs the degree 2 hop
 *@pre : people >= 0
 *@param[in] friendlist : original input jagged array 
 *@param[in] people : number of people 
 *@param[in,out] copy : the duplicate of the original input jagged array. copy is then updated on the heap again 
 *
 */

void degree2 ( char **friendlist , long people , char **copy ) //function to help carry out degree 2 updates
{
  for( long row = 0 ; row < people ; row += 1 ) //loops down array of pointers
  {
    long length = (long)strlen(friendlist[row] ) ; 
    for ( long column = 0 ; column < length ; column += 1 ) 
    {
      if (friendlist[row][column] == '0' && indirect_contact( friendlist , row , column , people ) > -1 ) //if the char at position is 0 and there is indirect contact, means update to 1 because there is degree 2 relation 
      {
        copy[row][column] = '1' ; //updates the position to char 1 for array copy 
      }
    }
  }
}

/**
 *Function recursively performs degree 2 hop on jagged array and stops when base case degree==1 is reached 
 *@pre : people >= 0 
 *@param[in,out] friendlist : original input jagged array , friendlist is updated on the heap 
 *@param[in] people : number of people 
 *@param[in] degree : the degree required 
 *@param[in,out] copy : the duplicate of the original input jagged array. Copy is then printed 
 */

void recursive ( char **friendlist , long people , long degree , char **copy )
{
  if ( degree == 1 )  //base case
  {
    print_triangle ( copy , people ) ; 
  }
  else
  {
    degree2 ( friendlist , people , copy ) ;  //for degree 3, it will perform degree 2 twice , and so on
    for ( long i = 0 ; i < people ; i += 1 ) 
    {
      long length = (long)strlen(friendlist[i]) ; //length for row 0 is 2 because of new line char
      for ( long j = 0 ; j <= length ; j += 1 ) // less than equal length because must include new line char
      {
        friendlist[i][j] = copy[i][j] ; //copies array friendlist to array copy including the null and new line char
      }
    }
    recursive ( friendlist , people , degree - 1 , copy ) ;
  }
}

/**
 * Function duplicates the original jagged array 
 * @pre : people >= 0 
 * @param[in] people : number of people 
 * @param[in] friendlist : the jagged array 
 * @return : returns the duplicated jagged array
 */

char **copy_array (long people, char **friendlist )  //function that copies friendlist to another array. may need to check if second calloc is correct 
{
  char **copy; 
  copy = calloc( (size_t)people , sizeof(char * ) ) ;  //allocating the array of pointers 

  if ( copy == NULL ) 
  {
    cs1010_println_string("array not initialised");
    free ( copy ) ; 
    return NULL ; 
  }

  for ( long i = 0 ; i < people ; i += 1 ) 
  {
    copy[i] = calloc( (size_t)i + 3 , sizeof(char) ) ; //to create the jagged array , i + 3 because of the new line char and null char behind
    if ( copy [i] == NULL )
    {
      cs1010_println_string(" array not initialised");
      for ( long m = 0 ; m < people ; m += 1 ) 
      {
        free(copy[m]) ; 
      }
      free(copy) ; 
      return NULL ; 
    }
  }

  for ( long i = 0 ; i < people ; i += 1 ) 
  {
    long length = (long)strlen(friendlist[i]) ; //length for row 0 is 2 because of new line char
    for ( long j = 0 ; j <= length ; j += 1 ) // less than equal length because must include new line char
    {
      copy[i][j] = friendlist[i][j] ; //copies array friendlist to array copy including the null and new line char
    }
  }
  return copy ; 
}


int main()
{
  long people = cs1010_read_long() ;
  long degree = cs1010_read_long() ;

  char **friendlist = cs1010_read_line_array((size_t)people) ; 
  if ( friendlist == NULL ) //null check for **friendlist 
  {
    cs1010_println_string("Array not initialised");
    return 1 ; 
  }

  char **copy = copy_array( people , friendlist ) ; 

  recursive ( friendlist , people , degree , copy ) ; 


  for ( long i = 0 ; i < people ; i += 1 )  //loop that frees up the friendlist array 
  {
    free ( friendlist[i] ) ; 
    free ( copy[i] ) ; 
  }
  free ( friendlist ) ; 

  free ( copy ) ; 
}




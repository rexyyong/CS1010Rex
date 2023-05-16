/**
 * CS1010 Semester 1 AY22/23
 * Assignment 5: Contact
 *
 * @file: contact.c
 * @author: rex yong (Group c05)
 */


#include "cs1010.h"

/**
 *Function checks if 2 people are direct contact
 *@pre : id1 != id2
 *@param [in] contactlist : jagged array
 *@param[in] id1 : person 1 
 *@param[in] id2 : person 2 
 *@return : true (direct contact) or false (not direct contact)
 */

bool direct_contact ( char **contactlist , long id1, long id2 ) //assuming id1 < id 2 
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

int main()
{
  long n = cs1010_read_long() ;
  char **contactlist = cs1010_read_line_array((size_t)n) ; //command to read in jagged array , remember to free 
  
  if ( contactlist == NULL ) //null check for **contactlist
  {
    cs1010_println_string(" array not initialised");
    return 1 ;
  }

  long id1 = cs1010_read_long() ; 
  long id2 = cs1010_read_long() ;

  bool direct = direct_contact ( contactlist , id1 , id2 ) ; //will return true if it is direct contact
  long indirect = indirect_contact ( contactlist , id1 , id2 , n ) ; 

  if ( direct == true ) 
  {
    cs1010_println_string("direct contact");
  }
  else if ( indirect > -1 ) //if indirect == -1, means that there is no indirect contact
  {
    cs1010_print_string("contact through ");
    cs1010_println_long(indirect);
  }
  else
  {
    cs1010_println_string("no contact"); //if there is no direct contact or indirect contact, then there is no contact
  }

  for ( size_t i = 0 ; i < (size_t)n ; i += 1 ) //loop to free the arrays that store the char 
  {
    free ( contactlist[i] ) ; 
  }
  free(contactlist) ; //line to free the array of pointers 

}

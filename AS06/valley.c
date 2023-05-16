/**
 * CS1010 Semester 1 AY22/23
 * Assignment 6: Valley
 *
 * @file: valley.c
 * @author: rex yong jin xiang (Group c05)
 */
#include "cs1010.h"


/**
 *Function identifies the valley in strict v_array
 *@pre: length > 1
 *@param[in]array : the input array
 *@param[in] left : left index of array
 *@param[in] right : right index of array 
 *@param[in] length : length of array
 *@return : valley of v_array
 */
long valley(long *array , long left , long right , long length) //finds valley of array
{
  long mid = (left + right) / 2 ;  //mid point index
  if(mid == 0 && array[mid] < array[mid+1]) { //valley all the way on left
    return array[mid] ; 
  }

  if(mid == length - 1 && array[mid] < array[mid-1]) { //valley all the way on right 
    return array[mid] ; 
  }

  if(array[mid] < array[mid+1] && array[mid] < array[mid-1]) //valley in between extreme left and right
  {
    return array[mid] ; 
  }

  if(array[mid] > array[mid+1]) { //means its on left of valley
    return valley(array , mid + 1 , right , length) ; //param left is set to mid + 1 so that searching range changes
  }
  return valley(array , left , mid - 1 , length) ; //means its on right of valley
}

int main()
{
  long length = cs1010_read_long() ;
  long *array = cs1010_read_long_array((size_t)length) ; 
  if(array == NULL) {
    cs1010_println_string("array not initialised");
    return 1; 
  }

  long right = length - 1;
  long left = 0 ; 
  long answer = valley(array , left , right , length) ; 
  cs1010_println_long(answer);

  free(array) ; 
}

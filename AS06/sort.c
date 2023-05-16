/**
 * CS1010 Semester 1 AY22/23
 * Assignment 6: Sort
 *
 * @file: sort.c
 * @author: rex yong jin xiang   (Group c05)
 */
#include "cs1010.h"

/**
 *Function creates output array on heap 
 *@pre: n > 0 
 *@param[in] n : the number of numbers in input array 
 *@return: output array 
 */ 
long* output_array(long n)
{
  long length = n ; 
  long *output = calloc((size_t)length , sizeof(long)) ; //creates an ouput array on heap

  if(output == NULL) {
    cs1010_println_string("array not initialised");
    return NULL ; 
  }
  return output ; 
}

/**
 *function sorts the input array and stores it in output array. It then prints answer 
 *@pre: n > 0 
 *@param[in] v_array : input array 
 *@param[in] output : output array to be edited 
 *@param[in] n : number of numbers in input array
 */
void sort_output(long *v_array , long *output , long n)
{
  long start = 0 ; //index of starting number
  long end = n - 1 ; //index of ending number
  long position = n - 1 ; // index position of output array 

  while (start <= end) { //loop continues until the output array is completely filled 
    if(v_array[start] > v_array[end]) { //first it compares the start and end. The reason this works is because for V array, start and end are supposed to be maximums. So if v_array[start] > v_array[end] , it means that the maximum in the whole array is v_array[start], so i will store it in last index of output array. 
      output[position] = v_array[start] ; 
      start += 1 ;  //update start
      position -= 1 ; //update position
    }
    else {
      output[position] = v_array[end] ; 
      end -= 1 ; 
      position -= 1 ; 
    }
  }

  for(long i = 0 ; i < n ; i += 1) {
    cs1010_println_long(output[i]);
  }
}

int main()
{
  long n = cs1010_read_long() ; 
  long *v_array = cs1010_read_long_array((size_t)n) ; 

  if(v_array == NULL) {
    cs1010_println_string("array not initialised");
    return 1;
  }

  long *output = output_array(n) ; 
  sort_output(v_array , output , n) ; 

  free(v_array) ; 
  free(output) ; 
}

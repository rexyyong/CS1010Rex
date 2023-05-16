/**
 * CS1010 Semester 1 AY22/23
 * Assignment 1: Digits
 *
 * Read in a positive integer from the standard input and print
 * the sum of its digits to the standard output.
 *
 * @file: digits.c
 * @author: Rex yong jin xiang (Group C05)
 */

#include "cs1010.h"
#include <math.h>

long sum_of_digits_cubed(long L)
{
  if (L == 0) {
    return 0;
  } 
  long remaining = L/10; //Obtains L without the ones place. EG if L == 1234, remaining == 123
  long to_subtract_from_L = remaining*10; // EG if L == 1234, to subtract from will be 1230. 
  long ones_digit = L - to_subtract_from_L; //this step looks at the ones place. EG L==1234, the ones digit is 4
  long cubed_result = ones_digit * ones_digit * ones_digit ; //ones digit to power of 3
  long answer = cubed_result + sum_of_digits_cubed(remaining); //recursive function, stores the final result in var answer 
  return answer;
}

int main()
{
  long L = cs1010_read_long() ;
  long final_cubed_answer = sum_of_digits_cubed(L);
  cs1010_println_long(final_cubed_answer);
}

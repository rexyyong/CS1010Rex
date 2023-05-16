/**
 * CS1010 Semester 1 AY22/23
 * Assignment 1: Suffix
 *
 * Read in a number and prints out the number with the appropriate suffix.
 *
 * @file: suffix.c
 * @author: Rex yong jin xiang (Group C05)
 */
#include "cs1010.h"

long last_2_digit (long x) 
{
  long value_last_2_digits = x - ((x/100)*100);
  if (value_last_2_digits == 11) {
    return 11; //this value will be used to print 11th
  } if (value_last_2_digits == 12) {
    return 12; //this value will be used to print 12th
  } if (value_last_2_digits == 13) {
    return 13; //this value will be used to print 13th
  } return 0;
}

long last_1_digit (long x)
{
  long value_last_1_digit = x - ((x/10)*10);
  if (value_last_1_digit == 1) {
    return 1; //this value will be used to print 1st 
  } if (value_last_1_digit == 2) {
    return 2; //this value will be used to print 2nd  
  } if (value_last_1_digit == 3) {
    return 3; //this value will be used to print 3rd 
  } return 0;
}

void print_with_suffix (long x)
{
  long last_2 = last_2_digit(x);
  long last_1 = last_1_digit(x);
  if (last_2 != 11 && last_1 == 1) { //prints out st for digits ending with 1, but not with 11
    cs1010_print_long(x);
    cs1010_println_string("st");
  } else if (last_2 != 12 && last_1 == 2) { //prints out nd for digits ending with 2, but not with 12
    cs1010_print_long(x);
    cs1010_println_string("nd");
  } else if (last_2 != 13 && last_1 == 3) { //prints out rd for digits ending with 3, but not with 13
    cs1010_print_long(x);
    cs1010_println_string("rd");
  } else {
    cs1010_print_long(x);
    cs1010_println_string("th");
  }
}

int main() 
{
  long x = cs1010_read_long();
  print_with_suffix(x);
}

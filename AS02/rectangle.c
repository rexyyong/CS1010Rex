/**
 * CS1010 Semester 1 AY22/23
 * Assignment 2: Rectangle
 *
 * @file: rectangle.c
 * @author: rex yong jin xiang (Group c05)
 */
#include "cs1010.h"

#define TOP_LEFT "╔"
#define TOP_RIGHT "╗"
#define BOTTOM_RIGHT "╝"
#define BOTTOM_LEFT "╚"
#define HORIZONTAL "═"
#define VERTICAL "║"

void first_row( long width ) //function for first row
{
  cs1010_print_string(TOP_LEFT);
  if( width > 2)
  {
    for( long i = 0 ; i < width - 2 ; i += 1 ) 
    {
      cs1010_print_string(HORIZONTAL);
    }
  }
  cs1010_println_string(TOP_RIGHT); //prints new line after top right
}

void spaces_for_body( long width ) // this function helps to print the spaces in the body
{
  if( width > 2)
  {
    for( long i = 0 ; i < width - 2 ; i += 1 ) 
    {
      cs1010_print_string(" "); //prints space between the verticals
    }
  }
}

     
void second_row( long width, long height ) //function for second row
{
  if( height > 2) //only need to execute this if height > 2
  {
    for( long h = 1 ; h <= height-2 ; h += 1 ) 
    {
      cs1010_print_string(VERTICAL);
      spaces_for_body( width );
      cs1010_println_string(VERTICAL); //prints new line after vertical
    }
  }
}
 

void last_row( long width ) //function for last row
{
  cs1010_print_string(BOTTOM_LEFT);
  if( width > 2)
  {
    for( long i = 0 ; i < width - 2 ; i += 1 ) 
    {
      cs1010_print_string(HORIZONTAL);
    }
  }
  cs1010_println_string(BOTTOM_RIGHT); //prints new line after top right
}



int main()
{
  long width = cs1010_read_long() ;
  long height = cs1010_read_long() ;

  first_row( width );
  second_row( width , height );
  last_row( width );
}


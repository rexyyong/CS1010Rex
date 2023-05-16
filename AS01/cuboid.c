/**
 * CS1010 Semester 1 AY22/23
 * Assignment 1: Cuboid
 *
 * Read in three positive integer corresponding to the width,
 * length, and height of a cuboid from the standard input, and
 * print the total surface area and the length of its diagonal
 * to the standard output.
 *
 * @file: cuboid.c
 * @author: Rex yong jin xiang (Group C05)
 */

#include "cs1010.h"
#include <math.h>


long area_of_rectangle(long w, long l)
{
  if (w == 0 || l == 0) { //if any side is 0, area will be 0
    return 0;
  } {
    long area = 2 * w * l; //calculate the 2 sides of areas for easier addition
      return area;
  }
}

double hypotenuse_of (double w, double l)
{
  double hypotenuse = sqrt(w*w +  l*l);
  return hypotenuse;
}

int main() 
{
  long w = cs1010_read_long() ;
  long l = cs1010_read_long() ;
  long h = cs1010_read_long() ;
  long surface_1 = area_of_rectangle(w,l); //includes both surface of dimension w and l
  long surface_2 = area_of_rectangle(l,h); //includes both surface of dimension l and h
  long surface_3 = area_of_rectangle(w,h); //includes both surface of dimension w and h
  long total_surface_area = surface_1 + surface_2 + surface_3; //area of all 6 sides of cube

  double hypotenuse_w_l = hypotenuse_of( (double) w,(double) l); //gives the hypotenuse of right andgle triangle with side w and l
  double diagonal_of_cuboid = hypotenuse_of( hypotenuse_w_l , (double) h) ;



  cs1010_println_long(total_surface_area); //Printing out answer of total surface area
  cs1010_println_double( diagonal_of_cuboid);
}

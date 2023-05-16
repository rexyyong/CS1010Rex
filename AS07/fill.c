/**
 * CS1010 Semester 1 AY22/23
 * Assignment 8: Fill
 *
 * @file: fill.c
 * @author: rex yong (Group c05)
 */


#include "cs1010.h"
#include <stdbool.h>


/**
 *This function creates the 3D array to store the row, column and RGB colors
 *@pre : row & col > 0 
 *@param[in] rows : number of rows in picture
 *@param[in] col : number of columns in picture
 *@return : returns the created 3D array, with the RGB colors from input stored inside
 */
long ***make_array(long rows , long col)  //creating 3d array
{
  long ***array;

  array = calloc((size_t)rows , sizeof(long**)) ; //rows portion 
  if (array == NULL) {
    cs1010_println_string("array not initialised");
    free(array) ; 
    return NULL;
  }

  array[0] = calloc((size_t)(rows * col) , sizeof(long*)); //col portion
  if (array[0] == NULL) {
    cs1010_println_string("array not initialised");
    free (array[0]) ; 
    free (array) ; 
    return NULL ; 
  }

  for (long i = 1 ; i < rows ; i += 1) {
    array[i] = array[i-1] + col ; 
  }


  for (long r = 0 ; r < rows ; r += 1) {
    for( long x = 0 ; x < col ; x += 1) {
      array[r][x] = cs1010_read_long_array(3) ;  //asiigning the input into the 3d array
      if (array[r][x] == NULL) {
        cs1010_println_string("array not initialised");
        return NULL ; 
      }
    }
  }
  return array; 
}


/**
 *This function prints out the final RGB colors in the array
 *@pre: rows & col > 0 
 *@param[in] array : 3D array with RGB colors
 *@param[in] rows : number of rows in array
 *@param[in] col : number of columns in array
 */
void print_rgb_colors(long ***array , long rows , long col) 
{
  for (long i = 0 ; i < rows ; i += 1) {
    for (long j = 0 ; j < col ; j += 1) {
      for (long k = 0 ; k < 3 ; k += 1) {
        cs1010_print_long(array[i][j][k]);
        cs1010_print_string(" ");
      }
    cs1010_println_string("");
    }
  }
}


/**
 *This bool function checks if adjacent pixels are of same segment
 *@pre: row & col > 0 
 *@param[in] array : 3D array with RGB colors
 *@param[in] current_rgb : rgb combination of the initial pixel we are checking from
 *@param[in] row_coord : row coordinate of initial pixel we are checking from
 *@param[in] col_coord : col coordinate of initial pixel we are checking from
 *@return : returns  true if pixels are same segment
 */
bool same_segment(long ***array , long current_rgb[3] , long row_coord , long col_coord)
{
  for (long i = 0 ; i < 3 ; i += 1) {
    if(array[row_coord][col_coord][i] != current_rgb[i]) { //checks for false case
      return false ; 
    }
  }
  return true ; 
}


/**
 *This function recursively calls itself and changes pixels of same segment to the rgb value to be filled
 *@pre: row & col > 0 
 *@param[in,out] row : number of rows in array, passed into same_segment function
 *@param[in,out] col : number of columns in array, passed into same_segment function
 *@param[in,out] array : 3D array with RGB colors, passed into same_segment function
 *@param[in,out] current_rgb : rgb combination of the initial pixel we are checking from, passed into same_segment function
 *@param[in] rgb_fill_value : rgb combination to fill into pixels
 *@param[in,out] row_coord : row coordinate of initial pixel we are checking from, passed into same_segment function
 *@param[in,out] col_coord : col coordinate of initial pixel we are checking from, passed into same_segment function
 */


void paint_segments(long row , long col , long ***array , long current_rgb[3] , long rgb_fill_value[3] , long row_coord , long col_coord) //function will keep on running and keep on checking as long as there are same segments
{

  for (long i = 0 ; i < 3 ; i += 1) { //changes the RGB color of the first coordinate
    array[row_coord][col_coord][i] = rgb_fill_value[i] ; 
  }

  if(row_coord - 1 >= 0 && row > 2 && same_segment(array , current_rgb , row_coord - 1 , col_coord)) { //checks up
    paint_segments(row , col , array , current_rgb , rgb_fill_value , row_coord - 1 , col_coord) ; //continue the paint segment for new coordinate

  }

  if(row_coord + 1 < row && row > 2 && same_segment(array , current_rgb , row_coord + 1 , col_coord)) { //checks down
    //cs1010_println_long(row_coord + 1);
    paint_segments(row , col , array , current_rgb , rgb_fill_value , row_coord + 1 , col_coord) ; //continue the paint segment for new coordinate
  }

  if(col_coord - 1 >= 0 && col > 2 && same_segment(array , current_rgb , row_coord , col_coord - 1)) { //checks left
    paint_segments(row , col , array , current_rgb , rgb_fill_value , row_coord , col_coord - 1) ; //continue the paint segment for new coordinate
  }

  if(col_coord + 1 < col && col > 2 && same_segment(array , current_rgb , row_coord , col_coord + 1)) { //checks right
    paint_segments(row , col , array , current_rgb , rgb_fill_value , row_coord , col_coord + 1) ; //continue the paint segment for new coordinate
  }
}


/**
 *This function allows the number of fill operations to be carried out by reading in the coordinates and fill value
 *@pre: row & col > 0 
 *@param[in,out] row : number of rows in array , passed into paint_segments function
 *@param[in,out] col : number of columns in array , passed into paint_segments function
 *@param[in,out] array : 3D array with RGB colors ,  passed into paint_segments function
 */
void to_fill (long row , long col , long ***array) 
{
  long row_coord = cs1010_read_long() ;
  long col_coord = cs1010_read_long() ;

  long current_rgb[3] = {0} ; 
  for (long j = 0 ; j < 3 ; j += 1) {
    current_rgb[j] = array[row_coord][col_coord][j] ; //assigning the current rgb values
  }


  long rgb_fill_value[3] = {0} ; 
  for (long i = 0 ; i < 3 ; i += 1) {
    rgb_fill_value[i] = cs1010_read_long() ; //reading in the rgb fill values
  }

  paint_segments(row , col , array , current_rgb , rgb_fill_value , row_coord , col_coord) ; 
}


int main() 
{
  long rows = cs1010_read_long() ;
  long col = cs1010_read_long() ;

  long ***array = make_array(rows , col) ; 
  if (array == NULL) {
    cs1010_println_string("array not initialised");
    return 1; 
  }

  long fill_operations = cs1010_read_long() ;

  for (long f = 0 ; f < fill_operations ; f += 1) {
    to_fill (rows , col , array) ; 
  }

  cs1010_print_string("P3");
  cs1010_print_string(" ");
  cs1010_print_long(col);
  cs1010_print_string(" ");
  cs1010_print_long(rows);
  cs1010_print_string(" ");
  cs1010_println_long(255);

  print_rgb_colors(array , rows , col) ; 


  for (long r = 0 ; r < rows ; r += 1) {
    for( long x = 0 ; x < col ; x += 1) {
      free(array[r][x]) ; 
    }
  }

  free(array[0]) ; 
  free(array) ; 

}

/*

long **make_array(long rows , long col) 
{
  long **array;

  array = calloc((size_t)rows , sizeof(long*)) ; 
  if (array == NULL) {
    cs1010_println_string("array not initialised");
    return NULL;
  }

  array[0] = calloc((size_t)(3 * rows * col) , sizeof(long));
  if (array[0] == NULL) {
    cs1010_println_string("array not initialised");
    return NULL ; 
  }

  for (long i = 1 ; i < rows ; i += 1) {
    array[i] = array[i-1] + (3 * col) ; 
  }
  return array ; 
}


void print_array(long **array , long rows , long col) 
{
  for (long i = 0 ; i < rows ; i += 1) {
    for (long j = 0 ; j < 3 * col ; j += 1) {
      cs1010_print_long(array[i][j]);
      cs1010_print_string(" ");
    }
    cs1010_println_string("");
  }
}

int main() 
{
  long rows = cs1010_read_long() ;
  long col = cs1010_read_long() ;

  long **array = make_array(rows , col) ; 


  for (long i = 0 ; i < rows ; i += 1) { //nested for loops reads in RGB inputs and stores it in 2d Array
    for (long j = 0 ; j < 3 * col ; j += 1) {
      array[i][j] = cs1010_read_long() ;
    }
  }


  long fill_operations = cs1010_read_long() ;

  print_array(array , rows , col) ; 


  free(array[0]) ; 
  free(array) ; 


}

*/

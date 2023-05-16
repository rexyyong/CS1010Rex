/**
 * CS1010 Semester 1 AY22/23
 * Assignment 8: maze
 *
 * @file: maze.c
 * @author: rex (Group c05)
 */
#include "cs1010.h"
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define EMPTY '.'
#define WALL  '#'
#define USER  '@'

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

/**
 * Print one row of the maze to the screen (with colors)
 * 
 * @param[in] maze_row The 1D array representing a row of maze.
 */
void print_maze_row_with_color(char *maze_row) {
  long l = (long)strlen(maze_row); 
  for (long j = 0; j < l; j++) {
    if (maze_row[j] == EMPTY) {
      cs1010_print_string(BLUE);
    } else if (maze_row[j] == USER) {
      cs1010_print_string(RED);
    } else {
      cs1010_print_string(YELLOW);
    }
    putchar(maze_row[j]);
  }
  cs1010_println_string("");
  cs1010_print_string(RESET);
}

/**
 * Print the maze to the screen.
 * @param[in] maze The 2D array representing the maze.
 * @param[in] nrows The number of rows
 * @param[in] steps The number of steps taken so far.
 */
void print_maze(char **maze, long nrows, long steps) {
  if (isatty(fileno(stdout))) {
    cs1010_clear_screen();
  }
  for (long i = 0; i < nrows; i += 1) {
    if (!isatty(fileno(stdout))) {
      cs1010_println_string(maze[i]);
    } else {
      print_maze_row_with_color(maze[i]);
    }
  }
  cs1010_println_long(steps);
  if (isatty(fileno(stdout))) {
    usleep(100*1000);
  }
}


/**
 *This function makes the explored array to track where skully has gone
 *@pre: row > 0 col > 0 
 *@param[in] row : number of rows in maze
 *@param[in] col : number of columns in maze
 *@return: 2 d array called explore
 */
long** make_explored_array (long row , long col) 
{
  long **explored; 
  explored = calloc((size_t)row , sizeof(long *)) ; 
  if (explored == NULL) {
    cs1010_println_string("array not initialised");
    free(explored) ; 
    return NULL;
  }

  explored[0] = calloc((size_t)(row * col) , sizeof(long)) ; 
  if (explored[0] == NULL) {
    cs1010_println_string("array not initialised");
    free(explored) ; 
    free(explored[0]) ; 
  }

  for (long i = 1 ; i < row ; i += 1) {
    explored[i] = explored[i-1] + col ; 
  }
  return explored ; 
}

/**
 *This function swaps the @ and . signs
 *@pre: new_row > 0 and new_col > 0 
 *@param[in,out] array : the maze array , new position will be updated
 *@param[in] new_row : the destination row
 *@param[in] new_col : destination col
 *@param[in] row_pos_of_scully : initial row pos
 *@param[in] col_pos_of_scully : initial col pos
 *@param[in] steps : number of steps skully has taken
 */
void swap(char **array , long new_row , long new_col , long row_pos_of_scully , long col_pos_of_scully , long steps[1]) 
{
  steps[0] += 1 ; //updates steps whenever swap occurs
  char temp = array[new_row][new_col] ;  //temporary stores . to temp
  array[new_row][new_col] = array[row_pos_of_scully][col_pos_of_scully] ; //assigns @ to new coordinate
  array[row_pos_of_scully][col_pos_of_scully] = temp ; //assigns . to previous coordinate
}



/**
 *This recursive function helps skully move recursively
 *@pre: row , col > 0 
 *@param[in,out] array : the maze array , new position will be uploaded
 *@param[in,out] explored_array : 2d array that stores the places skully has visited
 *@param[in] row : number of rows in maze
 *@param[in] col : number of columns in maze
 *@param[in] steps : number of steps skully has taken
 *@param[in] row_pos_of_scully : initial row pos
 *@param[in] col_pos_of_scully : initial col pos
 *@return: true if skully is at exit
 */
bool move(char **array , long **explored_array , long row , long col , long steps[1] , long row_pos_of_scully , long col_pos_of_scully) 
{
  if ((row_pos_of_scully == 0 || row_pos_of_scully == row - 1) && (col_pos_of_scully >= 0 && col_pos_of_scully < col)) { //vertical borders
    return true; 
  }
  if ((col_pos_of_scully == 0 || col_pos_of_scully == col - 1) && (row_pos_of_scully >= 0 && row_pos_of_scully < row)) { //horizontal borders
    return true;
  }

  explored_array[row_pos_of_scully][col_pos_of_scully] = 1 ; //updates explored array to 1 if scully moves

  if (row_pos_of_scully - 1 >= 0 && array[row_pos_of_scully - 1][col_pos_of_scully] == '.' && explored_array[row_pos_of_scully - 1][col_pos_of_scully] != 1) { //checks up
    swap (array , row_pos_of_scully - 1 , col_pos_of_scully , row_pos_of_scully , col_pos_of_scully , steps) ; 
    print_maze(array, row , steps[0]) ;  
    if(move(array , explored_array , row , col , steps , row_pos_of_scully - 1 , col_pos_of_scully)) {
      return true ; 
    }
    swap (array , row_pos_of_scully , col_pos_of_scully , row_pos_of_scully - 1 , col_pos_of_scully , steps) ; 
    print_maze(array, row , steps[0]) ;  
  }

  if (col_pos_of_scully + 1 < col && array[row_pos_of_scully][col_pos_of_scully + 1] == '.' && explored_array[row_pos_of_scully][col_pos_of_scully + 1] != 1) { //checks right
    swap (array , row_pos_of_scully , col_pos_of_scully + 1, row_pos_of_scully , col_pos_of_scully , steps) ; 
    print_maze(array, row , steps[0]) ;  
    if(move(array , explored_array , row , col , steps , row_pos_of_scully , col_pos_of_scully + 1)) {
      return true ; 
    }

    swap (array , row_pos_of_scully , col_pos_of_scully , row_pos_of_scully , col_pos_of_scully + 1 , steps) ; 
    print_maze(array, row , steps[0]) ;  
  }

  if (row_pos_of_scully + 1 < row && array[row_pos_of_scully + 1][col_pos_of_scully] == '.' && explored_array[row_pos_of_scully + 1][col_pos_of_scully] != 1) { //checks down
    swap (array , row_pos_of_scully + 1 , col_pos_of_scully , row_pos_of_scully , col_pos_of_scully , steps) ; 
    print_maze(array, row , steps[0]) ;  
    if(move(array , explored_array , row , col , steps , row_pos_of_scully + 1 , col_pos_of_scully)) {
      return true;
    }
    swap (array , row_pos_of_scully , col_pos_of_scully , row_pos_of_scully + 1 , col_pos_of_scully , steps) ; 
    print_maze(array, row , steps[0]) ;  
    
  }

  if (col_pos_of_scully - 1 >= 0 && array[row_pos_of_scully][col_pos_of_scully - 1] == '.' && explored_array[row_pos_of_scully][col_pos_of_scully - 1] != 1) { //checks left
    swap (array , row_pos_of_scully , col_pos_of_scully - 1, row_pos_of_scully , col_pos_of_scully , steps) ; 
    print_maze(array, row , steps[0]) ;  
    if(move(array , explored_array , row , col , steps , row_pos_of_scully , col_pos_of_scully - 1)) {
      return true ; 
    }
    swap (array , row_pos_of_scully , col_pos_of_scully , row_pos_of_scully , col_pos_of_scully - 1 , steps) ; 
    print_maze(array, row , steps[0]) ;  
   
  }
  return false;
}

int main ()
{
  long row = cs1010_read_long() ;
  long col = cs1010_read_long() ;
  long steps[1] = {0} ; //steps array to store the number of steps
  long initial_row; 
  long initial_col;

  long **explored_array = make_explored_array (row , col) ; //creating arrray of explored positions , with values initialised to 0


  char **array = cs1010_read_word_array((size_t)(row)) ;  //reading in input array
  if (array == NULL) { //dealign with allocation error
    cs1010_println_string("array not initialised");
    for (long i = 0 ; i < row ; i += 1) {
      free(array[i]) ; 
    }
    free(array) ; 
  }

  print_maze(array , row , steps[0]) ;

  for ( long i = 0 ; i < row ; i += 1) { //these 2 loops will find the coordinates initial position of '@' 
    for ( long j = 0 ; j < col ; j += 1) {
      if (array[i][j] == '@') {
        initial_row = i ; 
        initial_col = j ; 
      }
    }
  }

  explored_array[initial_row][initial_col] = 1 ; 

  move(array , explored_array , row , col , steps , initial_row , initial_col);  
        


  for (long i = 0 ; i < row ; i += 1) { //freeing array to prevent memory leak
    free(array[i]) ; 
  }
  free(array) ; 
  free(explored_array[0]) ; 
  free(explored_array) ; 

}
























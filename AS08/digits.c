/**
 * CS1010 Semester 1 AY22/23
 * Assignment 8: Digits
 *
 * @file: digits.c
 * @author: rex yong (Group c05)
 */

#include "cs1010.h"

#define NCOLS 28
#define NROWS 28
#define WHITE '.'
#define BLACK '#'
#define K 5

typedef struct digit {
  char **array;
  long label;
} digit;

typedef struct neighbour {
  long label; 
  long distance;
} neighbour; 


typedef struct k_nearest {
  long label;
  long distance;
} k_nearest ; 

//to return distance of the training arrays compared test array
/**
 *This function calculates the distance of training sample vs test sample
 *@pre : iterations >= 0 
 *@param[in] test_array : contains the 28 * 28 matrix of test sample
 *@param[in] training : 28 * 28 matrix of training sample
 *@param[in] largest_distance_so_far : the largest distance recorded so far
 *@param[in] iterations : number of training samples that has been compared to test samples
 *@return: the distance between training sample and test sample
 */
long distance(char **test_array , char **training , long largest_distance_so_far , size_t iterations) {
  long count = 0 ; 
  for (long i = 0 ; i < NROWS ; i += 1) {
    for (long j = 0 ; j < NCOLS ; j += 1) {
      if (test_array[i][j] != training[i][j]) {
        count += 1 ; 
      }

      if (count > largest_distance_so_far && iterations > 4) { 
        //stops once its largest distance and more than 5 iterations because we do not need to 
        //consider more than 5 iterations 
        return count;
      }
    }
  }
  return count ; 
}

//choose digits 
/**
 *This function decides which label is the recognised label when both labels appear twice
 *@pre: 2 distinct labels appear twice each
 *@param[in] number_with_freq_2 : array that contains the labels which appeared twice
 *@param[in] k_array : array that contains the k nearest labels and distances
 *@return: the recognised label
 */
long choose_digit(long number_with_freq_2[2] , k_nearest k_array[K])
{
  long min_so_far;
  long min_label ; 
  for (long i = 4 ; i >= 0 ; i -= 1) {
    if (k_array[i].label == number_with_freq_2[0]) {
      min_so_far = k_array[i].distance ; 
      min_label = k_array[i].label ;
    }
  }

  for (long j = 4 ; j >= 0 ; j -= 1) {
    if (k_array[j].label == number_with_freq_2[1] && min_so_far > k_array[j].distance) {
      min_so_far = k_array[j].distance;
      min_label = k_array[j].label ; 
    }
    if (k_array[j].label == number_with_freq_2[1] && min_so_far == k_array[j].distance) {
      if (k_array[j].label < number_with_freq_2[0]) {
        min_label = k_array[j].label ; 
      }
    }
  }
  return min_label;
}

/**
 *This function returns the recognised label if all labels each appear once
 *@pre: the labels each appear once
 *@param[in] k_array : array that contains the k nearest labels and distances
 *@return: the recognised label
 */
long frequency_one_tie(k_nearest k_array[K]) 
{
  long element = 0 ; 
  long min_so_far = k_array[0].distance ; 
  for (long i = 1 ; i < K ; i += 1) {
    if (k_array[i].distance < min_so_far) {
      min_so_far = k_array[i].distance ; 
      element = i ; 
    }
  }
  return k_array[element].label ; 
}

/**
 *This function returns most recognised label.  
 *It first checks if the label has highest occurence
 *Otherwise if 2 labels each appeared twice, it will call choose_digit function
 *Otherwise if all labels appear once each , it will call frequency_one_tie function
 *@param[in] k_array : array that contains the k nearest labels and distances
 *@return: the recognised label
 */
long most_common_digit (k_nearest k_array[K]) 
{
  long frequency_array[10] = {0} ; //size 10 for 10 digits, 0 to 9
  long number_with_freq_2[2] ; //stores numbers that appear twice
  //populate frequency array
  for (size_t i = 0 ; i < K ; i += 1) {
    frequency_array[k_array[i].label] += 1 ;
  }
  long highest_frequency = 0 ; 
  long most_common = 0 ;
  long count = 0; //tracks how many times numbers appear twice

  for (long x = 0 ; x < 10 ; x += 1) {
    if(frequency_array[x] == 2) {
      number_with_freq_2[count] = x ; 
      count += 1;
    }
    if(count == 2) {
      return choose_digit(number_with_freq_2 , k_array) ;
    }
  }

  for (size_t j = 0 ; j < 10 ; j += 1) { 
    //this loop will identify the most_common_digit
    //j represents the digits 0 - 9
    if (frequency_array[j] > highest_frequency) { 
      //if the higest occurence is equal, it will not update since condition is > higest_occurence
      most_common = (long)j ; 
      highest_frequency = frequency_array[j] ; 
    }
  }
  //if there is a tie in all labels, where highest frequency is 1
  if(highest_frequency == 1) {
    return frequency_one_tie(k_array) ; 
  }
  return most_common; 
}

/**
 *This function returns the recognised label from k nearest samples array
 *This function sorts and populates the k nearest array of size 5 with the labels and distances
 *@param[in] label_distance : the label and distance obtained when training samples is compared with test sample
 *@param[in] num_training : number of training samples given in input
 *@return : recognised label
 */
long recognise_digit (neighbour *label_distance , size_t num_training) 
{
  k_nearest k_array[K] ;//make array of size 5
  for (size_t i = 0 ; i < K ; i += 1) { //loops for size of k nearest array
    //long minimum = largest_distance_so_far ; 
    long minimum = 28 * 28 ; 
    long k_nearest_element = 0; //the index of k nearest element

    for (size_t j = 0 ; j < num_training ; j += 1) { 
      if (label_distance[j].distance < minimum) { 
        //this condition will look for minimum distance
        minimum = label_distance[j].distance ; 
        k_nearest_element = (long)j ;
      }
      else if ((label_distance[j].distance == minimum) && (label_distance[j].label < label_distance[k_nearest_element].label)) {
        //this condition decides the distance when there is a tie
        //minimum = label_distance[j].distance ; 
        k_nearest_element = (long)j ; 
      }
    }
    k_array[i].distance = minimum ; 
    k_array[i].label = label_distance[k_nearest_element].label ; 
    label_distance[k_nearest_element].distance = 28 * 28 + 1; 
    //last step updates the smallest element to largest so that it won't be double counted 
  }
  long recognised_digit = most_common_digit(k_array) ; 
  return recognised_digit ; 
}

/**
 * This function looks for recognised label by calling comparisons of training smaples with different test samples
 *This function loops through test arrays, and then allocates the distance of test array and training array
 *into another array named label_distance of type neighbour
 *It then passes the label_distance array into recognise_digit function to find recognised label
 *@param[in] num_training : num of training smaples given
 *@param[in] training : array of training sample matrix and trainign sample label
 *@param[in] test_array : array containing the test sample
 *@return: recognised label
 */
long call_recognised(size_t num_training , digit *training , char **test_array) 
{
  neighbour *label_distance = calloc(num_training , sizeof(neighbour)) ; 
  //null check
  if (label_distance == NULL) {
    cs1010_println_string("error");
    free(label_distance) ; 
    return 1; 
  }
  long largest_distance_so_far = 0 ; 
  for (size_t i = 0 ; i < num_training ; i += 1) {
    label_distance[i].label = training[i].label ; //updating label number
    long dist = distance (test_array , training[i].array , largest_distance_so_far , i) ; 
    label_distance[i].distance = dist ; //updating distance in

    if (dist > largest_distance_so_far) { //updates largest distance to maximum
      largest_distance_so_far = dist ; 
    }
  }

  long recognised = recognise_digit(label_distance , num_training) ; 
  free(label_distance) ; 
  for(long r = 0 ; r < NROWS ; r += 1) {
    free(test_array[r]) ; 
  }
  free(test_array) ; 
  return recognised; 
}

/**
 *function calls the respective checks to recognise digit, and then it prints output
 *@pre: num_training >= 1
 *@param[in] num_training : the num of training samples taken in 
 *@param[in] training : the label and sample matrix of training samples
 */
void call_checks_and_print(size_t num_training , digit *training) 
{
  size_t num_test = cs1010_read_size_t() ;
  long correctly_recognised = 0 ; 

  for (size_t i = 0 ; i < num_test ; i += 1) {
    long label = cs1010_read_long() ;
    char **test_array = cs1010_read_word_array(NROWS) ; 
    // Null check
    if (test_array == NULL) {  
      for (long k = 0 ; k < NROWS ; k += 1) {
        free(test_array[k]) ;
      }
      free(test_array) ; 
    }

    cs1010_print_long(label);
    cs1010_print_string(" ");
    long recognised = call_recognised(num_training , training , test_array) ;
    cs1010_println_long(recognised);

    if (label == recognised) {
      correctly_recognised += 1;
    }
  }
  //calculate the percentage accuracy
  double accuracy = ((double)correctly_recognised / (double)num_test) * 100 ; 
  cs1010_println_double(accuracy);
}

/**
 *Function frees memory 
 *@param[in] num_training : number of training samples taken in
 *@param[in] training : label and 2d matrix of training samples
 */
void free_mem(size_t num_training , digit *training)
{
  for (size_t j = 0 ; j < num_training ; j += 1) {
    for (long k = 0 ; k < NROWS ; k += 1) {
      free(training[j].array[k]) ; 
    }
    free(training[j].array) ;
  }
  free(training) ; 
}

/**
 *Function performs null check
 *@param[in] training : label and 2d matrix of trainign samples
 *@param[in] i : the index of training.array 
 *@param[in] num_training : number of training samples taken in
 */
void null_check(digit *training , size_t i , size_t num_training)
{
  if (training[i].array == NULL) {  
    cs1010_println_string("error allocating");
    for (size_t j = 0 ; j < num_training ; j += 1) {
      for (long k = 0 ; k < NROWS ; k += 1) {
        free(training[j].array[k]) ; 
      }
      free(training[j].array) ;
    }
  }
}

int main() 
{
  //reading in of training labels and arrays
  size_t num_training = cs1010_read_size_t() ;

  digit *training = calloc(num_training , sizeof(digit)) ; //allocate memory according to number of training
  if (training == NULL) {
    cs1010_println_string("error");
    free(training) ; 
    return 1; 
  }

  for (size_t i = 0 ; i < num_training ; i += 1) {
    training[i].label = cs1010_read_long() ;
    training[i].array = cs1010_read_word_array(NROWS) ; 
    null_check(training , i , num_training) ; 
  }

  call_checks_and_print(num_training , training) ;
  free_mem(num_training , training); 
}





/*
   long choose_digit(long number_with_freq_2[2] , k_nearest k_array[K])
   {

   long smallest_distance_so_far = 28 * 28 ; 
   for (long i = 0 ; i < K ; i += 1) {
//identifies which digit has smallest distance
if((k_array[i].label == number_with_freq_2[0] || k_array[i].label == number_with_freq_2[1]) && k_array[i].distance < smallest_distance_so_far) {
smallest_distance_so_far = k_array[i].distance ; 
//cs1010_println_long(smallest_distance_so_far);
}
}
long chosen_digit; 

//if 2 different labels both have the same smallest distance
long count = 0;
long clashing_labels[2] = {-1} ; 
for(long i = 0 ; i < K ; i += 1) {
if(k_array[i].distance == smallest_distance_so_far && (k_array[i].label != clashing_labels[0]) && count < 2) {
//the second time a smallest distance clashes, it will check if it is the same label
clashing_labels[count] = k_array[i].label ; //updates the label in 
count += 1; 
}
}

if(count == 2) { //signifies that 2 diff labels have same smallets distance
if(clashing_labels[0] < clashing_labels[1]) {
return clashing_labels[0] ; 
}
return clashing_labels[1];
}

//if there are no clashes in smallest distance
for(long x = 0 ; x < K ; x += 1) {

if(k_array[x].distance == smallest_distance_so_far && (k_array[x].label == number_with_freq_2[0] || k_array[x].label == number_with_freq_2[1])) {
//chooses digit based on which has smallest distance
chosen_digit = k_array[x].label;
//return k_array[x].label ; 
}
}
return chosen_digit;
}
*/


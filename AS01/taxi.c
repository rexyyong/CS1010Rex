/**
 * CS1010 Semester 1 AY22/23
 * Assignment 1: Taxi
 *
 * Read in four positive integer corresponding to the day of the week,
 * the hour and minute of boarding, and the distance travelled.  Print
 * to the standard output, the taxi fare for the trip.
 *
 * @file: taxi.c
 * @author: Rex yong jin xiang (Group C05)
 */

#include "cs1010.h"
#include <stdbool.h>

bool is_weekday(long day) //function that returns true if it is weekday, false if weekend
{
  if (day >= 1 && day <= 5) {
    return true; 
  } return false;
}


bool is_morning_peak (long hours, long minutes)
{
  long time = (hours * 100) + minutes; //representing time in HHMM format, and storing it into var time 
  if(time >= 600 && time <= 929) { //if time is between 0600hrs and 0929 hrs inclusive
    return true;
  } return false;
}


bool is_evening_peak (long hours, long minutes)
{
  long time = (hours * 100) + minutes; //representing time in HHMM format, and storing it into var time 
  if(time >= 1800 && time <= 2359 ) { //if time is between 1800hrs and 2359 hrs inclusive
    return true;
  } return false;
}


bool is_midnight_peak (long hours, long minutes)
{
  long time = (hours * 100) + minutes; //representing time in HHMM format, and storing it into var time 
  if(time >= 0 && time <= 559 ) { //if time is between 0000hrs and 0559 hrs inclusive
    return true;
  } return false;
}


long what_surcharge (bool morning_peak, bool midnight_peak, bool evening_peak , bool weekday)
{
  long surcharge; //defining variable to store surcharge value
  if (weekday == 1 && morning_peak == 1) {
    return surcharge = 25; // surcharge == 25%
  } if (evening_peak == 1) {
    return surcharge = 25;
  } if (midnight_peak == 1) {
    return surcharge = 50;
  } return surcharge = 0;
}

double basic_fare(long distance)
{
  if ( distance>10000 ) {
    long factor = ((distance-10000)/350); //defining variable factor, the number used to multiply in fare 
    if ((distance-10000)%350 >0) { //If there is remainder, means that we need to add 1 to factor to account for part thereof fare 
      factor += 1;
    } else {
      factor =((distance-10000)/350) ;
    }
    double fare = 3.9 + 23*0.24 + (double)factor*0.24 ; 
    return fare;
  } if (distance>1000) {
    long factor = ((distance-1000)/400);
    if ((distance-1000)%400>0) { //If there is remainder, means that we need to add 1 to factor to account for part thereof fare 
      factor += 1;
    } else {
      factor =((distance-1000)/400) ;
    }
    double fare = 3.9 + (double)factor*0.24;
    return fare;
  } 
    double fare = 3.9;
    return fare;
  
}

double final_fare (long surcharge_percentage, double final_basic_fare)
{
  if(surcharge_percentage == 25) {
    double total_fare = final_basic_fare * (double)125/(double)100 ;
    return total_fare; 
  } if (surcharge_percentage == 50) {
    double total_fare = final_basic_fare * (double)150/(double)100 ;
    return total_fare; 
  }
  return final_basic_fare;
  
}



int main()
{
  //obtaining inputs for the program 
  long day = cs1010_read_long() ;
  long hours = cs1010_read_long() ;
  long minutes = cs1010_read_long() ;
  long distance = cs1010_read_long() ;

  bool morning_peak = is_morning_peak(hours, minutes); //storing the true or false values into the respective variables
  bool evening_peak = is_evening_peak(hours, minutes);
  bool midnight_peak = is_midnight_peak(hours, minutes);
  bool weekday = is_weekday (day);

  long surcharge_percentage = what_surcharge (morning_peak, midnight_peak, evening_peak, weekday) ; // returns surcharge percentage and stores in variable
  
  double final_basic_fare = basic_fare(distance);

  double total_fare = final_fare( surcharge_percentage, final_basic_fare);
  cs1010_println_double(total_fare);

}

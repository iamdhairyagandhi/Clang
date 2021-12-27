#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"
#include "calendar.h"
#include "my_memory_checker_216.h"

/*****************************************************/
/* In this file you will provide tests for your      */
/* calendar application.  Each test should be named  */
/* test1(), test2(), etc. Each test must have a      */
/* brief description of what it is testing (this     */
/* description is important).                        */
/*                                                   */
/* You can tell whether any test failed if after     */
/* executing the students tests, you executed        */
/* "echo $?" on the command line and you get a value */
/* other than 0.  "echo $?" prints the status of     */
/* the last command executed by the shell.           */
/*                                                   */
/* Notice that main just calls test1(), test2(), etc.*/
/* and once one fails, the program eventually        */
/* return EXIT_FAILURE; otherwise EXIT_SUCCESS will  */
/* be returned.                                      */
/*****************************************************/

static int
comp_minutes(const void *ptr1, const void *ptr2)
{
   return ((Event *)ptr1)->duration_minutes -
          ((Event *)ptr2)->duration_minutes;
}

typedef struct task_info
{
   double cost;
   char *prog_language;
} Task_info;

static Task_info *create_task_info(double cost, const char *prog_language)
{
   Task_info *task_info = malloc(sizeof(Task_info));

   if (task_info)
   {
      task_info->prog_language = malloc(strlen(prog_language) + 1);
      if (task_info->prog_language)
      {
         task_info->cost = cost;
         strcpy(task_info->prog_language, prog_language);
         return task_info;
      }
   }

   return NULL;
}

/* Description here: This test checks print_calendar with no events and destroy calendar 
 * if init_calendar and print_calendar return SUCCESS ancd prints correctly the calendar 
 * with no events  */
static int test1()
{
   int days = 7;
   Calendar *calendar;

   if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS)
   {
      if (print_calendar(calendar, stdout, 1) == SUCCESS)
      {
         return destroy_calendar(calendar);
      }
   }

   return FAILURE;
}

/* test if add_event works successfully with a call that should add the respective event 
 * and with another, test if it doesn't add a event that already exists and doesn't add
 * a event to a day that is greater than the calendar-.days */
static int test2()
{
   int days = 1;
   Calendar *calendar;

   init_calendar("Spr", days, comp_minutes, NULL, &calendar);
   if (add_event(calendar, "e", 1600, 100, NULL, 1) == SUCCESS &&
       add_event(calendar, "event 1", 1700, 200, NULL, 1) == FAILURE &&
       add_event(calendar, "day 2 event 1", 1600, 100, NULL, 2) == FAILURE)
   {
      return SUCCESS;
   }
   return FAILURE;
}

/* test init_calendar fails with illegal arguments  */
static int test3()
{
   int days = 7, result = SUCCESS;
   Calendar *calendar;

   if (init_calendar(NULL, days, comp_minutes, NULL, &calendar) == SUCCESS ||
       init_calendar("Spr", -1, comp_minutes, NULL, &calendar) == SUCCESS ||
       init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS)
   {
      result = FAILURE;
   }
   return result;
}

/* test destroy_calendar */
static int test4()
{
   int days = 7;
   Calendar *calendar;

   if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS)
   {
      add_event(calendar, "event 1", 1600, 100, NULL, 1);
      add_event(calendar, "event 1", 1700, 200, NULL, 1);
      add_event(calendar, "day 2 event 1", 1600, 100, NULL, 2);
      return destroy_calendar(calendar);
   }
   return FAILURE;
}

/* test if find_event finds event successfully */
static int test5()
{
   int days = 2;
   Calendar *calendar;
   Event *event;

   init_calendar("Spr", days, comp_minutes, NULL, &calendar);
   add_event(calendar, "event 1", 1600, 100, NULL, 1);
   add_event(calendar, "event 1", 1700, 200, NULL, 1);
   add_event(calendar, "day 2 event 1", 1600, 100, NULL, 2);
   print_calendar(calendar, stdout, 1);
   return find_event(calendar, "day 2 event 1", &event);
}

/* test if find_event_in_day finds event at the start and end of list,
 * successfully and returns FAILURE for an event that doesn't exist */
static int test6()
{
   int days = 2;
   Calendar *calendar;
   Event *event;

   init_calendar("Spr", days, comp_minutes, NULL, &calendar);
   add_event(calendar, "event 1", 1600, 100, NULL, 1);
   add_event(calendar, "event 1", 1700, 200, NULL, 1);
   add_event(calendar, "day 2 event 1", 1600, 100, NULL, 2);
   add_event(calendar, "day 2 event 2", 1600, 100, NULL, 2);
   print_calendar(calendar, stdout, 1);
   if (find_event_in_day(calendar, "day 2 event 1", 2, &event) == SUCCESS &&
       find_event_in_day(calendar, "day 2 event 2", 2, &event) == SUCCESS &&
       find_event_in_day(calendar, "day 2 event 3", 2, &event) == FAILURE)
   {
      return SUCCESS;
   }
   return FAILURE;
}

/* test if remove_event removes event from a list with only one event and afrom nother with 2,
 * successfully and returns FAILURE for an event that doesn't exist */
static int test7()
{
   int days = 2;
   Calendar *calendar;

   init_calendar("Spr", days, comp_minutes, NULL, &calendar);
   add_event(calendar, "event 1", 1600, 100, NULL, 1);
   add_event(calendar, "event 1", 1700, 200, NULL, 1);
   add_event(calendar, "day 2 event 1", 1600, 100, NULL, 2);
   add_event(calendar, "day 2 event 2", 1600, 100, NULL, 2);
   print_calendar(calendar, stdout, 1);
   if (remove_event(calendar, "day 2 event 1") == SUCCESS &&
       remove_event(calendar, "event 1") == SUCCESS &&
       remove_event(calendar, "day 2 event 3") == FAILURE)
   {
      print_calendar(calendar, stdout, 1);
      return SUCCESS;
   }
   print_calendar(calendar, stdout, 1);
   return FAILURE;
}

/* test if get_event_info return event info successfully and NULL in case the event
 * is not found*/
static int test8()
{
   int days = 2;
   Calendar *calendar;
   Task_info *info;

   init_calendar("Spr", days, comp_minutes, NULL, &calendar);
   add_event(calendar, "event 1", 1600, 100, NULL, 1);
   info = create_task_info(3500, "Java");
   add_event(calendar, "event 1", 1700, 200, info, 1);
   add_event(calendar, "day 2 event 1", 1600, 100, NULL, 2);
   add_event(calendar, "day 2 event 2", 1600, 100, NULL, 2);
   print_calendar(calendar, stdout, 1);
   return get_event_info(calendar, "event 1") != NULL &&
          get_event_info(calendar, "event 2") == NULL;
}

/* test if clear_calendar clears the calendar successfully and sets total number 
 * of events to 0*/
static int test9()
{
   int days = 2;
   Calendar *calendar;
   Task_info *info;

   init_calendar("Spr", days, comp_minutes, NULL, &calendar);
   add_event(calendar, "event 1", 1600, 100, NULL, 1);
   info = create_task_info(3500, "Java");
   add_event(calendar, "event 1", 1700, 200, info, 1);
   add_event(calendar, "day 2 event 1", 1600, 100, NULL, 2);
   add_event(calendar, "day 2 event 2", 1600, 100, NULL, 2);
   print_calendar(calendar, stdout, 1);
   return clear_calendar(calendar) && calendar->total_events == 0;
}

/* test if clear_day clears all events in that day successfully */
static int test10()
{
   int days = 2;
   Calendar *calendar;
   Task_info *info;

   init_calendar("Spr", days, comp_minutes, NULL, &calendar);
   add_event(calendar, "event 1", 1600, 100, NULL, 1);
   info = create_task_info(3500, "Java");
   add_event(calendar, "event 1", 1700, 200, info, 1);
   add_event(calendar, "day 2 event 1", 1600, 100, NULL, 2);
   add_event(calendar, "day 2 event 2", 1600, 100, NULL, 2);
   print_calendar(calendar, stdout, 1);
   return clear_day(calendar, 2) && calendar->events[1] == NULL;
}

int main()
{
   int result = SUCCESS;

   /***** Starting memory checking *****/
   start_memory_check();
   /***** Starting memory checking *****/

   if (test1() == FAILURE)
      result = FAILURE;
   if (test2() != FAILURE)
      result = FAILURE;
   if (test3() == FAILURE)
      result = FAILURE;
   if (test4() == FAILURE)
      result = FAILURE;
   if (test5() == FAILURE)
      result = FAILURE;
   if (test6() == FAILURE)
      result = FAILURE;
   if (test7() == FAILURE)
      result = FAILURE;
   if (!test8())
      result = FAILURE;
   if (!test9())
      result = FAILURE;
   if (!test10())
      result = FAILURE;

   /****** Gathering memory checking info *****/
   stop_memory_check();
   /****** Gathering memory checking info *****/

   if (result == FAILURE)
   {
      exit(EXIT_FAILURE);
   }

   return EXIT_SUCCESS;
}

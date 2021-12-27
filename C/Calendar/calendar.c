
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"
#include "calendar.h"
/*
Check if:
    - calendar or name are NULL
    - days < 1
    - memory allocation fails
else:
    - allocate memory for:
        - calendar struct
        - name field
        - events field (days * sizeof(**events))
    - return success
*/
int init_calendar(const char *name, int days,
                  int (*comp_func)(const void *ptr1, const void *ptr2),
                  void (*free_info_func)(void *ptr), Calendar **calendar)
{
    Calendar *filler_calendar;
    if (calendar == NULL || name == NULL || days < 1)
    {
        return FAILURE;
    }

    filler_calendar = malloc(sizeof(Calendar));
    if (filler_calendar == NULL)
    {
        return FAILURE;
    }

    filler_calendar->name = malloc(strlen(name) * sizeof(char) + 1);
    if (filler_calendar->name == NULL)
    {
        return FAILURE;
    }

    filler_calendar->events = calloc(days, sizeof(Event *));
    if (filler_calendar->events == NULL)
    {
        return FAILURE;
    }
    filler_calendar->comp_func = comp_func;
    filler_calendar->free_info_func = free_info_func;
    strcpy(filler_calendar->name, name);
    filler_calendar->total_events = 0;
    filler_calendar->days = days;
    *calendar = filler_calendar;

    return SUCCESS;
}
/*
Check null

Calendar's Name: "Summer Calendar"
Days: 3
Total Events: 4

**** Events ****
Day 1
Event's Name: "group meeting", Start_time: 500, Duration: 60
Event's Name: "review meeting", Start_time: 800, Duration: 80
Event's Name: "zoo visit", Start_time: 900, Duration: 50
Day 2
Day 3
Event's Name: "lunch", Start_time: 1200, Duration: 45
*/
int print_calendar(Calendar *calendar, FILE *output_stream, int print_all)
{

    int i = 0;

    if (calendar == NULL || output_stream == NULL)
    {
        return FAILURE;
    }

    if (print_all)
    {
        fprintf(output_stream, "%s\"%s\"\n", "Calendar's Name: ", calendar->name);
        fprintf(output_stream, "%s%d\n", "Days: ", calendar->days);
        fprintf(output_stream, "%s%d\n", "Total Events: ", calendar->total_events);
    }
    printf("\n");
    printf("**** Events ****\n");
    if (calendar->total_events == 0)
    {
        return SUCCESS;
    }
    for (i = 0; i < calendar->days; i++)
    {
        Event *curr_event = calendar->events[i];

        fprintf(output_stream, "Day %d\n", i + 1);
        while (curr_event != NULL)
        {
            fprintf(output_stream, "Event's Name: \"%s\", Start_time: %d, Duration: %d\n",
                    curr_event->name, curr_event->start_time, curr_event->duration_minutes);
            curr_event = curr_event->next;
        }
    }
    return SUCCESS;
}
int add_event(Calendar *calendar, const char *name, int start_time,
              int duration_minutes, void *info, int day)
{
    Event *filler_event, *new_event, *this_next, *same = NULL;

    /*TODO add the conditions-> check description. initialize the variables as above, but after
	 * the if that checks all of these conditions */
    if (calendar == NULL || name == NULL || start_time < 0 || start_time > 2400 ||
        duration_minutes <= 0 || day < 1 || day > calendar->days)
    {
        return FAILURE;
    }
    this_next = calendar->events[day - 1];
    filler_event = calendar->events[day - 1];
    new_event = malloc(sizeof(Event));
    if (new_event == NULL)
    {
        return FAILURE;
    }
    new_event->name = malloc(strlen(name) + 1);
    if (new_event->name == NULL)
    {
        return FAILURE;
    }
    strcpy(new_event->name, name);
    new_event->duration_minutes = duration_minutes;
    new_event->start_time = start_time;
    new_event->info = info;
    new_event->next = NULL;
    if (find_event(calendar, new_event->name, &same) == SUCCESS)
    {
        return FAILURE;
    }
    if (!calendar->events[day - 1])
    { /* list empty */
        calendar->events[day - 1] = new_event;
        calendar->total_events++;
        return SUCCESS;
    }
    if (calendar->comp_func(calendar->events[day - 1], new_event) >= 0)
    {
        new_event->next = calendar->events[day - 1];
        calendar->events[day - 1] = new_event;
        calendar->total_events++;
        return SUCCESS;
    }
    while (filler_event != NULL)
    {
        if (filler_event->next != NULL && calendar->comp_func(filler_event->next, new_event) == 0)
        {
            this_next = filler_event;
        }
        else if (calendar->comp_func(filler_event, new_event) < 0)
        {
            this_next = filler_event;
        }
        filler_event = filler_event->next;
    }

    if (this_next->next)
    {
        new_event->next = this_next->next;
    }
    this_next->next = new_event;
    calendar->total_events++;

    return SUCCESS;
}
/*
 Check if:
    - Calendar and/or name are NULL
    if(calendar has aan event == name){
        success;
    }
*/
int find_event(Calendar *calendar, const char *name, Event **event)
{
    int isfound = 0, i = 0, check = 0;
    /*Event *filler_event;*/
    if (calendar == NULL || name == NULL)
    {
        return FAILURE;
    }

    for (i = 0; i < calendar->days; i++)
    {
        check = find_event_in_day(calendar, name, i + 1, event);
        if (check == 0)
        {
            isfound = 1;
            break;
        }
    }
    if (isfound)
    {
        return SUCCESS;
    }
    return FAILURE;
}
int find_event_in_day(Calendar *calendar, const char *name, int day,
                      Event **event)
{
    int isfound = 0, i = 0;
    Event *filler_event = calendar->events[day - 1];
    if (calendar == NULL || name == NULL)
    {
        return FAILURE;
    }

    if (day < 1 || day > calendar->days)
    {
        return FAILURE;
    }

    while (filler_event != NULL)
    {
        if (strcmp(filler_event->name, name) == 0)
        {
            *event = filler_event;
            isfound = 1;
            break;
        }
        filler_event = filler_event->next;
    }
    if (!isfound)
    {
        return FAILURE;
    }
    return SUCCESS;
}
int remove_event(Calendar *calendar, const char *name)
{
    int i;
    Event *filler_event, *this, *prev;
    /*  Checking conditions */
    if (calendar == NULL || name == NULL)
    {
        return FAILURE;
    }

    if (find_event(calendar, name, &filler_event) == FAILURE)
    {
        return FAILURE;
    }

    /* Iterating thru the events and searching the event to remove */
    for (i = 0; i < calendar->days; i++)
    {
        this = calendar->events[i];

        if (this != NULL)
        {
            /* if this = event name */
            if (strcmp(this->name, name) == 0)
            {
                calendar->events[i] = this->next;
                this->next = NULL;
                if (this->info != NULL && calendar->free_info_func != NULL)
                {
                    calendar->free_info_func(filler_event->info);
                }
                free(this->name);
                free(this);
                (calendar->total_events)--;
                return SUCCESS;
            }
            /* if {a b c d e} are events 
                  {0 1 2 3 4} are locations
                   and we want to remove c
                    
                    - we go to c
                    - we update 2 = d
                    - we update 3 = e
                    - location --;

                    in general:
                    - reach at the index to remove (n)
                    - update n+1 position's event at nth position for list size - n times
                   */
            else
            {
                while (this && strcmp(this->name, name) != 0)
                {
                    prev = this;       /* n to n+1 */
                    this = this->next; /* n+1 to (n+1)+1 */
                }
                /* move previous pointer to this->next, skip target */
                if (this != NULL)
                {
                    prev->next = this->next;
                    this->next = NULL;
                    if (this->info != NULL && calendar->free_info_func != NULL)
                    {
                        calendar->free_info_func(filler_event->info);
                    }
                    free(this->name);
                    free(this);
                    (calendar->total_events)--;

                    return SUCCESS;
                }
            }
            /* Release that chunk of memory to close memory leaks */
        }
    }
    return FAILURE; /* For end */
}

void *get_event_info(Calendar *calendar, const char *name)
{
    Event *filler_event;
    find_event(calendar, name, &filler_event);
    if (filler_event->info == NULL)
    {
        return NULL;
    }
    return filler_event->info;
}
int clear_calendar(Calendar *calendar)
{
    int i;
    /*Event *replace_event;*/
    if (calendar == NULL)
    {
        return FAILURE;
    }

    for (i = 0; i < calendar->days; i++)
    {
        clear_day(calendar, i + 1);
    }
    return SUCCESS;
}
int clear_day(Calendar *calendar, int day)
{
    Event *filler_event, *temp_event;
    if (calendar == NULL || day < 1 || day > calendar->days)
    {
        return FAILURE;
    }
    filler_event = calendar->events[day - 1];

    while (filler_event)
    {
        temp_event = filler_event->next;
        remove_event(calendar, filler_event->name);
        filler_event = temp_event;
    }
    /* remove_event(calendar,filler_event->name);
    */
    return SUCCESS;
}
int destroy_calendar(Calendar *calendar)
{
    if (calendar == NULL)
    {
        return FAILURE;
    }
    else
    {
        clear_calendar(calendar);
        free(calendar->name);
        free(calendar->events);
        free(calendar);
        return SUCCESS;
    }
}

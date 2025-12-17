#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NAME_LEN 20
typedef struct Boat Boat;
typedef struct ArrayList ArrayList;
struct Boat //Struct that contains boat info
{
int start_x, start_y, delta_x, delta_y, start_time;
char name[NAME_LEN + 1];
};
struct ArrayList //Struct that contains struct of boat
{
struct Boat *array;
int size, capacity;
};
// Given a point to a list initialize the list
ArrayList *initArrayList(int n);
// Given a list and a boat tot add to it, add the boat to the end
// of the list
// Expand the list if necessary
void appendToList(ArrayList *list, Boat newBoat);
// Check if the list is full
// Expand the list
// Add the boat to the end of the list
// Update the lists size
list->size++;
copyBoat(&list->array[list->size - 1], newBoat);
}
//storing values from temp
void copyBoat(Boat *orig, Boat temp) {
orig->delta_x = temp.delta_x;
orig->delta_y = temp.delta_y;
orig->start_x = temp.start_x;
orig->start_y = temp.start_y;
orig->start_time = temp.start_time;
strcpy(orig->name, temp.name);
}
int query(int x, int y, int storm_width, int storm_height, int
Grid_width,
int Grid_height, ArrayList *list, int cur_time, int
print_flag)
{
int boat_list = 0; //inilizing anwser
Boat temp;
int boat_new_y, boat_new_x;
int storm_end_x = 0, storm_end_y;
int time_elapsed;
for (int i = 0; i < list->size; i++) { //looping through all the
boats in the list
copyBoat(&temp, list->array[i]); //getting current boat
if (temp.delta_x == 0) {
// Get the current location of the boat (based on time)
boat_new_x = temp.start_x;
time_elapsed = cur_time - temp.start_time;
boat_new_y = temp.start_y + (temp.delta_y *
time_elapsed); //using time passed to determine boat location
if (boat_new_y < 0) { //determines if the new value of y is
negative thus off the bottome of the grid
boat_new_y += Grid_height; //wraps the boat around the
grid
}
if (boat_new_y >= Grid_height) { //determins if new boat y
is greater then grid height
boat_new_y -= boat_new_y; //wraps the boat around
}
storm_end_y = y + storm_height;
if (storm_end_y >= Grid_height) { //if statemnt that
determines if the storm needs to wrap around
storm_end_y -= Grid_height; // we wrap the storm around by
subtracting the storms value by grid height
if (boat_new_y < storm_end_y || boat_new_y >= y) { //if
statement that determnines if bots in the storm by comp[aring its
new y value to the y of the storm
boat_list++;
if (print_flag != 0) {
printf("Boat in the storm: %s\n", temp.name);
}
}
} else {
if (boat_new_y >= y && boat_new_y < storm_end_y) { //if
statemnt to determine if boat is in the storm
boat_list++;
if (print_flag != 0) {
printf("Boat in the storm: %s\n", temp.name);
}
}
}
} else if (temp.delta_y == 0) { //wraps offest around word if
needed
boat_new_y = temp.start_y;
time_elapsed = cur_time - temp.start_time;
boat_new_x = temp.start_x + (temp.delta_x *
time_elapsed); //using time passed to determine boat location
if (boat_new_x < 0) {
boat_new_x = Grid_width + boat_new_x;
}
if (boat_new_x >= Grid_width) {
boat_new_x = boat_new_x - Grid_width;
}
storm_end_x = x + storm_width;
//if statemnt is tru then strom is out of bounds and wraps around
if (storm_end_x >= Grid_width) {
storm_end_x -= Grid_width;
//if boat new x value is in between the end of the storm and
greater then the inputted x the boat is in the storm
if (boat_new_x < storm_end_x || boat_new_x >= x) {
boat_list++;
if (print_flag != 0) { //if the value of our flag changes
the boat is in the storm
printf("Boat in the storm: %s\n", temp.name);
}
}
} else if (storm_end_x < Grid_width) {
if (boat_new_x >= x && boat_new_x < storm_end_x) {
boat_list++;
if (print_flag != 0) {
printf("%s\n", temp.name);
}
}
}
}
}
return boat_list;
}
void cleanList(ArrayList *list, int n) { //cleaning up memory
for (int i = 0; i < n; i++) {
free(list[i].array);
}
free(list);
}

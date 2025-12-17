#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
//The users input has to be between 100 and 1
#define max 100
#define min 1
// Define a function 'boat_guess'
int boat_guess(int o, int p, int x[o+1][p+1])
{
// Declare an integer array 'y'
int y[(o+1)*(p+1)+2];
// Declare an integer variable 'k' and initialize it to 0. This variable will
keep track of the number of elements in the array 'y'
int k = 0;
// Declare an integer variable 'temp' which will be used as a temporary
variable during swapping of elements in the array 'y'
int temp;
// Loop through all the elements of the 2D array 'x'
for(int i = 0; i <= o; i++)
{
for(int j = 0; j <= p; j++)
{
// If the current element of 'x' is not equal to -1
if(x[i][j] != -1)
{
// Add the current element to the array 'y'
y[k] = x[i][j];
// Increase the value of 'k' by 1
k++;
}
}
}
// Sorts the elements of the array 'y' in ascending order
for(int i = 0; i < k; i++)
{
for(int j = i; j < k; j++)
{
// If the current element is greater than the next element, swap them
if(y[i] > y[j])
{
temp = y[i];
y[i] = y[j];
y[j] = temp;
}
}
}
if(k == 1)
{
// If there is only 1 element in the array 'y', return that element
return y[0];
}
if(k % 2 == 0)
{
// If the number of elements in the array 'y' is even return the middle
element
return y[(k/2) - 1];
}
else
{
// in any other case return the middle element
return y[((k+1)/2) - 1];
}
}
int main()
{
int speed_m, location_m;
// Read in the maximum speed value from the user.
scanf("%d", &speed_m);
// Keep prompting the user for a valid maximum speed value
// until the value entered is within the range of min and max.
// The while loop will repeat until a valid value is entered.
while(speed_m < min || speed_m > max)
{
scanf("%d", &speed_m);
}
// Read in the maximum location value from the user.
scanf("%d", &location_m);
// Keep prompting the user for a valid maximum location value
// until the value entered is within the range of min and max.
// The while loop will repeat until a valid value is entered.
while(location_m < min || location_m > max)
{
scanf("%d", &location_m);
}
// Initialize a two-dimensional array to store values of boat speeds and
locations.
int boats[location_m + 1][speed_m + 1];
// Fill the boat array with values.
for(int i = 0; i <= location_m; i++)
{
for(int j = 0; j <= speed_m; j++)
{
// Store the sum of the location and speed values for each boat in the
current cell of the array.
boats[i][j] = i + j;
}
}
int count_picture = 0; // Initialize a picture number counter to 0.
char wake_r[20]; // Initialize a response string
int total = (location_m+1)*(speed_m+1);
int guess;
while(count_picture < 24)
{
guess = boat_guess(location_m,speed_m, boats);
//If the boat is found, print the location and break out of the loop
if(total == 1)
{
printf("! %d\n", guess);
fflush(stdout);
break;
}
//Print the guess and flush the output
printf("? %d\n", guess);
fflush(stdout);
//scanning for users response
scanf("%s", wake_r);
//If the response starts with 'W',
if(wake_r[0] == 'W')
{
//Loop through all the locations and speeds
for(int i = 0; i <= location_m; i++)
{
for(int j = 0; j <= speed_m; j++)
{
//If the boat at this location is less than or equal to the guess
and the boat has not been marked as eliminated mark the boat as eliminated
if(boats[i][j] <= guess && !(boats[i][j] == -1))
{
boats[i][j] = -1;
total--;
}
else if(!(boats[i][j] == -1))
{
//Otherwise, update the location of the boat
boats[i][j] = boats[i][j] + j;
}
}
}
}
//If the response starts with 'N',
else if(wake_r[0] == 'N')
{
//Read another string from the user
scanf("%s", wake_r);
//Loop through all the locations and speeds
for(int i = 0; i <= location_m; i++)
{
for(int j = 0; j <= speed_m; j++)
{
//If the boat at this location is greater than or equal to the
guess and the boat has not been marked as eliminated mark the boat as eliminated
if(boats[i][j] >= guess && !(boats[i][j] == -1))
{
boats[i][j] = -1;
total--;
}
else if (!(boats[i][j] == -1))
{
//Otherwise, update the location of the boat
boats[i][j] = boats[i][j] + j;
}
}
}
}
//If the response starts with 'B',
else if(wake_r[0] == 'B')
{
//Loop through all possible boat locations
for(int i = 0; i <= location_m; i++)
{
for(int j = 0; j <= speed_m; j++)
{
//If the boat is at this location is not equal to the guess and the
boat has not been marked as eliminated update the position of the boat
if(boats[i][j] != guess && !(boats[i][j] == -1))
{
boats[i][j] = -1;
total--;
}
else if (!(boats[i][j] == -1))
{
boats[i][j] = boats[i][j] + j;
}
}
}
}
count_picture++;
// Increase the picture number to keep track of the number of pictures
taken/hours passed.
}
return 0;
}

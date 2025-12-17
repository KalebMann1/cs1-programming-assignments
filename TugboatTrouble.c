#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct tugBoat tugboat;
//Tugboat struct that contains all info pertaining to the tugboat including
coordinates , name, relocated corrdinates, etc.
struct tugBoat
{
long long int x, y;
long long int r_x, r_y;
char name[20];
long long int dotprod;
long long int distance;
};
// Function to initialize tugboat properties
void initial_tug(tugboat *tug, int x, int y, int xs, int ys)
{
// Read in tugboat's coordinates and name
scanf("%lld %lld %s", &tug->x, &tug->y, tug->name);
// Calculate relocated coordinates of tugboat with respect to a reference point
tug->r_x = tug->x - xs;
tug->r_y = tug->y - ys;
// Calculate dot product of tugboat's relocated coordinates with orginal
coordinates
tug->dotprod = (tug->r_x * x) + (tug->r_y * y);
// Reset point coordinates
xs = 0;
ys = 0;
// Calculate distance from relocated point using Pythagorean theorem
tug->distance = (long)pow((tug->r_x - xs), 2) + (long)pow((tug->r_y - ys), 2);
}
void tug_boat_swap(tugboat *arr, int i, int j)
{
// Create a temporary tugboat and copy the properties of tugboat i to it
tugboat *temp = (tugboat *)malloc(sizeof(tugboat));
temp->x = arr[i].x;
temp->y = arr[i].y;
temp->r_x = arr[i].r_x;
temp->r_y = arr[i].r_y;
strcpy(temp->name, arr[i].name);
temp->dotprod = arr[i].dotprod;
temp->distance = arr[i].distance;
// Copy the properties of tugboat j to tugboat i
arr[i].x = arr[j].x;
arr[i].y = arr[j].y;
arr[i].r_x = arr[j].r_x;
arr[i].r_y = arr[j].r_y;
strcpy(arr[i].name, arr[j].name);
arr[i].dotprod = arr[j].dotprod;
arr[i].distance = arr[j].distance;
// Copy the properties of the temporary tugboat to tugboat j thus swapping
tugboats
arr[j].x = temp->x;
arr[j].y = temp->y;
arr[j].r_x = temp->r_x;
arr[j].r_y = temp->r_y;
strcpy(arr[j].name, temp->name);
arr[j].dotprod = temp->dotprod;
arr[j].distance = temp->distance;
}
// This function merges two sorted arrays of tugboats based on their dot product,
//distance, and name (in descending order of priority) into a single sorted array.
tugboat *merge(tugboat *first, int firstSize, tugboat *second, int secondSize)
{
int total = firstSize + secondSize;
// Allocate memory for the merged array.
tugboat *result = (tugboat *)calloc(total, sizeof(tugboat));
int firstPtr = 0;
int secondPtr = 0;
// Loop over both arrays and compare the tugboats.
for (int i = 0; i < total; i++)
{
if (firstPtr == firstSize)
{
// If we have already inserted all the tugboats from the first array,
// insert the remaining tugboats from the second array.
result[i] = second[secondPtr];
secondPtr++;
}
else if (secondPtr == secondSize)
{
// If we have already inserted all the tugboats from the second array,
// insert the remaining tugboats from the first array.
result[i] = first[firstPtr];
firstPtr++;
}
else if (first[firstPtr].dotprod < second[secondPtr].dotprod)
{
// If the dot product of the current tugboat in the first array is less than
// that of the current tugboat in the second array, insert the current
tugboat
// from the first array into the merged array.
result[i] = first[firstPtr];
firstPtr++;
}
else if (first[firstPtr].dotprod == second[secondPtr].dotprod)
{
if (first[firstPtr].distance < second[secondPtr].distance)
{
// If the dot products of the current tugboats in both arrays are equal,
but
// the distance of the current tugboat in the first array is less than that
// of the current tugboat in the second array, insert the current tugboat
// from the first array into the merged array.
result[i] = first[firstPtr];
firstPtr++;
}
else if (first[firstPtr].distance == second[secondPtr].distance)
{
if (strcmp(first[firstPtr].name, second[secondPtr].name) < 0)
{
// If the dot products and distances of the current tugboats in both
// arrays are equal, but the name of the current tugboat in the first
array
// comes before the name of the current tugboat in the second array
// alphabetically, insert the current tugboat from the first array into
// the merged array.
result[i] = first[firstPtr];
}
else
{
// Otherwise, insert the current tugboat from the second array into the
merged array.
result[i] = second[secondPtr];
}
}
else
{
// If the dot products of the current tugboats in both arrays are equal,
// but the distance of the current tugboat in the first array is greater
// than that of the current tugboat in the second array, insert the current
// tugboat from the second array into the merged array.
result[i] = second[secondPtr];
secondPtr++;
}
}
else
{
result[i] = second[secondPtr];
secondPtr++;
}
}
return result;
}
void mergeSort(tugboat *arr, int size)
{
if (size <= 1)
return;
// Getting the sizes of the two halves
int sizeLeft = size / 2;
int sizeRight = size - sizeLeft;
// Get the pointers into the two halves
tugboat *leftArr = arr;
tugboat *rightArr = &arr[sizeLeft];
// Sort the left side
mergeSort(leftArr, sizeLeft);
// Sort the right side
mergeSort(rightArr, sizeRight);
tugboat *result = (tugboat *)malloc(sizeof(tugboat) * size);
result = merge(leftArr, sizeLeft, rightArr, sizeRight);
// Copy result into arr
for (int i = 0; i < size; i++)
arr[i] = result[i];
// Clean up the memory from result
free(result);
}
void print_array(tugboat *arr, int size)
{
printf("%d\n", size); // Print the number of elements in the array
for (int i = 0; i < size; i++)
{
printf("%s\n", arr[i].name); // Print the name of each tugboat in the array
}
printf("\n"); // Print a new line at the end of the output
}
int main(void)
{
int xs, ys, xh, yh;
scanf("%d %d %d %d", &xs, &ys, &xh, &yh); // Read in the starting and ending
coordinates
int n;
scanf("%d", &n); // Read in the number of tugboats
tugboat arr[n]; // Create an array of tugboats
tugboat resolved[n]; // Create a new array to hold the stored tugboats
for (int i = 0; i < n; i++)
{
initial_tug(&arr[i], (xh - xs), (yh - ys), xs, ys); // Initialize each tugboat
in the array
}
mergeSort(arr, n); // Sort the array of tugboats based on dot product and
distance
tugboat prev; // Declare a variable to hold the previous tugboat
int j = 0; // Initialize a counter variable to keep track of the number of
resolved tugboats
// Calculate the dot product of the given vector
long long int vector_x = xh - xs;
long long int vector_y = yh - ys;
long long int vector_dot = (long)pow(vector_x, 2) + (long)pow(vector_y, 2);
for (int i = 0; i < n; i++)
{
if (arr[i].dotprod <= 0) // If the dot product is less than or equal to zero,
skip the tugboat
{
prev = arr[i];
continue;
}
if (arr[i].dotprod > vector_dot) // If the dot product is greater than the dot
product of the given vector, skip the tugboat
{
prev = arr[i];
continue;
}
if (arr[i].dotprod == prev.dotprod && i != 0) // If the dot product is the
same as the previous tugboat, skip the tugboat
{
prev = arr[i];
continue;
}
resolved[j] = arr[i]; // Add the tugboat to the array that is storing the
tugboats
j++;
prev = arr[i];
}
print_array(resolved, j);
return 0;
}

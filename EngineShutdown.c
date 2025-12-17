#include <stdio.h>
#include <stdlib.h>
#define MAX_N 11 // maximum number of actions
int n; // number of actions
int temp[MAX_N][MAX_N]; // 2D array to store the temperature change caused by doing
an action after another
int temp_drop_max = INT_MIN; // maximum temperature drop that can be achieved
int best_rank[MAX_N]; // array to store the rank of actions that results in the
maximum temperature drop
int current_rank[MAX_N]; // array to store the current order of actions being
explored
int action_visited[MAX_N]; // array to keep track of the actions that have been
visited
int actions[MAX_N]; // array to store the temperature change caused by each action
void find_best_rank(int action_count, int temp_drop)
{
if (action_count == n) // if all actions have been explored
{
if (temp_drop > temp_drop_max)
{
temp_drop_max = temp_drop; // if the new temperature drop is greater
than the maximum temperature drop so farupdate the maximum temperature drop
for (int i = 0; i < n; i++)
{
best_rank[i] = current_rank[i]; // update the best order of actions
}
}
return;
}
for (int i = 0; i < n; i++)
{
if (action_visited[i]) // if the action has already been explored
{
continue;
}
action_visited[i] = 1; // mark the action as visited
current_rank[action_count] = i; // add the action to the current order of
actions being explored
int new_temp_drop = temp_drop + actions[i]; // calculate the new
temperature drop caused by the current action
for (int j = 0; j < action_count; j++) // for each action that has been
explored so far
{
new_temp_drop += temp[current_rank[j]][i]; // add the temperature
change caused by doing the current action after the explored action
}
find_best_rank(action_count + 1, new_temp_drop); // explore the next action
action_visited[i] = 0; // mark the action as unvisited
}
}
int main()
{
scanf("%d", &n); // read the number of actions from the user
for (int i = 0; i < n; i++)
{
scanf("%d", &actions[i]); // for each action read the temperature change
caused by the action
}
for (int i = 0; i < n; i++)
{
for (int j = 0; j < n; j++)
{
scanf("%d", &temp[i][j]); // for each pair of actions read the
temperature change caused by doing one action after the other
}
}
find_best_rank(0, 0); // explore all possible orders of actions
for (int i = 0; i < n; i++) // prints the best order of actions
{
printf("%d", best_rank[i] + 1); // add 1 to the action index to convert it
to 1-based indexing (the input is 0-based)
}
printf("\n");
return 0;
}

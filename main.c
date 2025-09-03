// INCLUDES //
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_LEN 100

struct Human {
  char name[40];
  bool alive;
};

// The use of this is for later
typedef struct {
  char name[MAX_LEN];
  bool toggled;
} Task;

void ClearScreen() { printf("\033[2J\033[1;1H"); }

// THE MAIN FUNCTION //
int main() {
  char input[200];
  char tasks[MAX_TASKS][MAX_LEN];
  int taskCount = 0;

  while (true) {
    printf("> ");
    fgets(input, sizeof(input), stdin);

    // remove newline from fgets
    input[strcspn(input, "\n")] = 0;

    if (strcmp(input, "clear") == 0) {
      ClearScreen();
    } else if (strcmp(input, "exit") == 0) { // the exit command
      printf("Exiting...\n");
      break;
    } else if (strncmp(input, "add ", 4) == 0) { // the add command
      if (taskCount < MAX_TASKS) {
        strncpy(tasks[taskCount], input + 4, MAX_LEN - 1);
        tasks[taskCount][MAX_LEN - 1] = '\0'; // FIXED
        taskCount++;
        printf("Task added: %s\n", input + 4);
      } else {
        printf("Task list is full!\n");
      }
    } else if (strcmp(input, "list") &&
               strcmp(input, "ls") == 0) { // the list command
      if (taskCount == 0) {
        printf("No tasks yet\n");
      } else {
        printf("\nTasks:\n");
        for (int i = 0; i < taskCount; i++) {
          printf("%d. %s", i + 1, tasks[i]); // FIXED
          printf("\n");
        }
      }
    } else if (strncmp(input, "remove", 4) == 0) {
      int index = atoi(input + 7);
      if (index < 1 || index > taskCount) {
        printf("Invalid task number\n");
      } else {
        for (int i = index - 1; i < taskCount; i++) {
          strcpy(tasks[i], tasks[i + 1]);
        }
        taskCount--;
        printf("Task %d removed\n", index);
      }
    } else if (strncmp(input, "echo ", 5) == 0) { // the echo command
      printf("%s\n", input + 5);
    } else if (strncmp(input, "edit ", 5) == 0) { // the edit command
      char new_task_name[200];
      char *index_str = input + 5;
      int index = atoi(index_str);

      if (index < 1 || index > taskCount) {
        printf("Invalid Task Number");
      } else {
        printf("Enter a new Task name: ");
        fgets(new_task_name, sizeof(new_task_name), stdin);
        new_task_name[strcspn(new_task_name, "\n") == 0];

        strncpy(tasks[index - 1], new_task_name, MAX_LEN - 1);
        tasks[index - 1][MAX_LEN - 1] = '\n';

        printf("The Task %d updated to: %s", index, new_task_name);
      }
    } else {
      printf("Unknown command: %s\n", input);
    }
  }

  return 0;
}

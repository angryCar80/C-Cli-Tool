// INCLUDES //
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_LEN 100

typedef struct {
  char name[MAX_LEN];
  bool toggled;
} Task;

void ClearScreen() { printf("\033[2J\033[1;1H"); }

// THE MAIN FUNCTION //
int main() {
  char input[100];
  char tasks[MAX_TASKS][MAX_LEN];
  int taskCount = 0;

  while (true) {
    printf("> ");
    fgets(input, sizeof(input), stdin);

    // remove newline from fgets
    input[strcspn(input, "\n")] = 0;

    if (strcmp(input, "clear") == 0) {
      ClearScreen();
    } else if (strcmp(input, "exit") == 0) {
      printf("Exiting...\n");
      break;
    } else if (strncmp(input, "add ", 4) == 0) {
      if (taskCount < MAX_TASKS) {
        strncpy(tasks[taskCount], input + 4, MAX_LEN - 1);
        tasks[taskCount][MAX_LEN - 1] = '\0'; // FIXED
        taskCount++;
        printf("Task added: %s\n", input + 4);
      } else {
        printf("Task list is full!\n");
      }
    } else if (strcmp(input, "list") && strcmp(input, "ls") == 0) {
      printf("\nTasks:\n");
      for (int i = 0; i < taskCount; i++) {
        printf("%d. %s", i + 1, tasks[i]); // FIXED
        printf("\n");
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
    } else {
      printf("Unknown command: %s\n", input);
    }
  }

  return 0;
}


// INCLUDES //
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_LEN 100

void ClearScreen() { printf("\033[2J\033[1;1H"); }

typedef struct {
  char name[MAX_LEN];
  bool toggled;
} Task;

// THE MAIN FUNCTION //
int main() {
  char input[200];
  Task tasks[MAX_TASKS];
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

    } else if (strncmp(input, "add ", 4) == 0) {
      if (taskCount < MAX_TASKS) {
        strncpy(tasks[taskCount].name, input + 4, MAX_LEN - 1);
        tasks[taskCount].name[MAX_LEN - 1] = '\0';
        tasks[taskCount].toggled = false;
        taskCount++;
        printf("Task added: %s\n", input + 4);
      } else {
        printf("Task list is full!\n");
      }

    } else if (strcmp(input, "list") == 0 || strcmp(input, "ls") == 0) {
      if (taskCount == 0) {
        printf("No tasks yet\n");
      } else {
        printf("\nTasks:\n");
        for (int i = 0; i < taskCount; i++) {
          printf("%d. %s %s\n", i + 1, tasks[i].name,
                 tasks[i].toggled ? "[X]" : "[ ]");
        }
      }

    } else if (strncmp(input, "remove ", 7) == 0) {
      int index = atoi(input + 7);
      if (index < 1 || index > taskCount) {
        printf("Invalid task number\n");
      } else {
        for (int i = index - 1; i < taskCount - 1; i++) {
          strcpy(tasks[i].name, tasks[i + 1].name);
          tasks[i].toggled = tasks[i + 1].toggled;
        }
        taskCount--;
        printf("Task %d removed\n", index);
      }

    } else if (strncmp(input, "echo ", 5) == 0) {
      printf("%s\n", input + 5);

    } else if (strncmp(input, "edit ", 5) == 0) {
      char new_task_name[200];
      char *index_str = input + 5;
      int index = atoi(index_str);

      if (index < 1 || index > taskCount) {
        printf("Invalid task number\n");
      } else {
        printf("Enter a new task name: ");
        fgets(new_task_name, sizeof(new_task_name), stdin);
        new_task_name[strcspn(new_task_name, "\n")] = 0; // strip newline

        strncpy(tasks[index - 1].name, new_task_name, MAX_LEN - 1);
        tasks[index - 1].name[MAX_LEN - 1] = '\0';

        printf("Task %d updated to: %s\n", index, new_task_name);
      }

    } else if (strncmp(input, "toggle ", 7) == 0) {
      int index = atoi(input + 7);
      if (index < 1 || index > taskCount) {
        printf("Invalide Index");
      } else {
        tasks[index - 1].toggled = !tasks[index - 1].toggled;
        printf("Task %d marked as %s\n", index,
               tasks[index - 1].toggled ? "done" : "not done");
      }
    } else {
      printf("Unknown command: %s\n", input);
    }
  }
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dataloader.h"


int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage\n");
    fprintf(stderr, "%s set-password\n", argv[0]);
    fprintf(stderr, "%s set-timestamp <extra time in seconds>\n", argv[0]);
    return EXIT_FAILURE;
  }

  if (strcmp(argv[1], "set-password") == 0) {
    struct UserData data = { .timestamp = 0LL };
    char password[PW_ARRAY_LEN];
    printf("Enter new password: ");
    scanf(PW_SCANF, password);
    strcpy(data.password, password);
    if (!save(data)) {
      fprintf(stderr, "Failed to save user data\n");
      return EXIT_FAILURE;
    }
    printf("Password updated successfully\n");
    return EXIT_SUCCESS;
  }

  if (strcmp(argv[1], "set-timestamp") == 0) {
    if (argc < 3) {
      fprintf(stderr, "Please provide extra time in seconds\n");
      return EXIT_FAILURE;
    }
    struct UserData data;
    if (!load(&data)) {
      fprintf(stderr, "Failed to load user data\n");
      return EXIT_FAILURE;
    }
    long long extra_time = (long long) strtol(argv[2], NULL, 10);
    data.timestamp = ((long long) time(NULL)) + extra_time;
    if (!save(data)) {
      fprintf(stderr, "Failed to save user data\n");
      return EXIT_FAILURE;
    }
    printf("Timestamp updated successfully\n");
    return EXIT_SUCCESS;
  }

  fprintf(stderr, "Unknown command: %s\n", argv[1]);
  return EXIT_FAILURE;
}

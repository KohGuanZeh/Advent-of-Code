#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 2048

int ProcessGame(char **, size_t, long int *, long int *);

static int R;
static int G;
static int B;

int main(int argc, char const *argv[]) {
  if (argc != 5) {
    printf(
        "Number of supplied arguments is incorrect.\n"
        "ConundrumCube.exe <input-file-path> <R> <G> <B>\n");
    return -1;
  }
  FILE *filePtr = fopen(argv[1], "r");
  R = atoi(argv[2]);
  G = atoi(argv[3]);
  B = atoi(argv[4]);

  if (filePtr == NULL) {
    printf("Cannot locate file from path %s. Exiting...\n", filePtr);
    return 1;
  }

  long int sum = 0, pow = 0;
  char buffer[MAX_LEN + 1];
  char *strPtr = fgets(buffer, MAX_LEN, filePtr);
  while (strPtr != NULL) {
    if (ProcessGame(&strPtr, strlen(strPtr), &sum, &pow) > 0) {
      fclose(filePtr);
      printf("Something is wrong with given input. Exiting...\n");
      return 1;
    }
    strPtr = fgets(buffer, MAX_LEN, filePtr);
  }
  fclose(filePtr);
  printf("Sum of Game IDs: %ld\n", sum);
  printf("Sum of Powers: %ld\n", pow);
  return 0;
}

int ProcessGame(char **inputPtr, size_t length, long int *sum, long int *pow) {
  if (strncmp(*inputPtr, "Game ", 5) != 0) {
    return 1;
  }

  int maxR = 0, maxG = 0, maxB = 0;
  char *endPtr = *inputPtr + length;
  *inputPtr += 5;
  char *game = strtok(*inputPtr, ":");
  if (game == NULL) {
    return 1;
  }
  int gameID = atoi(game);

  *inputPtr += strlen(game) + 2;  // Skip Space
  char *set = strtok(*inputPtr, ";");
  while (set != NULL && *inputPtr < endPtr) {
    size_t setDataLength = strlen(set);
    char *numberStr = strtok(set, " ");
    char *color = strtok(NULL, ",");
    while (numberStr && color) {
      // printf("%s\n", numberStr);
      // printf("%s\n", color);
      int number = atoi(numberStr);
      if (strstr(color, "red")) {
        if (number > maxR) {
          maxR = number;
        }
      } else if (strstr(color, "green")) {
        if (number > maxG) {
          maxG = number;
        }
      } else if (strstr(color, "blue")) {
        if (number > maxB) {
          maxB = number;
        }
      }
      numberStr = strtok(NULL, " ");
      color = strtok(NULL, ",");
    }
    *inputPtr += setDataLength + 1;
    set = strtok(*inputPtr, ";");
  }

  if (maxR > R || maxG > G || maxB > B) {
    printf("Game %d NOT Met:\n", gameID);
  } else {
    printf("Game %d Met:\n", gameID);
    *sum += gameID;
  }
  printf("  Max Red: %d.\n", maxR);
  printf("  Max Green: %d.\n", maxG);
  printf("  Max Blue: %d.\n", maxB);
  *pow += (long int)maxR * maxG * maxB;
  return 0;
}
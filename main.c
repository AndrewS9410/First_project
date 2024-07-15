#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 23
#define VOID '-'
#define GRAIN '*'
#define GRAIN_Y 5
#define GRAIN_X 40

void initializeMainFrame(char ***main);
void drawFrame(char **main);
void initializeGrain(char **main);
void calculateGrainFall(char **main, int *stop);

int main() {
  char **main_frame = NULL;
  int stop = 20;

  srand(time(NULL));

  initializeMainFrame(&main_frame);
  initializeGrain(main_frame);

  while (stop) {
    drawFrame(main_frame);
    calculateGrainFall(main_frame, &stop);
    usleep(5e4);
  }

  for (int i = 0; i < HEIGHT; i++) {
    free(main_frame[i]);
  }
  free(main_frame);

  return 0;
}

void initializeMainFrame(char ***main) {
  *main = calloc(HEIGHT, sizeof(char *));
  for (int i = 0; i < HEIGHT; i++) {
    (*main)[i] = calloc(WIDTH, sizeof(char));
  }

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      (*main)[i][j] = VOID;
    }
  }
}

void initializeGrain(char **main) { main[GRAIN_Y][GRAIN_X] = GRAIN; }

void calculateGrainFall(char **main, int *stop) {
  int flag = 1;

  initializeGrain(main);

  for (int i = GRAIN_Y; i < HEIGHT - 1; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (main[i][j] == GRAIN && main[i + 1][j] == VOID) {
        main[i + 1][j] = GRAIN;
        main[i][j] = VOID;

        flag = 0;
        break;
      } else if (main[i][j] == GRAIN) {
        if (j > 0 && main[i + 1][j - 1] == VOID && rand() % 2 == 0) {
          main[i + 1][j - 1] = GRAIN;
          main[i][j] = VOID;

          flag = 0;
          break;
        } else if (j < WIDTH && main[i + 1][j + 1] == VOID && rand() % 2 == 0) {
          main[i + 1][j + 1] = GRAIN;
          main[i][j] = VOID;

          flag = 0;
          break;
        }
      }
    }
  }

  if (flag == 1) {
    *stop -= 1;
  }
}

void drawFrame(char **main) {
  system("clear");

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      printf("%c", main[i][j]);
    }
    printf("\n");
  }
}
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

enum minestatus_t { HAS_MINE, UNKNOWN };

struct _board_t {
  int ** board;
  int width;
  int height;
  int totalMines;
};
typedef struct _board_t board_t;

void printBoard(board_t * b) {
  printf("    ");
  for (int x = 0; x < b->width; x++) {
    printf("%d", x % 10);
  }
  printf("\n----");
  for (int x = 0; x < b->width; x++) {
    printf("-");
  }
  printf("\n");
  for (int y = 0; y < b->height; y++) {
    printf("%2d: ", y % 100);
    for (int x = 0; x < b->width; x++) {
      if (b->board[y][x] == HAS_MINE) {
        printf("*");
      }
      else {
        printf(" ");
      }
    }
    printf("\n");
  }
}

void addRandomMine(board_t * b) {
  int x;
  int y;
  //we could have a board too small for the number
  //of mines that we request. try w*h*10 times before
  //we give up
  int limit = b->width * b->height * 10;
  do {
    x = random() % b->width;
    y = random() % b->height;
    assert(limit > 0);
    limit--;
  } while (b->board[y][x] == HAS_MINE);
  b->board[y][x] = HAS_MINE;
  b->totalMines++;
}

board_t * makeBoard(int w, int h, int numMines) {
  board_t * ans = malloc(sizeof(*ans));
  ans->width = w;
  ans->height = h;
  ans->totalMines = numMines;
  ans->board = calloc(h, h * sizeof(int*));
  for (int i = 0; i < h; i++) {
    ans->board[i] = realloc(ans->board[i], w * sizeof(int*));
  }
  for (int j = 0; j < h; j++) {
    for (int k = 0; k < w; k++) {
    ans->board[j][k] = UNKNOWN;
    }
  }
  printBoard(ans);
  for (int i = 0; i < numMines; i++) {
    addRandomMine(ans);
  }
  return ans;
}

void freeBoard(board_t * b) {
  for (int i = 0; i < b->height; i++) {
    free(b->board[i]);
  }
  free(b->board);
  free(b);
}

int main(int argc, char ** argv) {
  if (argc != 4) {
    fprintf(stderr, "Usage: minesweeper width height numMines\n");
    return EXIT_FAILURE;
  }
  int width = atoi(argv[1]);
  int height = atoi(argv[2]);
  int numMines = atoi(argv[3]);
  if (width <= 0 || height <= 0 || numMines <= 0) {
    fprintf(stderr, "Width, height, and numMines must all be positive ints\n");
    return EXIT_FAILURE;
  }
  board_t * b = makeBoard(width, height, numMines);
  printBoard(b);
  freeBoard(b);
  return EXIT_SUCCESS;
}

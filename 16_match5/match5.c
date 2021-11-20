#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  NO,
  PAIR,
  THREE,
  FOUR,
  FIVE
} hand_ranking_t;


const char *ranking_to_string(hand_ranking_t r) {
  switch(r) {
  case FIVE:
    return "five of a kind";
    break;
  case FOUR:
    return "four of a kind";
    break;
  case THREE:
    return "three of a kind";
    break;
  case PAIR:
    return "pair";
    break;
  case NO:
    return "no match";
    break;
  default: __builtin_unreachable();
  }
}


int cnt_max(int arr[]) {
  int max = 0;
  for(int i=0; i<4; i++) {
    if(arr[i] > max) {
      max = arr[i];
    }
  }
  return max;
}

int count(char *hand, char c) {
  int count = 0;
  for(int i=0; i<strlen(hand); i++) {
    if(hand[i] == c) {
      count++;
    }
  }
  return count;
}

hand_ranking_t hand_type(char *hand) {
  int arr[4];
  for(int i=0; i<4; i++){
    arr[i] = count(hand, hand[i]);
  }
  int count = cnt_max(arr);
  switch(count) {
  case 1: return NO; break;
  case 2: return PAIR; break;
  case 3: return THREE; break;
  case 4: return FOUR; break;
  case 5: return FIVE; break;
  default: __builtin_unreachable();
  }
}
  
 

void hand_cmp(char *h1, char *h2) {
  hand_ranking_t r1;
  hand_ranking_t r2;
  r1 = hand_type(h1);
  r2 = hand_type(h2);

  const char *r_h1;
  const char *r_h2;
  r_h1 = ranking_to_string(r1);
  r_h2 = ranking_to_string(r2);

  if(r1 > r2) {
    printf("Hand 1's %s beats Hand 2's %s", r_h1, r_h2);
  }
  else if(r1 < r2) {
    printf("Hand 1's %s loses to Hand 2's %s", r_h1, r_h2);
  }
  else{
    printf("Both hands tie: each has %s", r_h1);
  }
}



int main(int argc, char **argv) {
  if(argc != 3) {
    perror("Need 2 inputs");
    return EXIT_FAILURE;
  }
  if(strlen(argv[1]) != 5 || strlen(argv[2]) != 5) {
    perror("Need 5 cards");
    return EXIT_FAILURE;
  }
  
  hand_cmp(argv[1], argv[2]);

  return EXIT_SUCCESS;
}



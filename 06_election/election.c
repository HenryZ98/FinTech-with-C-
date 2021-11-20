#include "election.h"
//include any other headers you need here...
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


state_t parseLine(const char * line) {
  //STEP 1: write me
  
  int count = 0;
  for (int a = 0; a < strlen(line); a++) {
    if (line[a] == ':') {
      count++;
    }
  }
  if(count != 2) {
    perror("Wrong type of input");
    exit(1);
  }
  
  state_t state;
  char delim[] = ":";
  char *ptr = strtok((char*)line, delim);
  char *s1 = ptr;
  ptr = strtok(NULL, delim);
  char *s2 = ptr;
  ptr = strtok(NULL, delim);
  char *s3 = ptr;

  if (strlen(s1) > MAX_STATE_NAME_LENGTH) {
    perror("Wrong state input");
    exit(0);
  }

  uint64_t pop;
  if (atoi(s2) == 0) {
    perror("Wrong population input");
    exit(1);
  }
  else {   
    pop = atoi(s2);
  }

  unsigned int elecVotes;
  if (atoi(s3) == 0) {
    perror("Wrong EVotes input");
    exit(1);
  }
  else {
    elecVotes = atoi(s3);
  }

  for(int i=0; i<MAX_STATE_NAME_LENGTH; i++) {
    state.name[i] = s1[i];
  }
  state.population = pop;
  state.electoralVotes = elecVotes;

  return state;
}

unsigned int countElectoralVotes(state_t * stateData,
                                 uint64_t * voteCounts,
                                 size_t nStates) {
  //STEP 2: write me
  
  uint64_t pop[nStates];
  for(int x=0; x<nStates; x++) {
    pop[x] = stateData[x].population;
  }
  
  unsigned int elecVotes[nStates];
  for (int y=0; y<nStates; y++) {
    elecVotes[y] = stateData[y].electoralVotes;
  }

  
  unsigned int count = 0;

  for(int i=0; i<nStates; i++) {
    if(voteCounts[i] >  (pop[i]/2)) {
      count += elecVotes[i];
    }
  }  
  return count;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  uint64_t pop[nStates];
  for(int x=0; x<nStates; x++) {
    pop[x] = stateData[x].population;
    } 
  
  for(int i=0; i<nStates; i++) {
    float c = ((float)voteCounts[i] / (float)pop[i]) * 100;
    if(c >= 49.5 && c <= 50.5) {
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n", stateData[i].name, c);
    }
  }
  
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
 
  uint64_t pop[nStates];
  for(int x=0; x<nStates; x++) {
    pop[x] = stateData[x].population;
    } 
  float max = 0;
  int idx = 0;
  for(int i=0; i<nStates; i++) {
    float c = ((float)voteCounts[i] / (float)pop[i]) * 100;
    // printf("%.2f%%\n", c);
    if(c > max) {
      max = c;
      idx = i;
    }
  }
  printf("Candidate A won %s with %.2f%% of the vote\n", stateData[idx].name, max);
}

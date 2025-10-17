#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define CANDIDATE_LIMIT 20
#define NAME_LIMIT 20
#define VOTE_LIMIT 999

typedef char word_t[NAME_LIMIT + 1];
typedef struct vote {
  int rank;
  word_t candidate;
} vote_t;
///////////////////////////////////////////////////////////////////////

int getword(char W[], int limit);

// add your other function prototypes here

///////////////////////////////////////////////////////////////////////

// main program provides traffic control

int main(int argc, char *argv[]) {
  int num_candidates, num_votes = 0, index = 0;
  vote_t votes[VOTE_LIMIT][CANDIDATE_LIMIT];
  int c;
  word_t candidates, all_candidates[CANDIDATE_LIMIT];
  scanf("%d", &num_candidates);
  for (int i = 0; i < num_candidates; i++) {
    getword(candidates, NAME_LIMIT);
    strcpy(all_candidates[i], candidates);
  }
  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      num_votes++;
      index = 0;
      continue;
    } else if (!isdigit(c)) {
      continue;
    }
    votes[num_votes][index] = c - '0';
    index++;
  }
  printf("Stage 1\n");
  printf("=======\n");
  printf("read %d candidates and %d votes\n", num_candidates, num_votes);
  printf("voter %d preferences...\n", num_votes);
  int curr_rank = 1, rank;
  for (int i = 0; i < num_candidates; i++) {
    for (int j = 0; j < num_candidates; j++) {
      if (votes[num_votes - 1][j] == curr_rank) {
        rank = j;
        curr_rank++;
        break;
      }
    }
    printf("    rank%3d: %s\n", i + 1, all_candidates[rank]);
  }

  return 0;
}

///////////////////////////////////////////////////////////////////////

// extract a single word out of the standard input, of not
// more than limit characters, argument array W must be
// limit+1 characters or bigger.
// function adapted from Figure 7.13 of Programming, Problem Solving,
// and Abstraction with C, by Alistair Moffat
//

int getword(char W[], int limit) {
  int c, len = 0;
  /* first, skip over any non alphabetics */
  while ((c = getchar()) != EOF && !isalpha(c)) {
    /* do nothing more */
  }
  if (c == EOF) {
    return EOF;
  }
  /* ok, first character of next word has been found */
  W[len++] = c;
  while (len < limit && (c = getchar()) != EOF && isalpha(c)) {
    /* another character to be stored */
    W[len++] = c;
  }
  /* now close off the string */
  W[len] = '\0';
  return 0;
}

///////////////////////////////////////////////////////////////////////

// add your other functions here

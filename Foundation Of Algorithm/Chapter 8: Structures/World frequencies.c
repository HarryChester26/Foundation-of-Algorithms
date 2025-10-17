/* Break the input up into a sequence of words, and only report
 * the unique ones.
 * Figure 7.14, PPSAA words.c - Alistair Moffat, October 2013
 * (c) University of Melbourne*/
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define MAXCHARS 10   /* Max chars per word */
#define MAXWORDS 1000 /* Max distinct words */

typedef char word_t[MAXCHARS + 1];
int getword(word_t W, int limit);
// TODO:  A struct for a single word and its frequency
typedef struct word {
  word_t c;
  int frequency;
} Word;
int main(int argc, char *argv[]) {
  word_t one_word;
  Word all_words[MAXWORDS];
  int numdistinct = 0, totwords = 0;
  while (getword(one_word, MAXCHARS) != EOF) {
    totwords = totwords + 1;
    /* linear search in array of previous words... */
    int found = 0;
    for (int i = 0; i < numdistinct && !found; i++) {
      // TODO:
      if ((strcmp(one_word, all_words[i].c) == 0)) {
        all_words[i].frequency++;
        found = 1;
        break;
      }
    }
    if (!found && numdistinct < MAXWORDS) {
      strcpy(all_words[numdistinct].c, one_word);
      all_words[numdistinct].frequency = 1;
      numdistinct += 1;
    }
    /* NB - program silently discards words after
       MAXWORDS distinct ones have been found */
  }
  printf("%d words read\n", totwords);
  for (int i = 0; i < numdistinct; i++) {
    printf("word #%2d is %-20s and appears %3d times\n", i, all_words[i].c,
           all_words[i].frequency);
  }
  return 0;
}

/* Extract a single word out of the standard input, of no more than limit
 * characters. Argument array W must be size limit+1 characters or larger.
 * Returns length of word stored into W, or EOF (-1) if there was no word.
 * (getword.c page 121, Alistair Moffat) */
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

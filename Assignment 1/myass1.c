/* Program to implement Australian House of Representatives preferential
   voting and determine election outcomes from vote preference orderings.

   Skeleton program written by Alistair Moffat, ammoffat@unimelb.edu.au,
   August 2025, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.
   All included code is (c) Copyright University of Melbourne, 2025

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been
   developed by another student, or by me in collaboration with other
   students, or by non-students as a result of request, solicitation, or
   payment, may not be submitted for assessment in this subject.  I
   understand that submitting for assessment work developed by or in
   collaboration with other students or non-students constitutes Academic
   Misconduct, and may be penalized by mark deductions, or by other
   penalties determined via the University of Melbourne Academic Honesty
   Policy, as described at https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will
   I do so until after the marks are released. I understand that providing
   my work to other students, regardless of my intention or any undertakings
   made to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring
   service, or drawing the attention of others to such services and code
   that may have been made available via such a service, may be regarded as
   Student General Misconduct (interfering with the teaching activities of
   the University and/or inciting others to commit Academic Misconduct).  I
   understand that an allegation of Student General Misconduct may arise
   regardless of whether or not I personally make use of such solutions or
   sought benefit from such actions.

   Signed by: Bui Huu Hiep (1665682)
   Dated:    Tue 9th Sep 2025

*/
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

////////////////////////////////////////////////////////////////////////

#define CANDIDATE_LIMIT 20
#define NAME_LIMIT 20
#define VOTE_LIMIT 999

////////////////////////////////////////////////////////////////////////

typedef char word_t[NAME_LIMIT + 1];
typedef struct {
  word_t name;
  // Number of 1st preference vote
  int num_vote;
  // The index of voters who vote 1st preference for this candidate
  int voter_list[VOTE_LIMIT];
  int can_index;
  bool is_eliminated;
} Candidate_t;

////////////////////////////////////////////////////////////////////////

int getword(char W[], int limit);
void print_stage(int stage);
int stage_1(int total_candidates, int votes[VOTE_LIMIT][CANDIDATE_LIMIT],
            Candidate_t all_candidates[CANDIDATE_LIMIT]);
void stage_2(int total_candidates, int votes[VOTE_LIMIT][CANDIDATE_LIMIT],
             int total_votes, Candidate_t all_candidates[CANDIDATE_LIMIT]);
void stage_3(int total_candidates, int voter[VOTE_LIMIT][CANDIDATE_LIMIT],
             int total_votes, Candidate_t all_candidates[CANDIDATE_LIMIT]);
void print_stage(int stage);
void selection_sort(Candidate_t all_candidates[CANDIDATE_LIMIT],
                    int total_candidates);
double calc_percentage(int votes, int total_votes);
int find_candidate(Candidate_t all_candidates[CANDIDATE_LIMIT],
                   int total_candidates, int idx);
void reset_election(Candidate_t all_candidates[CANDIDATE_LIMIT],
                    int total_candidates);
void collecting_votes(int total_votes, int voter[VOTE_LIMIT][CANDIDATE_LIMIT],
                      Candidate_t all_candidates[CANDIDATE_LIMIT]);

////////////////////////////////////////////////////////////////////////

// Main program

int main(int argc, char *argv[]) {
  int total_candidates, voter[VOTE_LIMIT][CANDIDATE_LIMIT];
  Candidate_t all_candidates[CANDIDATE_LIMIT];

  scanf("%d", &total_candidates);

  int total_votes = stage_1(total_candidates, voter, all_candidates);
  stage_2(total_candidates, voter, total_votes, all_candidates);
  stage_3(total_candidates, voter, total_votes, all_candidates);

  printf("tadaa!\n");
  return 0;
}

////////////////////////////////////////////////////////////////////////

// Extract a single word as a name of a candidate out of the standard input
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

////////////////////////////////////////////////////////////////////////

// Print_stage template
void print_stage(int stage) {
  printf("\n");
  printf("Stage %d\n", stage);
  printf("=======\n");
}

////////////////////////////////////////////////////////////////////////

// Sorting candidates in descending order and solving tie by alphabetical order
void selection_sort(Candidate_t all_candidates[CANDIDATE_LIMIT],
                    int total_candidates) {
  int max_index;
  for (int i = 0; i < total_candidates - 1; i++) {
    max_index = i;
    for (int j = i + 1; j < total_candidates; j++) {
      if (all_candidates[j].num_vote > all_candidates[max_index].num_vote) {
        max_index = j;
      } else if (all_candidates[j].num_vote ==
                 all_candidates[max_index].num_vote) {
        // Solve tie by alphabetical order
        if (strcmp(all_candidates[j].name, all_candidates[max_index].name) <
            0) {
          max_index = j;
        }
      }
    }
    // Swapping
    Candidate_t temp = all_candidates[i];
    all_candidates[i] = all_candidates[max_index];
    all_candidates[max_index] = temp;
  }
}

////////////////////////////////////////////////////////////////////////

// Calculate percentage of votes in total votes
double calc_percentage(int votes, int total_votes) {
  return (double)votes / (double)total_votes * 100.0;
}

////////////////////////////////////////////////////////////////////////

// Find the index of a candidate in all_candidates array by their original index
int find_candidate(Candidate_t all_candidates[CANDIDATE_LIMIT],
                   int num_candidates, int idx) {
  for (int i = 0; i < num_candidates; i++) {
    if (all_candidates[i].can_index == idx) {
      return i;
    }
  }
  return -1;
}

////////////////////////////////////////////////////////////////////////

// Reset the election to initial state
void reset_election(Candidate_t all_candidates[CANDIDATE_LIMIT],
                    int num_candidates) {
  for (int i = 0; i < num_candidates; i++) {
    all_candidates[i].num_vote = 0;
    all_candidates[i].is_eliminated = false;
  }
}

////////////////////////////////////////////////////////////////////////

// Collect the number of 1st votes for each candidate and save the their voters'
// index
void collecting_votes(int total_votes, int voter[VOTE_LIMIT][CANDIDATE_LIMIT],
                      Candidate_t all_candidates[CANDIDATE_LIMIT]) {

  /* As the preferences of a voter are stored in ascending order */
  for (int i = 0; i < total_votes; i++) {

    // Count the number of 1st votes for each candidate
    int vote_for = all_candidates[voter[i][0]].num_vote;

    // Saving the voter's index who voted for this candidate
    all_candidates[voter[i][0]].voter_list[vote_for] = i;

    all_candidates[voter[i][0]].num_vote++;
  }
}

////////////////////////////////////////////////////////////////////////
/* Stage 1 of the process */
int stage_1(int num_candidates, int voter[VOTE_LIMIT][CANDIDATE_LIMIT],
            Candidate_t all_candidates[CANDIDATE_LIMIT]) {

  word_t candidate;
  bool detect_number = false;
  int value = 0, num_votes = 0, candidate_index = 0, c;
  for (int i = 0; i < num_candidates; i++) {
    // Set base value of each candidate
    getword(candidate, NAME_LIMIT);
    strcpy(all_candidates[i].name, candidate);
    all_candidates[i].num_vote = 0;
    all_candidates[i].is_eliminated = false;
    all_candidates[i].can_index = i;
  }

  // Save the preferences of each voter
  while ((c = getchar()) != EOF) {
    if (!isdigit(c)) {
      /* A number has been detected from input and user finished inputting that
         number */
      if (detect_number) {
        /* Set the preference of the voter from most the least preferred
           corresponding with candidate index */
        voter[num_votes][value - 1] = candidate_index;
        candidate_index++;
        value = 0;
        detect_number = false;
      }
      // Move to the next voter as a newline is encountered
      if (c == '\n' && candidate_index > 0) {
        num_votes++;
        candidate_index = 0;
      }
    } else {
      /* Save our num input into a temporary value to deal with number > 10
        and set number detected to true */
      value = value * 10 + (c - '0');
      detect_number = true;
    }
  }

  print_stage(1);

  printf("read %d candidates and %d votes\n", num_candidates, num_votes);
  printf("voter %d preferences...\n", num_votes);

  // Get the preferences of the last voter in order from most to least preferred
  for (int i = 0; i < num_candidates; i++) {
    printf("    rank%3d: %s\n", i + 1,
           all_candidates[voter[num_votes - 1][i]].name);
  }

  return num_votes;
}

/* Stage 2 of the process, in this stage we will take advantages of the index
   order in all_candidates array corresponding with the candidate's index*/
void stage_2(int total_candidates, int voter[VOTE_LIMIT][CANDIDATE_LIMIT],
             int total_votes, Candidate_t all_candidates[CANDIDATE_LIMIT]) {

  print_stage(2);

  collecting_votes(total_votes, voter, all_candidates);

  bool winner_found = false;
  int winner_index, eliminated_index, curr_round = 1;

  /* Elimination process until we find a winner */
  while (!winner_found) {
    printf("round %d...\n", curr_round);

    int lowest_vote = total_votes;

    for (int i = 0; i < total_candidates; i++) {
      // Check if any candidate has a strict majority
      if (all_candidates[i].num_vote > total_votes / 2) {
        winner_found = true;
        winner_index = i;
      }

      /* If candidate is not eliminated, continue comparing their votes */
      if (all_candidates[i].is_eliminated == false) {

        /* Find the eliminated candidate with the lowest votes and save their
           index */
        if (all_candidates[i].num_vote < lowest_vote) {
          lowest_vote = all_candidates[i].num_vote;
          eliminated_index = i;
        }
        double percentage =
            calc_percentage(all_candidates[i].num_vote, total_votes);
        printf("    %-19s :%4d votes,%6.1f%%\n", all_candidates[i].name,
               all_candidates[i].num_vote, percentage);
      }
    }

    printf("    ----\n");

    // Winner found, end the election
    if (winner_found) {
      printf("    %s is declared elected\n\n",
             all_candidates[winner_index].name);
      break;
    }

    /* Remove eliminated candidate from the election */

    all_candidates[eliminated_index].is_eliminated = true;

    printf("    %s is eliminated and votes distributed\n\n",
           all_candidates[eliminated_index].name);
    // Redistribute the votes of the eleminated candidate
    if (all_candidates[eliminated_index].num_vote != 0) {
      int total_redistribution = all_candidates[eliminated_index].num_vote;

      for (int i = 0; i < total_redistribution; i++) {
        /* Get the index of the voter who voted for the elimanted candidate
           and move their vote to the next uneliminated candidate*/
        int voter_index = all_candidates[eliminated_index].voter_list[i];
        for (int j = 1; j < total_candidates; j++) {
          // Voter's preference is in ascending order so...
          int candidate_index = voter[voter_index][j];

          // If the next candidate is not eliminated, give them the vote
          if (all_candidates[candidate_index].is_eliminated == false) {

            // Save the new voter's position to the next candidate
            all_candidates[candidate_index]
                .voter_list[all_candidates[candidate_index].num_vote] =
                voter_index;

            all_candidates[candidate_index].num_vote++;
            break;
          }
        }
      }
    }

    // Next round
    curr_round++;
  }
}

/* Stage 3 of the process , in this stage candidates' index are correspond with
   index in all_candidates so we will have to search for the correct candidate
   index in winner and elimination process*/
void stage_3(int total_candidates, int voter[VOTE_LIMIT][CANDIDATE_LIMIT],
             int total_votes, Candidate_t all_candidates[CANDIDATE_LIMIT]) {
  print_stage(3);
  // Reset the election as stage 2 changed the state of all_candidates
  reset_election(all_candidates, total_candidates);

  collecting_votes(total_votes, voter, all_candidates);

  bool winner_found = false;
  int winner_index, eliminated_index, curr_round = 1;

  /* Elimination process until we find a winner */
  while (!winner_found) {

    selection_sort(all_candidates, total_candidates);

    printf("round %d...\n", curr_round);

    int lowest_vote = total_votes;

    for (int i = 0; i < total_candidates; i++) {
      // Check if any candidate has a strict majority
      if (all_candidates[i].num_vote > total_votes / 2) {
        winner_found = true;
        winner_index = all_candidates[i].can_index;
      }

      /* If candidate is not eliminated, continue comparing their votes */
      if (all_candidates[i].is_eliminated == false) {

        /* Find the eliminated candidate with the lowest votes and save their
           index */
        if (all_candidates[i].num_vote < lowest_vote) {
          lowest_vote = all_candidates[i].num_vote;
          eliminated_index = all_candidates[i].can_index;
        }
        double percentage =
            calc_percentage(all_candidates[i].num_vote, total_votes);
        printf("    %-19s :%4d votes,%6.1f%%\n", all_candidates[i].name,
               all_candidates[i].num_vote, percentage);
      }
    }

    printf("    ----\n");

    // Winner found, end the election
    if (winner_found) {
      // Find the position of the winner candidate in current all_candidates
      int res = find_candidate(all_candidates, total_candidates, winner_index);
      printf("    %s is declared elected\n\n", all_candidates[res].name);
      break;
    }

    /* Remove eliminated candidate from the election */

    // Find the position of eliminated candidate in current all_candidates
    int res =
        find_candidate(all_candidates, total_candidates, eliminated_index);

    all_candidates[res].is_eliminated = true;

    printf("    %s is eliminated and votes distributed\n\n",
           all_candidates[res].name);
    // Redistribute the votes of the eleminated candidate
    if (all_candidates[res].num_vote != 0) {
      int total_redistribution = all_candidates[res].num_vote;

      for (int i = 0; i < total_redistribution; i++) {
        /* Get the index of the voter who voted for the elimanted candidate
           and move their vote to the next uneliminated candidate*/
        int voter_index = all_candidates[res].voter_list[i];
        for (int j = 1; j < total_candidates; j++) {
          // Voter's preference is in ascending order so...
          int candidate_index = voter[voter_index][j];

          // Find the position of the worthy candidate in current all_candidates
          int temp =
              find_candidate(all_candidates, total_candidates, candidate_index);

          // If the next candidate is not eliminated, give them the vote
          if (all_candidates[temp].is_eliminated == false) {

            // Save the new voter's position to the next candidate
            all_candidates[temp].voter_list[all_candidates[temp].num_vote] =
                voter_index;

            all_candidates[temp].num_vote++;
            break;
          }
        }
      }
    }

    // Next round
    curr_round++;
  }
}

// Algorithms are FUN FUN FUN !!!

#include <stdbool.h>
#include <stdio.h>

#define MAX_NAME_LENGTH 50
#define MAX_MARRIAGE_COUNT 10
#define MAX_DIVORCE_COUNT 10
#define MAX_WORKING_YEARS 100
#define AUS 30000000
#define NZ 6000000

typedef struct {
  char titles[MAX_NAME_LENGTH];
  char given_name[MAX_NAME_LENGTH];
  char middle_name[MAX_NAME_LENGTH];
  char family_name[MAX_NAME_LENGTH];
} name_t;

typedef struct {
  int day;
  int month;
  int year;
} date_t;

typedef struct {
  date_t marriage_date;
  char spouse_name[MAX_NAME_LENGTH];
} marriage_t;

typedef struct {
  int year;
  double net_income;
  double tax_liability;
  bool tax_paid;
  date_t paid_date;
} working_year_t;

typedef struct {
  name_t name;
  date_t DOB;
  marriage_t marriages[MAX_MARRIAGE_COUNT];
  date_t divorces[MAX_DIVORCE_COUNT];
  bool is_alive;
  working_year_t working[MAX_WORKING_YEARS];
} person_t;

double average_death(person_t *country, int size) {
  int death_count = 0;
  for (int i = 0; i < size; i++) {
    if ((country + i)->is_alive == false) {
      death_count++;
    }
  }
  return death_count * 100 / (double)size;
}

double total_taxation_revenue(person_t *country, int size, int year) {
  double total_revenue = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < MAX_WORKING_YEARS; j++) {
      if ((country + i)->working[j].year == year) {
        total_revenue += (country + i)->working[j].tax_liability;
      }
    }
  }

  return total_revenue;
}

int main(int argc, char *argv[]) {
  person_t australia[AUS];
  person_t new_zealand[NZ];
  return 0;
}

#include <assert.h>
#include <complex.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* #DEFINE'S -----------------------------------------------------------------*/
#define SDELIM "==STAGE %d============================\n" // stage delimiter
#define THEEND "==THE END============================\n"  // end message
#define DIVIDER "-------------------------------------\n"
#define INITIAL                                                                \
  "Initial matrix: %dx%d, nnz=%d\n"             // initial matrix output format
#define TARGET "Target matrix: %dx%d, nnz=%d\n" // target matrix output format
#define CURRENT                                                                \
  "Current matrix: %dx%d, nnz=%d\n" // current matrix output format
#define PRTELE "(%d,%d)=%d\n"       // matrix elements output format
#define SET_VALUE ":%d,%d,%d\n"     // manipulation set input and output format
#define SWAP_VALUE ":%d,%d,%d,%d\n" // manipulation swap input and output format
#define MUL_ADD ":%d\n" // manipulation multiply and add input and output format
#define STAGE2F ":%d,%d\n" // manipulations in stage 2 input and output format
#define MTXDIM "%dx%d\n"   // matrix dimensions input format
#define MTXELE "%d,%d,%d"  // matrix elements input format
#define INSTRUCTION "INSTRUCTION %c" // instruction output format
#define MTXLMT 35                    // matrix limitation
#define NOT_FOUND -1                 // index of zero value elements
#define MEM_BASED 1                  // memory base for matrix capacity

/* TYPE DEFINITIONS ----------------------------------------------------------*/

// Compressed Sparse Row (CSR) matrix representation
typedef struct {
  int rows;  // number of rows in this matrix
  int cols;  // number of columns in this matrix
  int nnz;   // number of stored non-zeros values in this matrix
  int cap;   // matrix capacity to hold non-zero values
  int *vals; // non-zero values in this matrix
  int *cidx; // column indices of non-zero values, in row-major order
  int *rptr; // row pointers
} CSRMatrix_t;

/* FUNCTION PROTOTYPES -------------------------------------------------------*/

void read_user_input(CSRMatrix_t *, CSRMatrix_t *);
void handle_stage_0(CSRMatrix_t *, CSRMatrix_t *, int *);
void handle_stage_1_and_2(CSRMatrix_t *, CSRMatrix_t *, int *);

int cell_exist(CSRMatrix_t *, int, int);
void set_value(CSRMatrix_t *, int, int, int);
void swap_value(CSRMatrix_t *, int, int, int, int);
void multiply_value(CSRMatrix_t *, int);
void add_value(CSRMatrix_t *, int);
void copy_row(CSRMatrix_t *, int, int);
void copy_col(CSRMatrix_t *, int, int);
void swap_row(CSRMatrix_t *, int, int);
void swap_col(CSRMatrix_t *, int, int);

void reallocate_memory(CSRMatrix_t *, size_t);
void insert_element(CSRMatrix_t *, int, int, int);
void delete_element(CSRMatrix_t *, int, int);
void insert_row(CSRMatrix_t *, int, int, int *, int *);
void insert_col(CSRMatrix_t *, int, int, int *, int *);
bool target_matrix_reached(CSRMatrix_t *, CSRMatrix_t *);

/* INTERFACE FUNCTIONS FOR WORKING WITH CSR MATRICES -------------------------*/
CSRMatrix_t *csr_matrix_create(int, int); // create empty CSR matrix
void csr_matrix_free(CSRMatrix_t *);      // free input CSR matrix
void print_matrix(CSRMatrix_t *, const char *);

/* WHERE IT ALL HAPPENS------------------------------------------------------*/
int main(void) {
  int rows, cols;
  assert(scanf(MTXDIM, &rows, &cols) == 2);       // assert matrix dimensions
  CSRMatrix_t *A = csr_matrix_create(rows, cols); // create initial matrix of 0s
  CSRMatrix_t *B = csr_matrix_create(rows, cols); // create target matrix of 0s

  read_user_input(A, B);

  printf(THEEND);      // print "THE END" message
  csr_matrix_free(A);  // free initial matrix
  csr_matrix_free(B);  // free target matrix
  return EXIT_SUCCESS; // algorithms are fun!!!
}

/* STAGE IMPLEMENTATION------------------------------------------------------*/

// Read input user and print out the process
void read_user_input(CSRMatrix_t *A, CSRMatrix_t *B) {
  int r, c, v, count_sym = 0, stage = 0;
  char sym;
  // read user input until we receive two "#" symbols
  while (count_sym != 2) {
    // if user input as a format of three integers "r,c,v"
    if (scanf(MTXELE, &r, &c, &v) == 3) {
      count_sym == 0 ? insert_element(A, r, c, v) : insert_element(B, r, c, v);
    } else {
      // if user input as a symbol "#"
      if (scanf("%c", &sym) == 1 && sym == '#') {
        count_sym++;
      }
    }
  }

  // stage implementation
  handle_stage_0(A, B, &stage);
  handle_stage_1_and_2(A, B, &stage);
}

void handle_stage_0(CSRMatrix_t *A, CSRMatrix_t *B, int *stage) {
  printf(SDELIM, (*stage)++); // stage 0 header
  print_matrix(A, INITIAL);
  printf(DIVIDER);
  print_matrix(B, TARGET);
}

void handle_stage_1_and_2(CSRMatrix_t *A, CSRMatrix_t *B, int *stage) {
  bool stage_changed = false;
  int total_mnlps = 0;
  // Initial and target matrix are the same, then stop the process
  if (target_matrix_reached(A, B) == true) {
    printf(DIVIDER);
    printf("TA-DAA!!! SOLVED IN %d STEP(S)!\n", total_mnlps);
    return;
  }

  printf(SDELIM, (*stage)++); // stage 1 header

  // Collecting manipulations applied to the matrix
  char mnlp;
  while (scanf(" %c", &mnlp) != EOF) {
    // detect manipulations in stage 2
    if (stage_changed == false &&
        (mnlp == 'r' || mnlp == 'R' || mnlp == 'c' || mnlp == 'C')) {
      printf(SDELIM, (*stage)++); // stage 2 header
      stage_changed = true;       // stage 2 changed confirmed
    }

    // unrecognized manipulation, stop the process
    if (mnlp != 's' && mnlp != 'S' && mnlp != 'a' && mnlp != 'm' &&
        mnlp != 'r' && mnlp != 'R' && mnlp != 'c' && mnlp != 'C') {
      return;
    }

    // manipulation instruction output format
    printf(INSTRUCTION, mnlp);

    if (mnlp == 's') {
      int r, c, v;
      assert(scanf(SET_VALUE, &r, &c, &v) == 3);
      printf(SET_VALUE, r, c, v);
      set_value(A, r, c, v);
    } else if (mnlp == 'S') {
      int r1, c1, r2, c2;
      assert(scanf(SWAP_VALUE, &r1, &c1, &r2, &c2) == 4);
      printf(SWAP_VALUE, r1, c1, r2, c2);
      swap_value(A, r1, c1, r2, c2);
    } else if (mnlp == 'a' || mnlp == 'm') {
      int v;
      assert(scanf(MUL_ADD, &v) == 1);
      printf(MUL_ADD, v);
      if (mnlp == 'a') {
        add_value(A, v);
      } else {
        multiply_value(A, v);
      }
    } else if (mnlp == 'r' || mnlp == 'R') {
      int r1, r2;
      assert(scanf(STAGE2F, &r1, &r2) == 2);
      printf(STAGE2F, r1, r2);
      if (mnlp == 'r')
        copy_row(A, r1, r2);
      else
        swap_row(A, r1, r2);
    } else if (mnlp == 'c' || mnlp == 'C') {
      int c1, c2;
      assert(scanf(STAGE2F, &c1, &c2) == 2);
      printf(STAGE2F, c1, c2);
      if (mnlp == 'c')
        copy_col(A, c1, c2);
      else
        swap_col(A, c1, c2);
    }

    // Matrix output format for each manipulation
    print_matrix(A, CURRENT);
    print_matrix(B, TARGET);

    total_mnlps++;

    // reached the target matrix, then stop the process
    if (target_matrix_reached(A, B) == true) {
      printf(DIVIDER);
      printf("TA-DAA!!! SOLVED IN %d STEP(S)!\n", total_mnlps);
      break;
    }
  }
  // No manipulation applied, print stage 2 header and stop process
  if (total_mnlps == 0) {
    printf(SDELIM, (*stage)++);
  }
}

/* MATRIX MANIPULATION
 * FUNCTIONS------------------------------------------------*/

// check if the element at row r and col c is zero or not
int cell_exist(CSRMatrix_t *M, int r, int c) {
  if (r >= M->rows || c >= M->cols)
    return NOT_FOUND;

  for (int i = M->rptr[r]; i < M->rptr[r + 1]; i++) {
    // Finding the position of this non-zero value
    if (M->cidx[i] == c) {
      return i;
    }
  }
  // This element's value is zero
  return NOT_FOUND;
}

void set_value(CSRMatrix_t *M, int r, int c, int v) {

  // invalid row or column
  assert(r < M->rows && c < M->cols);

  // check if the element at row r and col c is zero or not
  int set_index = cell_exist(M, r, c);

  if (set_index != NOT_FOUND) {
    // set a non-zero cell to zero
    if (v == 0) {
      delete_element(M, r, c);
    } else {
      // set new value
      M->vals[set_index] = v;
    }
  } else if (set_index == NOT_FOUND && v != 0) {
    // set a zero element to non-zero element
    insert_element(M, r, c, v);
  }
}

void swap_value(CSRMatrix_t *M, int r1, int c1, int r2, int c2) {

  // invalid row or column
  assert(r1 < M->rows && r2 < M->rows && c1 < M->cols && c2 < M->cols);
  // identical elements, no operation needed
  if (r1 == r2 && c1 == c2) {
    return;
  }

  // check if the swaping elements are initially zero or not
  int index1 = cell_exist(M, r1, c1);
  int index2 = cell_exist(M, r2, c2);

  // Both elements are not zero
  if (index1 != NOT_FOUND && index2 != NOT_FOUND) {
    int temp = M->vals[index1];
    M->vals[index1] = M->vals[index2];
    M->vals[index2] = temp;
  } else if (index2 == NOT_FOUND && index1 != NOT_FOUND) {
    // the element at row r2 and col c2 is zero
    insert_element(M, r2, c2, M->vals[index1]);
    delete_element(M, r1, c1);
  } else if (index1 == NOT_FOUND && index2 != NOT_FOUND) {
    // the element at row r1 and c1 is zero
    insert_element(M, r1, c1, M->vals[index2]);
    delete_element(M, r2, c2);
  }
}

void multiply_value(CSRMatrix_t *M, int v) {
  // scalar is not zero
  if (v != 0) {
    for (int i = 0; i < M->nnz; i++) {
      M->vals[i] *= v;
    }
  } else {
    // scalar is zero
    for (int i = 0; i <= M->rows; i++) {
      M->rptr[i] = 0;
    }
    M->cap = M->nnz = 0;
  }
}

void add_value(CSRMatrix_t *M, int v) {
  for (int i = 0; i < M->nnz; i++) {
    M->vals[i] += v;
    // cell becomes zero after addition
    if (M->vals[i] == 0) {
      int r;
      // find the row of this cell
      for (r = 0; r < M->rows; r++) {
        if (i >= M->rptr[r] && i < M->rptr[r + 1]) {
          break;
        }
      }
      delete_element(M, r, M->cidx[i]);
      i--; // adjust index after deletion
    }
  }
}

void copy_row(CSRMatrix_t *M, int r1, int r2) {

  // invalid row
  assert(r1 < M->rows && r2 < M->rows);
  // identical rows, no operation needed
  if (r1 == r2) {
    return;
  }

  int start1 = M->rptr[r1], end1 = M->rptr[r1 + 1];
  int buf_capacity = end1 - start1; // number of non-zero elements in row r1
  // initialize buffers to copy information of nnz elements in row r1
  int *cols_buf = (int *)malloc(buf_capacity * sizeof(int));
  int *vals_buf = (int *)malloc(buf_capacity * sizeof(int));
  assert(cols_buf != NULL || vals_buf != NULL);

  // start copy all col idx and nnz vals of row r1 into buffers
  for (int i = start1, idx = 0; i < end1; i++, idx++) {
    cols_buf[idx] = M->cidx[i];
    vals_buf[idx] = M->vals[i];
  }

  // copying all cells in row r1 to row r2
  insert_row(M, r2, buf_capacity, cols_buf, vals_buf);

  // free buffers
  free(cols_buf);
  free(vals_buf);
}

void copy_col(CSRMatrix_t *M, int c1, int c2) {

  // invalid column
  assert(c1 < M->cols && c2 < M->cols);
  // identical columns, no operation needed
  if (c1 == c2) {
    return;
  }

  // initialize buffers to copy information of nnz elements in col c1
  int *rows_buf = (int *)malloc(M->nnz * sizeof(int));
  int *vals_buf = (int *)malloc(M->nnz * sizeof(int));
  assert(rows_buf != NULL || vals_buf != NULL);

  int buf_capacity = 0; // number of non-zero elements in col c1

  // start copying all row idx and nnz vals of col c1 into buffers
  for (int i = 0; i <= M->rows; i++) {
    for (int j = M->rptr[i]; j < M->rptr[i + 1]; j++) {
      if (M->cidx[j] == c1) {
        rows_buf[buf_capacity] = i;
        vals_buf[buf_capacity] = M->vals[j];
        buf_capacity++;
      }
    }
  }

  // copy all cells in col c1 to col c2
  insert_col(M, c2, buf_capacity, rows_buf, vals_buf);

  // free buffers
  free(rows_buf);
  free(vals_buf);
}

void swap_row(CSRMatrix_t *M, int r1, int r2) {

  // invalid row
  assert(r1 < M->rows && r2 < M->rows);
  // identical rows, no operation needed
  if (r1 == r2) {
    return;
  }

  int start2 = M->rptr[r2], end2 = M->rptr[r2 + 1];
  int buf_capacity = end2 - start2;
  // initialize buffers to copy information of nnz elements in row r2
  int *cols_buf = malloc(buf_capacity * sizeof(int));
  int *vals_buf = malloc(buf_capacity * sizeof(int));
  assert(cols_buf != NULL || vals_buf != NULL);

  // start copying all col idx and nnz vals of row r2 into buffers
  for (int i = start2, idx = 0; i < end2; i++, idx++) {
    cols_buf[idx] = M->cidx[i];
    vals_buf[idx] = M->vals[i];
  }

  // copy all cells in row r1 to row r2
  copy_row(M, r1, r2);

  // copy all cells in buffers (row r2) to row r1
  insert_row(M, r1, buf_capacity, cols_buf, vals_buf);

  // free buffers
  free(cols_buf);
  free(vals_buf);
}

void swap_col(CSRMatrix_t *M, int c1, int c2) {

  // invalid column
  assert(c1 < M->cols && c2 < M->cols);
  // identical columns, no operation needed
  if (c1 == c2) {
    return;
  }

  // initialize buffers to copy information of nnz elements in col c2
  int *rows_buf2 = (int *)malloc(M->nnz * sizeof(int));
  int *vals_buf2 = (int *)malloc(M->nnz * sizeof(int));
  assert(rows_buf2 != NULL || vals_buf2 != NULL);

  int buf_capacity = 0;

  // start copying all row idx and nnz vals of col c2 into buffers
  for (int i = 0; i <= M->rows; i++) {
    for (int j = M->rptr[i]; j < M->rptr[i + 1]; j++) {
      if (M->cidx[j] == c2) {
        rows_buf2[buf_capacity] = i;
        vals_buf2[buf_capacity] = M->vals[j];
        buf_capacity++;
      }
    }
  }

  // copy all cells in col c1 to col c2
  copy_col(M, c1, c2);

  // copy all initial cells in buffers (col c2) to col c1
  insert_col(M, c1, buf_capacity, rows_buf2, vals_buf2);

  // free buffers
  free(rows_buf2);
  free(vals_buf2);
}

/* ADDITIONAL FUNCTIONS USED TO SUPPORT MANIPULATING
 * PROCESSES------------------------------------*/

// memory reallocation function
void reallocate_memory(CSRMatrix_t *M, size_t new_cap) {
  // reallocate memory for vals and cidx arrays
  int *new_vals = realloc(M->vals, new_cap * sizeof(int));
  int *new_cidx = realloc(M->cidx, new_cap * sizeof(int));
  // check if memory was reallocated
  assert(new_vals != NULL || new_cidx != NULL);

  // save new pointers and capacity
  M->vals = new_vals;
  M->cidx = new_cidx;
  M->cap = new_cap;
}

// Inserting non-zero cells to the matrix in row-major order
void insert_element(CSRMatrix_t *M, int r, int c, int v) {

  // invalid row or column
  if (r >= M->rows || c >= M->cols) {
    return;
  }

  // setting cell to zero
  if (v == 0) {
    delete_element(M, r, c);
    return;
  }

  // Memory reallocation if the matrix reaches its maximum capacity
  if (M->nnz == M->cap) {
    size_t new_cap = (M->cap == 0) ? MEM_BASED : M->cap * 2;
    reallocate_memory(M, new_cap);
  }

  // set the insert index to the end of that row
  int insert_index = M->rptr[r + 1];
  int start = M->rptr[r], end = M->rptr[r + 1];

  for (int i = start; i < end; i++) {
    // searching where is the suitable position to add value (row-major order)
    if (c < M->cidx[i]) {
      insert_index = i;
      break;
      // cell already exists, update its value
    } else if (c == M->cidx[i]) {
      M->vals[i] = v;
      return;
    }
  }

  // Begin shifting index of other elements in the array
  for (int i = M->nnz; i > insert_index; i--) {
    M->cidx[i] = M->cidx[i - 1];
    M->vals[i] = M->vals[i - 1];
  }

  // Finish adding new element
  M->vals[insert_index] = v;
  M->cidx[insert_index] = c;

  // Increment number of non-zero cells in the matrix and value of row pointers
  M->nnz++;
  for (int i = r + 1; i <= M->rows; i++) {
    M->rptr[i]++;
  }
}

// Deleting element in the matrix as it've been changed to zero value
void delete_element(CSRMatrix_t *M, int r, int c) {

  // invalid row or column
  if (r >= M->rows || c >= M->cols) {
    return;
  }

  int delete_index = NOT_FOUND; // set the deleted index to NOT FOUND
  for (int i = M->rptr[r]; i < M->rptr[r + 1]; i++) {
    // Searching for the position of that elements
    if (M->cidx[i] == c) {
      delete_index = i;
      break;
    }
  }

  if (delete_index == NOT_FOUND)
    return;

  // Begin shifting to delete that element
  for (int i = delete_index; i < M->nnz - 1; i++) {
    M->cidx[i] = M->cidx[i + 1];
    M->vals[i] = M->vals[i + 1];
  }

  // Decrement number of non-zero cells in the matrix and value of row pointers
  M->nnz--;
  for (int i = r + 1; i <= M->rows; i++) {
    M->rptr[i]--;
  }
}

// Insert all elements in the buffers to row r
void insert_row(CSRMatrix_t *M, int r, int buf_length, int *cols_buf,
                int *vals_buf) {
  int nnz_of_row =
      M->rptr[r + 1] - M->rptr[r]; // number of non-zero elements in row r
  int shift = buf_length - nnz_of_row;

  if (shift > 0) {
    // Need to expand - shift elements to the right
    if (M->nnz + shift > M->cap) {
      size_t new_cap = (M->cap == 0) ? MEM_BASED : M->cap;
      while (M->nnz + shift > new_cap) {
        new_cap *= 2;
      }
      reallocate_memory(M, new_cap);
    }

    // Shift elements from the end of the matrix backwards
    for (int i = M->nnz - 1; i >= M->rptr[r + 1]; i--) {
      M->cidx[i + shift] = M->cidx[i];
      M->vals[i + shift] = M->vals[i];
    }

    // Update row pointers for all rows after r
    for (int i = r + 1; i <= M->rows; i++) {
      M->rptr[i] += shift;
    }

    // Insert new elements
    for (int i = 0; i < buf_length; i++) {
      M->cidx[M->rptr[r] + i] = cols_buf[i];
      M->vals[M->rptr[r] + i] = vals_buf[i];
    }

    M->nnz += shift;
  } else if (shift < 0) {
    // Need to contract - shift elements to the left
    shift = -shift; // make shift positive

    // Shift elements from the end of the matrix backwards
    for (int i = M->rptr[r + 1]; i < M->nnz; i++) {
      M->cidx[i - shift] = M->cidx[i];
      M->vals[i - shift] = M->vals[i];
    }

    // Update row pointers for all rows after r
    for (int i = r + 1; i <= M->rows; i++) {
      M->rptr[i] -= shift;
    }

    // Insert new elements
    for (int i = 0; i < buf_length; i++) {
      M->cidx[M->rptr[r] + i] = cols_buf[i];
      M->vals[M->rptr[r] + i] = vals_buf[i];
    }

    M->nnz -= shift;
  } else {
    // No size change - just replace elements
    for (int i = 0; i < buf_length; i++) {
      M->cidx[M->rptr[r] + i] = cols_buf[i];
      M->vals[M->rptr[r] + i] = vals_buf[i];
    }
  }
}

// Insert all cells in the buffers to col c
void insert_col(CSRMatrix_t *M, int c, int buf_length, int *rows_buf,
                int *vals_buf) {
  // delete all elements in col c
  for (int i = 0; i < M->rows; i++) {
    for (int j = M->rptr[i]; j < M->rptr[i + 1]; j++) {
      if (M->cidx[j] == c) {
        delete_element(M, i, c);
      }
    }
  }

  // insert all new elements from buffers to col c
  for (int i = 0; i < buf_length; i++) {
    insert_element(M, rows_buf[i], c, vals_buf[i]);
  }
}

// Check if we reach the target matrix or not
bool target_matrix_reached(CSRMatrix_t *A, CSRMatrix_t *B) {
  // different non-zero cells
  if (A->nnz != B->nnz) {
    return false;
  } else {
    // different values in cidx or vals array
    for (int i = 0; i < A->nnz; i++) {
      if (A->vals[i] != B->vals[i] || A->cidx[i] != B->cidx[i]) {
        return false;
      }
    }
  }
  // two matrices are identical
  return true;
}

void print_matrix(CSRMatrix_t *M, const char *msg) {

  // print out matrix's dimensions and its number of non-zero values
  printf(msg, M->rows, M->cols, M->nnz);

  // Check if we have any non-zero elements exceed the range (0-9)
  bool detect_outliers = false;
  for (int i = 0; i < M->nnz; i++) {
    if (M->vals[i] < 0 || M->vals[i] > 9) {
      detect_outliers = true;
      break;
    }
  }

  // Check if the dimensions of the matrix reach the limit or not
  if ((M->rows <= MTXLMT && M->cols <= MTXLMT) && detect_outliers == false) {
    // Begin printing stage
    for (int i = 0; i < M->rows; i++) {
      // Begin of row i
      printf("[");
      int start = M->rptr[i], end = M->rptr[i + 1];
      for (int j = 0; j < M->cols; j++) {
        if (M->cidx[start] == j && start < end) {
          printf("%d", M->vals[start++]);
        } else {
          printf(" ");
        }
      }
      // End of row i
      printf("]\n");
    }
  } else {
    // Matrix output in "(r,c)=v" format
    for (int i = 0; i < M->rows; i++) {
      for (int j = M->rptr[i]; j < M->rptr[i + 1]; j++) {
        printf(PRTELE, i, M->cidx[j], M->vals[j]);
      }
    }
  }
}

/* FUNCTIONS TO CREATE EMPTY MATRICES AND MANIPULATION
 * FUNCTIONS--------------------------------*/

// Create an empty CSR  matrix of nrows rows and ncols columns
CSRMatrix_t *csr_matrix_create(int nrows, int ncols) {
  assert(nrows >= 0 && ncols >= 0); // check matrix dimensions
  // allocate memory for this matrix
  CSRMatrix_t *A = (CSRMatrix_t *)malloc(sizeof(CSRMatrix_t));
  assert(A != NULL); // check if memory was allocated
  A->rows = nrows;   // set number of rows in the matrix
  A->cols = ncols;   // set number of columns in the matrix
  A->nnz = 0;        // initialize with no non-zero values
  A->cap = 0;        // initialize capacity to no non-zero values
  A->vals = NULL;    // no values to store...
  A->cidx = NULL;    // so there is no need to store column indices
  // allocate array to store row pointers
  A->rptr = (int *)malloc((size_t)(A->rows + 1) * sizeof(int));
  assert(A->rptr != NULL);
  for (int i = 0; i <= A->rows; i++) { // no values, so initialize ...
    A->rptr[i] = 0;                    // ... all row pointers to zeros
  }
  return A;
}

// Free input CSR matrix A
void csr_matrix_free(CSRMatrix_t *A) {
  assert(A != NULL);
  free(A->vals); // free matrix values
  free(A->cidx); // free column indices
  free(A->rptr); // free row pointers
  free(A);       // free matrix
}

/* THE END -------------------------------------------------------------------*/

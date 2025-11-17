
///////////////////////////////////////////////////////////////////

// comp10002 Practice Exam, 2025
// Sample Solution
// Prepared by Alistair Moffat, ammoffat@unimelb.edu.au
// (c) The University of Melbourne, 2025

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////
// Section 3 -- Programming
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// Question 10 -- Book/Library declarations
///////////////////////////////////////////////////////////////////

#if 0
A program is being written to manipulate data about books in
libraries.  Each book has a unique integer book number assigned
to it, an author, a title, a publisher, a year of publication, a
count of the total number of times it has been borrowed, and an
array storing the integer library card numbers of the (up to) ten
people who borrowed it most recently. The book title, author, and
publisher strings may contain up to forty characters.

The library itself might contain as many as 100,000 books.

Give suitable #define, typedef, and then variable declarations
(using fixed-length arrays) to represent the books being held by
the library.
#endif

#define MAXBOOKS 100000

#define MAXSTRLEN 40
#define MAXBORROWS 10

typedef char string_t[MAXSTRLEN + 1];

typedef struct {
  int booknum;
  string_t author, title, publisher;
  int pub_year;
  int tot_borrows;
  int num_borrowers;
  int borrowers[MAXBORROWS];
} book_t;

book_t all_books[MAXBOOKS]; // array of book information
int nbooks = 0;             // buddy variable for declared array

///////////////////////////////////////////////////////////////////
// Question 11 -- Packing a repetitive array
///////////////////////////////////////////////////////////////////

#if 0
Suppose that an integer array is being used to store sequences of
values that are strictly positive, for example:

    {1,1,1,2,2,2,2,2,5,4,4,1,1,1,1,1,1,3,3,3,0}

The last value in the array is always zero, and provides a
sentinel, meaning that a buddy variable is not required.

A student notices that there are often repeated values straight
after each other, and suggests that the data could be
restructured into a packed form, with negative numbers introduced
to indicate repetitions of the previous (positive) value.  For
example, the same data would be represented in this packed form
as:

    {1,-2,2,-4,5,4,-1,1,-5,3,-2,0}

In this packed representation each negative value -n means that
the immediately preceding value from the array should be
duplicated another n times.  For example, the first three values
of the original array, {1,1,1}, are represented by the first two
values of the packed array, {1,-2}.

Write a function

    void pack(int A[])

that carries out that transformation, replacing the sequence of
positive values in A[] by the corresponding packed form.

Because the packing process can never make the total number of
elements larger, A[] is guaranteed to already be large enough to
contain the packed sequence. That means that you do not need to
and should not declare any further arrays within your function.
Don't forget to place a sentinel value at the end of the packed
array.
#endif

void pack(int A[]) {
  int newn = 0;
  int oldn = 0;
  int reps = 0;
  // process until sentinel reached
  while (A[oldn] != 0) {
    // copy the first element of next run
    A[newn] = A[oldn];
    reps = 0;
    // and then count how many repeats
    while (A[oldn] == A[newn]) {
      // this loop always iterates at least once
      reps++;
      oldn++;
    }
    if (reps > 1) {
      // there was more than a single instance
      newn++;
      A[newn] = -(reps - 1);
    }
    newn++;
  }
  // assign new sentinel
  A[newn] = 0;
  return;
}

///////////////////////////////////////////////////////////////////
// Background declarations so that this will all compile,
//     you don't need to provide these in your answers
///////////////////////////////////////////////////////////////////

typedef double data_t;

int cmp_data(data_t *t1, data_t *t2) {
  if (*t1 < *t2)
    return -1;
  if (*t1 > *t2)
    return +1;
  return 0;
}

int get_int(data_t *d) { return 1; }

///////////////////////////////////////////////////////////////////
// The provided declarations, you don't have to type these either
///////////////////////////////////////////////////////////////////

typedef struct tree tree_t;

struct tree {
  data_t data;  // the data stored at this node
  tree_t *left; // left subtree of node
  tree_t *rght; // right subtree of node
};

///////////////////////////////////////////////////////////////////
// Prototypes for the required functions, you don't have to type
// these either!
///////////////////////////////////////////////////////////////////

int sum_tree(tree_t *t);
tree_t *bst_insert(tree_t *t, data_t *d);
tree_t *bst_merge(tree_t *t1, tree_t *t2);
int bst_check(tree_t *t);

///////////////////////////////////////////////////////////////////
// Question 12 -- Apply summing function across nodes in tree
///////////////////////////////////////////////////////////////////

#if 0
In the context of the declarations that have been provided, write
a function

    int sum_tree(tree_t *t);

that applies another function

    int get_int(data_t *d)

to each data item stored in the tree, and returns the sum of
those integer values, added up over all of the data_t elements
stored in the tree.  If t is empty then sum_tree(t) should return
zero.  You do not need to write get_int(), and may call it
without knowing anything about its operation.

Include comments prior to each main block of code to indicate
your intentions.
#endif

int sum_tree(tree_t *t) {
  int sum;
  if (t == NULL) {
    // empty tree
    return 0;
  }
  // get value for this data item
  sum = get_int(&(t->data));
  // then add on the left subtree's sum
  sum += sum_tree(t->left);
  // then add on the right subtree's sum
  sum += sum_tree(t->rght);
  // and then we are done
  return sum;
}

///////////////////////////////////////////////////////////////////
// Question 13 -- Insert a new node into a bst
///////////////////////////////////////////////////////////////////

#if 0
In the context of the declarations that have been provided, write
a function

    tree_t *bst_insert(tree_t *t, data_t *d);

that creates a new tree node that to contain a copy of the data
value indicated by *d, and inserts the nade into the correct 
place in t, returning the address of the root of the
extended tree.

For example, a typical calling sequence for this function might
be:

    tree_t *t=NULL;
    data_t d;
    while (get_value(&d)) {
        // now insert d into t
        t = bst_insert(t, &d);
    }
    // t now contains a copy of each of the data items read

Include comments prior to each main block of code to indicate
your intentions.

Before starting to answer this question, you should read the next
question too.  You may find it convenient to develop a single
helper function that can assist with both bst_insert() and the
bst_merge() function required by the next question.
#endif

// first, a helper function

tree_t *bst_insert_node(tree_t *t, tree_t *node) {
  if (t == NULL) {
    return node;
  }
  if (cmp_data(&(node->data), &(t->data)) < 0) {
    // recurse left if new data < subtree root
    t->left = bst_insert_node(t->left, node);
  } else {
    // recurse rght if new data >= subtree root
    t->rght = bst_insert_node(t->rght, node);
  }
  return t;
}

// and now the function that was asked for

tree_t *bst_insert(tree_t *t, data_t *d) {
  tree_t *node;
  // create a new node and put values into fields
  node = (tree_t *)malloc(sizeof(tree_t));
  assert(node);
  // copy over the data item
  node->data = *d;
  // this node will be a leaf, and won't have children
  node->left = node->rght = NULL;
  // and now get it inserted
  return bst_insert_node(t, node);
}

///////////////////////////////////////////////////////////////////
// Question 14 -- Merge two BSTs
///////////////////////////////////////////////////////////////////

#if 0
In the context of the declarations that have been provided, write
a function

    tree_t *bst_merge(tree_t *t1, tree_t *t2);

that constructs and returns a single tree containing the union
(the merge) of the elements in t1 and t2, by combining them and
at the same time destroying the original trees.

For example, a typical calling sequence for this function might
be:

    tree_t *t1=NULL, *t2=NULL;
    ...        // construct tree t1
    ...        // construct tree t2
    t1 = bst_merge(t1, t2);
    t2 = NULL; // this tree not required now

Include a comment prior to each main block of code to indicate
your intentions.
#endif

tree_t *bst_merge(tree_t *t1, tree_t *t2) {
  tree_t *left, *rght;
  if (t2 == NULL) {
    // easy base case
    return t1;
  }
  // cut t2 into three parts: root, left, right
  left = t2->left;
  rght = t2->rght;
  t2->left = t2->rght = NULL;
  // and insert each of the three parts into t1
  t1 = bst_insert_node(t1, t2);
  t1 = bst_merge(t1, left);
  t1 = bst_merge(t1, rght);
  return t1;
}

///////////////////////////////////////////////////////////////////
// Bonus qnswer to an invisible question, and just for fun:
// test if a binary tree has its nodes ordered and hence can be
// be regarded as being a binary search tree, this takes quite
// a bit of thinking
///////////////////////////////////////////////////////////////////

// First function here is the recursive helper

int recursive_bst_check(tree_t *t, data_t *min, data_t *max) {
  // base case
  if (t == NULL) {
    return 1;
  }
  // check that left subtree is BST, and that all values in it
  // are less than data value at this node
  if (!recursive_bst_check(t->left, min, &(t->data))) {
    return 0;
  }
  // ditto for right subtree
  if (!recursive_bst_check(t->rght, &(t->data), max)) {
    return 0;
  }
  // and now check this node is >= than min, if supplied
  if (min != NULL && cmp_data(min, &(t->data)) > 0) {
    return 0;
  }
  // finally, check this node is less than max, if supplied
  if (max != NULL && cmp_data(&(t->data), max) > 0) {
    return 0;
  }
  // nothing else to test
  return 1;
}

// And this is the actual function that answers the (possible
// future) question, it simply sets up its recursive friend with
// two extra initial arguments

int bst_check(tree_t *t) { return recursive_bst_check(t, NULL, NULL); }

///////////////////////////////////////////////////////////////////
// Section 4 -- Algorithms
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// Question 15 -- Student A
///////////////////////////////////////////////////////////////////

#if 0
Student A says, "this problem is easy to solve, and a solution
can always be achieved in O(n + kn) worst-case time, with O(1)
extra space required".
#endif

#if 0
Student A is planning to: (a) find the smallest element, in O(n)
time, and note its value, v, and also how many times it occurs,
f.  They are then going to (b) find the smallest value that is >
v, again in O(n) time, and add that second smallest value's
frequency to f and update v; and (c) keep on doing that until (d)
the sum of the frequencies as is being counted by f becomes >= k,
at which time they will have the k'th smallest.  At each
iteration of this process all elements <= the current value of v
will have been accounted for, and it can be known that there are
f such smaller values.

In total (at most) k+1 passes through the array A[] are needed,
each of which adds (at least) one to f.  Each pass takes O(n)
time, and hence the total is at most O(n + kn) time.  And just a
fixed number of new variables are required (v and f and some loop
control variables), so extra space is O(1).  This approach
matches all of the clues provided in the question.
#endif

///////////////////////////////////////////////////////////////////
// Question 16 -- Student B
///////////////////////////////////////////////////////////////////

#if 0
Student B says, "this problem is easy to solve, and a solution
can always be achieved in O(n + k log n) worst-case time,
provided I can use O(n) extra space."
#endif

#if 0
Student B knows about heaps, and is planning to: (a) copy the
array A[] to a new array B[]; then (b) build a min-heap in array
B[] (that is, a heap with the smallest element at the root and no
child allowed to be less than its parent) in O(n) time.  Once
that is done they will: (c) remove the smallest element from the
root of the heap and rebuild the heap, in O(logn) time; then (d)
do that another k-1 times, removing the next smallest element
from the root of the heap and rebuilding the heap, always in
O(logn) time.  That sequence will result in: (e) the (k+1)'th
element into the root position of the heap in array B[] is the
one that would be in A[k] if A[] was to be sorted.

In total, O(n) time and O(n) space is required to copy the array
and build the heap, and then there are k heap rebuilding steps
required, each taking O(logn) time, for a total of O(n + klogn)
time, matching the clues provided in the question.
#endif

///////////////////////////////////////////////////////////////////
// Question 17 -- Student C
///////////////////////////////////////////////////////////////////

#if 0
Student C says, "this problem is easy to solve, and a solution
can always be achieved in O(k + (n - k) log k) time in the worst
case, with O(k) extra space required".
#endif

#if 0
Student C also plans to use a heap, but theirs is of size k+1,
which is less than n.  They copy the first k+1 elements from A[]
to a new array B[], and build a max-heap in B[].  That takes O(k)
time.  Then every other element A[i] (that is, a further n-k-1
elements) is processed.  To process an element, it is compared
against the biggest item in B[], which (because B[] is a
max-heap) is in B[0].  If A[i] is bigger than B[0], no action
required, and B[] still contains the k+1 smallest values in
A[0..i].  Or, if A[i] < B[0], we do B[0] = A[i], and then rebuild
the heap in B[], taking O(log k) time when it happens.  This
works because B[0] is the biggest one of the k+!, and it get
replaced by something smaller.  So by the end of this process the
k+1 smallest items from A[] are in B[], and the biggest of those
k+1 items is in B[0], waiting to be "plucked" out as the value
that would go into A[k] if A[] swere to besorted.  Magic!

Analysis: O(k) space for B[], plus some counting variables.  And
time in worst case is O(k) + (n-k+1)*O(log k) = O(k + (n-k)log k),
as required.

Student C is going to get an H1 :-)
#endif

///////////////////////////////////////////////////////////////////
// Question 18 -- Which is faster?
///////////////////////////////////////////////////////////////////

#if 0
Students B and C then start arguing about whose algorithm will
execute the fastest, and you need to stop them fighting. What
should you tell them? And why?
#endif

#if 0
One way of answering this is to ask: "Under which conditions does
one method have asymptotic superiority over the other?"

To do this, note that Student B's method can only start being
non-linear (in n) when k = n/logn or larger, and when k = n/logn
the second term in Student C's approach will have already become

    n * (1 - 1/logn) * (log n - loglog n) = O(n log n).

which is never smaller than k log n for all values n/(log n) <= k
<= n/2.

So, Student B has the approach that for some combinations of k
and n is asymptotically faster.

[But note, when k is small relative to n, say, k=sqrt(n) or
k=log(n) the two methods have the same O(n) asymptotic cost, and
Student C's approach takes a LOT less space, so if the question
hadn't mentioned "faster", you would have also been expected to
compare them in terms of space.]

The other way of answering this is to say: Stop arguing (and get
a life) and start coding, let's do some experiments and measure
the time for different combinations of n and k. Because
asymptotic analysis is a great start on knowing how long some
algorithm will take, but in the end there is the constant factor
to take into account, and it might make the practical difference
in this case.

If you gave that second answer you'd also get the mark.

Tough marks, yes.  But these marks are to separate people who get
90 from people who get 95.  That might mean that the people who
get (even as high as 80 or 85) might not be able to generate the
"flash of insight" during the exam that is necessary to be able
to answer them.

Indeed, many students will be better off overall if they take the
time that is nominally allocated to these final questions, and
spending it instead carefully checking their earlier answer.

And if you have read this far, then keep going, there is another
"free gift" coming up...
#endif

///////////////////////////////////////////////////////////////////
// Bonus algorithm!
// Student D says, "you guys are such LOSERS, I can do O(n) expected
// time using O(1) space!
///////////////////////////////////////////////////////////////////

#if 0
Student D understands the way that quicksort works, and (in a
flash of algorithmic inspiration) realizes that a cunning
recursive approach can be used, sketched by this pseudocode:

    int find_kth(A, n, k) {
        if (n==1) {
            // base case, and k must be zero
        return A[0];
        }
        // recursive case, partition the array
        pivot = A[rand()%n]
        (fe, fg) = partition(A, n, pivot)
        // and now look at fe and fg relative to k and do
        //    at most *one* recursive call
        if (k<fe) {
        // k'th smallest is somewhere in the < zone
            return find_kth(A, fe, k)
        } else if (fe<=k && k<fg) {
        // k'th smallest is in the == zone
            return pivot
        } else {
        // k'th smallest is somewhere in the > zone
            return find_kth(A+fg, n-fg, k-fg)
        }
        // tadaa!
    }

In that second possible recursive call, the first two parts of
the partition (< pivot and = pivot) are bypassed, and so the
index of the element being looked for is similarly adjusted by
the same amount.

Analysis: if we get lucky and the pivot is always exactly the
midpoint at ecery recursion, then each recursive call would be on
exactly half of the previous array, giving

    T(1) = 1
    T(n) = n + T(n/2).

(because partition takes O(n) time) which has the solution T(n) =
2n-1 = O(n).

In the worst case, if we are unlucky, it becomes a bit like the
method of Student B of course, and the cost might be as large as
O(n(n-k)) which is O(n^2) when k<n/2.

On *average*, if the pivot is at a random location in the sorted
array, then the running time is O(n), just as the average running
time of quicksort is O(nlogn).

All of which matches the clues about execution time.

But what about space, you say?  In the question it says O(1)
extra space, whereas a recursive function takes O(logn)!  Yes,
but there is only a single recursive call made in any execution
of that function, and it comes at the end, so it can be flattened
into a simple loop and handled without needing a stack:

    int find_kth(A, n, k) {
        while (n>1) {
            pivot = A[rand()%n]
            (fe, fg) = partition(A, n, pivot)
            if (k<fe) {
            // k'th smallest is somewhere in the < zone
                n = fe;
            } else if (fe<=k && k<fg) {
            // k'th smallest is in the == zone
                return pivot
            } else {
            // k'th smallest is somewhere in the > zone
            A += fg;
            n -= fg;
            k -= fg;
            }
        }
        return A[0];
        // tadaa!
    }

That's a lot of algorithmic technology all being assembled in the
same place. But gee, it's a lot of FUN too!
#endif

///////////////////////////////////////////////////////////////////
// Scaffolding, for my own testing purposes, you don't need to write
// this in the exam and you don't need to submit it either
///////////////////////////////////////////////////////////////////

void print_array(int A[]);

int main(int argc, char *argv[]) {

  int A[100] = {1, 1, 1, 2, 2, 2, 2, 2, 5, 4, 4, 1, 1, 1, 1, 1, 1, 3, 3, 3, 0};
  print_array(A);
  pack(A);
  print_array(A);
  return 0;
}

void print_array(int A[]) {
  int i;
  for (i = 0; A[i] != 0; i++) {
    printf(" %2d", A[i]);
  }
  printf(" %2d\n", A[i]);
  return;
}

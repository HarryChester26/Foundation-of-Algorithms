int read_sequence(char *S, int limit) {
  int n = 0;
  int next;
  while ((next = getchar()) != EOF) {
    if (n == limit) {
      fprintf(stderr, "Too much data, limit is %d\n", limit);
      exit(EXIT_FAILURE);
    }
    S[n++] = next;
  }
  S[n] = '\0';
  return n;
}

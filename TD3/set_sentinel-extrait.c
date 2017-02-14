
#define SET_SIZE 10

struct set{
  int s[SET_SIZE];
};

#define BORNE    -999

// returns the expected position of c in sorted array s
// the returned value p is such that either s[p]==c,
// or c should be inserted in position p in s
static size_t find(int const s[], int data) {
  size_t i;
  for (i=0; (s[i] != BORNE) && (s[i] < data); ++i );
  return i;
}

int set__add(struct set* st, int data) {
  if (data < 0)
    return SET__ELEMENT_INVALID;

  int i = find(st->s, data);
  if ( (st->s[i] != BORNE) && (st->s[i] == data) ) // already in
    return SET__ELEMENT_DUPLICATION;

  if (st->s[SET_SIZE-1] == BORNE) // out of space
    return SET__CAPACITY_EXCEEDED;
  
  shift_right(st->s, i);
  st->s[i] = data;
  
  return SET__NO_ERROR;
}

#define FREECELL (59)

struct set * set__empty(void) {
  struct set * st = malloc(sizeof(struct set));

  st->s[SET_SIZE-1] = FREECELL;
  st->s[0] = BORNE;
  return st;
}


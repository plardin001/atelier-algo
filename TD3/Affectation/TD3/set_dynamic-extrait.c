
struct set{
  int* s;
  size_t capacity;
  size_t size;
  int* cursor;
};

#define MIN_CAPACITY 10 // should be > 0

struct set * set__empty(void) {
  assert( MIN_CAPACITY > 0 );

  struct set * st = malloc(sizeof(struct set));

  st->capacity = MIN_CAPACITY;
  st->s = malloc(st->capacity * sizeof(* st->s));

  st->size = 0;
  return st;
}

int set__add(struct set* st, int data) {
  if (data < 0)
    return SET__ELEMENT_INVALID;

  size_t p = find(st->s, st->size, data);
  if ((p < st->size) && (st->s[p] == data)) // already in
    return SET__ELEMENT_DUPLICATION;

  if (st->size == st->capacity) {
    st->capacity *= 2;
    st->s = realloc(st->s, st->capacity * sizeof(* st->s));
  }

  shift_right(st->s, p, st->size-1);
  st->s[p] = data;
  ++ st->size;

  return SET__NO_ERROR;
}

// with cursor
void set__crs_start(struct set *st) {
  st->cursor = st->s;
}

void set__crs_next(struct set *st) {
  st->cursor++;
}

int  set__crs_has_next(const struct set *st) {
  return st->cursor != (st->s + st->size);
}

int set__crs_data(const struct set *st) {
  return *(st->cursor);
}



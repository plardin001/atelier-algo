
struct set {
  struct link *link;
};


// returns the position of data in lnk: NULL if data is/should be inserted
// in first position, or a cell p s.t. p->next has value data or is the
// first cell with a value greater than data
static struct lelement * find(struct link *lnk, int data) {
  struct lelement *p = NULL;
  for (struct lelement *l = lnk__first(lnk); 
       !llm__is_end_mark(l); 
       l = llm__next(l)) {
    if (l->data >= data)
      return p;
    p = l;
  }
 return p;
}

int set__add(struct set * st, int data) {
  if (data < 0)
    return SET__ELEMENT_INVALID;

  struct lelement * pred = find(st->link, data);
  struct lelement * current = (pred == NULL ? lnk__first(st->link) : pred->next);
  
  if ( (! llm__is_end_mark(current)) && (current->data == data) ) // already in
    return SET__ELEMENT_DUPLICATION;

  struct lelement * l = malloc(sizeof(struct lelement));
  l->data = data;

  if (pred == NULL)
    lnk__add_head(st->link, l);
  else
    lnk__add_after(st->link, pred, l);

  return SET__NO_ERROR;
}


struct set * set__empty(void) {
  struct set * st = malloc(sizeof(struct set));

  st->link = malloc(sizeof(struct link));
  *(st->link) = lnk__empty();
  return st;
}



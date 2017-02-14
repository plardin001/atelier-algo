#include <assert.h>
#include <stdio.h>
#include "link.h"

void	test_lnk__empty()
{

	struct	link l;
	
	printf("---------------------test de lnk__empty--------------\n");
  	l.head = NULL;
	lnk__empty(&l);
 	assert(l.head->next == l.head);
	free(l.head);
	printf("OK\n");
}

void	test_lnk__first()
{
  	struct link l;
  
	printf("----------------test de lnk__first----------------\n");
	lnk__empty(&l);
  	assert(lnk__first(&l) == (l.head));
	free(l.head);
	printf("OK\n");
}

void test_llm__is_end_mark()
{

  	struct lelement e;
	struct lelement next;
  
	printf("------------------test de lmm__is_end_mark--------------");	
  	printf("\nEntree pointeur NULL\n");
	assert(llm__is_end_mark(NULL) == 0);
 	e.next = &e;
  	printf("Entree sentinelle\n");
	assert(llm__is_end_mark(&e) == 1);
	e.next = &next;
  	printf("Entree non sentinelle\n");
	assert(llm__is_end_mark(&e) == 0);
	printf("OK\n");
}

void	test_lnk__add_head()
{
	struct link l;
	struct lelement new;

	printf("-------test de lnk__add_head----------\n");
	
	printf("Liste vide\n");
	lnk__empty(&l);
	new.data = 42;
	lnk__add_head(&l, &new);
	assert(l.head->data == 42);
	free(l.head->next);
	printf("OK\n");
}

void	test_lnk__remove_head()
{
  	struct link l;
  	struct lelement e;
  
  	printf("------------test de lnk__remove_head---------------\n");
	lnk__empty(&l);
  	printf("Liste vide\n");
  	assert(lnk__remove_head(&l) == NULL);
  	printf("Liste a un element\n");
	lnk__add_head(&l, &e);
  	assert(lnk__remove_head(&l) == &e);
  	assert(llm__is_end_mark(l.head));
	free(l.head);
	printf("OK\n");
}

void	test_llm__next()
{
	struct lelement e1;
	struct lelement e2;
  	struct link l; 
	
	printf("-------------test de llm__next-----------\n");
	lnk__empty(&l);
  	lnk__add_head(&l, &e1);
  	lnk__add_head(&l, &e2);
  	assert(llm__next(&e2) == &e1);
  	free((l.head)->next->next);
	printf("OK\n");
}

void	test_lnk__add_after()
{
	struct link l;
  	struct lelement e1;
  	struct lelement e2;
  	struct lelement e3;
  
	printf("----------------test de lnk__add_after-------------------\n");
	lnk__empty(&l);
  	lnk__add_head(&l, &e2);
  	lnk__add_head(&l, &e1);
  	lnk__add_after(&l, &e1, &e3);    
	assert(e1.next == &e3);
	assert(e3.next == &e2);
	assert(llm__is_end_mark(e2.next));
	free(e2.next);
	printf("OK\n");
}

void	test_lnk__remove_after()
{
	struct link l;
	struct lelement e1;
	struct lelement e2;
	struct lelement e3;
  
	printf("--------------test de lnk__remove_after-----------------\n");
	lnk__empty(&l);
	lnk__add_head(&l, &e3);
	lnk__add_head(&l, &e2);
	lnk__add_head(&l, &e1);
	assert(lnk__remove_after(&l, &e1) == &e2);    
	assert(e1.next == &e3);
	assert(llm__is_end_mark(e3.next));
	free(e3.next);
	printf("OK\n");
}

void test_lnk__add_tail()
{
	struct link l;
	struct lelement e1;
	struct lelement e2;
  
	
	printf("--------------test de lnk__add_tail-----------------\n");
	lnk__empty(&l);
	lnk__add_tail(&l, &e1);
	lnk__add_tail(&l, &e2);    
	assert(e1.next == &e2);
	assert(llm__is_end_mark(e2.next));
	free(e2.next);
	printf("OK\n");
}

void test_lnk__remove_tail()
{
	struct link l;
	struct lelement e1;
	struct lelement e2;
	struct lelement e3;
  
	printf("---------------test de lnk__remove_tail-----------------\n");
	lnk__empty(&l);
	lnk__add_tail(&l, &e1);
  	lnk__add_tail(&l, &e2);    
  	lnk__add_tail(&l, &e3); 
	assert(lnk__remove_tail(&l) == &e3);
	assert(llm__is_end_mark(e2.next));
	free(e2.next);
	printf("OK\n");
}

int main()
{

  test_lnk__empty();
  test_lnk__first();
  test_llm__is_end_mark();
  test_lnk__add_head();
  test_lnk__remove_head();
  test_llm__next();
  test_lnk__add_after();
  test_lnk__remove_after();
  test_lnk__add_tail();
  test_lnk__remove_tail();

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Slist.h"


typedef struct student {
	int id;
} student;

slist*  mylist = NULL;
slist*  mylist2 = NULL;
void print_student (int index, void* data, void* itemData) {
	student* item = (student*) itemData;
	printf ("Student: %d", index);
	printf ("\tID: %d\n", item->id);
}

bool compare_student (student* st1, student* st2) {
	return (st1->id < st2->id);
}
bool is_student_equal (student* st1, student* st2) {
	return (st1->id == st2->id);
}
void free_student_mem (student* st) {
	free (st);
}

int main ()
{
	int i;
	slist* tmp = NULL;
	student* finder = (student*) malloc (sizeof (student));
	student* insert = (student*) malloc (sizeof (student));
	insert->id = 99;
	finder->id = 9;
	for (i = 0; i < 10; ++i) {
		student* person1 = (student*) malloc (sizeof (student));
		person1->id = i;
		mylist = slist_append (mylist, (void*) person1);
	}

	for (i = 10; i < 20; ++i) {
		student* person1 = (student*) malloc (sizeof (student));
		person1->id = i;
		mylist2 = slist_append (mylist2, (void*) person1);
	}
	/* concat 2 list */
	mylist2 = slist_concat (mylist2, mylist);

	/* trace data of list */
	slist_trace (mylist2, NULL, &print_student);
	printf ("\n");
	/* short list */
	printf ("\nlist after soft:\n");
	mylist2 = slist_sort (mylist2, &compare_student);
	slist_trace (mylist2, NULL, &print_student);
	/* find and remove item */
	printf ("\nfind and remove item data (9):\n");
	tmp = slist_find (mylist2, finder, &is_student_equal);
	mylist2 = slist_remove_by_data_x (mylist2, tmp->data, &free_student_mem);
	slist_trace (mylist2, NULL, &print_student);
	/* remove item by index */
	printf ("\nremove item by index (0):\n");
	mylist2 = slist_remove_by_index_x (mylist2, 0, &free_student_mem);
	slist_trace (mylist2, NULL, &print_student);
	/* find and insert item */
	printf ("\ninsert item (99 after 10):\n");
	finder->id = 10;
	tmp = slist_find (mylist2, finder, &is_student_equal);
	mylist2 = slist_insert (mylist2, insert, tmp->data, &is_student_equal);
	slist_trace (mylist2, NULL, &print_student);

	getchar ();


}

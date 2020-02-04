/***************************************************************************//**

  @file         linkedlist_test.c

  @author       Renzo Loor

  @date         monday,  03 january 2020

  @brief	
*******************************************************************************/
#include "ll.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LIST_FOR_EACH(list) for(int i = 0; i < list_size((list)) ; ++i)



#define ASSERT_NON_ZERO(b) do { \
if ((b) == 0) { \
	fprintf(stdout, "\nAssertion failed at %s:%d %s ",__FILE__,__LINE__,#b); \
	return false; \
} \
} while (0)

#define ASSERT_ZERO(b) do { \
if ((b) != 0) { \
	fprintf(stdout, "\nAssertion failed at %s:%d %s ",__FILE__,__LINE__,#b); \
	return false; \
} \
} while (0)

#define ASSERT_TEST(b) do { \
if (!(b)) { \
	fprintf(stdout, "\nAssertion failed at %s:%d %s ",__FILE__,__LINE__,#b); \
	return false; \
} \
} while (0)

#define RUN_TEST(test) do { \
fprintf(stdout, "Running "#test"... "); \
if (test()) { \
	fprintf(stdout, "[OK]\n");\
} else { \
	fprintf(stdout, "[Failed]\n"); \
} \
} while(0)

static bool isVocal(char ch){
	return 	((ch =='a') || (ch == 'A')	||(ch =='e') || (ch == 'E')	||(ch =='i') || (ch == 'I')
			||(ch =='o') || (ch == 'O')	||(ch =='u') || (ch == 'U'));
}
static int computer(void* data){
	char* name = (char*)data;
	int c = 0;
	for(int i=0;i<strlen(name);++i)
		c+= isVocal(name[i]);
	return c;
}


bool pruebaDeInsert(){
	linked_list_t* list = list_alloc();
	int data = 42;
	ASSERT_NON_ZERO(list_insert(NULL,1984,NULL));
	ASSERT_NON_ZERO(list_insert(NULL,1984,&data));

	ASSERT_ZERO(list_insert(list,1984,&data));
	ASSERT_NON_ZERO(list_insert(list,1984,&data));
	ASSERT_NON_ZERO(list_insert(list,1984,&data));
	list_free(list);
	return true;
}

bool pruebaDeDelete(){
	linked_list_t* list = list_alloc();
	
	ASSERT_NON_ZERO(list_remove(NULL,1984));

	ASSERT_NON_ZERO(list_remove(list,1984));

	list_free(list);
	return true;
}

bool pruebaDeSearch(){
	linked_list_t* list = list_alloc();
	
	ASSERT_TEST(list_find(NULL,1984) != 0);

	ASSERT_TEST(list_find(list,1984) == 0);
	list_free(list);
	return true;
}

bool pruebaDeAllocation(){

	linked_list_t* list = list_alloc();

	list_free(list);
	return true;
}

bool pruebaDeUpdate(){
	linked_list_t* list = list_alloc();
	ASSERT_NON_ZERO(list_update(NULL,1984,NULL));
	ASSERT_NON_ZERO(list_update(NULL,0,NULL));
	ASSERT_NON_ZERO(list_update(NULL,-1984,NULL));

	ASSERT_NON_ZERO(list_update(list,-1984,NULL));

	list_free(list);
	return true;
}


bool prueba1(){
	linked_list_t* list1 = list_alloc();
	linked_list_t* list2 = list_alloc();
	linked_list_t* list3 = list_alloc();

	int marcas = 6 , numOfLannisters = 4;
	int marcados[6] = {46,23,51,62,34,39};
	int n1 = 1 ,n2 = 3, n3 = numOfLannisters;
	linked_list_t* arr1[n1];
	linked_list_t* arr2[n2];
	linked_list_t* arr3[numOfLannisters];
	ASSERT_TEST(list_size(list1) == 0);
	ASSERT_ZERO(list_insert(list1,46,"Ana"));
	ASSERT_ZERO(list_insert(list1,23,"Alex"));
	ASSERT_ZERO(list_insert(list1,51,"Carlos"));
	ASSERT_ZERO(list_insert(list1,62,"Brian"));
	ASSERT_ZERO(list_insert(list1,34,"Maria"));
	ASSERT_ZERO(list_insert(list1,39,"Ariel"));
	ASSERT_TEST(list_size(list1) == marcas);

	ASSERT_ZERO(list_insert(list2,444,"Roberto"));
	ASSERT_ZERO(list_insert(list2,333,"Tommy"));
	ASSERT_ZERO(list_insert(list2,111,"Alex"));
	ASSERT_ZERO(list_insert(list2,222,"Ruben"));
	ASSERT_TEST(list_size(list2) == numOfLannisters);

	ASSERT_ZERO(list_insert(list3,444,"Roberto"));
	ASSERT_ZERO(list_insert(list3,111,"Alex"));
	ASSERT_TEST(list_size(list3) == (numOfLannisters-2));

	LIST_FOR_EACH(list1){
		ASSERT_TEST(list_find(list1,marcados[i]) == 1);
	}

	ASSERT_ZERO(list_remove(list1,34));
	ASSERT_ZERO(list_remove(list1,39));
	ASSERT_TEST(list_size(list1) == (marcas-2));
	ASSERT_TEST(list_find(list1,34) == 0);
	ASSERT_TEST(list_find(list1,39) == 0);

	ASSERT_ZERO(list_insert(list1,34,"Maria"));
	ASSERT_ZERO(list_insert(list1,39,"Ariel"));
	ASSERT_TEST(list_find(list1,34) == 1);
	ASSERT_TEST(list_find(list1,39) == 1);

	ASSERT_ZERO(list_split(list1,n1,arr1)); // list1 is freed
	ASSERT_TEST(list_size(arr1[0]) == marcas); // arr1[0] is identical to list1 before list_split

	ASSERT_ZERO(list_split(list2,n2,arr2)); // list2 is freed
	ASSERT_TEST(list_find(arr2[0],111) == 1);
	ASSERT_TEST(list_find(arr2[0],444) == 1);
	ASSERT_TEST(list_size(arr2[0]) == 2);
	ASSERT_TEST(list_find(arr2[1],222) == 1);
	ASSERT_TEST(list_size(arr2[1]) == 1);
	ASSERT_TEST(list_find(arr2[2],333) == 1);
	ASSERT_TEST(list_size(arr2[2]) == 1);

	ASSERT_ZERO(list_split(list3,n3,arr3)); // list3 is freed
	ASSERT_TEST(list_find(arr3[0],111) == 1);
	ASSERT_TEST(list_find(arr3[1],444) == 1);
	ASSERT_TEST(list_size(arr3[0]) == 1);
	ASSERT_TEST(list_size(arr3[1]) == 1);
	ASSERT_TEST(list_size(arr3[2]) == 0); // empty list
	ASSERT_TEST(list_size(arr3[2]) == 0); // empty list


	// free all allocated lists
	for(int i=0;i<n1;++i)
		list_free(arr1[i]);
	for(int i=0;i<n2;++i)
		list_free(arr2[i]);
	for(int i=0;i<n3;++i)
		list_free(arr3[i]);
	return true;
}

bool prueba2(){
	linked_list_t* list1 = list_alloc();
	linked_list_t* list2 = list_alloc();
	linked_list_t* list3 = list_alloc();
	int result;

	ASSERT_ZERO(list_insert(list1,46,"Ana"));
	ASSERT_ZERO(list_insert(list1,23,"Alex"));
	ASSERT_ZERO(list_insert(list1,51,"Carlos"));
	ASSERT_ZERO(list_insert(list1,62,"Abel"));
	ASSERT_ZERO(list_insert(list1,34,"Maria"));
	ASSERT_ZERO(list_insert(list1,39,"Ariel"));

	ASSERT_ZERO(list_insert(list2,444,"Roberto"));
	ASSERT_ZERO(list_insert(list2,333,"Tommy"));
	ASSERT_ZERO(list_insert(list2,111,"Alex"));
	ASSERT_ZERO(list_insert(list2,222,"Ruben"));

	ASSERT_ZERO(list_insert(list3,1111,"Rene"));

	ASSERT_ZERO(list_compute(list1,46,computer,&result));
	ASSERT_TEST(result == 2);
	ASSERT_ZERO(list_compute(list1,23,computer,&result));
	ASSERT_TEST(result == 2);
	ASSERT_ZERO(list_compute(list1,51,computer,&result));
	ASSERT_TEST(result == 2);
	ASSERT_ZERO(list_compute(list2,444,computer,&result));
	ASSERT_TEST(result == 3);
	ASSERT_ZERO(list_compute(list2,333,computer,&result));
	ASSERT_TEST(result == 1);
	ASSERT_ZERO(list_compute(list3,1111,computer,&result));
	ASSERT_TEST(result == 2);

	ASSERT_ZERO(list_update(list1,34,"Maria se fue"));
	ASSERT_ZERO(list_update(list1,39,"Ariel el malo"));
	ASSERT_ZERO(list_update(list1,46,"Ana la cubana"));
	ASSERT_ZERO(list_update(list2,222,"Ruben el rey"));
	ASSERT_ZERO(list_update(list2,444,"Roberto el jugador"));
	ASSERT_ZERO(list_update(list3,1111,"Rene la rana"));

	ASSERT_ZERO(list_compute(list1,34,computer,&result));
	ASSERT_TEST(result == 6);
	ASSERT_ZERO(list_compute(list1,39,computer,&result));
	ASSERT_TEST(result == 6);
	ASSERT_ZERO(list_compute(list1,46,computer,&result));
	ASSERT_TEST(result == 6);
	ASSERT_ZERO(list_compute(list2,222,computer,&result));
	ASSERT_TEST(result == 4);
	ASSERT_ZERO(list_compute(list2,444,computer,&result));
	ASSERT_TEST(result == 7);
	ASSERT_ZERO(list_compute(list3,1111,computer,&result));
	ASSERT_TEST(result == 5);

	list_free(list1);
	list_free(list2);
	list_free(list3);
	return true;
}


int main(){

	RUN_TEST(pruebaDeInsert);
	RUN_TEST(pruebaDeDelete);
	RUN_TEST(pruebaDeSearch);
	RUN_TEST(pruebaDeAllocation);
	RUN_TEST(pruebaDeUpdate);
	RUN_TEST(prueba1);
	RUN_TEST(prueba2);

	return 0;
}

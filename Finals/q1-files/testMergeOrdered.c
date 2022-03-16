// 
// testMergeOrdered.c   ... 

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "list.h"

List mergeOrdered (List list1, List list2);


int main(int argc, char *argv[])
{
	char buffer[1024] ;


	char *line1=fgets(buffer, sizeof(buffer), stdin);
	List list1 = getList(line1);
	fprintf(stdout, "list1: ");
	showList(stdout, list1);

	char *line2=fgets(buffer, sizeof(buffer), stdin);
	List list2 = getList(line2);
	fprintf(stdout, "list2: ");
	showList(stdout, list2);

	List ansL = mergeOrdered(list1, list2);

	fprintf(stdout, "answer List: ");
	showList(stdout, ansL);

	dropList(list1);
	dropList(list2);
	dropList(ansL);

	return 0;

}

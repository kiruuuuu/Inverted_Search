#include "dll.h"

int print_list(flist *head)
{
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
    else
    {
        flist *temp = head;
	    while (temp != NULL)		
	    {
		    printf("%s -> ", temp -> f_name);
		    temp = temp -> link;
	    }

	    printf("NULL\n");
    }
    return SUCCESS;
}
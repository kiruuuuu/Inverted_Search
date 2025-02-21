#include "dll.h"

int store_file_names(flist **head, char  *data)
{
    flist *new = malloc(sizeof(flist));
    if(new == NULL)
        return FAILURE;

         strcpy(new->f_name,data);
         new->link=NULL;
     
      if(*head==NULL){
         *head=new;
         return SUCCESS;
      } 
     else
     {
     flist *temp=*head;
     while(temp->link != NULL)
     {
        temp=temp->link;
     }
     temp->link=new;
     }
     return SUCCESS;

}
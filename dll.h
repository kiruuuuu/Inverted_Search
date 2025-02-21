#ifndef DLL_H
#define DLL_L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET   "\033[0m"  
#define RED     "\033[1;31m" 
#define GREEN   "\033[1;32m" 
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"

#define SUCCESS    1
#define FAILURE    0

#define REPEATED    -2

#define NAMELENGTH  50

typedef struct node
{
    char f_name[NAMELENGTH];
    struct node *link;
}flist;


typedef struct main_node
{
    char word[50];
    int f_count;
    struct sub_node *s_link;
    struct main_node *m_link;
}Main;

typedef struct sub_node
{
    char f_name[NAMELENGTH];
    int w_count;
    struct sub_node *link;
}Sub;


void read_validate(int argc,char *argv[],flist **head);
int store_file_names(flist **head, char  *data);
int IsFileDuplicate (char* filename, flist **head);
int print_list(flist *head);
int Create_database(flist **head, Main **arr,flist **head2);
int display_database(Main **arr);
void search_database(Main **arr,char str[]);
int save_database(Main **arr,char file_name[]);
int update_database(flist **head, Main **arr, char f_name[]);
flist* remove_duplicate_files(flist **head1,flist **head2);


#endif
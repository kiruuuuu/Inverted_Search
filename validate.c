#include "dll.h"

void read_validate(int argc, char *argv[], flist **head)
{
    // Loop through each argument (starting from index 1 to skip the program name)
    for(int i = 1; i < argc; i++)
    {
        // Check if the argument ends with ".txt" extension
        if(strstr(argv[i], ".") != NULL && strcmp(strstr(argv[i], "."), ".txt") == 0)
        {
            FILE *f_name = fopen(argv[i], "r");  // Try to open the file in read mode
            if(f_name == NULL)  // If the file doesn't exist or can't be opened
            {
                continue;  // Skip to the next file
            }
            else  // If the file is opened successfully
            {
                char ch = fgetc(f_name);  // Read the first character of the file
                if(ch != EOF)  // If the file is not empty
                {
                    // Check if the file is already in the list
                    if(IsFileDuplicate(argv[i], head) == REPEATED)
                    {
                        printf(RED"%s Duplicate file\n"RESET,argv[i]);  // Print a message for duplicates
                    }
                    else
                    {
                        // If the file is not a duplicate, add it to the file list
                        if(store_file_names(head, argv[i]) == SUCCESS)
                        {
                            printf(YELLOW"%s List stored \n"RESET,argv[i]);  // Print success message
                        }
                        else
                        {
                            printf(RED"List not stored successfully\n"RESET);  // Print error message if adding fails
                        }
                    }
                }
                else
                {
                    fclose(f_name);  // Close the file if it's empty
                    continue;  // Skip to the next file
                }
            }
        }
        else  // If the argument doesn't have a valid ".txt" extension
        {
            printf(RED"Invalid extension\n"RESET);  // Print an error message for invalid extensions
        }
    }
}

// Function to check if a file is a duplicate in the file list
int IsFileDuplicate(char* filename, flist **head)
{
    flist *temp = *head;  // Temporary pointer to traverse the file list

    // Traverse the list to check for duplicates
    while (temp != NULL)
    {
        // Compare the file name with each node's file name
        if((strncmp(filename, temp->f_name, NAMELENGTH)) == 0)
        {
            return REPEATED;  // Return REPEATED if a match is found
        }
        temp = temp->link;  // Move to the next node
    }

    return FAILURE;  // Return FAILURE if no match is found
}

// Function to remove files that are duplicates between two file lists

flist* remove_duplicate_files(flist **head1, flist **head2)
{
    flist *head3 = NULL;  // New list to store unique files
    flist *temp = *head1;  // Temporary pointer to traverse the first file list

    // Traverse the first list to find files that are not in the second list
    while(temp != NULL)
    {
        // If the file from head1 is not in head2, add it to head3
        if(IsFileDuplicate(temp->f_name, head2) == FAILURE)
        {
            flist *new = malloc(sizeof(flist));  // Allocate memory for a new node
            if(new == NULL)  // If memory allocation fails
                return FAILURE;  // Return failure

            strcpy(new->f_name, temp->f_name);  // Copy the file name to the new node
            new->link = NULL;  // Initialize the link of the new node to NULL

            // If head3 is empty, make new the first node
            if (head3 == NULL) 
            {
                head3 = new; 
            }
            else  // Otherwise, add new to the end of the list
            {
                flist *last = head3;
                while (last->link != NULL)
                {
                    last = last->link;  // Traverse to the last node
                }
                last->link = new;  // Link the new node to the last node
            }
        }
        temp = temp->link;  // Move to the next node in head1
    }

    return head3;  // Return the new list containing unique files from head1
}

#include "dll.h"

extern int update;  // Global variable to track if the database is being updated
extern int create;  // Global variable to track if the database is being created

int update_database(flist **head, Main **arr, char f_name[])
{
    system("clear");  // Clear the terminal screen for fresh output
    update = 1;       // Set update flag to indicate that the database is being updated
    create = 0;       // Set create flag to 0, indicating no creation is occurring

    // Check if the file name has a valid ".txt" extension
    if (strstr(f_name, ".") != NULL && strcmp(strstr(f_name, "."), ".txt") == 0)
    {
        FILE *fptr = fopen(f_name, "r");  // Open the file in read mode
        if (fptr)  // If the file is opened successfully
        {
            printf("valid file name\n");  // Print message confirming the valid file name
        }
        else  // If file opening fails
        {
            return FAILURE;  // Return failure
        }

        char ch = fgetc(fptr);  // Read the first character of the file
        if (ch != '#')  // If the file doesn't start with a '#'
        {
            return FAILURE;  // Return failure
        }
        else  // If the file starts with '#', process the file
        {
            rewind(fptr);  // Rewind the file pointer to the beginning of the file
            char str[100];  // Array to store each line read from the file
            int index;      // Index for storing words based on their starting letter

            // Read each word from the file
            while (fscanf(fptr, "%s", str) != EOF)
            {
                char *token = strtok(&str[1], ";");  // Tokenize the string (ignoring the initial '#')

                index = atoi(token);  // Convert the first token to an integer index
                token = strtok(NULL, ";");  // Get the word

                // Allocate memory for the main node (for the word)
                Main *mainnode = malloc(sizeof(Main));
                // Allocate memory for the sub-node (for the file and word count)
                Sub *subnode = malloc(sizeof(Sub));

                // Check if memory allocation for main node or sub node failed
                if (mainnode == NULL || subnode == NULL)
                {
                    return FAILURE;  // Return failure if memory allocation fails
                }

                // Copy the word to the main node
                strcpy(mainnode->word, token);
                mainnode->m_link = NULL;  // Initialize the main node's link to NULL
                mainnode->s_link = subnode;  // Link the sub-node to the main node

                // Tokenize and extract the file count
                token = strtok(NULL, ";");
                mainnode->f_count = atoi(token);

                // Tokenize and extract the file name for the sub-node
                token = strtok(NULL, ";");
                strcpy(subnode->f_name, token);

                // Check if the file is already in the file list; if not, store it
                if (IsFileDuplicate(token, head) != REPEATED)
                    store_file_names(head, token);

                // Tokenize and extract the word count for the sub-node
                token = strtok(NULL, ";");
                subnode->w_count = atoi(token);

                Sub *prev = subnode;  // Pointer to track the previous sub-node
                int j = 1;  // Variable to keep track of the sub-nodes

                // Loop to process the remaining sub-nodes for the word
                while (j < mainnode->f_count)
                {
                    subnode = malloc(sizeof(Sub));  // Allocate memory for the new sub-node
                    if (subnode == NULL)
                    {
                        return FAILURE;  // Return failure if memory allocation fails
                    }
                    subnode->link = NULL;  // Initialize the link of the new sub-node

                    // Tokenize and extract the file name for the sub-node
                    token = strtok(NULL, ";");
                    strcpy(subnode->f_name, token);

                    // Check if the file is already in the file list; if not, store it
                    if (IsFileDuplicate(token, head) != REPEATED)
                        store_file_names(head, token);

                    // Tokenize and extract the word count for the sub-node
                    token = strtok(NULL, ";");
                    subnode->w_count = atoi(token);

                    prev->link = subnode;  // Link the previous sub-node to the current sub-node
                    prev = subnode;  // Move the 'prev' pointer to the current sub-node
                    j++;  // Increment the counter for sub-nodes
                }

                // Check if the index slot in the array is empty
                if (arr[index] == NULL)
                {
                    arr[index] = mainnode;  // Assign the main node to the array slot
                }
                else
                {
                    Main *temp = arr[index];  // If the slot is not empty, find the last main node
                    while (temp->m_link != NULL)
                    {
                        temp = temp->m_link;  // Traverse to the last main node
                    }
                    temp->m_link = mainnode;  // Link the new main node to the end of the list
                }
            }
        }
    }
    else  // If the file name is not valid (doesn't end with .txt)
    {
        printf(RED"Invalid file name\n"RESET);  // Print an error message
    }

    // Print the updated file list
    print_list(*head);
    return SUCCESS;  // Return success after updating the database
}

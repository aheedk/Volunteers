//Aheed Kamil
// This code is from project 8 and is updated and uses new concepts

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define EMAIL_LEN 100
#define NAME_LEN 30

struct volunteer // Define the structure for a volunteer

{
    char first[NAME_LEN + 1];
    char last[NAME_LEN + 1];
    char email[EMAIL_LEN + 1];
    int grade_level;
    struct volunteer *next; // Pointer to the next volunteer in the list
};

struct volunteer *add_to_list(struct volunteer *list); // Add a volunteer to the list
void search_list(struct volunteer *list);            
void print_list(struct volunteer *list);             
void clear_list(struct volunteer *list);              
struct volunteer *delete_from_list(struct volunteer *list); 
int read_line(char str[], int n);                    

int main(void)
{
    char code;
    struct volunteer *volunteer_list = NULL;

    // Display the available operation codes
    printf("Operation Code: a for adding to the list, s for searching"
           ", d for deleting from the list, p for printing the list; q for quit.\n");

    // Main loop to execute user commands
    for (;;)
    {
        printf("Enter operation code: ");
        scanf(" %c", &code);
        while (getchar() != '\n') /* skips to end of line */
            ;
        switch (code)
        {
        case 'a':
            volunteer_list = add_to_list(volunteer_list); 
            break;
        case 's':
            search_list(volunteer_list); 
            break;
        case 'd':
            volunteer_list = delete_from_list(volunteer_list); 
            break;
        case 'p':
            print_list(volunteer_list); 
            break;
        case 'q':
            clear_list(volunteer_list); 
            return 0;
        default:
            printf("Illegal code\n");
        }
        printf("\n");
    }
}

// Function to add a volunteer to the list
struct volunteer *add_to_list(struct volunteer *list)
{
    struct volunteer *new_volunteer, *p;
    char email[EMAIL_LEN + 1];

    // Allocate memory for the new volunteer
    new_volunteer = malloc(sizeof(struct volunteer));
    if (new_volunteer == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Prompt user to enter volunteer information
    printf("Enter last name: ");
    read_line(new_volunteer->last, NAME_LEN);
    printf("Enter first name: ");
    read_line(new_volunteer->first, NAME_LEN);
    printf("Enter email address: ");
    read_line(email, EMAIL_LEN);

    for (p = list; p != NULL; p = p->next)      // Check if the volunteer already exists in the list

    {
        if (strcmp(p->email, email) == 0 && strcmp(p->last, new_volunteer->last) == 0)
        {
            printf("Volunteer already exists.\n");
            free(new_volunteer);
            return list;
        }
    }

    strcpy(new_volunteer->email, email);

    printf("Enter grade level: ");
    scanf("%d", &new_volunteer->grade_level);
    new_volunteer->next = NULL;

    // If the list is empty, the new volunteer becomes the head of the list
    if (list == NULL)
        return new_volunteer;

    for (p = list; p->next != NULL; p = p->next)
        ;
    p->next = new_volunteer;
    return list;
}

// Function to delete a volunteer from the list
struct volunteer *delete_from_list(struct volunteer *list)
{
    char last_name[NAME_LEN + 1];
    char first_name[NAME_LEN + 1];
    char email[EMAIL_LEN + 1];
    int grade_level;

    printf("Enter last name: ");
    read_line(last_name, NAME_LEN);
    printf("Enter first name: ");
    read_line(first_name, NAME_LEN);
    printf("Enter email address: ");
    read_line(email, EMAIL_LEN);
    printf("Enter grade level: ");
    scanf("%d", &grade_level);

    struct volunteer *current = list;
    struct volunteer *previous = NULL;

    // Traverse the list to find the volunteer to be deleted
    while (current != NULL)
    {
        if (strcmp(current->last, last_name) == 0 &&
            strcmp(current->first, first_name) == 0 &&
            strcmp(current->email, email) == 0 &&
            current->grade_level == grade_level)
        {
            // If the volunteer is found, update the pointers to remove it from the list
            if (previous == NULL)
            {
                list = current->next; 
            }
            else
            {
                previous->next = current->next;
            }
            free(current); 
            return list;
        }
        previous = current;
        current = current->next;
    }

    // If the volunteer is not found, print a message
    printf("Volunteer does not exist.\n");
    return list;
}

// Function to search for volunteers by grade level
void search_list(struct volunteer *list)
{
    int grade;
    struct volunteer *p;
    printf("Enter grade level: ");
    scanf("%d", &grade);
    int found = 0; // Flag to indicate if any volunteer is found
    for (p = list; p != NULL; p = p->next)
    {
        if (p->grade_level == grade)
        {
            printf("%-12s%-12s%-30s\n", p->last, p->first, p->email);
            found = 1;
        }
    }
    if (!found)
        printf("not found\n");
}

// Function to print all volunteers in the list
void print_list(struct volunteer *list)
{
    struct volunteer *p;
    for (p = list; p != NULL; p = p->next)
        printf("%-12s%-12s%-30s%5d\n", p->last, p->first, p->email, p->grade_level);
}

// Function to free memory allocated for the list
void clear_list(struct volunteer *list)
{
    struct volunteer *p;

    while (list != NULL)
    {
        p = list;
        list = list->next;
        free(p);
    }
}

// Function to read a line of input from the user
int read_line(char str[], int n)
{
    int ch, i = 0;

    while (isspace(ch = getchar()))
        ;
    str[i++] = ch;
    while ((ch = getchar()) != '\n')
    {
        if (i < n)
            str[i++] = ch;
    }
    while (i > 0 && isspace(str[i - 1]))
        i--;
    str[i] = '\0';
    return i;
}

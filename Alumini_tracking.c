#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Alumni {
    int id;
    char name[50];
    char department[50];
    int graduationYear;
    char occupation[50];
    struct Alumni *next;
} Alumni;

// Function Prototypes
Alumni* createAlumni(int id, char name[], char dept[], int year, char occ[]);
void insertAlumni(Alumni **head, int id, char name[], char dept[], int year, char occ[]);
Alumni* searchByID(Alumni *head, int id);
Alumni* searchByName(Alumni *head, const char *name);
void deleteByID(Alumni **head, int id);
void displayList(Alumni *head);
void reverseDisplay(Alumni *head);
void cloneList(Alumni *head, Alumni **cloneHead);
void departmentWiseList(Alumni *head, const char *dept);

int main() {
    Alumni *head = NULL, *cloneHead = NULL;
    int choice, id, year;
    char name[50], dept[50], occ[50];

    while (1) {
        printf("\n---- Alumni Tracking System ----\n");
        printf("1. Insert Alumni\n2. Search by ID\n3. Search by Name\n");
        printf("4. Delete by ID\n5. Display List\n6. Reverse Display\n");
        printf("7. Clone List\n8. Department-wise List\n9. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter ID: ");
                scanf("%d", &id);
                getchar();
                printf("Enter Name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                printf("Enter Department: ");
                fgets(dept, sizeof(dept), stdin);
                dept[strcspn(dept, "\n")] = 0;
                printf("Enter Graduation Year: ");
                scanf("%d", &year);
                getchar();
                printf("Enter Occupation: ");
                fgets(occ, sizeof(occ), stdin);
                occ[strcspn(occ, "\n")] = 0;
                insertAlumni(&head, id, name, dept, year, occ);
                break;
            
            case 2:
                printf("Enter ID to search: ");
                scanf("%d", &id);
                Alumni *foundID;
                foundID = searchByID(head, id);
                if (foundID)
                    printf("Found: %d | %s | %s | %d | %s\n", foundID->id, foundID->name, foundID->department, foundID->graduationYear, foundID->occupation);
                else
                    printf("Alumni not found!\n");
                break;
            
            case 3:
                printf("Enter Name to search: ");
                getchar();
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                Alumni *foundName;
                foundName = searchByName(head, name);
                if (foundName)
                    printf("Found: %d | %s | %s | %d | %s\n", foundName->id, foundName->name, foundName->department, foundName->graduationYear, foundName->occupation);
                else
                    printf("Alumni not found!\n");
                break;
            
            case 4:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                deleteByID(&head, id);
                break;
            
            case 5:
                displayList(head);
                break;

            case 6:
                reverseDisplay(head);
                break;

            case 7:
                cloneList(head, &cloneHead);
                printf("Cloned List:\n");
                displayList(cloneHead);
                break;

            case 8:
                printf("Enter Department: ");
                getchar();
                fgets(dept, sizeof(dept), stdin);
                dept[strcspn(dept, "\n")] = 0;
                departmentWiseList(head, dept);
                break;

            case 9:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Create new Alumni node
Alumni* createAlumni(int id, char name[], char dept[], int year, char occ[]) {
    Alumni *newAlumni = (Alumni*)malloc(sizeof(Alumni));
    newAlumni->id = id;
    strcpy(newAlumni->name, name);
    strcpy(newAlumni->department, dept);
    newAlumni->graduationYear = year;
    strcpy(newAlumni->occupation, occ);
    newAlumni->next = NULL;
    return newAlumni;
}

// Insert at End
void insertAlumni(Alumni **head, int id, char name[], char dept[], int year, char occ[]) {
    Alumni *newAlumni = createAlumni(id, name, dept, year, occ);
    if (*head == NULL) {
        *head = newAlumni;
        return;
    }
    Alumni *temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = newAlumni;
}

// Search by ID
Alumni* searchByID(Alumni *head, int id) {
    while (head) {
        if (head->id == id)
            return head;
        head = head->next;
    }
    return NULL;
}

// Search by Name
Alumni* searchByName(Alumni *head, const char *name) {
    while (head) {
        if (strcasecmp(head->name, name) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

// Delete Node by ID
void deleteByID(Alumni **head, int id) {
    Alumni *temp = *head, *prev = NULL;
    while (temp && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) {
        printf("Record not found!\n");
        return;
    }
    if (prev)
        prev->next = temp->next;
    else
        *head = temp->next;
    free(temp);
    printf("Alumni with ID %d deleted successfully!\n", id);
}

// Display Full List
void displayList(Alumni *head) {
    if (!head) {
        printf("No Records!\n");
        return;
    }
    while (head) {
        printf("%d | %s | %s | %d | %s\n", head->id, head->name, head->department, head->graduationYear, head->occupation);
        head = head->next;
    }
}

// Reverse Display using Recursion
void reverseDisplay(Alumni *head) {
    if (!head) return;
    reverseDisplay(head->next);
    printf("%d | %s | %s | %d | %s\n", head->id, head->name, head->department, head->graduationYear, head->occupation);
}

// Clone Linked List
void cloneList(Alumni *head, Alumni **cloneHead) {
    *cloneHead = NULL;
    Alumni *tail = NULL;
    while (head) {
        Alumni *newNode = createAlumni(head->id, head->name, head->department, head->graduationYear, head->occupation);
        if (*cloneHead == NULL)
            *cloneHead = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
        head = head->next;
    }
}

// Department-wise Display
void departmentWiseList(Alumni *head, const char *dept) {
    int found = 0;
    while (head) {
        if (strcasecmp(head->department, dept) == 0) {
            printf("%d | %s | %s | %d | %s\n", head->id, head->name, head->department, head->graduationYear, head->occupation);
            found = 1;
        }
        head = head->next;
    }
    if (!found)
        printf("No records found for Department: %s\n", dept);
}

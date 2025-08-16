/*
 - Student Name:Heba Fialah
 - Id:1211315
 - Section:1
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_d 31     //maximum length of name
#define N 129
typedef struct node *Node;
struct node {         // Define a struct which contain a pointer leads to the second struct & a place to the string which will put
    char data[31];
    Node next;
    Node prev;

};

//*******************************   Function   ******************************************
void displayMainMenu();

void DeleteList(Node L);

Node deleteString(Node p, char name[], int *isDeleted);

Node MakeEmpty(Node L);

int isEmpty(Node L);

void insert(Node l, char new_data[]);

void append(struct node **head_ref, char new_data[]);

void printStrings(Node x);

Node sortStrings(Node L);

int getMax(Node L);

void trim_str(char s[]);

int is_valid(char str[]);

Node readFile(Node x);

void outputFile(Node x);

//**************************************************************************************
//_________________________________Main Function________________________________________
int main() {
    Node head = NULL; // Define a struct node that we will start with
    Node list = NULL;
    //head= MakeEmpty(head);
    int operation;   //to scan the operation
    int *isDeleted = 0;
    char newWord[31];
    char nameDel[31];
     printf("\n\n\t\t______________________ Welcome to Radix Sort Project ___________________________\n\n");

    do {

        displayMainMenu();
        printf("Enter Operation:\n");
        scanf("%d", &operation);
        switch (operation) {
            case 1:   //read from file and return the linked list of name
                //head=NULL;
                // head= readFile(head);
                list = readFile(list);
                break;
            case 2:   //print the name before sorting
                printStrings(list);
                break;
            case 3:   //radix sort

                head = sortStrings(list);
                printf("\n\t\t List was Sorted.\n");
                // printStrings(head);
                break;
            case 4:   //print the list after sorting it
                printStrings(head);
                break;
            case 5:   //add new name
                printf("\n\t\t Write the name : ");
                scanf("%s", &newWord);  //read the name
                if (is_valid(newWord) && strlen(newWord) < MAX_d - 1) {  //check if valid
                    trim_str(newWord);                                     //trim the string

                    append(&head, newWord);                             //function to add name to list
                    append(&list, newWord);
                    printf("\n\t\t Add Successfully.\n");
                    //  printf("This name [%s] is added to the list.", newWord);
                    head = sortStrings(head);
                } else {          //if the name invalid
                    printf("\n\tString not valid does not added.\n");
                }
                break;
            case 6:   //delete name from the list
                printf("\n\t\t Write the name you want to delete it : ");
                scanf("%s", &nameDel);
                head = deleteString(head, nameDel, &isDeleted);//sort
                list = deleteString(list, nameDel, &isDeleted);
                if (isDeleted) {
                    printf("\n\t\t Delete Successfully.\n");
                    head = sortStrings(head);
                } else {
                    printf("\n\t\t Name Not Found it. \n");
                }
                // printf("This name [%s] is deleted from the list.", nameDel);
                // head = sortStrings(head);
                break;
            case 7:   //print in file
                printf("The data is save in output file.\n");
                outputFile(head);   //function to print in file
                break;
            case 8:
                printf("\n << Thank you for choosing my program.>> \n");
                break;
            default:
                printf("Try again because number of option does not exist");
        }

    } while (operation != 8);

    return 0;


}
//********************** Implemantation the function *********************

void displayMainMenu() { //main menu
    printf("\n\t\t____________________________________________\n");
    printf("\n\t\t Please chose from the list :              \n\n");
    printf("\t\t\t| 1) - Read the list from the file.   \n");
    printf("\t\t\t| 2) - Print name.           \n");
    printf("\t\t\t| 3) - Sort the List.       \n");
    printf("\t\t\t| 4) - Print the List after sorting.      \n");
    printf("\t\t\t| 5) - ADD element to the list.           \n");
    printf("\t\t\t| 6) - Delete element from the list.    \n");
    printf("\t\t\t| 7) - Print the list in File after sorting.\n");
    printf("\t\t\t| 8) - Exits.                               \n");
    printf("\n\t\t____________________________________________\n");
    printf("\t\t\t => ");
}

//**********************  Add & Delete & print & Make empty & Check Linked List if empty Functions *********************
void DeleteList(Node L) {
    Node P = L;
    Node temp;
    while (P != NULL) {
        temp = P->next;
        free(P);
        P = temp;
    }
}

Node deleteString(Node p, char name[], int *isDeleted) { //delete name from the list
    Node temp = p;
    if (isEmpty(p)) {   //check if the list is empty
       printf("there is no Name to delete it ");
        return  p;

    } else {
        while (temp != NULL && strcmp(temp->data, name) != 0) {
            temp = temp->next;
        }
        if (temp != NULL) {        //while there is a struct node to delete,do the next statements
            if (p == temp) {
                p = temp->next;
                (temp->next)->prev = p->next;
                free(temp);
                *isDeleted = 1;
                return p;
            } else if (temp->next != NULL) {
                (temp->prev)->next = temp->next;
                (temp->next)->prev = temp->prev;
                free(temp);
                *isDeleted = 1;
                return p;
            } else if (temp->next == NULL) {
                (temp->prev)->next = NULL;
                free(temp);
                *isDeleted = 1;
                return p;
            }
        } else {
            *isDeleted = 0;
            return p;
        }
    }
}

Node MakeEmpty(Node L) {  //to ensure that the linked list (L) is empty
    if (L != NULL)        //if not empty
        DeleteList(L);    //call function to delete the linked list as a data and  as a struct
    L = (Node) malloc(sizeof(struct node));  //give the linked list(head) a new place with struct node size
    if (L == NULL)                                //if there is no place for the linked list,print that
        printf("Out of memory!\n");
    L->next = NULL;                               //make the pointer in the struct node points on NULL
    return L;
}

int isEmpty(Node L) {  //boolean function which checks if the linked list is empty or no
    return L == NULL;  //if the head does not point on node.so it's empty (1) else (0)
}

void insert(Node l, char new_data[]) { //l contains the data of the node we will insert in linked list

    Node new_node = (Node) malloc(sizeof(struct node)); //give it a place
    strcpy(new_node->data, new_data); //put the required data in the node


    Node last = l;


    new_node->next = NULL;
    new_node->prev = NULL;


    if (l == NULL) {
        l = new_node;

    } else {
        while (last && last->next != NULL) {
            last = last->next;
        }

        last->next = new_node;
        new_node->prev = last;
    }
}

void append(struct node **head_ref, char new_data[]) { //function to append name at specific index

    struct node *new_node = (struct node *) malloc(sizeof(struct node));
    strcpy(new_node->data, new_data);


    struct node *last = *head_ref;

    new_node->next = NULL;
    new_node->prev = NULL;


    if (*head_ref == NULL) {
        *head_ref = new_node;


    } else {
        while (last && last->next != NULL) {
            last = last->next;
        }

        last->next = new_node;
        new_node->prev = last;

    }
}

void printStrings(Node x) {  //Function to print the list before & after sorting
    Node curr = x;

    if (isEmpty(x)) {
        printf("It's Empty..");
    } else {

        while (curr != NULL) {
            printf("[%s]->", curr->data);
            curr = curr->next;
        }
        printf("NULL");
    }
}

//********************* Radix Sort **********************
Node sortStrings(Node L) {  //radix sort
    if (isEmpty(L)) {  //check if the list is empty
        printf("The string is not available");
        return L;
    }
    int x, z;
    Node sorted = L; //define the struct node to point on linked list,make it easy to deal without lose data
    Node bucket_sort[N] = {NULL};//bucket or table
    int max = getMax(L); //to get the max number of characters in the string
    while (max) {        //to sort every character along the tallest string individually
        while (sorted != NULL) {  //while there is a node
            char name[31];        //to store the name
            strcpy(name, sorted->data);  //copy string
            if (strlen(name) <
                max) { //if the length of name is less than the max ,add this name in the index(32) to that present space in ascii table
                x = 32;
                append(&bucket_sort[x], name);
            } else { //get the index of character ,and add this name in index(x) to that present in ascii table
                z = max - 1;
                x = name[z];
                append(&bucket_sort[x], name);
            }
            sorted = sorted->next;  //points the next to check if there is a next node
        }
        max--; //decrement the max length
        sorted = MakeEmpty(sorted); //make empty for the sorted list
        sorted = NULL;
        for (int i = 0; i < N; i++) {
            Node l = bucket_sort[i]; //define a new struct node which will store the new nodes after sort them by a specific character
            while (l) {
                append(&sorted, l->data);
                l = l->next;
            }
        }
        for (int i = 0; i < N; i++) { //make empty for the next sorting if exist
            bucket_sort[i] = MakeEmpty(bucket_sort[i]);
            bucket_sort[i] = NULL;
        }

    }


    return sorted;
}

//********************* string Function **************************
int getMax(Node L) { //to get the max number of the character in a string in linked list
    Node curr=L;
    int max = strlen(curr->data);      // max has the number of the characters of the first node

    while (curr != NULL) {                 // while there is a node
        if (strlen(curr->data) > max)
            max = strlen(curr->data);  //store the number in 'max'
        curr = curr->next;                 //to check if there is a next node
    }
    return max;                            // return the max number of the characters in linked list
}

void trim_str(char s[]) // to put '\0' to end of string
{
    int y = 0, j = 0;
    while (s[y] == ' ' && s[y] != '\0') // if begin with space
    {
        y++;
    }
    for (; s[y] != '\0'; y++, j++)         // shift the space
    {
        s[j] = s[y];
    }
    s[j] = '\0';
    int i = strlen(s) - 1;
    while (s[i] != '\n' && s[i] != '\0' && i < 30) {
        i++;
    }
    s[i] = '\0';
    return;
}

int is_valid(char str[])                 // check if the string are valid or not
{

    if (str[0] == ' ' || str[0] == '\n') // if the first is space trim the string
    {

        return 0;
    }
    if (strlen(str) == 0 || strlen(str) > 30)  //if the length of name greater than 30 or if there is an empty line
        return 0;
    else if (strlen(str) < 30 && str[0] >= '0' && str[0] <= '9') //if the first character of name is digit
        return 0;
    else
        return 1;
}

//********************** Read from file & Print in file ****************
Node readFile(Node x) {   //function to read the name from file
    char temp[100];     //took a place for the string that will be scanned
    int n = 0;
//    x = MakeEmpty(x) ;
    Node p = x;
    FILE *in = fopen("Input.txt", "r");               //open the file
    if (in == NULL)                                                 //check if exist
        printf("Error the file does not exist\n");
    else
        while (fgets(temp, 100, in)!=NULL ) {   //read all name in file
            trim_str(temp);                                       //trim the string(remove first space)
            if (!is_valid(temp)) {                                 //check if the string valid
                n++;                                                 //count the invalid string
            } else {
                append(&x, temp);                   //add the name to the list
            }

        }
    if (n) {  //print number of invalid string
        printf("\t\t Note::that there is %d string not valid and dose not added.\n", n);
    }
    printf("Read Successfully.\n");
    fclose(in); //close file
    return x;  //return the linked list of name
}

void outputFile(Node x) {  //print the list in file
    Node curr = x;
    FILE *fp;
    fp = fopen("Output.txt", "w");
    while (curr != NULL) {
        fprintf(fp, "[%s]->", curr->data);
        curr = curr->next;
    }
    fprintf(fp, "NULL");
    fclose(fp);
}


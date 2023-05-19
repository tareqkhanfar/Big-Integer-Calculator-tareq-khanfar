#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct LinkedList {
    Node* head;
    Node* tail;
    int isNegative;
} LinkedList;

LinkedList* NewLinkedList() {
    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
    list->head = list->tail = NULL;
    list->isNegative = 0;
    return list;
}

LinkedList* CopyLinkedList(LinkedList* original) {
    LinkedList* copy = NewLinkedList();

    if (!original || !original->head) {
        return copy;
    }

    Node* curNode = original->head;
    while (curNode) {
        AddNodeToEnd(copy, curNode->data);
        curNode = curNode->next;
    }

    return copy;
}

Node* NewNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void AddNodeToFront(LinkedList* list, int data) {
    Node* newNode = NewNode(data);

    if (!list->head) {
        list->head = list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
}

void AddNodeToEnd(LinkedList* list, int data) {
    Node* newNode = NewNode(data);

    if (!list->head) {
        list->head = list->tail = newNode;
    } else {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
}

LinkedList* SubtractLinkedLists(LinkedList* list1, LinkedList* list2) {
    // Omitted for brevity
}

int CompareLinkedLists(LinkedList* list1, LinkedList* list2) {
    // Omitted for brevity
}

void PrintLinkedList(LinkedList* list) {
    Node* curNode = list->head;
    if (list->isNegative) {
        printf("-");
    }

    while (curNode) {
        printf("%d", curNode->data);
        curNode = curNode->next;
    }
    printf("\n");
}

LinkedList* AddLinkedLists(LinkedList* list1, LinkedList* list2) {
    // Omitted for brevity
}

void RemoveLeadingZeros(LinkedList* list) {
    // Omitted for brevity
}

LinkedList* MultiplyLinkedLists(LinkedList* list1, LinkedList* list2) {
    // Omitted for brevity
}

int CompareLengths(LinkedList* list1, LinkedList* list2) {
    // Omitted for brevity
}

LinkedList* DivideLinkedLists(LinkedList* list1, LinkedList* list2) {
    // Omitted for brevity
}

void FreeLinkedList(LinkedList* list) {
    // Omitted for brevity
}

int LinkedListLength(LinkedList* list) {
    // Omitted for brevity
}

int IsSmaller(LinkedList* list1, LinkedList* list2) {
    // Omitted for brevity
}

int IsGreater(LinkedList* list1, LinkedList* list2) {
    // Omitted for brevity
}

LinkedList* ReadDataFromFile(const char* filename) {
    // Omitted for brevity
}

int main()
{
    LinkedList* list1 = readDataFromFile("num1.txt");
    LinkedList* list2 = readDataFromFile("num2.txt");

    printf("First Number From File: ");
    printList(list1);
    printf("\n#######################################################################################\n");

    printf("Second Number From File: ");
    printList(list2);
    printf("\n##################################################################################################\n");

    int choice;

    do
    {
        printf("1- Addition\n");
        printf("2- Subtraction\n");
        printf("3- Multiplication\n");
        printf("4- Division\n");
        printf("5- Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            LinkedList* addition = AddToList(list1, list2);
            printf("Addition Result: ");
            printList(addition);
            freeList(addition); // Clear memory after using the list
            break;
        }
        case 2:
        {
            LinkedList* subtraction = subtractToList(list1, list2);
            printf("Subtraction Result: ");
            printList(subtraction);
            freeList(subtraction); // Clear memory after using the list
            break;
        }
        case 3:
        {
            LinkedList* multiplication = MultiblyToList(list1, list2);
            printf("Multiplication Result: ");
            printList(multiplication);
            freeList(multiplication); // Clear memory after using the list
            break;
        }
        case 4:
        {
            LinkedList* division = devideToList(list1, list2);
            printf("Division Result: ");
            printList(division);
            freeList(division); // Clear memory after using the list
            break;
        }
        case 5:
        {
            printf("Exiting the program.\n");
            break;
        }
        default:
        {
            printf("Invalid choice. Please try again.\n");
            break;
        }
        }
    }
    while (choice != 5);

    // Clear memory after finishing with the lists
    freeList(list1);
    freeList(list2);

    return 0;
}


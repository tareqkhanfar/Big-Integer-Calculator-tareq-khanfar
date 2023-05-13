#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node
{
    int data;
    struct Node* next;
    struct Node* prev;
};


struct LinkedList
{
    struct Node* head;
    struct Node* tail;
    bool isNegative;

};
struct LinkedList* createLinkedList() {
    struct LinkedList* newList = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    newList->isNegative = false;

    return newList;
}

struct LinkedList* copyLinkedList(struct LinkedList* original) {
    struct LinkedList* copy = createLinkedList();

    if (original == NULL || original->head == NULL) {
        return copy;
    }

    struct Node* current = original->head;
    while (current != NULL) {
        append(copy, current->data);
        current = current->next;
    }

    return copy;
}


struct Node* createNode(int data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}
void append(struct LinkedList* list, int data);
void prepend(struct LinkedList* list, int data) {
    struct Node* newNode = createNode(data);

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
}


void append(struct LinkedList* list, int data) {
 struct Node* newNode = createNode(data);


    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
        return;
    }

    list->tail->next = newNode;
    newNode->prev = list->tail;
    list->tail = newNode;
}



struct LinkedList* subtractLinkedLists(struct LinkedList* list1, struct LinkedList* list2) {
    struct LinkedList* result = createLinkedList();

    // Check if both lists are empty
    if (list1->head == NULL && list2->head == NULL) {
        prepend(result, 0);
        return result;
    }

    // Check if only list2 is empty
    if (list2->head == NULL) {
        return list1;
    }

    // Check if only list1 is empty
    if (list1->head == NULL) {
        list2->isNegative = !list2->isNegative;
        return list2;
    }

    // Check if list2 is greater than list1
    if (isGreaterOrEqual(list2, list1)) {
        struct LinkedList* temp = list1;
        list1 = list2;
        list2 = temp;
        list2->isNegative = !list2->isNegative;
    }

    struct Node* p1 = list1->tail;
    struct Node* p2 = list2->tail;
    int borrow = 0;

    while (p1 != NULL && p2 != NULL) {
        int data1 = p1->data;
        int data2 = p2->data;

        int diff = data1 - data2 - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
           prepend(result, diff);

        p1 = p1->prev;
        p2 = p2->prev;
    }

    // Copy the remaining digits from list1 to the result
    while (p1 != NULL) {
        int diff = p1->data - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        prepend(result, diff);

        p1 = p1->prev;
    }

    removeLeadingZeros(result);

    if (list2->isNegative) {
        result->isNegative = true;
    }

    return result;
}

int isGreaterOrEqual(struct LinkedList* list1, struct LinkedList* list2) {
    int length1 = getLinkedListLength(list1);
    int length2 = getLinkedListLength(list2);

    // If list1 has more digits than list2, it is definitely greater
    if (length1 > length2) {
        return true;
    }
    // If list2 has more digits than list1, it is definitely greater
    else if (length1 < length2) {
        return 0;
    }
    else {
        // Traverse the lists from most significant digit to least significant digit
        struct Node* node1 = list1->head;
        struct Node* node2 = list2->head;

        while (node1 != NULL && node2 != NULL) {
            // Compare the digits
            if (node1->data > node2->data) {
                return 1;
            }
            else if (node1->data < node2->data) {
                return 0;
            }

            // Move to the next digits
            node1 = node1->next;
            node2 = node2->next;
        }

        // If we reach this point, the lists are equal
        return 1;
    }
}


void display(struct LinkedList* list)
{
    struct Node* current = list->head;
    if (list->isNegative) {
    printf("-");
}

    while (current != NULL)
    {
        printf("%d", current->data);
        current = current->next;
    }
    printf("\n");
}

struct LinkedList* add_linked_lists(struct LinkedList* list1, struct LinkedList* list2)
{
    struct LinkedList* result = createLinkedList();
    struct Node* ptr1 = list1->tail;
    struct Node* ptr2 = list2->tail;
    int carry = 0;

    while (ptr1 != NULL || ptr2 != NULL)
    {
        int num1 = (ptr1 != NULL) ? ptr1->data : 0;
        int num2 = (ptr2 != NULL) ? ptr2->data : 0;

        int total = num1 + num2 + carry;
        carry = total / 10;
        int digit = total % 10;

        prepend(result, digit);

        if (ptr1 != NULL)
            ptr1 = ptr1->prev;
        if (ptr2 != NULL)
            ptr2 = ptr2->prev;
    }

    if (carry)
        prepend(result, carry);

    return result;
}


void removeLeadingZeros(struct LinkedList* list) {
    struct Node* current = list->head;

    // Traverse the list until a non-zero digit is encountered or the end of the list is reached
    while (current != NULL && current->data == 0) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }

    // Update the head of the list
    list->head = current;

    // If the list is empty, update the tail as well
    if (current == NULL) {
        list->tail = NULL;
    }
}


struct LinkedList* multiply_linked_lists(struct LinkedList* list1, struct LinkedList* list2)
{
    struct LinkedList* result = createLinkedList();
    struct Node* ptr2 = list2->tail;
    int offset = 0;

    while (ptr2 != NULL)
    {
        int num2 = ptr2->data;
        struct Node* ptr1 = list1->tail;
        int carry = 0;
        struct LinkedList* temp_result = createLinkedList();

        while (ptr1 != NULL)
        {
            int num1 = ptr1->data;
            int product = num1 * num2 + carry;
            carry = product / 10;
            int digit = product % 10;
            prepend(temp_result, digit);
            ptr1 = ptr1->prev;
        }
        if (carry)
            prepend(temp_result, carry);

        for (int i = 0; i < offset; i++)
            prepend(temp_result, 0);

        result = add_linked_lists(result, temp_result);
        ptr2 = ptr2->prev;
        offset++;
    }

    return result;
}
int is_greater(struct LinkedList* list1, struct LinkedList* list2);

struct LinkedList* divide_linked_lists(struct LinkedList* list1, struct LinkedList* list2) {
    // Check for division by zero


    // Create a new linked list to store the division result
    struct LinkedList* result = createLinkedList();

    // Check if the dividend is smaller than the divisor
    if (isSmaller(list1, list2)) {
        append(result, 0);
        return result;
    }

    // Copy the dividend and divisor lists
    struct LinkedList* dividend = copyLinkedList(list1);
    struct LinkedList* divisor = copyLinkedList(list2);

    // Initialize variables for long division
    struct Node* dividendNode = dividend->head;
    int dividendLength = getLinkedListLength(dividend);
    int divisorLength = getLinkedListLength(divisor);
    struct LinkedList* tempDividend = createLinkedList();
    int carry = 0;
    int quotient = 0;

    // Perform long division on the linked lists
    while (dividendNode != NULL) {
        // Append the next digit from the dividend to the temporary dividend
        append(tempDividend, dividendNode->data);

        // Check if the temporary dividend is greater than or equal to the divisor
        if (isGreaterOrEqual(tempDividend, divisor)) {
            // Perform subtraction to find the quotient digit
            quotient = 0;
            while (isGreaterOrEqual(tempDividend, divisor)) {
                tempDividend = subtractLinkedLists(tempDividend, divisor);
                quotient++;
            }
        } else {
            // The quotient digit is 0
            quotient = 0;
        }

        // Add the quotient digit to the result list
        append(result, quotient);

        // Move to the next digit of the dividend
        dividendNode = dividendNode->next;
    }

    // Handle the case when the dividend is less than the divisor
    if (result->head == NULL) {
        append(result, 0);

    }

    // Clean up memory
    freeLinkedList(dividend);
    freeLinkedList(divisor);
    freeLinkedList(tempDividend);

    return result;
}

void freeLinkedList(struct LinkedList* list) {
    if (list == NULL) {
        return;
    }

    struct Node* current = list->head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }

    free(list);
}
int getLinkedListLength(struct LinkedList* list) {
    if (list == NULL || list->head == NULL) {
        return 0;  // Return 0 if the list is empty
    }

    int length = 0;
    struct Node* current = list->head;

    while (current != NULL) {
        length++;
        current = current->next;
    }

    return length;
}


int isSmaller(struct LinkedList* list1, struct LinkedList* list2) {
    int length1 = getLinkedListLength(list1);
    int length2 = getLinkedListLength(list2);

    if (length1 < length2) {
        return 1;
    } else if (length1 > length2) {
        return 0;
    } else {
        struct Node* current1 = list1->head;
        struct Node* current2 = list2->head;

        while (current1 != NULL && current2 != NULL) {
            if (current1->data < current2->data) {
                return 1;
            } else if (current1->data > current2->data) {
                return 0;
            }

            current1 = current1->next;
            current2 = current2->next;
        }

        return 0;
    }
}

int is_greater(struct LinkedList* list1, struct LinkedList* list2) {
    struct Node* ptr1 = list1->head;
    struct Node* ptr2 = list2->head;

    if (list1->head == NULL && list2->head == NULL)
        return 0;

    if (list1->head == NULL)
        return 0;

    if (list2->head == NULL)
        return 1;

    while (ptr1 != NULL && ptr2 != NULL) {
        if (ptr1->data > ptr2->data)
            return 1;
        else if (ptr1->data < ptr2->data)
            return 0;

        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    // If we reach this point, it means the lists have the same digits
    // but one list might have more digits than the other
    if (ptr1 != NULL)
        return 1;
    if (ptr2 != NULL)
        return 0;

    return 0; // Lists are equal
}

struct LinkedList* readNumbersFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return NULL;
    }

    struct LinkedList* list = createLinkedList();
    int num;
    while (fscanf(file, "%d", &num) == 1) {
        if (num != -1) {
            append(list, num);
        }
    }

    fclose(file);
    return list;
}





int main()
{
struct LinkedList* list1 = readNumbersFromFile("num1.txt");
struct LinkedList* list2 = readNumbersFromFile("num2.txt");



display(list1);
display(list2);
// Add numbers to the linked lists

    int choice;



    do {
        printf("\n----- MENU -----\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Division\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
             case 1: {
                struct LinkedList* addition = add_linked_lists(list1, list2);
                printf("Addition Result: ");
                display(addition);
                break;
            }
            case 2: {
                                struct LinkedList* subtraction = subtractLinkedLists(list1, list2);
                printf("Subtraction Result: ");
                display(subtraction);
                break;
            }
            case 3: {
                struct LinkedList* multiplication = multiply_linked_lists(list1, list2);
                printf("Multiplication Result: ");
                display(multiplication);
                break;
            }
            case 4: {
                struct LinkedList* division = divide_linked_lists(list1, list2);
                printf("Division Result: ");
                display(division);
                break;
            }
            case 5: {
                printf("Exiting the program.\n");
                break;
            }
            default: {
                printf("Invalid choice. Please try again.\n");
                break;
            }
        }
    } while (choice != 5);

    return 0;
}



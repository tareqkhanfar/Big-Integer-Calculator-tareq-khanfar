#include <stdio.h>
#include <stdlib.h>

struct LinkedList* getSmallerList(struct LinkedList* list1, struct LinkedList* list2);
struct LinkedList* getGreaterList(struct LinkedList* list1, struct LinkedList* list2);
void addLast(struct LinkedList* list, int data);

struct Node
{
    int data; // contain the number from file
    struct Node* next; // to pointing to the next node
    struct Node* prev;// to pointing to the prev node
};

struct LinkedList
{
    struct Node* head;// pointer  first Node
    struct Node* tail; // pointer  last node
    int isNegative;// flag to determining if the list is negative or positive

};
struct LinkedList* createLinkedList()
// this is a method to create new LinkedList in memoery
{
    struct LinkedList* newList = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    newList->isNegative = 0;

    return newList;
}

struct LinkedList* LinkedListCopy(struct LinkedList* original)

// this method take a list and then return new List different pointer with Original list
{
    struct LinkedList* copy = createLinkedList();

    if (original == NULL || original->head == NULL)
    {
        return copy;
    }

    struct Node* current = original->head;
    while (current != NULL)
    {
        addLast(copy, current->data);
        current = current->next;
    }

    return copy;
}


struct Node* createNewNode(int data)
{

    // create new Node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}


void addFirst(struct LinkedList* list, int data)
{
    struct Node* newNode = createNewNode(data);

    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
}


void addLast(struct LinkedList* list, int data)
{
    struct Node* newNode = createNewNode(data);


    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
        return;
    }

    list->tail->next = newNode;
    newNode->prev = list->tail;
    list->tail = newNode;
}



struct LinkedList* subtractToList(struct LinkedList* list1, struct LinkedList* list2)
{
    struct LinkedList* result = createLinkedList();

    // Check if both lists are empty
    if (list1->head == NULL && list2->head == NULL)
    {
        addFirst(result, 0);
        return result;
    }

    // Check if only list2 is empty
    if (list2->head == NULL)
    {
        return list1;
    }

    // Check if only list1 is empty
    if (list1->head == NULL)
    {
        list2->isNegative = !list2->isNegative;
        return list2;
    }

    // Check if list2 is greater than list1
    if (isGreaterOrEqual(list2, list1))
    {
        struct LinkedList* temp = list1;
        list1 = list2;
        list2 = temp;
        list2->isNegative = !list2->isNegative;
    }

    struct Node* p1 = list1->tail;
    struct Node* p2 = list2->tail;
    int borrow = 0;

    while (p1 != NULL && p2 != NULL)
    {
        int data1 = p1->data;
        int data2 = p2->data;

        int different = data1 - data2 - borrow;

        if (different < 0)
        {
            different += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        addFirst(result, different);

        p1 = p1->prev;
        p2 = p2->prev;
    }

    // Copy the remaining digits from list1 to the result
    while (p1 != NULL)
    {
        int diff = p1->data - borrow;

        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        addFirst(result, diff);

        p1 = p1->prev;
    }

    removeLeadingZeros(result);

    if (list2->isNegative)
    {
        result->isNegative = 1;
    }

    return result;
}

int isGreaterOrEqual(struct LinkedList* list1, struct LinkedList* list2)
{
    int length1 = getLength(list1);
    int length2 = getLength(list2);

    // If list1 has more digits than list2, it is definitely greater
    if (length1 > length2)
    {
        return 1;
    }
    // If list2 has more digits than list1, it is definitely greater
    else if (length1 < length2)
    {
        return 0;
    }
    else
    {
        // Traverse the lists from most significant digit to least significant digit
        struct Node* node1 = list1->head;
        struct Node* node2 = list2->head;

        while (node1 != NULL && node2 != NULL)
        {
            // Compare the digits
            if (node1->data > node2->data)
            {
                return 1;
            }
            else if (node1->data < node2->data)
            {
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


void printList(struct LinkedList* list)
{
    struct Node* current = list->head;
    if (list->isNegative)
    {
        printf("-");
    }

    while (current != NULL)
    {
        printf("%d", current->data);
        current = current->next;
    }
    printf("\n");
}

struct LinkedList* AddToList(struct LinkedList* list1, struct LinkedList* list2)
{
    struct LinkedList* result = createLinkedList();
    struct Node* ptr1 = list1->tail;
    struct Node* ptr2 = list2->tail;
    int carry = 0;

    while (ptr1 != NULL || ptr2 != NULL)
    {
        int num1 ;
        int num2 ;

        if (ptr1 != NULL ) {
            num1 = ptr1->data ;
        }else {
        num1 = 0 ;
        }
         if (ptr2 != NULL ) {
            num2 = ptr2->data ;
        }else {
        num2 = 0 ;
        }

        int total = num1 + num2 + carry;
        carry = total / 10;
        int digit = total % 10;

        addFirst(result, digit);

        if (ptr1 != NULL)
            ptr1 = ptr1->prev;
        if (ptr2 != NULL)
            ptr2 = ptr2->prev;
    }

    if (carry)
        addFirst(result, carry);

    return result;
}


void removeLeadingZeros(struct LinkedList* list)
{
    struct Node* current = list->head;

    // Traverse the list until a non-zero digit is encountered or the end of the list is reached
    while (current != NULL && current->data == 0)
    {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }

    // Update the head of the list
    list->head = current;

    // If the list is empty, update the tail as well
    if (current == NULL)
    {
        list->tail = NULL;
    }
}


struct LinkedList* MultiblyToList(struct LinkedList* list1, struct LinkedList* list2)
{
    struct LinkedList* result = createLinkedList();
    struct Node* ptr2 = list2->tail;
    int offset = 0;

    while (ptr2 != NULL)
    {
        struct Node* ptr1 = list1->tail;
        struct LinkedList* temp_result = createLinkedList();

        for (int i = 0; i < offset; i++)
        {
            addFirst(temp_result, 0);
        }

        int carry = 0;

        while (ptr1 != NULL)
        {
            int product = ptr1->data * ptr2->data + carry;
            int digit = product % 10;
            carry = product / 10;

            addFirst(temp_result, digit);
            ptr1 = ptr1->prev;
        }

        if (carry != 0)
        {
            addFirst(temp_result, carry);
        }

        result = AddToList(result, temp_result);
        freeLinkedList(temp_result);
        ptr2 = ptr2->prev;
        offset++;
    }

    return result;
}

int is_greater(struct LinkedList* list1, struct LinkedList* list2);

struct LinkedList* devideToList(struct LinkedList* list1, struct LinkedList* list2)
{
    // Check for division by zero


    // Create a new linked list to store the division result
    struct LinkedList* result = createLinkedList();

    // Check if the dividend is smaller than the divisor
    if (isSmaller(list1, list2))
    {
        addLast(result, 0);
        return result;
    }

    // Copy the dividend and divisor lists
    struct LinkedList* dividend = LinkedListCopy(list1);
    struct LinkedList* divisor = LinkedListCopy(list2);

    // Initialize variables for long division
    struct Node* dividendNode = dividend->head;
    int dividendLength = getLength(dividend);
    int divisorLength = getLength(divisor);
    struct LinkedList* tempDividend = createLinkedList();
    int carry = 0;
    int quotient = 0;

    // Perform long division on the linked lists
    while (dividendNode != NULL)
    {
        // addLast the next digit from the dividend to the temporary dividend
        addLast(tempDividend, dividendNode->data);

        // Check if the temporary dividend is greater than or equal to the divisor
        if (isGreaterOrEqual(tempDividend, divisor))
        {
            // Perform subtraction to find the quotient digit
            quotient = 0;
            while (isGreaterOrEqual(tempDividend, divisor))
            {
                tempDividend = subtractToList(tempDividend, divisor);
                quotient++;
            }
        }
        else
        {
            // The quotient digit is 0
            quotient = 0;
        }

        // Add the quotient digit to the result list
        addLast(result, quotient);

        // Move to the next digit of the dividend
        dividendNode = dividendNode->next;
    }

    // Handle the case when the dividend is less than the divisor
    if (result->head == NULL)
    {
        addLast(result, 0);

    }

    // Clean up memory
    freeLinkedList(dividend);
    freeLinkedList(divisor);
    freeLinkedList(tempDividend);

    return result;
}

void freeLinkedList(struct LinkedList* list)
{
    if (list == NULL)
    {
        return;
    }

    struct Node* current = list->head;
    while (current != NULL)
    {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }

    free(list);
}
int getLength(struct LinkedList* list)
{
    if (list == NULL || list->head == NULL)
    {
        return 0;  // Return 0 if the list is empty
    }

    int length = 0;
    struct Node* current = list->head;

    while (current != NULL)
    {
        length++;
        current = current->next;
    }

    return length;
}


int isSmaller(struct LinkedList* list1, struct LinkedList* list2)
{
    int length1 = getLength(list1);
    int length2 = getLength(list2);

    if (length1 < length2)
    {
        return 1;
    }
    else if (length1 > length2)
    {
        return 0;
    }
    else
    {
        struct Node* current1 = list1->head;
        struct Node* current2 = list2->head;

        while (current1 != NULL && current2 != NULL)
        {
            if (current1->data < current2->data)
            {
                return 1;
            }
            else if (current1->data > current2->data)
            {
                return 0;
            }

            current1 = current1->next;
            current2 = current2->next;
        }

        return 0;
    }
}

int is_greater(struct LinkedList* list1, struct LinkedList* list2)
{
    struct Node* ptr1 = list1->head;
    struct Node* ptr2 = list2->head;

    if (list1->head == NULL && list2->head == NULL)
        return 0;

    if (list1->head == NULL)
        return 0;

    if (list2->head == NULL)
        return 1;

    while (ptr1 != NULL && ptr2 != NULL)
    {
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

 void  readDataFromFile(const char* filename , struct LinkedList** list1 , struct LinkedList** list2)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return NULL;
    }

    struct LinkedList* list[100];

    int num;

    int index = 0 ;
    char ch = ' ' ;
    char sign = ' ';
    list[0] = createLinkedList() ;
    fscanf(file, "%c" , &sign);
    list[index]->isNegative = (sign == '-');

    while (fscanf(file, "%d%c" , &num , &ch) == 2)
    {
      if (sign == '-'){
        list[index]->isNegative = 1 ;
      }
      else if (sign == '+'){
        list[index]->isNegative = 0;
      }
            addLast(list[index], num);


        if (ch == '\n') {
            index++;
          list[index] = createLinkedList() ;

              fscanf(file, "%c" , &sign);

            list[index]->isNegative = (sign == '-');


        }

        printf("%d\n" , index);
    }
*list1 = list[0] ;
*list2 = list[1];
  for (int i = 0; i <= index-1; i++)
    {
        printf("Linked List %d: ", i);
        printList(list[i]);
        printf("\n");
    }

    fclose(file);
}



void ControllerAddition (struct LinkedList* list1 ,struct LinkedList* list2) {

if (list1->isNegative == 0 && list2->isNegative == 0) {
        struct LinkedList* result = AddToList (list1 , list2 );


    // addition
}
else if ((list1->isNegative = 1 && list2->isNegative == 0 )|| (list1->isNegative = 0 && list2->isNegative == 1) ) {
struct    LinkedList* max = getGreaterList (list1 , list2) ;
 struct   LinkedList* min = getSmallerList (list1 , list2) ;
  struct LinkedList* result =  subtractToList(max , min) ;
   result->isNegative = max->isNegative ;
}
else if (list1->isNegative = 1 && list2->isNegative == 1){

struct LinkedList* result = AddToList(list1 , list2) ;
result->isNegative = list1->isNegative ;

}


}

void ControllerSubtraction (struct LinkedList* list1 , struct LinkedList* list2) {

if (list1->isNegative == 0 && list2->isNegative == 0){ // + +
struct LinkedList* max = getGreaterList (list1 , list2) ;
 struct LinkedList* min = getSmallerList (list1 , list2) ;
  struct LinkedList* result =  subtractToList(max , min) ;
   result->isNegative = max->isNegative ;
}
else if (list1->isNegative == 1 && list2 ->isNegative == 0) { // - +
  struct LinkedList* result = AddToList(list1 , list2) ;
result->isNegative = list1->isNegative ;
}
else if (list1->isNegative == 1 && list2->isNegative ==1){ // - -
    struct    LinkedList* max = getGreaterList (list1 , list2) ;
 struct   LinkedList* min = getSmallerList (list1 , list2) ;
  struct LinkedList* result =  subtractToList(max , min) ;
   result->isNegative = max->isNegative ;
}
else if (list1->isNegative==0 && list2->isNegative == 1) {
 struct LinkedList* result = AddToList (list1 , list2 );

}


}

void ControllerMultiblication (struct LinkedList* list1 , struct LinkedList* list2) {

if ((list1->isNegative == 0 && list2->isNegative == 0)||(list1->isNegative == 1 && list2->isNegative == 1)) {
    struct LinkedList* result = MultiblyToList(list1 , list2);

}
else if ((list1->isNegative == 1 && list2 ->isNegative == 0) || (list1->isNegative == 0 && list2 ->isNegative == 1)) {
          struct LinkedList* result = MultiblyToList(list1 , list2);
          result->isNegative = 1 ;

}


}

void ControllerDivision (struct LinkedList* list1 , struct LinkedList* list2) {

if ((list1->isNegative == 0 && list2->isNegative == 0)||(list1->isNegative == 1 && list2->isNegative == 1)) {
    struct LinkedList* result = devideToList(list1 , list2);

}
else if ((list1->isNegative == 1 && list2 ->isNegative == 0) || (list1->isNegative == 0 && list2 ->isNegative == 1)) {
          struct LinkedList* result = devideToList(list1 , list2);
          result->isNegative = 1 ;

}

}

struct LinkedList* getGreaterList(struct LinkedList* list1, struct LinkedList* list2)
{
    struct Node* curr1 = list1->head;
    struct Node* curr2 = list2->head;

    while (curr1 != NULL && curr2 != NULL)
    {
        if (curr1->data > curr2->data)
            return list1;
        else if (curr2->data > curr1->data)
            return list2;

        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    // If both lists have the same elements up to this point,
    // the greater list is the one with more elements
    if (curr1 != NULL)
        return list1;
    else if (curr2 != NULL)
        return list2;

    // If both lists have the same elements and length, return any list
    return list1;
}


struct LinkedList* getSmallerList(struct LinkedList* list1, struct LinkedList* list2)
{
    struct Node* curr1 = list1->head;
    struct Node* curr2 = list2->head;

    while (curr1 != NULL && curr2 != NULL)
    {
        if (curr1->data < curr2->data)
            return list1;
        else if (curr2->data < curr1->data)
            return list2;

        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    // If both lists have the same elements up to this point,
    // the smaller list is the one with fewer elements
    if (curr1 != NULL)
        return list2;
    else if (curr2 != NULL)
        return list1;

    // If both lists have the same elements and length, return any list
    return list1;
}


int main()
{
    struct LinkedList* list1 = createLinkedList() ;

      struct LinkedList* list2 = createLinkedList();
     readDataFromFile("num1.txt" , &list1 , &list2);

     printList(list1) ;
     printList(list2);


    printf ("First Number From File : ") ;
    printList(list1);
        printf ("\n#######################################################################################\n") ;

    printf ("Second Number From File : ") ;

    printList(list2);
printf ("\n##################################################################################################\n") ;

// Add numbers to the linked lists

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
            struct LinkedList* addition = AddToList(list1, list2);
            printf("Addition Result: ");
            printList(addition);
            break;
        }
        case 2:
        {
            struct LinkedList* subtraction = subtractToList(list1, list2);
            printf("Subtraction Result: ");
            printList(subtraction);
            break;
        }
        case 3:
        {
            struct LinkedList* multiplication = MultiblyToList(list1, list2);
            printf("Multiplication Result: ");
            printList(multiplication);
            break;
        }
        case 4:
        {
            struct LinkedList* division = devideToList(list1, list2);
            printf("Division Result: ");
            printList(division);
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

    return 0;
}



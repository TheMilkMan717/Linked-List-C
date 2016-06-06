//FILE: srsproject_10.c
//NAME: Steven Sakol
//DATE: 11/26/2014
//PURPOSE: This program is a continuation of project 9.  It adds functionality to option 2 and option 5.
//         In option 2, the user can create a new file or use an existing file to load into the Linked List.
//         In option 5, the user can print out the contents of the list to the screen.

#include <stdio.h>
#include <stdlib.h>

//MAXNUMBERLENGTH is 6 to have a max of 5 digits including '+' and '-', and an extra space for null terminator
const int MAXNUMBERLENGTH = 6;

struct Structure_List{
    int dataItem;
    struct Structure_List *nextNode;
};

typedef struct Structure_List node;

void function1();
void enterKeyboard(node *firstNode);
void function3();
void function4();
void printList(node *firstNode);
void function6();

node *initializeNode(node *node);
int validation(char numbers[MAXNUMBERLENGTH]);
int addToList(char input[MAXNUMBERLENGTH], node *firstNode);
int convertToInt(char input[MAXNUMBERLENGTH]);

int main(void)
{
    //holds the user's menu option selection
    char input[2];

    
    //header
    printf("\t\t\tLinked List Program\n\nThis program puts numbers in a Linked List in ascending order.\nIt allows the user to load the List from an existing file,\ncreate a new file and enter numbers into it, or to enter\nnumbers one at a time from the keyboard.  Numbers can then be\nadded to or removed from the List until the user decides they\nare finished at which time the List can be printed and the\nordered numbers can be written to the file \"ordered.txt\"");
    
    system("PAUSE");
    
    //creates a variable that will start the Linked List
    node *firstNode = NULL;
    
    //displays the menu until the user enters in the command to quit the program
    do{
        system("cls");
        //menu
        printf("\nMenu\n\n1: Empty the List\n2: Load the List from the \"linked.txt\" file\n3: Add a number to the list\n4: Remove a number from the list\n5: Print the list\n6: Write the list to the \"ordered.txt\" file\nQ to quit\n\n");
        printf("Enter in a menu option: ");
        //takes user input and "ignores" everything after the first character by putting a null character in position 1
        scanf("%s", input);
        input[1] = '\0';
        
        //input validation
        while(input[0] != '1' && input[0] != '2' && input[0] != '3' && input[0] != '4' && input[0] != '5' && input[0] != '6' && (input[0] != 'Q' && input[0] != 'q')){
            printf("\n\nPlease enter in a valid menu option: ");
            scanf("%s", input);
            input[1] = '\0';
        }//end while
        
        //uses the input to call the appropriate function
        switch(input[0]){
            case '1':
                //function1();
                break;
            case '2':
                //initializes the firstNode every time Option 2 is called
                firstNode = initializeNode(firstNode);
                enterKeyboard(firstNode);
                break;
            case '3':
                //function3();
                break;
            case '4':
                //function4();
                break;
            case '5':
                printList(firstNode);
                break;
            case '6':
                //function6();
                break;
            default:
                break;
        }//end switch
    }//end do
    while((input[0] != 'Q') && (input[0] != 'q'));

    return 0;
}//end main

void function1(){
    
}

void enterKeyboard(node *firstNode){
    char option[2];

    printf("\nWould you like to enter data into the file, or would you like to load an existing file into the list? (N for new file, E to load an existing file): ");
    scanf("%s", option);
    option[1] = '\0';
    
    //input validation
    while(option[0] != 'N' && option[0] != 'n' && option[0] != 'E' && option[0] != 'e'){
        printf("\n\nPlease enter in a valid option (N for new file, E to load an existing file): ");
        scanf("%s", option);
        option[1] = '\0';
    }//end validation
    
    if(option[0] == 'N' || option[0] == 'n'){
        //char array that will hold the user's input
        char numbers[MAXNUMBERLENGTH];
        
        //creates and opens the "linked.txt" file
        FILE *outputStream = fopen("linked.txt", "w");
        
        printf("\n\nEnter in a series of numbers(one at a time) up to 5 digits long (Including a sign).\nType X when finished.\n");
        
        //asks for input until the user enters the command to quit the function
        do{
            printf("\n-->> ");
            scanf("%s", numbers);
            
            //acts as a boolean to keep track of the validity of the input
            int invalid = validation(numbers);
            
            //if the user input is an 'x' or 'X', break
            if((strcmp(numbers, "x") == 0) || (strcmp(numbers, "X") == 0)){
                break;
            }//end if
            else{
                //if the input is less than 5 digits (not including '+' or '-')
                if(strlen(numbers) <= MAXNUMBERLENGTH){
                    if(!invalid){
                        fprintf(outputStream, "%s\n", numbers);
                    }//end if
                }//end if
            }//end else
        }//end do
        while((strcmp(numbers, "x") != 0) && (strcmp(numbers, "X") != 0));
        
        fclose(outputStream);
        
        //opens the file again to read to insert numbers into list
        FILE *inputStream = fopen("linked.txt", "r");
        
        //holds the input from the file
        char readInput[MAXNUMBERLENGTH];
        
        //reads until it reaches the end of file
        while(1){
            //reads the data in
            fscanf(inputStream, "%s", readInput);
            //checks for end of file and breaks if true
            if(feof(inputStream)){
                break;
            }
            int option = addToList(readInput, firstNode);
        }//end while
        
        fclose(inputStream);
        
    }//end if
    else if(option[0] == 'E' || option [0] == 'e'){
        FILE *existingFile = fopen("linked.txt", "r");
        
        if(existingFile){
            printf("\nLoading the \"linked.txt\" file.....\n");
            system("PAUSE");
            
            //holds the input from the file
            char readInput[MAXNUMBERLENGTH];
            
            //reads until it reaches the end of file
            while(1){
                //reads the data in
                fscanf(existingFile, "%s", readInput);
                //checks for end of file before it reads the file and breaks if true
                if(feof(existingFile)){
                    break;
                }//end if
                
                //boolean for input validation
                int invalid = validation(readInput);
                //if the input is valid, it will add it to the list
                if(!invalid){
                    //option is only used to store the return value
                    int option = addToList(readInput, firstNode);
                }//end if
            }//end while
            
            fclose(existingFile);

        }//end if
        else{
            printf("\n\nERROR FILE DOES NOT EXIST...\n\n");
            system("PAUSE");
        }//end else
        
    }//end else if
    else{
        printf("\n\nERROR in Processing\n\n");
        system("PAUSE");
    }//end else
    
    
}//end enterKeyboard()

void function3(){
    
}

void function4(){
    
}

void printList(node *firstNode){
    printf("\n\nThe Contents of the List\n\n");
    if(firstNode != NULL){
        //the traverseNode will act as a temporary node in order to read the dataItem for each item in the list
        node *traverseNode = initializeNode(NULL);
        traverseNode = firstNode -> nextNode;
        
        //the traverseNode is NULL at the end of the list
        while(traverseNode != NULL){
            printf("%i\n", (traverseNode -> dataItem));
            traverseNode = traverseNode -> nextNode;
        }//end while
    }//end if
    else{
        printf("\n\nNothing in Linked List...\n\n");
    }
    system("PAUSE");
}

void function6(){
    
}

node *initializeNode(node *node){
    //allocates space in memory for any node of the Linked List
    node = malloc(sizeof(node));
    node -> nextNode = NULL;
    //returns the node after initializing
    return node;
}//end initializeNode

int validation(char numbers[MAXNUMBERLENGTH]){
    //processes each character to determine the validity of the input
    int i;
    for(i = 0; i < strlen(numbers); i += 1){
        //if the input has a character other than a digit or '-' or '+'
        if(!isdigit(numbers[i]) && numbers[i] != '-' && numbers[i] != '+'){
            //the input is considered invalid
            return 1;
        }//end if
    }//end for
    
    return 0;
}//end validation

int addToList(char input[MAXNUMBERLENGTH], node *firstNode){
    //converts the char input to integer
    int convertedInteger = convertToInt(input);
    
    //creates the new node
    node *newNode = initializeNode(NULL);
    newNode -> dataItem = convertedInteger;

    //creates a temporary node to transverse list
    node *tempNode = initializeNode(NULL);
    
    //tempNode is pointing to the firstNode's nextNode(the first node in the Linked List) in order to transverse the list
    tempNode -> nextNode = firstNode -> nextNode;
    
    
    //Option 1 --> There is nothing in the Linked List
    if(firstNode -> nextNode == NULL){
        firstNode -> nextNode = newNode;
        return 1;
    }
    
    //Option 2 --> The New Node's dataItem is less than or equal to the first Node in the Linked List
    if((newNode -> dataItem) <= ((firstNode -> nextNode) -> dataItem)){
        firstNode -> nextNode = newNode;
        newNode -> nextNode = (tempNode -> nextNode);
        return 2;
    }
    
    int inserted = 0;
    
    //Options 3 and 4
    while(!inserted){
        //Option 3 --> The New Node is inserted in the middle of the Linked List
        //if the New Node is greater than an item and the next item is not null
        if((newNode -> dataItem) >= (tempNode -> dataItem) && ((tempNode -> nextNode) != NULL)){
            //if the New Node is less than or equal to the Next Node
            if((newNode -> dataItem) <= ((tempNode -> nextNode) -> dataItem)){
                newNode -> nextNode = tempNode -> nextNode;
                tempNode -> nextNode = newNode;
                inserted = 1;
                return 3;
            }//end if
        }//end if
        //Option 4 --> The New Node is inserted at the end of the Linked List
        else if((newNode -> dataItem) >= (tempNode -> dataItem) && (tempNode -> nextNode == NULL)){
            tempNode -> nextNode = newNode;
            inserted = 1;
            return 4;
        }
        tempNode = tempNode -> nextNode;
    }//end while
    
    return 0;
}//end addToList

int convertToInt(char input[MAXNUMBERLENGTH]){
    if(input[strlen(input) - 1] == '-'){
        return (atoi(input) * -1);
    }
    else{
        return atoi(input);
    }
}//end convertToInt
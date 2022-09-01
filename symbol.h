#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "macro.h"

#define SIZE 81
#define LABEL_SIZE 31

int IC /*Instructions counter */,DC /*Data counter */;

/*
 * Creating a linked list that stores the labels
 */
typedef struct label {
    char name[LABEL_SIZE];  /* Save the name of the label */
    char type[SIZE];        /* Save the type of the label (data,string,struct) */
    unsigned int adrs;      /* Save the address of the labels (MAIN,LOOP,END, etc) */
    int data[10];           /* Save the data of the label */
    struct label *next;     /* Pointer to the next list of labels */
}label;

char symbolName[SIZE];
/*
 * Creating a linked list that stores the operands
 */
typedef struct operand {
    int source;
    int target;
    struct operand *next;
}operand;

/* Creating a linked list that holds the
 * information of the operands for the encoding
 */
typedef struct kidud{
    int opcode;                     /* Save the command num in decimal */
    int source;                     /* Save the source num in decimal */
    int source_mion;                /* Save the source mion num in binary */
    int target_mion;                /* Save the target mion num in binary */
    int target;                     /* Save the target num in decimal */
    int ARE;                        /* Save the 'ARE' num  */
    int adrs;                       /* decimal*/
    char label_source[LABEL_SIZE];  /* Save the source label */
    char label_target[LABEL_SIZE];  /* Save the target label */
    struct kidud *next;             /* Pointer to the next list of kidud */
}kidud;

operand op;

typedef struct print{
    unsigned int adrs ;
    unsigned int code ;
    struct print *next;
}print;

/* Check if the first word in the line is a label
 * return 1 if it's a line with label
 * return 0 if it's NOT.
 */
int is_label(char line[]);

/* This function inserts the label type
 * and its name into the linked list
 * in the case of entry or extern labels
 */
void is_entry_or_extern(char line[], label *head);

/* Checking if the name (of the label)
 * we got is existed or not in the linked list of labels
 */
int check_if_exist(label **head, char *symbolName);

/* This func checks which operation(command) include
 * in the line and return is location in the command array
 */
int find_the_command(char line[],int flag);

/* This func check every char in the word and return 1
 * if the word include only low chars and 0 if not
 */
int is_commend(char *commend);

/* The func compare between the word she gets
* and the command array and checks if this word is a command or not
* if it is she return the location in the array
* if not she return -1
*/
int command_num(char *commend);

/* This function returns the number
 * of operands that each command should receive
 */
int  num_of_operand(int opcode);

/*
 * This function checks whether the list of operands is empty or not
 */
int check_if_empty(operand *head);

/*
 * This function generates a new list of labels and allocates memory for them.
 * If there is not enough memory an error message will be printed.
 * Returns an initialized label linked list.
 */
label *new_label();

/*
 * This function generates a new list of kidud and allocates memory .
 * If there is not enough memory an error message will be printed.
 * Returns an initialized kidud linked list.
 */
kidud *new_kidud();

/*
 * This function inserts the name of the
 * label into the linked list of labels
 */
void label_data_in(label **head , char *symbolN );
/*
 * This function returns the position in the direct array and this
 * indicates what type of sentence this is
 * (data, string, struct, entry, external).
 * If there is no match -1 will be returned
 */
int which_directives(char line[],int flag);

/*This function counts how many operands are
 * received in the line entered by counting commas (',').
 */
int count_num (char *commend,int flag);

/*
 * A function that checks whether the line is empty or not.
 * If empty, 1 will be returned
 * If not empty, 0 will be returned
 */
int empty_line(char *token,int i);

/*
 * This function checks whether the label is defined legally.
 * If the label is valid 1 will be returned.
 * If the label is invalid -1 will be returned
 * And if the received word is NULL, 0 will be returned
 */
int valid_label(char *token);

/* This function performs comparisons between the label names when confirmed
 * There are labels found during the lines of code.
 * If the name found matches the name of the label found in the linked list of labels, 1 will be returned.
 * If the name is not in the list, an error message will appear and the program will stop.
 *If it is an entry or extern label, 0 will be returned.
 */
int compare_labels(label *head, char *token,int addres);

/* This function counts the number of commas
 * found in the operands and returns the number of times found
 */
int count_psik(char *tok);

/* This function converts numbers from decimal base to binary base
 * and returns the binary number that will be received
 */
int decimal_to_bin(int num);

/* This function takes a binary
 * number and converts it to
 * a decimal number
 */
int binary_to_decimal(int bin_num);
/*
 * The function takes the number and raises it in the desired chest
 */

int power(int base, int exponent);






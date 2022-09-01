#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "symbol.h"

#define SIZE 81

/* This function performs a first pass over the file after deploying the macros
 * and begins the data storage process during the program.
 */
void first_check(FILE *file , label *head ,  label *tail , char *argv[] , int i);

/* This func check if the num of operands
 * that we get is equals to the number it
 * should be.
 * return 1 if it's true , 0if is false
 */
int two_operand(int have,int needs);

/* After we get a .data this func
 * get the data and set it into the right space in
 * the label
 */
void take_data( label *current,char line[]);

/* This fun get a string and convert it to a number*/
int from_char_to_int(char *token);

/* After we get a .string this func
 * get the data and set it into the right space in
 * the label
 */
void take_string( label *current,char line[]);

/* After we get a .struct this func
 * get the data and set it into the right space in
 * the label
 */
void take_struct( label *current,char line[]);

/* This function divides the received line into
 * parts and with the help of different operations
 * Extracts the relevant information from it and
 * enters it into the linked list of kidud
 */
void split_line(char line[],int from , kidud *khead);

/* This function returns the starting position of the next line
 * The label found (if found).
 * If there is no label and no row type then -1 will be returned
 */
int start_word(char line[]);
/*
 * This input function finds the relevant numbers in the row and returns them
 */

int take_numbersForlabel(char token[]);

/*
 * This input function finds the relevant numbers in the row and returns them
 */
int take_numbersForImmediate(char token[]);

/* This function traverses the line and looks for relevant information
 * in the resulting operands,
 * thereby storing the information in the appropriate linked lists.
 */
void find_the_label(char line[] , label *lcurrent , label **lhead , int opcode , kidud *khead);

/* This function iterates over the line and looks for the values
 * received in operands and registers.
 */
int find_numbers(char *tok);

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LABEL_SIZE 31
#define SIZE 81

#define START_MACRO 0
#define END_MACRO 1
#define REG_LINE 2
#define MACRO_DATA 3

/*
 * Creating a linked list to store the macros
 */
typedef struct macro{
    char macro_name[LABEL_SIZE]; /* Storing the names of the macros */
    char macro_data[SIZE]; /* Storing the data of the macros */
    struct macro *next; /* Pointer to the next list of macros */
}macro;


/*
 * this func is the pre-processor of the assembler.
 * she gets - argc and the argv (from the terminal),
 * the head of the macro's list,
 * the index from the main loop.
 * return a FILE after the layout of macros.
 */
FILE* go_to_work(int argc , char *argv[] , macro* mhead , int i);

/*
 * this func finds if the line include a macro definition or the end of it.
 * she gets - the current line to work on ,
 * a flag that represents if a macro or end macro is found ,
 * the head of macro list
 * and the current macro list to work on.
 * return an int :
 * 0 - if is a macro definition (start or during).
 * 1 - if is the end of the macro definition.
 * 2 - if it's a regular line.
 * 3 - if we recognize the macro name in the line, and it's not a macro definition.
 */
int macro_or_not(char line[] , int flag , macro *mcurrent,macro **mhead);

/*
 * This function inserts the macro's information into the appropriate place in the macro's linked list.
 * It gets the top of the macro list and also the name of the macro,
 * so that we can insert the information in the place that fits the name.
 * If the name of the macro is not in the list, NULL will be returned
 */
char *macro_data(char *macro_name, macro *head);

/*
 * This function generates a new list of macros and allocates memory for them.
 * If there is not enough memory an error message will be printed.
 * Returns an initialized macro linked list.
 */
macro *new_macro();

/* This function receives a line and "cleans" the spaces from the
 * beginning of the line to the first place
 * where there is a value that is not empty
 */
void clear_spaces (char *line);

/* This function receives a line
 * and where it detects /n it will
 * be replaced by /0.
 */
void end_line(char *line) ;

/* This function accepts 2 different strings
 * and concatenates them into a unified string.
 */
char *file_name(char *file , char *end_file);


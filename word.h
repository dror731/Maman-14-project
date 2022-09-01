#ifndef WORD
#define WORD

#include "first_check.h"


/* This function performs a second pass on the output file
 * we received after deploying the macros.
 * In this transition, the legality of the text is also
 * checked and sent to relevant functions at the end.
 * The values from the text will be inserted into the
 * appropriate linked lists, and thus we will reach
 * the step of printing the output files.
 */
void sentens(label *head  , kidud *khead , char *argv[] , int i);

/*In this function, we go over the names of the labels received
 * in the previous pass and if they are found to be identical to
 * the names in the current pass, then the address will be inserted into them
 */
void check_current(label **head);

/*
 *In this function I insert the appropriate values
 * of the various variables during the program into their appropriate places.
 *which we will use in the coding process
 * regarding the coding of the source variables
 */
void tipol_bekidud_source(kidud *khead , label *lhead);

/*
 *In this function I insert the appropriate values
 * of the various variables during the program into their appropriate places.
 *which we will use in the coding process
 * regarding the coding of the target variables
 */
void tipol_bekidud_target(kidud *khead , label *lhead);

/*
 * This function generates a new list to print in the end and allocates memory .
 * If there is not enough memory an error message will be printed.
 * Returns an initialized print linked list.
 */
print *new_print();

/*
 *In this function we assemble the lines of
 * coding that will eventually be printed to the output jumps
 */
void final_kidud(print *phead ,kidud *khead , label *lhead);
#endif

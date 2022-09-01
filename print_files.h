#ifndef PRINT_FILES
#define PRINT_FILES

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "word.h"

#define ON 1
#define OFF 0


/* This function is responsible for
 * outputting the appropriate output
 * files (ob,ext,ent).
*/
int go_to_print(print *phead , label *lhead , char *argv[] , int i);

/* With the help of this function we convert a number
 * to the corresponding value according to the symbol table defined for us
 * which is in base 32.
 * in the value that will be returned
 * is the value after the conversion of the number.
 */
char *convert_to_mozar(unsigned int adrs);



#endif

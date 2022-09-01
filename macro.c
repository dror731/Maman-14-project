#ifndef MACRO_C
#define MACRO_C
#include "macro.h"
/* ################################################# */
FILE* go_to_work(int argc , char *argv[],macro *mhead , int i){
    char line[SIZE] , *tok , tmp[SIZE] , space[]= " \t" ,*file_target = NULL ,*file_input = NULL;/*on this line we do our work */
    int flag = 0 ;
    FILE *fp , *target;


    macro* mcurrent , *mnew = NULL;
    mcurrent = mhead;
    mcurrent->next = mnew;
/* ----------------------------------------------- */
    memset(line, '\0', SIZE);
    memset(tmp, '\0', SIZE);
    if (argc < 2){
        puts("Error: Please enter a filename.");
        exit(0);
    }
/* ----------------------------------------------- */
        file_input = file_name(argv[i] , ".as\0");
        file_target = file_name(argv[i] , ".am\0");

        fp = fopen(file_input,"r");
        target = fopen(file_target ,"w+");

        while (fgets(line, SIZE - 1, fp)) {

            if (line[0] == ';')
                continue;

            switch (macro_or_not(line, flag, mcurrent , &mhead)) {
                case START_MACRO:
                    flag = 1; /* start fo the macro , flag ON*/
                    break;
                case END_MACRO:
                    flag = 0;/* end fo the macro , flag OFF*/
                    mnew = new_macro();
                    mcurrent->next = mnew;
                    mcurrent = mcurrent->next;
                    break;
                case REG_LINE:
                    if (flag == 0) {
                        fprintf(target, "%s", line); /* copy the line from the source file to the target file*/
                        break;
                    }else
                        break;
                case MACRO_DATA:
                    strcpy(tmp,line);
                    tok = strtok(tmp,space);
                    fprintf(target, "%s", macro_data(tok,mhead)); /* print the macro data instead of the macro mcurrent*/
                 break;
            }

        }
    fclose(fp);
    fclose(target);
    return target;
}
/* ################################################# */
int macro_or_not(char line[] , int flag , macro *mcurrent,macro **mhead){ /* this func check if we got a line that include a macro or macro data or endmacro*/
    char tmp[SIZE],mac[]= "macro",endmac[]= "endmacro\n",space[]= " \t";
    macro *new_mhead = *mhead;

    memset(tmp,'\0',SIZE);
    strcpy(tmp,line);

    clear_spaces(tmp);
    strtok(tmp, space);
/* ----------------------------------------------- */

    if (strcmp(mac, tmp) == 0) { /* we are in the start of the macro*/
        strcpy(mcurrent->macro_name, strtok(NULL, space));  /*save the macro name in the struct */
        return 0;
    }
    if(flag ==1 && strcmp(endmac, tmp) != 0 ){ /* we got the data of the macro */
        strcat(mcurrent->macro_data,line); /*save the macro data in the struct */
        return 0;
    }

    if (strcmp(endmac, tmp) == 0) { /* we are in the endmacro*/
        return 1;
    }

    while (new_mhead != NULL) {

        if (strcmp(new_mhead->macro_name, tmp) == 0 && flag == 0) { /* if we sew the macro name in the file and we need to replace it with the data*/
            return 3;
        } else
            new_mhead= new_mhead->next;
    }
    return 2;
}
/* ################################################# */
char *macro_data(char *macro_name, macro *head){
    while (head != NULL){
        if (strcmp(macro_name,head->macro_name)==0){
            return head->macro_data;
        }
        head=head->next;
    }
    return NULL;
}
/* ################################################# */
macro *new_macro(){
    macro *new = calloc(1, sizeof(macro));
    if (new == NULL){
        printf("ERROR - NOT ENOUGH MEMORY \n");
        exit(1);
    }
    new->next = NULL;
    return new;
}
/* ################################################# */
void clear_spaces (char *line) { /* this func take the line she gets and return the same line without the spaces in the beginning*/
    int count = 0;
/* ---------------------------------------------- */
    while (line[count]==' ' || line[count]=='\t' ) {
        count++;
    }
    if (count != 0) {
        int i = 0;
        while (line[i + count] != '\0') {
            line[i] = line[i + count];
            i++;
        }
        line[i] = '\0';
    }

}
/* ################################################# */
void end_line(char *line) {
    int i;
    for (i = 0; i < strlen(line); i++) {
        if (line[i] == '\n')
            line[i] = '\0';
    }
}
/* ################################################# */
char *file_name(char *file , char *end_file){
    char *result = malloc(strlen(file)+strlen(end_file)+1);
    if(result != NULL){
        strcpy(result, file);
        strcat(result, end_file);
        return result;
    }
    return NULL;
}
#endif

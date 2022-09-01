#include "print_files.h"

char *wirdKidud[32]={"!", "@", "#", "$", "%",
                   "^", "&", "*", "<", ">",
                   "a","b", "c", "d", "e",
                   "f","g", "h", "i", "j",
                   "k","l", "m", "n", "o",
                   "p","q", "r", "s", "t",
                   "u", "v"};

/* ################################################# */
int go_to_print(print *phead , label *lhead , char *argv[] , int i) { /* Creating the output files*/
    char *ob_file = NULL, *ent_file = NULL, *ext_file = NULL ;
    int extern_flag = OFF , entry_flag = OFF , j =100;


    FILE *file_p1 = NULL , *file_p2 = NULL , *file_p3=NULL;
    label *curr_head = lhead;
    print *pcurrent = phead;


    ob_file = file_name(argv[i] , ".ob\0");
    file_p3 = fopen(ob_file, "w+"); /*Creating the ob file and inserting the values into it*/
    if (ob_file == NULL || file_p3 == NULL) {
        printf("Can't create or rewrite to file %s.", ob_file);
        return -1;
    } else{
        fprintf(file_p3, "\t    %s %s\n\n", wirdKidud[IC], wirdKidud[DC]);/*Print to the output file*/
        while(pcurrent != NULL && j <IC+DC+100){
            pcurrent->adrs = j;
            j++;
            pcurrent=pcurrent->next;
        }
        pcurrent = phead;
        while (pcurrent != NULL){
            fprintf(file_p3,"\t%s\t\t%s\n",convert_to_mozar( pcurrent->adrs),convert_to_mozar(pcurrent->code));/*Print to the output file*/
            pcurrent=pcurrent->next;
        }

    }
        while (curr_head != NULL) {
            if (strcmp(".extern", curr_head->type) == 0) {
                extern_flag = ON;
            }
            if (strcmp(".entry", curr_head->type) == 0) {
                entry_flag = ON;
            }
            curr_head = curr_head->next;
        }
        if (extern_flag == ON) { /* A flag on indicates that there are variables in the program of type extern*/
            ext_file = file_name(argv[i] , ".ext\0");
            file_p1 = fopen(ext_file, "w+");
            if (ext_file == NULL || file_p1 == NULL) { /* Creating the ext file and inserting the values into it*/
                printf("Can't create or rewrite to file %s.", ext_file);
                return -1;
            }

            curr_head = lhead;
            pcurrent = phead;
            while (pcurrent != NULL){
                int ext_adrs;
                ext_adrs = 100;
                while (curr_head != NULL) {
                    if (strcmp(".extern", curr_head->type) == 0) {
                    fprintf(file_p1, "\t%s\t%s\n", curr_head->name, convert_to_mozar(ext_adrs)); /*Print to the output file*/
                    }
                    ext_adrs++;
                curr_head = curr_head->next;
                }
                ext_adrs++;
            pcurrent = pcurrent->next;
            }

        }
        if (entry_flag == ON) { /* A flag on indicates that there are variables in the entry type program*/
            ent_file = file_name(argv[i], ".ent\0");
            file_p2 = fopen(ent_file, "w+"); /* Creating the ent file and inserting the values into it*/
            if (ent_file == NULL || file_p2 == NULL) {
                printf("Can't create or rewrite to file %s.", ent_file);
                return -1;
            }

            curr_head = lhead;
            while (curr_head != NULL) {
                if (strcmp(".entry", curr_head->type) == 0) {
                    fprintf(file_p2, "\t%s\t%s\n", curr_head->name, convert_to_mozar(curr_head->adrs));/*Print to the output file*/
                }
                curr_head = curr_head->next;

            }
        }
    fclose(file_p1);
    fclose(file_p2);
    fclose(file_p3);

    return 1;
    }
/* ################################################# */
char *convert_to_mozar(unsigned int adrs){
    unsigned int res1 , res2;
    char *result ;

    res1 = adrs/32;  /* the right value*/
    res2 = adrs%32;  /* the left value*/

    result = file_name(wirdKidud[res1],wirdKidud[res2]); /* Connection between the 2 values*/
    result[2]='\0';
    return result;
}
/* ################################################# */



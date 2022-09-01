#ifndef SYMBOL_C
#define SYMBOL_C
#include "symbol.h"

char *command[16] = {"mov","cmp", "add", "sub",
                     "not","clr", "lea", "inc",
                     "dec", "jmp","bne", "get",
                     "prn", "jsr", "rts", "hlt"};

char *direct[5]={".data", ".string", ".struct", ".entry", ".extern"};
/* ################################################# */
int is_label(char line[] ) { /* check if the first word in the line is a label*/
    char tmp[SIZE],space[] = " \t" , *token;
    int token_size;
/* ----------------------------------------------- */
  if(line[0]=='\t' || line[0]=='\0' || line[0]==' '|| line[0]=='\n')
    return 0;

    memset(symbolName, '\0', SIZE);
    memset(tmp, '\0', SIZE);
    strcpy(tmp, line);
    clear_spaces(tmp);
    token = strtok(tmp, space);/* we look only on the first word in the line*/
    token_size = strlen(token); /*the length of token*/
/* ----------------------------------------------- */
    if ((isspace(*token) != 0) ||(command_num(token)!=-1) || token[0] == '.' )
        return 0;

    if (valid_label(token)==1 ){  /* if the word include only alphabet letter*/
        tmp[token_size-1]='\0';
        strcat(symbolName, token);
        return 1;  /* return 1 if the word is a label.*/
    }
  
    if(valid_label(token)==-1) {
      printf(" ERROR : a label %s is not defined correctly", token);
      exit(1);
    }

   return 0;   /* return 0 if the word is NOT a label.*/
}
/* ################################################# */
void is_entry_or_extern(char line[] , label *head){
    char *tok1 , *tok2 ,tmp[SIZE] , space[] = " \t";
    memset(tmp,'\0',SIZE);
    strcpy(tmp,line);
    end_line(tmp);

    tok1 = strtok(tmp,space);
    tok2 = strtok(NULL,"\0");

    if (tok1 != NULL && tok2 != NULL){
        strcpy(head->type,tok1); /*Inserting the label type in the designated place in the list */
        strcpy(head->name,tok2); /* Inserting the name of the label in the designated place in the list*/
    }
}
/* ################################################# */
int check_if_exist(label **head, char *symbolName) {/*checking if the name (of the label) we got is exist or not in the struct */
    label *new = *head;
    if (symbolName == NULL)
        return 2;
    while (new != NULL) {
        if (strcmp(new->name, symbolName) == 0 && strcmp(new->type , ".entry") != 0){
            printf("ERROR Duplicate symbols %s!\n",new->name);
            exit(1);/*if true return 0 */
        }
        new = new->next;
    
        if (new == NULL)
            return 1;
    }
    return 1; /*if false return 1*/
}
/* ################################################# */
int find_the_command(char line[], int flag) {
    char tmp[SIZE],space[] = " \t",*tok1 ,*tok2 ;
    int token1_size ,token2_size ,num;
/* ----------------------------------------------- */
    memset(tmp, '\0', SIZE);
    strcpy(tmp, line);
/* ----------------------------------------------- */
    if (flag == 0) {
        tok1 = strtok(tmp, space);
        end_line(tok1);
        token1_size = strlen(tok1);
        if (token1_size == 3 && is_commend(tok1) == 1) {
            num = command_num(tok1); /* Checking what type of command it is*/
            return num;
        }
    }
    if (flag == 1) {
        strtok(tmp, space);
        tok2 = strtok(NULL, space);
        end_line(tok2);
        token2_size = strlen(tok2);

        if (token2_size == 3 && is_commend(tok2) == 1) {
            num = command_num(tok2); /* Checking what type of command it is*/
            return num;
        }
    }
    return -1;
}
/* ################################################# */
int command_num(char *commend) {
    int i;
    for (i = 0; i < 16; i++) {
        if (strcmp(commend, command[i]) == 0) /* Go through the array of commands*/
            return i;
    }
    return -1;
}
/* ################################################# */
int is_commend(char *commend) {
    int i;
    for (i = 0; i < strlen(commend); i++) {
        if (islower(commend[i])) /* Going over the received word and checking whether it matches the definitions for the actions*/
            return 1;
    }
    return 0;
}
/* ################################################# */
int num_of_operand(int opcode) {
    if (check_if_empty(&op)) { /* Enter how many operands each command should receive*/
        switch (opcode) {
            case 0:
            case 1:
            case 2: /*First group get 2 operands */
            case 3:
            case 6:
                op.source = 1;
                op.target = 1;
                return op.source+op.target;
            case 4:
            case 5:
            case 7:
            case 8:
            case 9: /* Second group get 1 operands*/
            case 10:
            case 11:
            case 12:
            case 13:
                op.source = 0;
                op.target = 1;
                return op.source+op.target;
            case 14:
            case 15: /* Third group get 0 operands*/
                op.source = 0;
                op.target = 0;
                return op.source+op.target;
        }
    }
    return 0;
}
/* ################################################# */
int check_if_empty(operand *head) {

    while (head != NULL) {
        head = head->next;
        return 1;
    }
    return 0; /*if not return 0*/
}
/* ################################################# */
label *new_label() {
    label *new = calloc(1, sizeof(label));
    if (new == NULL) {
        printf("ERROR - NOT ENOUGH MEMORY \n");
        exit(1);
    }
    new->next = NULL;
    return new;
}
/* ################################################# */
kidud *new_kidud() {
    kidud *new = calloc(1, sizeof(kidud));
    if (new == NULL) {
        printf("ERROR - NOT ENOUGH MEMORY \n");
        exit(1);
    }
    new->next = NULL;
    return new;
}
/* ################################################# */
void label_data_in(label **head , char *symbolN ){
    label *new = *head;
    strcpy(new->name,symbolN);
}
/* ################################################# */
int which_directives(char line[],int flag){
    char *tok ,tmp[SIZE] , space[] = " \t";
    int i ;
    memset(tmp,'\0',SIZE);
    strcpy(tmp,line);
    tok=NULL;

    if(isspace(*line)!=0)
        return -1;

    if (flag == 1) {
        strtok(tmp, space);
        tok = strtok(NULL, space);
        if (tok[0] == '.') {
            for (i = 0; i < sizeof(direct); i++) {
                if (strcmp(tok, direct[i]) == 0){
                    return i;
                  }
            }
        } else {
            end_line(tok);
            for (i = 0; i < 5; i++){
                if (strcmp(tok, direct[i]) == 0){
                    return i;
                  }

            }
        }
    }
    if (flag==0){
        tok = strtok(tmp, space);
        if (tok[0] == '.') {
            for (i = 0; i < sizeof(direct); i++) {
                if (strcmp(tok, direct[i]) == 0) {
                    return i;
                }
            }
        }
    }
    return -1;
}
/* ################################################# */
int count_num(char *commend,int flag) {
    int i, counter = 0,notEpty=0;
    char tmp[SIZE] , *space = " \t" , *token ;
    token = NULL;
    memset(tmp,'\0',SIZE);
    strcpy(tmp,commend);
    if (flag == 1) {
        strtok(tmp , space);
        strtok(NULL , space);
        token = strtok(NULL , "\n");
    }
    else {
        strtok(tmp , space);
        token = strtok(NULL , "\n");
    }
    if (token==NULL){
        return 0;
    }
    else{
        for (i = 0; i < strlen(token); i++) {
            if (isspace(token[i]))
                i++;
            if(isalpha(token[i]) || token[i]=='#')
                notEpty=1;
            if (token[i] == ','){
                if(empty_line(token,i+1)==0){
                    counter++;
                }
            }
        }
        if(notEpty==1)
            return counter + 1;
    }
    return 0;
}
/* ################################################# */
int empty_line(char *token,int i){
    if(token == NULL)
        return 1;

    for(;i<strlen(token);i++){
        if(isspace(token[i])== 0){
            return 0; /* if token is NOT empty*/
        }
    }
    return 1; /* if token is empty*/
}
/* ################################################# */
int valid_label(char *token){
    int i , j , size;
    i=0;

    size = strlen(token);
    if (token == NULL){
        return 0;/*token is NULL */
    }
    if (isalpha(token[i])&& token[size-1]==':'){
        for (j = 0; j < size ; j++) {
            if (isalpha(token[j])|| isdigit(token[j])){
                return 1;/*this is a valid label */
            }
        }
    }
    return -1; /*this is NOT a valid label */
}
/* ################################################# */
int compare_labels(label *head, char *token,int addres) {/*checking if the name (of the label) we got is exist or not in the struct */
    label *new = head;
    if (token == NULL)
        return 0;
    while (new != NULL) {
        if (strcmp(new->name, token) == 0){
            return 1;/*if true return 1 */
        }
        if (strcmp(new->type,".extern") == 0 || strcmp(new->type,".entry") == 0)
            return 0;
        new = new->next;

        if (new == NULL){
            printf("ERROR - THE STRING - %s - DONT EXIST IN THE LABELS LIST\n",token);
            exit(1);
          }
    }
    return 0; /*if false return 0*/
}
/* ################################################# */
int count_psik(char *tok){
    int i , count =0;
    if (tok != NULL) {
        for (i = 0; i < strlen(tok); i++) {
            if (tok[i] == ',')
                count++;
        }
    }
    return count;
}
/* ################################################# */
int decimal_to_bin(int num){
    unsigned int i=0,abs = num;
    int j;
    char temp;
    char * bin = (char *)malloc(11* sizeof(char));
    if (bin == NULL)
        return -1;
    while(i<7){
        bin[i]= abs%2+'0';
        abs=abs/2;
        i++;
    }
    for (j=0;j<5;j++){
        temp = bin[7 - j];
        bin[7 - j] = bin[j];
        bin[j] = temp;
    }
    bin[10] = '\0';
    return atoi(bin);
}
/* ################################################# */
int binary_to_decimal( int bin_num)
{
    int decimal_num = 0, temp =0, rem,num=2;
    while (bin_num != 0)
    {
        rem = bin_num % 10;
        bin_num = bin_num / 10;
        decimal_num = decimal_num +rem*power(num,temp);
        temp++;
    }
    return decimal_num;
}
/* ################################################# */
int power(int base, int exponent){/* The function takes the number and raises it in the desired chest*/

    int result=1;
    for (; exponent>0; exponent--)
    {
        result = result * base;
    }
    return result;
}

#endif

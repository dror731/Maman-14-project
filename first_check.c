#ifndef FIRST_CHECK
#define FIRST_CHECK
#include "first_check.h"
int flag;
/* ################################################# */
void first_check(FILE *file , label *head ,  label *tail , char *argv[] ,int i) {
    int j = 0 , direct;
    char tmp[SIZE],line[SIZE] , space[] = " \t" , *fileN = NULL;
    label *current , *new_tail;
/* ----------------------------------------------- */
    memset(line, '\0', SIZE);
    IC=0;
    DC=0;
    fileN = file_name(argv[i] , ".am\0");
    file = fopen(fileN,"r");
/* ----------------------------------------------- */
    current = head;
    new_tail = tail;
    while (fgets(line, SIZE - 1, file)){
        strcpy(tmp, line);
        flag=0;
        new_tail = new_label();

       if(tmp[j] != ';') {
           if (line[j] == '.') {
               char *token;
               token = strtok(tmp, space);

               direct = which_directives(token, flag);

               if (direct == 3 || direct == 4)
                   is_entry_or_extern(line, current);
                   current->next = new_tail;
                   current = current->next;


           } else {
               if (tmp[j] != '.'){
                   clear_spaces(tmp);
                   if (isalpha(tmp[j])) { /*check if the line start with a alphabet char*/
                       if (is_label(line) == 1) {/* send to is_label func - return 0 if it's not and 1 if it's label*/
                           flag = 1; /* a label is found*/
                           if (check_if_exist(&head, symbolName) ==1) { /* check if this symbol exists already 1-no 0-yes*/
                               label_data_in(&current, symbolName); /* get the label name inside head*/
                               current->next = new_tail;
                               current = current->next;
                           }
                       }
                   }
               }
           }
       }
    }
    while (current!=NULL){
        current= current->next;
    }
   fclose(file);
}
/* ################################################# */
int two_operand(int have,int needs){
    if (have==needs)
        return 1;
    else {
        printf("ERROR - THE NUM OF OPERAND IS NOT AS IT SHOULD\n");
        exit(1);
    }
    return 0;
}
/* ################################################# */
void take_data(label *current,char line[]){
  
    char tmp[SIZE] ,value[SIZE] ,data[SIZE] ,*token3;
    int i = 0, j = 0,k=0, numbers,num=0;
/* ----------------------------------------------- */ 
    memset(tmp, '\0', SIZE);
    strcpy(tmp, line);
    memset(value, '\0', SIZE);
    memset(data, '\0', SIZE);
    strtok(tmp, ".");
    strtok(NULL, " \t");
    token3 = strtok(NULL, "\n");
/* ----------------------------------------------- */
    clear_spaces(token3);
    end_line(token3);
    strcpy(current->type,"data");
    current->adrs=DC+IC+100;
    
     for ( i = 0; i < strlen(token3); i++) {
         if (token3[i] == ',' || token3[i] == '\n') {
             numbers= from_char_to_int(data);
             current->data[k]=numbers;
              k++;
           num++;
           DC++;
             memset(data, '\0', SIZE);
             j=0;
         }
       
         if (isdigit(token3[i]) || token3[i] == '-') {
             data[j] = token3[i];
             j++;
         }
     }
  
     if(i == strlen(token3) ){
        numbers = from_char_to_int(data);
        current->data[k]=numbers;
       num++;
        k++;
       DC++;
       }
}
/* ################################################# */
int from_char_to_int(char *token) {
  int num;
  num = atoi(token);
  return num;
}
/* ################################################# */
void take_string(label *current,char line[]){

    char tmp[SIZE] , value[SIZE] , data[SIZE] , *token3 ;
    int i = 0,asski=0,k=0,num=0;
    /* ----------------------------------------------- */ 
    strcpy(current->type,"data");
    memset(tmp, '\0', SIZE);
    strcpy(tmp, line);
    memset(value, '\0', SIZE);
    memset(data, '\0', SIZE);
    strtok(tmp, ".");
    strtok(NULL, " \t");
    token3 = strtok(NULL, "\n");
    clear_spaces(token3);
    end_line(token3);
    current->adrs=DC+IC+100;

/* ----------------------------------------------- */
    if(token3[i]=='"')
        i++;

    while(token3[i] != '"'){
      asski=(int)token3[i];
      current->data[k]=(int)asski;
      num++;
      k++;
      i++;
      DC++;

      }
    DC++;
}
/* ################################################# */
void take_struct( label *current,char line[]){
    char tmp[SIZE] , value[SIZE] , data[SIZE] ,*token3;
    int i = 0,k=0, numbers , asski =0,num=0;
/* ----------------------------------------------- */
    flag =0;
    memset(tmp, '\0', SIZE);
    strcpy(tmp, line);
    memset(value, '\0', SIZE);
    memset(data, '\0', SIZE);
    strtok(tmp, ".");
    strtok(NULL, " \t");
    token3 = strtok(NULL, "\n");
    clear_spaces(token3);
    end_line(token3);
    strcpy(current->type,"struct");
    current->adrs=DC+IC+100;
/* ----------------------------------------------- */
    while(token3[i] != '\0' ){
        if (isdigit(token3[i]) || token3[i] == '-') {
          numbers =  take_numbersForlabel(token3);
          current->data[k] = numbers;
          num++;
          DC++;
          k++;
         }
        if(token3[i] ==',')
          i++;
        if(token3[i]=='"'){
          i++;
          while(token3[i] != '"'){
            asski=(int)token3[i];
            num++;
            current->data[k]=(int)asski;
            k++;
            i++;
            DC++;
          }
        }
      i++;
      }
    DC++;
   }
/* ################################################# */
void split_line(char line[],int from , kidud *khead) {
    char tmp[SIZE] , space[] = " \t", *tok ;
/* ----------------------------------------------- */
    memset(tmp,'\0',SIZE);
    strcpy(tmp,line);
/* ----------------------------------------------- */
    if (is_label(line) == 0) {
        strtok(tmp, space);
        tok = strtok(NULL, "\0");
        if (tok != NULL) {
            clear_spaces(tok);
            end_line(tok);
            if (count_psik(tok) == 1) {
                char *tok1,*tok2 ;
                tok1 = strtok(tok, ",");
                tok2 = strtok(NULL,"\0");

                khead->source = find_numbers(tok1); /* Inserting the values into the appropriate place before coding*/
                khead->target = find_numbers(tok2);
            }else{
                khead->target = find_numbers(tok);
            }
        }
    }
    if (is_label(line) == 1) {
        strtok(tmp, space);
        strtok(NULL, space);
        tok = strtok(NULL, "\0");
        if (tok != NULL) {
            clear_spaces(tok);
            end_line(tok);
            if (count_psik(tok) == 1) {
                char *tok1,*tok2;
                tok1 = strtok(tok, ",");
                tok2 = strtok(NULL,"\0");
               khead->source = find_numbers(tok1);/*Inserting the values into the appropriate place before coding*/
               khead->target = find_numbers(tok2);

            } else{
                khead->target = find_numbers(tok);
            }
        }
    }
}
/* ################################################# */
int start_word(char line[]){
    char tmp[SIZE] , space[] = " \t";
    int j = 0, token_size;
/* ----------------------------------------------- */
    memset(symbolName, '\0', SIZE);
    memset(tmp, '\0', SIZE);
    strcpy(tmp, line);
    strtok(tmp, space);
    token_size = strlen(tmp);
/* ----------------------------------------------- */

    if (isalpha(tmp[j])&& tmp[token_size-1]==':'&& which_directives(line,flag)==-1 )
        return token_size;

      if(which_directives(line,flag)==-1)
       return 1;

  return -1;
}
/* ################################################# */
 int take_numbersForlabel(char token[]){

     char data[SIZE],tmp[SIZE];
     int i = 0,j = 0,numbers;
/* ----------------------------------------------- */
    memset(data, '\0', SIZE);
    memset(tmp, '\0', SIZE);
    strcpy(tmp,token);
/* ----------------------------------------------- */
    if(isalpha(tmp[i]) || tmp[i]==' ' || tmp[i]=='\t') {
        while(tmp[i]!='.'){
            i++;
         }
    }

    if(tmp[i]=='.')
        i++;

    while(tmp[i] !=',' && i < strlen(token)){
        data[j] = tmp[i];
        i++;
        j++;
    }
    numbers = from_char_to_int(data);

  return numbers;
}
/* ################################################# */
 int take_numbersForImmediate(char token[]){
    char data[SIZE],tmp[SIZE];
    int i = 0,j = 0,numbers;
/* ----------------------------------------------- */
    memset(data, '\0', SIZE);
    memset(tmp, '\0', SIZE);
    strcpy(tmp,token);
/* ----------------------------------------------- */
    while(tmp[i] != '#' ){
        i++;
    }
    if(tmp[i]=='#')
        i++;

    while(tmp[i] !='\0'){
        data[j] = tmp[i];
        i++;
        j++;
    }
    numbers = from_char_to_int(data);

  return numbers;
}
/* ################################################# */
void find_the_label(char line[] , label *lcurrent , label **lhead , int opcode , kidud *khead){

    char tmp[SIZE], *tok, space[] = " \t", *tok2 = NULL;
    int i = 0 , j = 0 , addres;
/* ----------------------------------------------- */
    label *new = *lhead;
    memset(tmp, '\0', SIZE);
    strcpy(tmp, line);
    end_line(tmp);
/* ----------------------------------------------- */
    if (line[0] != '\0') {
        if(IC != 0 && opcode !=-1 )
            IC++;
        addres=IC+100;
        if (is_label(tmp) == 1) {
            lcurrent->adrs=addres;
            khead->ARE = 00;
          if(strcmp(lcurrent->type, "NULL") != 0){
             strcpy(lcurrent->type, "code");
            }
            strtok(tmp, space);
            strtok(NULL, space);
            tok = strtok(NULL, "\n");
            if (tok != NULL) {
              IC++;

                while (tok[i] != '\0') {
                    if (tok[i] == ',') {
                        tok = strtok(tok, ",");
                        tok2 = strtok(NULL, "\0");
                    }
                    if (i + 1 == strlen(tok))
                        tok = strtok(tok, "\0");
                    i++;
                }
                clear_spaces(tok);
                if (tok[0] == 'r')
                    strcpy(khead->label_source,"r");/*inserting the name of the label into the designated place*/

                for (j = 0; j < strlen(tok); j++) {
                    if (tok[j] == '.'){
                        strtok(tok,".");
                        IC++;

                        tok[j] = '\0';
                    }
                    if(tok[j] == 'r' || tok[j] == '#'){
                        tok[j] = '\0';
                    }
                }
                if (khead->label_source[0] == '\0'){
                    clear_spaces(tok);
                    strcpy(khead->label_source,tok);/*inserting the name of the label into the designated place*/
                }
                compare_labels(new,tok,addres);
            }
            if (tok2 != NULL) {
               IC++;


                for (j = 0; j < strlen(tok2); j++) {
                    if (tok2[j] == 'r')
                        strcpy(khead->label_target,"r");/*inserting the register into the designated place*/

                    if (tok2[j] == '.'){
                        strtok(tok2,".");
                        IC++;

                        tok2[j] = '\0';
                      }
                    if(tok2[j] == 'r' || tok2[j] == '#'){
                        tok2[j] = '\0';
                    }
                }
                if (khead->label_target[0] == '\0') {
                    clear_spaces(tok2);
                    strcpy(khead->label_target, tok2);/*inserting the name of the label into the designated place*/
                }
                compare_labels(new,tok2,addres);

                if(tok[0]=='r' && tok2[0]=='r')
                  IC--;

            }
            if(tok != NULL && tok2 == NULL){
                strcpy(khead->label_target,khead->label_source);  /* If there is no destination operand and a source operand is found, then the source and destination will move*/
                khead->label_source[0]= '\0';
            }
        }
        if (is_label(tmp) == 0) {
            strtok(tmp, space);
            tok = strtok(NULL, "\0");
            if (tok != NULL) {
              IC++;

                while (tok[i] != '\0') {
                    if (tok[i] == ',') {
                        tok = strtok(tok, ",");                        
                        tok2 = strtok(NULL, "\0");
                    }
                    if (i + 1 == strlen(tok))
                        tok = strtok(tok, "\0");
                  i++;
                }

              if(tok != NULL && tok2 != NULL){
                    clear_spaces(tok);
                    clear_spaces(tok2);
                    if(tok[0]=='r' && tok2[0]=='r')
                        IC--;

              }
                clear_spaces(tok);
                if (tok[0] == 'r')
                    strcpy(khead->label_source,"r");
                for (j = 0; j < strlen(tok); j++) {


                    if (tok[j] == '.'){
                        strtok(tok,".");
                        IC++;
                        tok[j] = '\0';
                    }

                    if(tok[j] == 'r' || tok[j] == '#'){
                        tok[j] = '\0';
                    }
                }
                if (khead->label_source[0] == '\0') {
                    clear_spaces(tok);
                    strcpy(khead->label_source, tok);
                }
                compare_labels(new,tok,addres);
            }

            if (tok2 != NULL) {
                clear_spaces(tok2);
                if (tok2[0] == 'r')
                    strcpy(khead->label_target,"r");

                IC++;

                for (j = 0; j < strlen(tok2); j++) {
                    if (tok2[j] == '.'){
                        strtok(tok2,".");
                        IC++;

                        tok2[j] = '\0';
                    }

                    if(tok2[j] == 'r' || tok2[j] == '#'){
                        tok2[j] = '\0';
                    }
                }
                if (khead->label_target[0] == '\0'){
                    clear_spaces(tok2);
                    strcpy(khead->label_target,tok2);
                }
                compare_labels(new,tok2,addres);
            }
            if(tok != NULL && tok2 ==NULL){
                strcpy(khead->label_target,khead->label_source);
                khead->label_source[0]= '\0';
            }
        }
    }
     if(opcode==15 ||opcode==14){
        IC++;
     }
}
/* ################################################# */
int find_numbers(char *tok){
    int i = 0,j = 0 , numbers;
    char data[1];
    memset(data,'\0',1);

    if (tok != NULL){
        while (tok[j] != '\0') {
            if (tok[j] != ' ' && tok[j] != '\t') {
                if (tok[j] == '#' && (tok[j+1] == '-' || isdigit(tok[j+1]))) {
                    numbers = take_numbersForImmediate(tok);
                    return numbers;
                }
                if (isdigit(tok[j]) && (tok[j-1] == '.')) {
                    numbers = take_numbersForlabel(tok); /* The assignment of the numbers of the operands to their places*/
                    return numbers;
                }
                if (tok[j] == 'r' && isdigit(tok[j+1])) {
                    data[i] = tok[j+1];
                    if (isdigit(data[i])) {
                        numbers = from_char_to_int(data); /* The assignment of the numbers of the operands to their places*/
                        return numbers;
                    }
                }
            }
            j++;
        }
    }
    return 0;
}
#endif

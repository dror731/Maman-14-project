#include "word.h"
/* ################################################# */
void sentens(label *head  , kidud *khead , char *argv[] , int i){
    char line[SIZE], tmp[SIZE],*fileN = NULL;
    int from, opcode, operand_i_have, operands_i_need, flag=0, j=0;

    FILE *file;
    label *current_label;
    kidud *current_kidud , *tail_kidud;

    current_label = head;
    current_kidud = khead;

    memset(line, '\0', SIZE);
    memset(tmp, '\0', SIZE);

    fileN = file_name(argv[i] , ".am\0"); /* Reading the resulting file after deploying the macros*/
    file = fopen(fileN,"r");

        while (strcmp(current_label->type, "\0") !=0)  {
            current_label = current_label->next;
        }
/* ----------------------------------------------- */
    while (fgets(line, SIZE - 1, file)) {
        strcpy(tmp, line);
        tail_kidud = new_kidud();
        clear_spaces(tmp);
        if (tmp[j] != ';' && tmp[j] != '.') {
            if (is_label(tmp) == 1) {
                flag = 1;
                if (current_label->next != NULL && IC != 0)
                    current_label = current_label->next;
            }
            from = start_word(tmp);
            split_line(tmp, from, current_kidud);
            opcode = find_the_command(tmp, flag);
            current_kidud->opcode = opcode;

            if (opcode != -1) {

                operands_i_need = num_of_operand(opcode);
                operand_i_have = count_num(tmp, flag);
                two_operand(operand_i_have, operands_i_need); /* Checking whether the number of received operands is necessary according to the instructions*/
                find_the_label(line, current_label, &head, opcode, current_kidud);
            }
            switch (which_directives(line, flag)) {
                case 0:
                    take_data(current_label, line);
                    break;
                case 1:
                    take_string(current_label, line);
                    break;
                case 2:
                    take_struct(current_label, line);
                    break;
            }
            flag = 0;
            current_kidud->next = tail_kidud;
            current_kidud = current_kidud->next;
        }
      check_current(&head);
    }
    fclose(file);
}
/* ################################################# */
void check_current(label **head ){

  label *new=*head;
  label *tmp=*head;


  while (strcmp(".entry",new->type)==0 || strcmp(".extern",new->type)==0) { /*Do the characters of type entry or extern continue forward*/
    new=new->next;
    }


  while(new!=NULL){

    if(strcmp(new->name,tmp->name)==0)
    {
      tmp->adrs=new->adrs;
      new=new->next;
      tmp=tmp->next;
      }

    new=new->next;
    }
  }
/* ################################################# */
void tipol_bekidud_source(kidud *khead , label *lhead){

    label *new = lhead;
    khead=khead->next;
    while(khead!=NULL) {
        new=lhead;
        while(new!=NULL){
            if(strcmp(khead->label_source,new->name)==0){

                if(strcmp(new->type,"data")==0){
                    khead->source_mion=1;
                    khead->ARE=2;
                }


                if(strcmp(new->type,"struct")==0){
                    khead->source_mion=2;
                    khead->ARE=2;

                }

                if(strcmp(new->type,".entry")==0){
                    khead->source_mion=1;

                }

                if(strcmp(new->type,".extern")==0){
                    khead->source_mion=1;
                    khead->ARE=1;
                }
            }
            if(new->next!= NULL)
                new=new->next;
            else
                break;
        }

        if(strcmp(khead->label_source,"r")==0){
            khead->source_mion=3;
        }

        if(strcmp(khead->label_source,"\0")==0 && khead->source != 0){
            khead->source_mion=0;
        }

        if(khead->next!= NULL)
            khead=khead->next;
        else
            break;

    }
}
/* ################################################# */
void tipol_bekidud_target(kidud *khead , label *lhead){

    label *new = lhead;
    khead=khead->next;
    while(khead!=NULL) {
        new=lhead;
        while(new!=NULL){
            if(strcmp(khead->label_target,new->name)==0){ /* If the label name matches the target operand name*/
                if(strcmp(new->type,"data")==0){ /* If it is of data type*/
                    khead->target_mion=1;
                    khead->ARE=2;
                }

                if(strcmp(new->type,"struct")==0) /* If it is of struct type*/
                    khead->source_mion=2;
                    khead->ARE=2;
                }

                if(strcmp(new->type,".entry")==0){  /* If it is of entry type*/
                    khead->target_mion=1;
                }

                if(strcmp(new->type,".extern")==0){ /* If it is of extern type*/
                    khead->target_mion=1;
                    khead->ARE=1;
                }
            if(new->next!= NULL)
                new=new->next;
            else
                break;
            }
        if(strcmp(khead->label_target,"r")==0){  /* If it is register*/
            khead->target_mion=3;
        }

        if(strcmp(khead->label_target,"\0")==0 && khead->target != 0){
            khead->target_mion=0;
        }

        if(khead->next!= NULL)
            khead=khead->next;
        else
            break;
        }
    }
/* ################################################# */
print *new_print() {
    print *new = calloc(1, sizeof(print));
    if (new == NULL) {
        printf("ERROR - NOT ENOUGH MEMORY \n");
        exit(1);
    }
    new->next = NULL;
    return new;
}
/* ################################################# */
void final_kidud(print *phead ,kidud *khead , label *lhead){
    print *newp  = phead;
    kidud *new_khead  = khead;
    label *new_lhead  = lhead;

    unsigned int code_line  = 0;
    int i;

    while(new_khead != NULL) {
        code_line = 0;
        if (new_khead->opcode != -1) { /* Here the row coding process is done according to the command, the addressing methods and the ARE*/
            code_line |= new_khead->opcode;
            code_line <<= 2;
            code_line |= new_khead->source_mion;
            code_line <<= 2;
            code_line |= new_khead->target_mion;
            code_line <<= 2;
            code_line |= 0;
            newp->code = code_line;
        }

        if (new_khead->label_source[0] != '\0') {

            if (strcmp(new_khead->label_source, "r") == 0 && strcmp(new_khead->label_target, "r") == 0) { /*If both operands are registers*/
                newp->next = new_print();
                newp = newp->next;
                newp->code |= new_khead->source;
                newp->code <<= 4;
                newp->code |= new_khead->target;
                newp->code <<= 2;
            }
            if (strcmp(new_khead->label_source, "r") == 0 && strcmp(new_khead->label_target, "r") != 0) { /*If only the source operand is a register */
                newp->next = new_print();
                newp = newp->next;
                newp->code |= new_khead->source;
                newp->code <<= 6;
            }

            new_lhead = lhead;
            while (new_lhead != NULL) {
                if (strcmp(new_lhead->name, new_khead->label_source) == 0) {
                    newp->next = new_print();
                    newp = newp->next;
                    newp->code |= new_lhead->adrs;
                    newp->code <<= 2;
                    newp->code |= new_khead->source_mion;
                    if (new_khead->source != 0) {
                        newp->next = new_print();
                        newp = newp->next;
                        newp->code |= new_khead->source;
                        newp->code <<= 2;
                    }
                }
                new_lhead = new_lhead->next;
            }

        }
        if (strcmp(new_khead->label_target, "\0") == 0) { /* If no variable exists in the target operand*/
            if (new_khead->target != 0) {
                newp->next = new_print();
                newp = newp->next;
                newp->code = new_khead->target;
                newp->code= decimal_to_bin(newp->code);
                newp->code = binary_to_decimal(newp->code);
                newp->code >>= 2;
                newp->code <<= 2;
            }
        }
        if (new_khead->label_target[0] != '\0') {
            if (strcmp(new_khead->label_source, "r") != 0 && strcmp(new_khead->label_target, "r") == 0) {/* If only the target operand is a register*/
                newp->next = new_print();
                newp = newp->next;
                newp->code |= new_khead->target;
                newp->code <<= 2;
            }
            new_lhead = lhead;
            while (new_lhead != NULL) {
                if (strcmp(new_lhead->name, new_khead->label_target) == 0) {
                    newp->next = new_print();
                    newp = newp->next;
                    newp->code |= new_lhead->adrs;
                    newp->code <<= 2;
                    newp->code |= new_khead->ARE;
                }
                new_lhead = new_lhead->next;
            }
        }
        if (new_khead->opcode != -1 && new_khead->next != NULL) {
            newp->next = new_print();
            newp = newp->next;
        }
        new_khead = new_khead->next;
    }
     new_khead  = khead;
     new_lhead  = lhead;

    while (new_khead !=NULL ){

        if (new_khead->opcode == -1 ) {
            while (new_lhead != NULL) {
                if (strcmp(new_lhead->type, "data") == 0 || strcmp(new_lhead->type, "struct") == 0) { /* Performing the coding for the data lines*/
                    for (i = 0; i < 7; i++) {
                        if (new_lhead->data[i] != 0) {
                            newp->next = new_print();
                            newp = newp->next;
                            if (new_lhead->data[i] <0){
                                newp->code = decimal_to_bin(new_lhead->data[i]);
                                newp->code = binary_to_decimal(newp->code);
                                newp->code >>= 2;
                                newp->code <<= 2;
                            } else
                                newp->code = new_lhead->data[i];
                        }
                    }
                    if (strcmp(new_lhead->type, "struct") == 0) {
                        newp->next = new_print();
                        newp = newp->next;
                        newp->code = 0;
                    }
                }
                new_lhead = new_lhead->next;
            }
        }

        new_khead = new_khead->next;
    }

}
/* ################################################# */

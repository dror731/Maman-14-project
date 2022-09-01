#include "main.h"

/* ################################################# */
int main(int argc, char *argv[]) {
    int i ;
    FILE* file;

    for (i = 1; i  < argc ; i++ ) {
	

        label *lhead;
 	label *ltail;
        kidud *khead;
	kidud *ktail;
        macro *mhead;
        print *phead;

        lhead = new_label();
        ltail = new_label();
        lhead->next = ltail;

        khead = new_kidud();
        ktail = new_kidud();
        khead->next=ktail;

        phead = new_print();

        mhead = new_macro();

	printf("\t --- Welcome - let's get to work with %s ---\n\n",argv[i]);

        file = go_to_work( argc , argv , mhead , i );

        first_check(file ,lhead , ltail , argv , i );

        sentens(lhead,khead ,argv , i);

        tipol_bekidud_source(khead,lhead);

        tipol_bekidud_target(khead,lhead);

        final_kidud(phead,khead,lhead);

        go_to_print(phead,lhead,argv,i);


	printf("\t --- Thank you  - were done whit the file %s ---\n",argv[i]);

        free(khead);
        free(lhead);
        free(phead);
        free(ktail);
        free(ltail);
        free(mhead);

    }
    return 0;
}
/* ################################################# */




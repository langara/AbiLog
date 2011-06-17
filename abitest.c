#include "abilog.h"

typedef struct {
    char *text1, *text2;
    int i1, i2;
} textpair;

typedef struct {
    textpair *pair1, *pair2;
} obj;


int main(void) {
    textpair p1,p2;

    p1.i1 = 11;
    p1.i2 = 12;
    p2.i1 = 21;
    p2.i2 = 22;

    p1.text1 = "p1t1value";
    p1.text2 = (char*)0;
    p2.text1 = "p2t1value";
    p2.text2 = "p2t2value";

    obj theobj;
    theobj.pair1 = &p1;
    theobj.pair2 = &p2;

    ABI_STAMP();
    ABI_STAMP();
    char *dupa = "dupa";
    fprintf(stderr, "%s\n", dupa);
    ABI_LOG_MULTILINE(5, "fjdklf;jd lfa;j dfkla ;fjkdal ;fjkadl; jfkglasklfhsdjkgldfkslg sdfjkgl sdfjklg ");

    ABI_LOG_MEMBER1_INT(p1.i1);
    ABI_LOG_MEMBER1_INT(p2.i1);
    ABI_LOG_MEMBER2_INT(&p2,i1);
    ABI_LOG_MEMBER3_INT(&theobj,pair1,i1);




    //ABI_LOG_MEMBER1_STR(p1.text1);
    //ABI_LOG_MEMBER1_STR(p1.text2);


    return 0;
}

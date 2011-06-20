#include "abilog.h"

typedef struct {
    char *text1, *text2;
    int int1, int2;
} thestruct_t;

typedef struct {
    thestruct_t *struct1ptr, *struct2ptr;
} obj_t;

typedef struct {
    obj_t *obj1ptr, *obj2ptr;   
} objpair_t;

int main(void) {

    thestruct_t s1,s2;

    s1.int1 = 11;
    s1.int2 = 12;
    s2.int1 = 21;
    s2.int2 = 22;

    s1.text1 = (char*)"p1t1value";
    s1.text2 = (char*)0;
    s2.text1 = (char*)"p2t1value";
    s2.text2 = (char*)"p2t2value";

    obj_t obj;
    obj.struct1ptr = &s1;
    obj.struct2ptr = &s2;

    objpair_t opair;
    opair.obj1ptr = 0;
    opair.obj2ptr = &obj;

    ABI_STAMP();
    ABI_STAMP();
    char *dupa = (char*)"dupa";
    fprintf(stderr, "%s\n", dupa);
    ABI_LOG_MULTILINE(5, "fjdklf;jd lfa;j dfkla ;fjkdal ;fjkadl; jfkglasklfhsdjkgldfkslg sdfjkgl sdfjklg ");

    ABI_STAMP();

    ABI_LOG_INT(s1.int1);
    ABI_LOG_INT(s2.int1);

    ABI_LOG_MEMBER2_INT(&s2,int1);

    ABI_LOG_MEMBER3_INT(&obj,struct1ptr,int1);

    ABI_LOG_MEMBER4_INT(&opair, obj1ptr, struct1ptr, int1);
    ABI_LOG_MEMBER4_INT(&opair, obj1ptr, struct2ptr, int1);
    ABI_LOG_MEMBER4_INT(&opair, obj2ptr, struct1ptr, int1);
    ABI_LOG_MEMBER4_INT(&opair, obj2ptr, struct2ptr, int2);

    ABI_STAMP();

    obj.struct2ptr = 0;

    ABI_LOG_INT(s1.int1);
    ABI_LOG_INT(s2.int1);

    ABI_LOG_MEMBER2_INT(&s2,int1);

    ABI_LOG_MEMBER3_INT(&obj,struct1ptr,int1);

    ABI_LOG_MEMBER4_INT(&opair, obj1ptr, struct1ptr, int1);
    ABI_LOG_MEMBER4_INT(&opair, obj1ptr, struct2ptr, int1);
    ABI_LOG_MEMBER4_INT(&opair, obj2ptr, struct1ptr, int1);
    ABI_LOG_MEMBER4_INT(&opair, obj2ptr, struct2ptr, int2);


    ABI_STAMP();
    ABI_STAMP();

    ABI_LOG_STR(s1.text1);
    ABI_LOG_STR_MULTILINE(2,s2.text2);

    ABI_LOG_MEMBER2_STR(&s2,text1);

    ABI_LOG_MEMBER3_STR(&obj,struct1ptr,text1);

    ABI_LOG_MEMBER4_STR(&opair, obj1ptr, struct1ptr, text1);
    ABI_LOG_MEMBER4_STR(&opair, obj1ptr, struct2ptr, text1);
    ABI_LOG_MEMBER4_STR(&opair, obj2ptr, struct1ptr, text1);
    ABI_LOG_MEMBER4_STR(&opair, obj2ptr, struct2ptr, text2);

    ABI_STAMP();

    obj.struct2ptr = 0;

    ABI_LOG_STR(s1.text1);
    ABI_LOG_STR(s2.text1);

    ABI_LOG_MEMBER2_STR(&s2,text1);

    ABI_LOG_MEMBER3_STR(&obj,struct1ptr,text1);

    ABI_LOG_MEMBER4_STR(&opair, obj1ptr, struct1ptr, text1);
    ABI_LOG_MEMBER4_STR(&opair, obj1ptr, struct2ptr, text1);
    ABI_LOG_MEMBER4_STR(&opair, obj2ptr, struct1ptr, text1);
    ABI_LOG_MEMBER4_STR(&opair, obj2ptr, struct2ptr, text2);

    ABI_LOG_MEMBER4_STR_MULTILINE(3,&opair, obj2ptr, struct1ptr, text1);
    ABI_LOG_MEMBER4_STR_MULTILINE(2,&opair, obj2ptr, struct1ptr, text1);
    ABI_LOG_MEMBER4_STR_MULTILINE(1,&opair, obj2ptr, struct1ptr, text1);
    return 0;
}

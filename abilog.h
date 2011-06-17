#ifndef ABILOG_H_INCLUDED
    #define ABILOG_H_INCLUDED

    #include <stdio.h> //TODO: czy to moge zawsze? (C/C++; Linux/Windows/Porta; inkludowanie wielokrotne?(bo user moze juz zainkludowal))

    #define ABI_ENABLED //undef this to disable all logging (and reinclude the file? TODO: check if it would work)
    #define ABI_BUFLEN 100
    char abi_data_buffer[ABI_BUFLEN];
    int abi_data_i;
    int abi_data_j;

#endif // #ifndef ABILOG_H_INCLUDED

#undef ABI_PORTA_SIP
#undef ABI_PORTA
#undef ABI_UNIX
#undef ABI_WINDOWS
#undef ABI_UNKNOWN_SYSTEM

#if defined sipsyslog
    #define ABI_PORTA_SIP
#elif defined SYSLOG_EVT_CRIT
    #define ABI_PORTA
#elif defined __unix__
    #define ABI_UNIX
#else
    #define ABI_UNKNOWN_SYSTEM
#endif


#undef ABI_LOG
#undef ABI_LOGF
#undef ABI_STAMP
#undef ABI_LOG_MULTILINE
#undef ABI_LOG_MEMBER
#undef ABI_LOG_MEMBER_MULTILINE

#ifdef ABI_ENABLED

    #if defined ABI_PORTA_SIP
        #define ABI_LOG(text) sipsyslog(LOG_CRIT,0,"EVENT",(text))
    #elif defined ABI_PORTA
        #define ABI_LOG(text) SYSLOG_EVT_CRIT(0, 0, 0, (text))
    #elif defined ABI_UNIX
        #define ABI_LOG(text) fprintf(stderr, "%s\n", (text))
    #elif defined ABI_WINDOWS
        #define ABI_LOG(text) fprintf(stderr, "%s\n", (text))
    #endif

    #define ABI_LOGF(...) \
        do { \
            abi_data_i = snprintf(abi_data_buffer, ABI_BUFLEN, __VA_ARGS__); \
            /* TODO: assert abi_data_i < ABI_BUFLEN ? */ \
            ABI_LOG(abi_data_buffer); \
        } while (0)

    //#define ABI_STAMP() ABI_LOGF("ABI_STAMP: %s (line: %d)", __PRETTY_FUNCTION__, __LINE__)
    //#define ABI_STAMP() ABI_LOGF("ABI_STAMP: %s (line: %d)", __FUNCTION__, __LINE__)
    #define ABI_STAMP() ABI_LOGF("##### ABI_STAMP #####: %s (line: %d)", __FILE__, __LINE__)

    #define ABI_LOG_MULTILINE(width, longtext) \
        /* TODO: assert width+1 < ABI_BUFLEN */ \
        do { \
            abi_data_i = 0; /* already written chars */ \
            abi_data_j = width + 1; /* last time written chars */ \
            while(abi_data_j > width) { \
                abi_data_j = snprintf(abi_data_buffer, width + 1, "%s", &longtext[abi_data_i]); \
                ABI_LOG(abi_data_buffer); \
                abi_data_i += width; \
            } \
        } \
        while(0)

    #define ABI_LOG_MEMBER1_INT(numbername) ABI_LOGF("ABILOG: " #numbername " == %d", numbername)

    #define ABI_LOG_MEMBER2_INT(objectptr, numbername) \
        do { \
            if(!(objectptr)) \
                ABI_LOG("ABILOG: " #objectptr " == NULL!"); \
            else \
                ABI_LOG_MEMBER1_INT((*(objectptr)).numbername); \
        } \
        while(0)

    #define ABI_LOG_MEMBER3_INT(objectptr, subobjectname, numbername) \
        do { \
            if(!(objectptr)) \
                ABI_LOG("ABILOG: " #objectptr " == NULL!"); \
            else \
                ABI_LOG_MEMBER2_INT((*(objectptr)).subobjectname, numbername); \
        } \
        while(0)

    #define ABI_LOG_MEMBER4_INT(objectptr, subobjectname, subsubobjectname, numbername) \
        do { \
            if(!(objectptr)) \
                ABI_LOG("ABILOG: " #objectptr " == NULL!"); \
            else \
                ABI_LOG_MEMBER3_INT((*(objectptr)).subobjectname,subsubobjectname, numbername); \
        } \
        while(0)
/*
    #define ABI_LOG_MEMBER1_STR(member) \
        do { \
            if(!member) \
                ABI_LOG("ABILOG: " #member " == NULL!"); \
            else \
                ABI_LOGF("ABILOG: " #member " == %s", member); \
        } \
        while(0)

    #define ABI_LOG_MEMBER2_STR(object, member) \
        do { \
            if(!object) \
                ABI_LOG("ABILOG: " #object " == NULL!"); \
            else \
                ABI_LOG_MEMBER1_STR(object->member); \
        } \
        while(0)

    #define ABI_LOG_MEMBER3_STR(object, subobject, member) \
        do { \
            if(!object) \
                ABI_LOG("ABILOG: " #object " == NULL!"); \
            else \
                ABI_LOG_MEMBER2_STR(object->subobject, member); \
        } \
        while(0)

    #define ABI_LOG_MEMBER4_STR(object, subobject, subsubobject, member) \
        do { \
            if(!object) \
                ABI_LOG("ABILOG: " #object " == NULL!"); \
            else \
                ABI_LOG_MEMBER3_STR(object->subobject, object->subobject->subsubobject, member); \
        } \
        while(0)
*/


#endif // #ifdef ABI_ENABLED






/*

#define ABI_LOG(text) \
    #ifdef ABI_ENABLED \
        #if defined ABI_PORTA_SIP \
            sipsyslog(LOG_CRIT,0,"EVENT",(text)); \
        #elif defined ABI_PORTA \
            SYSLOG_EVT_CRIT(0, 0, 0, (text)); \
        #else \
            fprintf(stderr, (text)); \ //TODO: trzeba by sie upewniac czy jest stdio zainkludowany
        #endif \
            
        ....
    #endif //#ifdef ABI_ENABLED


*/



            //sipsyslog(LOG_CRIT,0,"EVENT",Parms("ABILOG: %s (line: %d)", __PRETTY_FUNCTION__, __LINE__)); 

    //SYSLOG_EVT_CRIT(0, 0, 0, Parms("ABIGAIL: ThreePartyFactoryURIs[%d] == %s", SIP_USER_REF_MSN1, SipNewSettings::ThreePartyFactoryURIs[SIP_USER_REF_MSN1].c_str()));


/*
ABI_STAMP() // loguje ładnie miejsce (jaki plik, jaka funkcja, linijka kodu..)

ABI_LOG("dupa")
ABI_LOGF("dupa%s: %d, test","bla",5)
ABI_LOG_MULTILINE(40,somelongtext) // 40 is width

ABI_LOG_MEMBER(object, subobject, member) // object->subobject->member (sprawdza najpierw czy nie są zerami i raportuje) (member ma być char*)
ABI_LOG_MEMBER_MULTILINE(40,object, subobject, member)

*/






//TODO: zeby w c ++ uzywal cout, lub cerr zamiast printf

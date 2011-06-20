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


#undef ABI_LOG_INT
#undef ABI_LOG_MEMBER2_INT
#undef ABI_LOG_MEMBER3_INT
#undef ABI_LOG_MEMBER4_INT

#undef ABI_LOG_STR
#undef ABI_LOG_MEMBER2_STR
#undef ABI_LOG_MEMBER3_STR
#undef ABI_LOG_MEMBER4_STR

#undef ABI_LOG_STR_MULTILINE
#undef ABI_LOG_MEMBER2_STR_MULTILINE
#undef ABI_LOG_MEMBER3_STR_MULTILINE
#undef ABI_LOG_MEMBER4_STR_MULTILINE


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

    #define ABI_STAMP() ABI_LOGF("ABILOG: %s:%d: ############# STAMP (function:%s) #############", __FILE__, __LINE__, __PRETTY_FUNCTION__)

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

    #define ABI_LOG_INT(number) ABI_LOGF("ABILOG: %s:%d: " #number " == %d", __FILE__, __LINE__, number)

    #define ABI_LOG_MEMBER2_INT(objectptr, numbername) \
        do { \
            if(!(objectptr)) \
                ABI_LOGF("ABILOG: %s:%d: " #objectptr " == NULL!", __FILE__, __LINE__); \
            else \
                ABI_LOG_INT((objectptr)->numbername); \
        } \
        while(0)

    #define ABI_LOG_MEMBER3_INT(objectptr, subobjectname, numbername) \
        do { \
            if(!(objectptr)) \
                ABI_LOGF("ABILOG: %s:%d: " #objectptr " == NULL!", __FILE__, __LINE__); \
            else \
                ABI_LOG_MEMBER2_INT((objectptr)->subobjectname, numbername); \
        } \
        while(0)

    #define ABI_LOG_MEMBER4_INT(objectptr, subobjectname, subsubobjectname, numbername) \
        do { \
            if(!(objectptr)) \
                ABI_LOGF("ABILOG: %s:%d: " #objectptr " == NULL!", __FILE__, __LINE__); \
            else \
                ABI_LOG_MEMBER3_INT((objectptr)->subobjectname,subsubobjectname, numbername); \
        } \
        while(0)




    #define ABI_LOG_STR(str) ABI_LOGF("ABILOG: %s:%d: " #str " == \"%s\"", __FILE__, __LINE__, (str))

    #define ABI_LOG_MEMBER2_STR(objectptr, stringname) \
        do { \
            if(!(objectptr)) \
                ABI_LOGF("ABILOG: %s:%d: " #objectptr " == NULL!", __FILE__, __LINE__); \
            else \
                ABI_LOG_STR((objectptr)->stringname); \
        } \
        while(0)

    #define ABI_LOG_MEMBER3_STR(objectptr, subobjectname, stringname) \
        do { \
            if(!(objectptr)) \
                ABI_LOGF("ABILOG: %s:%d: " #objectptr " == NULL!", __FILE__, __LINE__); \
            else \
                ABI_LOG_MEMBER2_STR((objectptr)->subobjectname, stringname); \
        } \
        while(0)

    #define ABI_LOG_MEMBER4_STR(objectptr, subobjectname, subsubobjectname, stringname) \
        do { \
            if(!(objectptr)) \
                ABI_LOGF("ABILOG: %s:%d: " #objectptr " == NULL!", __FILE__, __LINE__); \
            else \
                ABI_LOG_MEMBER3_STR((objectptr)->subobjectname,subsubobjectname, stringname); \
        } \
        while(0)




    #define ABI_LOG_STR_MULTILINE(width,str) \
        do { \
            ABI_LOGF("ABILOG: %s:%d: " #str " == ### MULTILINE ###:", __FILE__, __LINE__); \
            ABI_LOG("### MULTILINE BEGIN ###"); \
            ABI_LOG_MULTILINE(width,str); \
            ABI_LOG("### MULTILINE END ###"); \
        } \
        while(0)

    #define ABI_LOG_MEMBER2_STR_MULTILINE(width, objectptr, stringname) \
        do { \
            if(!(objectptr)) \
                ABI_LOGF("ABILOG: %s:%d: " #objectptr " == NULL!", __FILE__, __LINE__); \
            else \
                ABI_LOG_STR_MULTILINE(width,(objectptr)->stringname); \
        } \
        while(0)

    #define ABI_LOG_MEMBER3_STR_MULTILINE(width,objectptr, subobjectname, stringname) \
        do { \
            if(!(objectptr)) \
                ABI_LOGF("ABILOG: %s:%d: " #objectptr " == NULL!", __FILE__, __LINE__); \
            else \
                ABI_LOG_MEMBER2_STR_MULTILINE(width,(objectptr)->subobjectname, stringname); \
        } \
        while(0)

    #define ABI_LOG_MEMBER4_STR_MULTILINE(width, objectptr, subobjectname, subsubobjectname, stringname) \
        do { \
            if(!(objectptr)) \
                ABI_LOGF("ABILOG: %s:%d: " #objectptr " == NULL!", __FILE__, __LINE__); \
            else \
                ABI_LOG_MEMBER3_STR_MULTILINE(width,(objectptr)->subobjectname,subsubobjectname, stringname); \
        } \
        while(0)


#endif // #ifdef ABI_ENABLED

//TODO: zeby w c ++ uzywal cout, lub cerr zamiast printf

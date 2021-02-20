#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdbool.h>

typedef struct dataInfo
{
    int no_Of_Packets;
} DataInfo;

typedef struct voiceInfo
{
    bool show_Caller_ID;
    bool roamin;
} VoiceInfo;

typedef union extraInfo
{
    DataInfo data_Info;
    VoiceInfo voice_Info;;
} ExtraInfo;

typedef struct entry
{
    char tage;
    int no_Of_Calling_Party;
    int no_Party_Of_To_Be_Called;
    ExtraInfo extra_Info;
} entry_type;

typedef struct node
{
    entry_type info;
    struct node *next;
} node_type;

typedef node_type *list_type;

void create_list (list_type *);

int empty_list (list_type );

int full_list (list_type );

void insert_list (list_type * , entry_type , int );

void retrieve_list (list_type * , entry_type * , int );

void clear_list (list_type *);

#endif // LIST_H_INCLUDED

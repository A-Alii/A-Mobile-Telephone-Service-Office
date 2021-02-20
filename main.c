#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void display_menu();
void insert_Data_Call(list_type *pl, entry_type entry, int *emergency_Calls_Count, int *voice_Calls_Count, int *data_Calls_Count);
void insert_Voice_Call(list_type *pl, entry_type entry, int *emergency_Calls_Count, int *voice_Calls_Count);
void insert_Emergency_Call(list_type *pl, entry_type entry, int *emergency_Calls_Count);
void scan_Main_Info(entry_type *entry, char tag);
void display_Call_Info(entry_type entry);

int main()
{
    int data_Calls_Count, voice_Calls_Count, emergency_Calls_Count, choice;
    entry_type entry;
    list_type list_calls;

    create_list(&list_calls);

    data_Calls_Count = 0;
    voice_Calls_Count = 0;
    emergency_Calls_Count = 0;
    choice = 0;

    do
    {
        display_menu();
        scanf("%d", &choice);
        switch(choice)
        {
        case 1:
            // data call coming
            scan_Main_Info(&entry, 'D');

            printf("please enter the number of packets: ");
            scanf("%d", &entry.extra_Info.data_Info.no_Of_Packets);

            insert_Data_Call(&list_calls, entry, &emergency_Calls_Count, &voice_Calls_Count, &data_Calls_Count);
            printf("\n===============================The Data Call Inserted Successfully===================================\n");
            break;
        case 2:
            // voice call coming
            scan_Main_Info(&entry, 'V');

            int roaming;
            printf("Will you enable roaming: ");
            scanf("%d", &roaming);
            entry.extra_Info.voice_Info.roamin = roaming == 0 ? false : true;

            int show_Caller_ID;
            printf("Will you show caller id: ");
            scanf("%d", &show_Caller_ID);
            entry.extra_Info.voice_Info.show_Caller_ID = show_Caller_ID == 0 ? false : true;

            insert_Voice_Call(&list_calls, entry, &emergency_Calls_Count, &voice_Calls_Count);
            printf("\n===============================The Voice Call Inserted Successfully===================================\n");
            break;
        case 3:
            // emergency call coming
            scan_Main_Info(&entry, 'E');

            insert_Emergency_Call(&list_calls, entry, &emergency_Calls_Count);
            printf("\n===============================The Emergency Call Inserted Successfully===================================\n");
            break;
        case 4:
            // serve a call
            if(!empty_list(list_calls))
            {
                retrieve_list(&list_calls, &entry, 0);
                display_Call_Info(entry);
                switch(entry.tage)
                {
                case 'D':
                    data_Calls_Count--;
                    break;
                case 'V':
                    voice_Calls_Count--;
                    break;
                case 'E':
                    emergency_Calls_Count--;
                    break;
                }
            }
            else
            {
                printf("\n===============================There is no calls to be served===================================\n");
            }
            break;
        case 5:
        {
            // dismiss calls with least priority
            int start, end;
            start = -1;
            end = -1;
            if(data_Calls_Count > 0)
            {
                start = emergency_Calls_Count + voice_Calls_Count;
                end = data_Calls_Count + start;
            }
            else if (voice_Calls_Count > 0)
            {
                start = emergency_Calls_Count;
                end = start + voice_Calls_Count;
            }
            else
            {
                printf("\n===============================There is no calls to be dismissed===================================\n");
            }
            if(start != -1)
            {
                for (int position = start ; position < end ; position++)
                {
                    retrieve_list(&list_calls, &entry, position);
                }

                if(data_Calls_Count > 0)
                {
                    data_Calls_Count = 0;
                    printf("\n===============================All the data calls has been dismissed successfully===================================\n");
                }
                else if(voice_Calls_Count > 0)
                {
                    voice_Calls_Count = 0;
                    printf("\n===============================All the voice calls has been dismissed successfully===================================\n");
                }
            }
            break;
        }





        }
    }
    while(choice != 6);

    return 0;
}

void display_menu()
{
    printf("1. Data Call coming.\n");
    printf("2. Voice Call coming.\n");
    printf("3. Emergency Call coming.\n");
    printf("4. Serve a call.\n");
    printf("5. Dismiss calls with least priority.\n");
    printf("6. Exit.\n");
    printf("please enter your selection: ");
}

void insert_Data_Call(list_type *pl, entry_type entry, int *emergency_Calls_Count, int *voice_Calls_Count, int *data_Calls_Count)
{
    int position = *emergency_Calls_Count + *voice_Calls_Count + *data_Calls_Count;
    insert_list(pl, entry, position);
    (*data_Calls_Count)++;
}

void insert_Voice_Call(list_type *pl, entry_type entry, int *emergency_Calls_Count, int *voice_Calls_Count)
{
    int position = *emergency_Calls_Count + *voice_Calls_Count;
    insert_list(pl, entry, position);
    (*voice_Calls_Count)++;
}

void insert_Emergency_Call(list_type *pl, entry_type entry, int *emergency_Calls_Count)
{
    int position = *emergency_Calls_Count;
    insert_list(pl, entry, position);
    (*emergency_Calls_Count)++;
}

void scan_Main_Info(entry_type *entry, char tag)
{
    printf("please enter the number of calling party: ");
    scanf("%d", &entry->no_Of_Calling_Party);

    printf("please enter the number of the party to be called: ");
    scanf("%d", &entry->no_Party_Of_To_Be_Called);

    entry->tage = tag;
}

void display_Call_Info(entry_type entry)
{
    switch (entry.tage)
    {
    case 'D':
        printf("the call is of type 'Data Call' and the following is the call info:\n");
        printf("the number of calling party: %d\n", entry.no_Of_Calling_Party);
        printf("the number of party to be called: %d\n", entry.no_Party_Of_To_Be_Called);
        printf("the number of packets: %d\n", entry.extra_Info.data_Info.no_Of_Packets);
        break;

    case 'V':
        printf("the call is of type 'Data Call' and the following is the call info:\n");
        printf("the number of calling party: %d\n", entry.no_Of_Calling_Party);
        printf("the number of party to be called: %d\n", entry.no_Party_Of_To_Be_Called);
        printf("the has roaming: " + entry.extra_Info.voice_Info.roamin ? "Yes" : "No");
        printf("the call has show caller ID: " + entry.extra_Info.voice_Info.show_Caller_ID ? "Yes" : "No");
        break;

    case 'E':
        printf("the call is of type 'Data Call' and the following is the call info:\n");
        printf("the number of calling party: %d\n", entry.no_Of_Calling_Party);
        printf("the number of party to be called: %d\n", entry.no_Party_Of_To_Be_Called);
        break;
    }
    printf("\n===============================End Of Call Info===================================\n");
}

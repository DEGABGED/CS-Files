/*
    Francis Zac Q. dela Cruz
    2015-08086
    CS11-THXY1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STRSHORT 50 //for single values
#define STRLEN 200  //for single entries

/*
    SONGLIST STRUCTURES AND FUNCTIONS
*/
/*A Linked List node that stores a song entry's data. (Title, Artist, Composer, Album, Genre, Rating, Remarks).*/
/*NOTE: Rating is a float value because user rating sometimes can't be confined to integers. A similar reason explains why Genre is a string that can store the name of any genre.*/
typedef struct SongList{
    int id;
    char * title;
    char * artist;
    char * composer;
    char * album;
    char * genre;
    float rating;
    char * remarks;
    struct SongList * next; //in the case of a single song query, this will be null
} SongList;

/*Adds a SongList node to the song library “song”. The data of the song entry is parsed from the “data” string.*/
SongList * addSong(SongList * song, char data[]){
    SongList * ptr = song;
    if(!song){
        song = (SongList*) malloc(sizeof(SongList));
        ptr = song;
    } else{
        while(ptr->next) ptr = ptr->next;
        ptr->next = (SongList*) malloc(sizeof(SongList));
        ptr = ptr->next;
    }

    char * token;
    const char * delim = "\t";
    token = strtok(data, delim);
    ptr->id = atoi(token);
    token = strtok(NULL, delim);
    ptr->title = (char*) malloc(sizeof(char)*STRSHORT);
    strcpy(ptr->title, token);
    token = strtok(NULL, delim);
    ptr->artist = (char*) malloc(sizeof(char)*STRSHORT);
    strcpy(ptr->artist, token);
    token = strtok(NULL, delim);
    ptr->composer = (char*) malloc(sizeof(char)*STRSHORT);
    strcpy(ptr->composer, token);
    token = strtok(NULL, delim);
    ptr->album = (char*) malloc(sizeof(char)*STRSHORT);
    strcpy(ptr->album, token);
    token = strtok(NULL, delim);
    ptr->genre = (char*) malloc(sizeof(char)*STRSHORT);
    strcpy(ptr->genre, token);
    token = strtok(NULL, delim);
    ptr->rating = atof(token);
    token = strtok(NULL, delim);
    ptr->remarks = (char*) malloc(sizeof(char)*STRSHORT);
    strcpy(ptr->remarks, token);
    ptr->next = NULL;
    return song;
}

/*Sorts the song library “list” using insertion sort. If “onlyLastSong” is 1 (true), then only the last node, or the most recently added one, is sorted.*/
SongList * sortInsertion(SongList * list, int onlyLastSong){
    if(!list) return NULL;
    if(!(list->next)) return list;
    SongList * ptr = list->next;
    SongList * ptr_bef = list;
    SongList * ptr_lim = ptr;
    if(onlyLastSong){
        while(ptr_bef->next->next) ptr_bef = ptr_bef->next;
        ptr = ptr_bef->next;
        ptr_lim = ptr;
    }
    while(ptr){
        //remove ptr and insert it somewhere else
        ptr_lim = ptr->next;
        ptr_bef->next = ptr_lim;
        ptr->next = NULL;
        ptr_bef = list;

        //insert the ptr somewhere
        if(strcmp(ptr_bef->title, ptr->title) > 0){ //head
            ptr->next = ptr_bef;
            list = ptr;
        } else {
            while(ptr_bef->next != ptr_lim){
                if(strcmp(ptr_bef->next->title, ptr->title) > 0){
                    break;
                }
                ptr_bef = ptr_bef->next;
            }
            ptr->next = ptr_bef->next;
            ptr_bef->next = ptr;
        }
        while(ptr_bef->next != ptr_lim) ptr_bef = ptr_bef->next;
        ptr = ptr_lim;
    }
    return list;
}

/*Prints the song entry/ies. If “printType” is 0, all fields but the ID is printed. Otherwise, all fields are printed. If printAll is 0, only the first node is printed. Otherwise, the entire list is printed.*/
void printSLEntry(SongList * song, int printType, int printAll){ //0: print all but the id; 1: print all //0: print 1 song; 1: print all
    SongList * ptr = song;
    int spaces;
    while(ptr){
        if(printType) printf("%d%s", ptr->id, ptr->id > 9999999 ? "" : "\t");
        printf("%s", ptr->title);
        for(spaces = strlen(ptr->title); spaces < 40; spaces++) printf(" ");
        printf("%s", ptr->artist);
        for(spaces = strlen(ptr->artist); spaces < 24; spaces++) printf(" ");
        printf("%s", ptr->composer);
        for(spaces = strlen(ptr->composer); spaces < 20; spaces++) printf(" ");
        printf("%s", ptr->album);
        for(spaces = strlen(ptr->album); spaces < 24; spaces++) printf(" ");
        printf("%s", ptr->genre);
        for(spaces = strlen(ptr->genre); spaces < 16; spaces++) printf(" ");
        printf("%.2f    ", ptr->rating);
        printf("%s", ptr->remarks);
        if(!printAll) break;
        ptr = ptr->next;
    }
}

/*Frees the list upon program exit.*/
void freeList(SongList * song){
    SongList * ptr = song;
    while(ptr){
        ptr = ptr->next;
        free(song->title);
        free(song->artist);
        free(song->composer);
        free(song->album);
        free(song->genre);
        free(song->remarks);
        free(song);
        song = ptr;
    }
}

/*
    HELPER FUNCTIONS
    - Help with editing strings, values, etc.
*/

//Copied from my MP1 and Class Project
/*Removes whitespaces on the beginning and end of the string.*/
void trim(char * string){
    int ndx_s = 0; /*start of string*/
    int ndx_e = strlen(string) - 1; /*end of string*/

    /*Removes whitespaces after text*/
    while(*(string+ndx_e) == ' ' || *(string+ndx_e) == '\t' || *(string+ndx_e) == '\n'){
        *(string+ndx_e) = '\0';
        ndx_e--;
    }
    ndx_e++;

    int ndx_s_out = 0; /*start of string w/o whitespaces*/
    for(ndx_s = 0; ndx_s <= ndx_e; ndx_s++){
        if(*(string+ndx_s) == ' ' || *(string+ndx_s) == '\t' || *(string+ndx_s) == '\n'){
            ndx_s_out++;
        } else {
            break;
        }
    }

    /*shifting of characters, removing whitespace*/
    if(ndx_s_out){
        for(ndx_s = 0; ndx_s + ndx_s_out <= ndx_e; ndx_s++){
            *(string+ndx_s) = *(string+ndx_s+ndx_s_out);
        }
    }
}

/*Initializes the array of field strings (eg. “Title”, “Artist”, etc.)*/
char** tableInit(char** cols){
    cols = (char**) malloc(sizeof(char*)*8);
    int x;
    for(x=0;x<8;x++){
        *(cols+x) = (char*) malloc(sizeof(char)*STRSHORT);
        switch(x){
            case 0: strcpy(*(cols+x), "ID"); break;
            case 1: strcpy(*(cols+x), "Title"); break;
            case 2: strcpy(*(cols+x), "Artist"); break;
            case 3: strcpy(*(cols+x), "Composer"); break;
            case 4: strcpy(*(cols+x), "Album"); break;
            case 5: strcpy(*(cols+x), "Genre"); break;
            case 6: strcpy(*(cols+x), "Rating"); break;
            case 7: strcpy(*(cols+x), "Remarks"); break;
            default: break;
        }
    }
    return cols;
}

/*Converts the string into lower case.*/
void stringCase(char * string){
    char * ptr = string;
    while(*ptr != '\0'){
        *ptr = tolower(*ptr);
        ptr++;
    }
}

/*Finds the string b in the string a as a substring. Basically strstr() but ignoring case.*/
int queryFind(char * a, char * b){
    //find b in a
    char * acpy = (char*) malloc(strlen(a));
    strcpy(acpy, a);
    stringCase(acpy);
    stringCase(b);
    if(strstr(acpy, b)){
        free(acpy);
        return 1;
    } else {
        free(acpy);
        return 0;
    }
}

/*
    FILE IO FUNCTIONS
    - For reading and writing on files
*/

/*Imports the song library from the filestream as a SongList. The maxID determines the next IDs of songs to be added.*/
SongList * importLibrary(SongList * library, FILE * fp, int * maxID){
    if(!fp) return NULL; //doublechecking
    char string[STRLEN];
    fgets(string, STRLEN, fp);
    while(string[0] != '\0' && string[0] != '\n'){
        if(string[0] != '#'){ //# comment
            if(string[0] != '~'){ //~max id metadata
                library = addSong(library, string);
            } else {
                *maxID = atoi(string+1);
            }
        }
        string[0] = '\0';
        fgets(string, STRLEN, fp);
    }
    return library;
}

/*Exports the song library into the filestream. The maxID is stored in the file as well for future use.*/
void exportLibrary(SongList * library, FILE * fp, int maxID){
    if(!fp) return;
    SongList * ptr = library;
    char output[STRLEN];
    char rating_s[5];
    output[0] = '\0';
    sprintf(output, "~%d\n", maxID);
    fputs(output, fp);
    while(ptr){
        sprintf(output, "%d", ptr->id);
        strcat(output, "\t");
        strcat(output, ptr->title);
        strcat(output, "\t");
        strcat(output, ptr->artist);
        strcat(output, "\t");
        strcat(output, ptr->composer);
        strcat(output, "\t");
        strcat(output, ptr->album);
        strcat(output, "\t");
        strcat(output, ptr->genre);
        strcat(output, "\t");
        sprintf(rating_s, "%.2f", ptr->rating);
        strcat(output, rating_s);
        strcat(output, "\t");
        strcat(output, ptr->remarks);
        fputs(output, fp);
        ptr = ptr->next;
    }
}

/*
    DATA PROCESSING FUNCTIONS
    - These functions deal with data before writing on the file
*/

/*Adds a song to the song library.*/
SongList * addSongData(SongList * library, char ** cols, int * maxID){
    char string[STRSHORT];
    char output[STRLEN];
    char delim = '\t';

    sprintf(output, "%d", (*maxID)+1);
    (*maxID)++;
    //get the other data
    int x;
    float rating = 0;
    for(x=1; x<8; x++){
        printf("\nEnter %s%s: ", *(cols+x), x==2 ? " (Separate multiple artists with commas)" : x==3 ? " (Separate multiple composers with commas)" : "");
        fgets(string, STRLEN, stdin);
        trim(string);
        if(strlen(string) == 0){
            if(x!=1){
                strcpy(string, "---");
            } else {
                printf("Please enter a title.\n");
                x--;
                continue;
            }
        } else {
            if(x==6){ //rating
                rating = atof(string);
                if(rating < 1 || rating > 5){
                    printf("Please choose a score from 1 to 5 only.\n");
                    x--;
                    continue;
                }
            }
        }
        strcat(output, "\t");
        strcat(output, string);
    }
    strcat(output, "\n");
    //fputs(output, fp);
    library = addSong(library, output);
    return library;
}

/*Views the entire library.*/
void viewAllData(SongList * library){
    printf("ID      Title                                   Artist                  Composer            Album                   Genre           Rating  Remarks\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printSLEntry(library, 2, 1);
}

/*Searches the song library for a value under the specified field.*/
void execListQuery(SongList * library, int field, char * value){
    if(!value){
        value = (char*) malloc(sizeof(char)*4);
        strcpy(value, "---");
    }
    int isFound = 0, isQueried = 0;
    SongList * ptr = library;
    //check for queries with the value
    while(ptr){
        switch(field){
            case 0: if(ptr->id == atoi(value)) isQueried = 1; break;
            case 1: if(queryFind(ptr->title, value)) isQueried = 1; break;
            case 2: if(queryFind(ptr->artist, value)) isQueried = 1; break;
            case 3: if(queryFind(ptr->composer, value)) isQueried = 1; break;
            case 4: if(queryFind(ptr->album, value)) isQueried = 1; break;
            case 5: if(queryFind(ptr->genre, value)) isQueried = 1; break;
            case 6: if(ptr->rating >= atof(value)) isQueried = 1; break;
            default: break;
        }
        if(isQueried){
            if(!isFound){
                if(!field) printf("ID      ");
                printf("Title                                   Artist                  Composer            Album                   Genre           Rating\n");
                if(!field) printf("~~~~~~~~");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                isFound++;
            }
            printSLEntry(ptr, field?0:1, 0);
        }
        ptr = ptr->next;
        isQueried = 0;
    }

    if(!isFound){
        printf("No songs match the query. Try again.\n");
    }
}

/*Handles the user input of the list query.*/
void processListQuery(SongList * library, char ** cols){
    if(!library){
        printf("Your library is empty. Add songs!\n");
        return;
    }
    char string[STRLEN];
    int x;
    char delim = ' ';
    char * value = NULL;
    do{
        printf("\nPlease enter a valid query.\nForm: <field> <value> or ALL / QUIT\n:: ");
        fgets(string, STRLEN, stdin);
        if(!strcasecmp(string, "all\n")){
            viewAllData(library);
            return;
        } else if (!strcasecmp(string, "quit\n")){
            return;
        }
        //process query
        trim(string);
        if(strlen(string) == 0){
            viewAllData(library);
            return;
        }
        value = strtok(string, &delim);
        for(x=0; x<7; x++){
            if(!strcasecmp(value, *(cols+x))){
                //printf("Field: %s\n", *(cols+x));
                value = strtok(NULL, "\0");
                //printf("Value: %s\n\n", value);
                break;
            }
        }
        if(x==7){
            printf("No such field. Try Again.\n");
            continue;
        } else {
            break;
        }
    }while(1);
    //at this point, the field and value are set
    //x is the number of the query kind
    execListQuery(library, x, value);
}

/*Updates a song entry.*/
SongList * updateSongData(SongList * library, char ** cols){
    char string[STRSHORT];
    printf("\nEnter title of song you want to update: ");
    fgets(string, STRLEN, stdin);
    trim(string);
    //search for songs with the title
    SongList * ptr = library;
    SongList ** ptrlist = malloc(sizeof(SongList*));
    int songNum = 0;
    int id = 0;
    int ctr;
    while(ptr){
        if(queryFind(ptr->title, string)){
            if(!songNum){
                printf("\nID      Title                                   Artist                  Composer        Album                   Genre           Rating  Remarks\n");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            }
            printSLEntry(ptr, 1, 0);
            *(ptrlist+songNum) = ptr;
            songNum++;
            ptrlist = realloc(ptrlist, (sizeof(SongList*))*(songNum+1));
        }
        ptr = ptr->next;
    }

    if(songNum){
        if(songNum > 1){
            do{
                printf("\nIndicate ID of song you want to edit: ");
                scanf("%d", &id);
                getchar();
                for(ctr=0; ctr < songNum; ctr++){
                    if((*(ptrlist+ctr))->id == id){
                        ptr = *(ptrlist+ctr);
                        break;
                    }
                }
                if(ctr==songNum){ printf("Please try again.\n"); }
                else{
                    printf("\nID      Title                                   Artist                  Composer        Album                   Genre           Rating  Remarks\n");
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    printSLEntry(ptr, 1, 0);
                }
            }while(ctr == songNum);
        } else if(songNum == 1){
            ptr = (*ptrlist);
        }
    } else {
        printf("\nNo record of said song here.\n");
        return library;
    }

    free(ptrlist);

    if(!ptr){
        printf("Error occurred. Please try again.\n");
        return library;
    }

    //time to update
    //ptr = song to update; string: holds the new values
    for(ctr=1; ctr<8; ctr++){
        printf("\nEnter new %s%s, --- to set to null, or just press Enter to skip editing this field: ", *(cols+ctr), ctr==2 ? "/s" : (ctr==3 ? "/s" : ""));
        fgets(string, STRLEN, stdin);
        trim(string);
        if(strlen(string) == 0) continue;
        switch(ctr){
            case 1: strcpy(ptr->title, string); break;
            case 2: strcpy(ptr->artist, string); break;
            case 3: strcpy(ptr->composer, string); break;
            case 4: strcpy(ptr->album, string); break;
            case 5: strcpy(ptr->genre, string); break;
            case 6:
                ptr->rating = atof(string);
                if(ptr->rating < 1 || ptr->rating > 5){
                    printf("Please choose a score from 1 and 5 only.\n");
                    ctr--;
                }
                break;
            case 7: strcpy(ptr->remarks, strcat(string, "\n")); break;
            default: break;
        }
    }
    printf("Editing completed!\n");
    return library;
}

/*Function ran upon program start.*/
void main(){
    FILE * fp = NULL;
    char choice[STRSHORT];
    char** cols = NULL;
    SongList * library = NULL;
    int maxID = 0;
    printf("**************\n** Welcome! **\n**************\n");
    cols = tableInit(cols);

    //get the files
    char filepath[STRSHORT*2];
    printf("\nEnter input file path (library.output by default):: ");
    fgets(filepath, STRSHORT*2, stdin);
    trim(filepath);
    if(strlen(filepath)){
        fp = fopen(filepath, "r");
    } else {
        fp = fopen("library.output", "r");
    }
    if(fp){
        library = importLibrary(library, fp, &maxID);
        fclose(fp);
    } else {
        printf("No such file. Will start from empty library.\n");
    }
    printf("\nEnter output file path (library.output by default):: ");
    fgets(filepath, STRSHORT*2, stdin);
    trim(filepath);
    library = sortInsertion(library, 0);

    //start the program loop proper
    do{
        printf("\nEnter the command or first letter:\n(Add) entry\n(Update) entry\n(List) entries\n(Quit) program\n:: ");
        fgets(choice, STRSHORT, stdin);
        trim(choice);
        if(!strcasecmp(choice, "add") || !strcasecmp(choice, "a")){
            library = addSongData(library, cols, &maxID);
            library = sortInsertion(library, 1);
        } else if(!strcasecmp(choice, "list") || !strcasecmp(choice, "l")){
            processListQuery(library, cols);
        } else if(!strcasecmp(choice, "quit") || !strcasecmp(choice, "q")){
            printf("\n**************\n** Goodbye! **\n**************\n");
            break;
        } else if(!strcasecmp(choice, "update") || !strcasecmp(choice, "u")){
            library = updateSongData(library, cols);
        } else {
            printf("Try again.\n");
        }
    }while(1);
    int x;
    for(x=0; x<8; x++){
        free(*(cols+x));
    }
    free(cols);
    if(strlen(filepath)){
        fp = fopen(filepath, "w");
    } else {
        fp = fopen("library.output", "w");
    }
    exportLibrary(library, fp, maxID);
    fclose(fp);
    freeList(library);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STRSHORT 50
#define STRLEN 200
#define STRLONG 500

//mostly to be used for search queries
//for write queries, simple string concatenation will do
//more often than not only the song id, title and artist are needed
typedef struct SongList{
    int songID;
    char * songTitle;
    char * songArtist;
    char * songComposer;
    char * songAlbum;
    char * songGenre;
    float songRating;
    char * songRemarks;
    struct SongList * next; //in the case of a single song query, this will be null
} SongList;

SongList * createList(SongList * song){
    song = (SongList*) malloc(sizeof(SongList));
    song->next = NULL;
    return song;
}

SongList * addSong(SongList * song){
    if(!song) return createList(song);
    SongList * head = (SongList*) malloc(sizeof(SongList));
    head->next = song;
    return head;
}

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

FILE * addData(FILE * fp, char ** cols){
    char string[STRSHORT];
    char output[STRLEN];
    char delim = '\t';
    FILE * fpid;
    //assign an ID
    fpid = fopen("rawlib.output", "r");
    if(!fpid){
        printf("Error occurred. Please try again.\n");
        return fp;
    }

    int id = -1;
    fgets(output, STRLEN, fpid);
    if(strlen(output) <= 0){ //newfile
        //printf("output is <=0\n");
        id = 1;
    } else {
        id = atoi(strtok(output, &delim));
        //printf("%s\n", output);
        //printf("%d\n", atoi(strtok(output, &delim)));
        //printf("%d\n", id);
        while(id || output[0] == '#'){
            fgets(output, STRLEN, fpid);
            if(id < atoi(strtok(output, &delim))){
                id = atoi(strtok(output, &delim));
            } else {
                if(id) break;
            }
            //printf("%s\n", strtok(output, &delim));
            //printf("%d\n", atoi(strtok(output, &delim)));
            //printf("%d\n", id);
        }
        id++;
    }
    output[0] = '\0';
    //printf("end:%d\n", id);
    sprintf(output, "%d", id);
    int x;
    for(x=1; x<8; x++){
        printf("Enter %s: ", *(cols+x));
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
        }
        strcat(output, "\t");
        strcat(output, string);
    }
    strcat(output, "\n");
    fputs(output, fp);
    fclose(fpid);
    return fp;
}

void printEntry(char string[]){
    if(string[0] != '#'){
        char * token;
        char delim = '\t';
        int spaces = 0;
        token = strtok(string, &delim); //ID
        printf("%s", token);
        for(spaces = strlen(token); spaces < 8; spaces++) printf(" ");
        token = strtok(NULL, &delim); //Title
        printf("%s", token);
        for(spaces = strlen(token); spaces < 40; spaces++) printf(" ");
        token = strtok(NULL, &delim); //Artist
        printf("%s", token);
        for(spaces = strlen(token); spaces < 24; spaces++) printf(" ");
        token = strtok(NULL, &delim); //Composer
        printf("%s", token);
        for(spaces = strlen(token); spaces < 16; spaces++) printf(" ");
        token = strtok(NULL, &delim); //Album
        printf("%s", token);
        for(spaces = strlen(token); spaces < 24; spaces++) printf(" ");
        token = strtok(NULL, &delim); //Genre
        printf("%s", token);
        for(spaces = strlen(token); spaces < 16; spaces++) printf(" ");
        token = strtok(NULL, &delim); //Rating
        printf("%s", token);
        for(spaces = strlen(token); spaces < 8; spaces++) printf(" ");
        token = strtok(NULL, &delim); //Remarks
        printf("%s", token);
    }
}

void viewData(FILE * fp){
    printf("ID      Title                                   Artist                  Composer        Album                   Genre           Rating  Remarks\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    char string[STRLEN];
    fgets(string, STRLEN, fp);
    while(string[0] != '\0' && string[0] != '\n'){
        printEntry(string);
        string[0] = '\0';
        fgets(string, STRLEN, fp);
    }
}

void execListQuery(int field, char * value, FILE * fp, char ** cols){
    int forctr;
    SongList * results;
    //check for queries with the value
    char string[STRLEN];
    fgets(string, STRLEN, fp);
    char * entryValue;
    char delim = '\t';
    printf("ID      Title                                   Artist                  Composer        Album                   Genre           Rating  Remarks\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    while(string[0] != '\0' && string[0] != '\n'){
        if(string[0] != '#'){
            entryValue = strtok(string, &delim);
            for(forctr=0; forctr<field; forctr++) entryValue = strtok(NULL, &delim);
            printf("%s\n", entryValue);
            if(!strcasecmp(entryValue, value)){
                /*
                results = addSong(results);
                results->songID  = atoi(strtok(string, &delim));
                results->songTitle = (char*) malloc(sizeof(char)*STRSHORT);
                strcpy(results->songTitle, strtok(NULL, &delim));
                results->songArtist = (char*) malloc(sizeof(char)*STRSHORT);
                strcpy(results->songArtist, strtok(NULL, &delim));
                */
                printf("%s", string)
            }
        }
        string[0] = '\0';
        fgets(string, STRLEN, fp);
    }
}

void processListQuery(FILE * fp, char ** cols){
    char string[STRLEN];
    int x;
    char delim = ' ';
    char * value = NULL;
    do{
        printf("\nPlease enter a valid query.\nForm: <field> <value> or ALL / QUIT\n:: ");
        fgets(string, STRLEN, stdin);
        if(!strcmp(string, "all\n")){
            viewData(fp);
            return;
        } else if (!strcmp(string, "quit\n")){
            return;
        }
        //process query
        trim(string);
        if(strlen(string) == 0){
            printf("No entry detected. Try again.\n");
            continue;
        }
        printf("%s\n", string);
        value = strtok(string, &delim);
        for(x=0; x<7; x++){
            if(!strcasecmp(value, *(cols+x))){
                printf("Field: %s\n", *(cols+x));
                value = strtok(NULL, &delim);
                printf("Value: %s\n\n", value);
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
    //x is the number of the query kind
    execListQuery(x, value, fp, cols);
}

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

void main(){
    FILE * fpw = NULL;
    FILE * fpr = NULL;
    char choice[STRSHORT];
    char** cols;
    cols = tableInit(cols);
    printf("**************\n** Welcome! **\n**************\n");
    do{
        printf("\n(Add) entry\n(List) entries\n(Quit) program\n:: ");
        fgets(choice, STRSHORT, stdin);
        if(!strcmp(choice, "add\n")){
            fpw = fopen("rawlib.output", "a+");
            if(fpw){
                 fpw = addData(fpw, cols);
                 fclose(fpw);
            } else {
                printf("Something wrong happened. Please try again.\n");
            }
        } else if(!strcmp(choice, "list\n")){
            fpr = fopen("rawlib.output", "r");
            if(fpr){
                processListQuery(fpr, cols);
                fclose(fpr);
            } else {
                printf("File is nonexistent.\n");
            }
        } else if(!strcmp(choice, "quit\n")){
            printf("\n**************\n** Goodbye! **\n**************\n");
            break;
        } else {
            printf("Try again.\n");
        }
    }while(1);
    int x;
    for(x=0; x<8; x++){
        free(*(cols+x));
    }
    free(cols);
}

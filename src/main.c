#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

fpos_t file_size(FILE *file){
    if(!file){return 0;}
    fpos_t original = 0;
    if(fgetpos(file, &original) != 0){
        printf("fgetpos() faile: %i", errno);
        return 0;   

    }

    fseek(file, 0, SEEK_END);
    long out = ftell(file);

    if(fsetpos(file, &original) != 0){
        printf("fsetpos() failed: %i\n", errno);
    }
    return out;
}

char *file_contents(char *path){
    FILE *file = fopen(path,  "r");
    if(!file){
        printf("Could not open file at %s\n", path);
        return NULL;
    }
    long size = file_size(file);
    char *contents = malloc(size + 1);
    char *write_it = contents;
    size_t bytes_read = 0;
    while(bytes_read < size){
        size_t bytes_read_this_iteration = fread(contents, 1, size - bytes_read, file);
        if(ferror(file)){
            printf("Error while reading: %i\n", errno);
            free(contents);
            return NULL;
        }

        bytes_read += bytes_read_this_iteration;
        write_it += bytes_read_this_iteration;
        if(feof(file)){
            break;
            }
    }

    contents[bytes_read] = '\0';
    return contents;
}

void print_usage(char **argv){
    printf("USAGE: %s <path_to_file_to_compile>\n", argv[0]);
}

typedef struct Error{
    enum ErrorType{
        ERROR_NONE = 0,
        ERROR_ARGUMENTS,
        ERROR_TYPE,
        ERROR_TODO,
        ERROR_SYNTAX,
        ERROR_GENERIC,
    } type;
    char *msg;
}Error;

Error ok = {ERROR_NONE, NULL};

void print_error(Error err){
    if (err.type == ERROR_NONE){
        return;
    }
    printf("Error: ");
    switch(err.type){
        default:
            printf("Unkown error type...");
            break;
       
        case ERROR_TODO:
            printf("TODO (not implemented)");
            break;
        case ERROR_SYNTAX:
            printf("Invalid Syntax");
            break;
        case ERROR_TYPE:
            printf("Mismatched types");
            break;
        case ERROR_ARGUMENTS:
            printf("Invalid arguments"); 
        case ERROR_NONE:
            break;
        case ERROR_GENERIC:
            break;
    }
    putchar('\n');
    if(err.msg){
        printf("     : %s\n", err.msg);
    }


}

#define ERROR_CREATE(n, t, msg)  \
            Error(n) = {(t), (msg)} 
#define ERROR_PREP(n, t, message) \
        (n).type = (t);           \
        (n).msg = (message);

const char *whitespace = " \r\n";
const char *delimiters = "\r\n";

// Lex the next Token from source, and point to it with BEG and END.
Error lex(char *source, char **beg, char **end){
    Error err = ok;
    if(!source || !beg || !end) {
        ERROR_PREP(err, ERROR_ARGUMENTS, "Can Not lex empty source.");
        return err; 
    }
    *beg = source;
    *beg += strspn(*beg, whitespace);
    *end = *beg;
    *end += strcspn(*beg, delimiters);
    return err;
}

Error parse_expr(char *source){
    char *beg = source;
    char *end = source;
    Error err = ok;
    while((err = lex(end, &beg, &end)).type == ERROR_NONE){
        if(end - beg == 0){ break;}
        printf("lexed: %.*s\n", end - beg, beg);   
    }
    
    return err;

};

int main(int argc, char **argv){
    if(argc < 2){
        print_usage(argv);
        exit(0);
    }

    char *path = argv[1];
    char *contents = file_contents(path);
    if(contents){
        printf("Contents of %s: \n---\n\"%s\"\n---\n", path, contents);

        Error err = parse_expr(contents);
        print_error(err);

        free(contents);

    }


    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

#define STR_SIZE 1024
#define CHUNK_SIZE 4096
#define ARRAY_COUNT(arr) (sizeof(arr) / sizeof(arr[0]))
#define LEN(arr) ARRAY_COUNT(arr)-1

char HOOK_KEYWORD[] = "HOOK";

int bracket_count = 0;
int parenthesis_count = 0;

List list_hook = {NULL, NULL, 0};

#define END_OF_WORD(char_) (char_ == ' ' \
    || char_ == '(' \
    || char_ == ')' \
    || char_ == '{' \
    || char_ == '}' \
    || char_ == ',' \
    || char_ == '\n' \
    || char_ == '\0' \
    || char_ == '"' \
    || char_ == ';' \
    || char_ == '\t' \
    || char_ == '*' )

#define END_TYPE(char_) (char_ == '(' \
    || char_ == '{' \
    || char_ == '}' \
    || char_ == '\n' \
    || char_ == '\0' \
    || char_ == '\t' )

typedef struct {
    char source[STR_SIZE];
    char function[STR_SIZE];
    char at[STR_SIZE];
    bool cancelable;
    int priority;
    char function_call[STR_SIZE];
    int num_args;
} Hook;

void load_list_hook(char * file, char * source) {
    FILE *file_ = fopen(file, "rb");
    if (!file_) {
        return;
    }
    Hook hook;
    for (int size = 0; (size = fread(&hook, 1, sizeof(Hook), file_)) > 0; ) {
        if (strcmp(hook.source, source) == 0) {
            continue;
        }
        Hook *hook_ = malloc(sizeof(Hook));
        memcpy(hook_, &hook, sizeof(Hook));
        list_append(&list_hook, hook_);
    }
}

void save_list_hook(char * file) {
    FILE *file_ = fopen(file, "wb");
    ListElement *element = list_hook.head;
    while (element) {
        Hook *hook = element->data;
        fwrite(hook, 1, sizeof(Hook), file_);
        element = element->next;
    }
}

void print_list_hook() {
    ListElement *element = list_hook.head;
    while (element) {
        Hook *hook = element->data;
        printf("Hook: %s %s %d %d\n", hook->function, hook->at, hook->cancelable, hook->priority);
        element = element->next;
    }
}

bool match_file(char * file, char * hook_file) {
    int end_file_char = strlen(file);
    int end_hook_file_char = strlen(hook_file);
    while (file[end_file_char] == hook_file[end_hook_file_char]) {
        end_file_char--;
        end_hook_file_char--;
    }
    return end_hook_file_char == 0;
}

char *get_c_file(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        if (strstr(argv[i], ".c")) {
            return argv[i];
        }
    }
    return NULL;
}

void gen_out_name(char *file_name, char *out_name) {
    char last_char = '\0';
    for (int i = 0; i < strlen(file_name); i++) {
        if (file_name[i] == 'c' && last_char == '.') {
            out_name[i] = 'o';
            out_name[i+1] = 'u';
            out_name[i+2] = 't';
            out_name[i+3] = '.';
            out_name[i+4] = 'c';
            break;
        }
        out_name[i] = file_name[i];
        last_char = file_name[i];
    }
}

int get_lastword(char *str) {
    int pos = 0;
    for (int i =0; str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == '\n' || str[i] == '*') {
            pos = i;
        }
    }
    return pos+1;
}

void copy_before_lastword(char *str, char *str_) {
    int pos = get_lastword(str);
    for (int i = 0; i < pos; i++) {
        str_[i] = str[i];
    }
}

void insert_arg(FILE* file, char full_arg_list[16][STR_SIZE], int num_args) {
    for (int i = 0; i < num_args; i++) {
        fprintf(file, "%s", &full_arg_list[i][get_lastword(full_arg_list[i])]);
        if (i < num_args-1) {
            fprintf(file, ", ");
        }
    }
}

void header_function(FILE* file_out, Hook *hook, char full_arg_list[16][STR_SIZE], char *return_type) {
    if (!hook->cancelable && strncmp(return_type, "void", 4) == 0) {
        fprintf(file_out, "    void %s(", hook->function_call);
    } else {
        fprintf(file_out, "    %s%s(", return_type,hook->function_call);
    }
    for (int i = 0; i < hook->num_args; i++) {
        fprintf(file_out, "%s", full_arg_list[i]);
        if (i < hook->num_args-1) {
            fprintf(file_out, ", ");
        }
    }
    if (hook->cancelable) {
        if (hook->num_args > 0) {
            fprintf(file_out, ", ");
        }
        fprintf(file_out, "bool *cancel");
    }
    fprintf(file_out, ");\n");
}

void insert_function(FILE* file_out, Hook *hook, char full_arg_list[16][STR_SIZE], char *return_type){
    // header_function(file_out, hook, full_arg_list, return_type);
    
    if (hook->cancelable) {
        if (strncmp(return_type, "void", 4) == 0) {
            fprintf(file_out, "    %s(", hook->function_call);
            insert_arg(file_out, full_arg_list, hook->num_args);
            if (hook->num_args > 0) {
                fprintf(file_out, ", ");
            }
            fprintf(file_out, "&cancel);\n");
            fprintf(file_out, "    if (cancel) { return; }\n");
        } else {
            fprintf(file_out, "    result = %s(", hook->function_call);
            insert_arg(file_out, full_arg_list, hook->num_args);
            if (hook->num_args > 0) {
                fprintf(file_out, ", ");
            }
            fprintf(file_out, "&cancel);\n");
            fprintf(file_out, "    if (cancel) { return result; }\n");
        }
    } else {
        fprintf(file_out, "    %s(", hook->function_call);
        insert_arg(file_out, full_arg_list, hook->num_args);
        fprintf(file_out, ");\n");
    }
}

bool insert_header_hook(FILE* file, char *function_name, char full_arg_list[16][STR_SIZE], char *return_type_) {
    fwrite("{\n", 1, 2, file);
    if (strncmp(return_type_, "void", 4) != 0) {
        fprintf(file, "%sresult;\n", return_type_);
    }
    ListElement *element = list_hook.head;
    bool cancel_insert = false;
    while (element) {
        Hook *hook = element->data;
        if (strcmp(hook->function, function_name) == 0) {
            header_function(file, hook, full_arg_list, return_type_);
            cancel_insert |= hook->cancelable;
        }
        element = element->next;
    }
    if (cancel_insert) {
        fprintf(file, "    bool cancel = FALSE;\n");
    }
    return true;
}

void insert_original_function_header(FILE* file, char *return_type, char* function_name,char full_arg_list[16][STR_SIZE], int full_arg_list_idx){
    fprintf(file, "    %soriginal_%s(", return_type, function_name);
    for (int i = 0; i <= full_arg_list_idx; i++) {
        fprintf(file, "%s", full_arg_list[i]);
        if (i < full_arg_list_idx) {
            fprintf(file, ", ");
        }
    }
    fprintf(file, ");\n");
}

void insert_original_function(FILE* file, char *return_type, char* function_name,char full_arg_list[16][STR_SIZE], int full_arg_list_idx, bool function_return) {
    // insert_original_function_header(file, return_type, function_name, full_arg_list, full_arg_list_idx);

    if (function_return) {
        fprintf(file, "    result = original_%s(", function_name);
    } else {
        fprintf(file, "    original_%s(", function_name);
    }
    insert_arg(file, full_arg_list, full_arg_list_idx+1);
    fprintf(file, ");\n");
}

void insert_hooks(FILE* file_out, char *return_type, char *function_name, char full_arg_list[16][STR_SIZE], int full_arg_list_idx, bool* file_modified) {
    bool hook_inserted = false;
    char return_type_[STR_SIZE] = "";
    copy_before_lastword(return_type, return_type_);
    
    bool function_return = false;
    if (strncmp(return_type, "void", 4) != 0) {
        function_return = true;
    }

    ListElement *element = list_hook.head;
    while (element) {
        Hook *hook = element->data;
        if (strcmp(hook->function, function_name) == 0 && strcmp(hook->at, "AT(FUNCTION_CALL)") == 0) {
            
            if (!hook_inserted) {
                hook_inserted = insert_header_hook(file_out, function_name, full_arg_list, return_type_);
                insert_original_function_header(file_out, return_type_, function_name, full_arg_list, full_arg_list_idx);
            }
            // printf("Hook found: %s %s %s %d\n", hook->file, hook->function, hook->at, hook->num_args);
            insert_function(file_out, hook, full_arg_list, return_type_);
        }
        element = element->next;
    }
    if (hook_inserted) {
        insert_original_function(file_out, return_type_, function_name, full_arg_list, full_arg_list_idx, function_return);
    }
    element = list_hook.head;
    while (element) {
        Hook *hook = element->data;
        if (strcmp(hook->function, function_name) == 0 && strcmp(hook->at, "AT(FUNCTION_RETURN)") == 0) {
            if (!hook_inserted) {
                hook_inserted = insert_header_hook(file_out, function_name, full_arg_list, return_type_);
                insert_original_function_header(file_out, return_type_, function_name, full_arg_list, full_arg_list_idx);
                insert_original_function(file_out, return_type_, function_name, full_arg_list, full_arg_list_idx, function_return);
            }
            // printf("Hook found: %s %s %s\n", hook->file, hook->function, hook->at);
            insert_function(file_out, hook, full_arg_list, return_type_);
        }
        element = element->next;
    }
    if (hook_inserted) {
        if (function_return){
            fprintf(file_out, "    return result;\n}\n\n%soriginal_%s(", return_type_, function_name);
        } else {
            fprintf(file_out, "}\n\n%soriginal_%s(", return_type_, function_name);
        }
        for (int i = 0; i <= full_arg_list_idx; i++) {
            fprintf(file_out, "%s", full_arg_list[i]);
            if (i < full_arg_list_idx) {
                fprintf(file_out, ", ");
            }
        }
        fprintf(file_out, ") ");
    }
    *file_modified = *file_modified || hook_inserted;
}

char* get_and_apply_hooks(char *file_name) {
    FILE *file = fopen(file_name, "r");

    // char file_out_name[] = "test/src/main.out.c";
    char *file_out_name = malloc(strlen(file_name)+5);
    gen_out_name(file_name, file_out_name);
    FILE *file_out = fopen(file_out_name, "wb");

    load_list_hook("hook.bin", file_name);

    char str_[CHUNK_SIZE] = "";
    bool in_quote = false;

    char full_arg_list[16][STR_SIZE] = {""};
    int full_arg_list_idx = 0;
    int full_arg_list_len = 0;

    Hook *hook = malloc(sizeof(Hook));
    strcpy(hook->source, file_name);

    char word_name[STR_SIZE] = "";
    int word_name_len = 0;
    bool end_of_word = false;

    char function_name[STR_SIZE] = "";
    bool in_function = false;

    char return_type[STR_SIZE] = "";
    int return_type_len = 0;

    bool in_return_type = true;
    bool start_get_return_type = false;

    bool in_hook = false;
    int in_hook_level = 0;
    bool finalise_hook = false;

    bool file_modified = false;
    for (int size = 0; (size = fread(str_, 1, CHUNK_SIZE, file)) > 0; ) {
        for (int i = 0; i < size; i++) {
            char char_ = str_[i];
            if (char_ == '"') {
                in_quote = !in_quote;
            }

            if (in_quote) {
                fwrite(&char_, 1, 1, file_out);
            }

            if (!in_quote) {
                if (char_ == ')') { // end of function call
                    parenthesis_count--;
                    if (in_hook_level == parenthesis_count && in_hook) {
                        in_hook = false;

                        strcpy(hook->function, full_arg_list[0]);
                        strcpy(hook->at, full_arg_list[1]);

                        for (int i = 0; i <= full_arg_list_idx; i++) {
                            printf("Arg: %s\n", full_arg_list[i]);
                        }

                        if (full_arg_list_idx > 1) {
                            printf("cancelable: %s %d\n", full_arg_list[2], strncmp(full_arg_list[2], "TRUE", 4));
                            hook->cancelable = (strncmp(full_arg_list[2], "TRUE", 4) == 0) || (strncmp(full_arg_list[2], "true", 4) == 0);
                        } else {
                            hook->cancelable = false;
                        }

                        if (full_arg_list_idx > 2) {
                            hook->priority = atoi(full_arg_list[3]);
                        } else {
                            hook->priority = 0;
                        }

                        finalise_hook = true;
                    }
                    if (parenthesis_count == 0) {
                        // printf("function name: %s\n", function_name);
                        // for (int i = 0; i <= full_arg_list_idx; i++) {
                        //     printf("Arg: %s\n", full_arg_list[i]);
                        // }
                    }
                }
                if (char_ == '}') { // end of code block
                    if (in_function && bracket_count == 1) {
                        in_function = false;
                        for (int i = 0; function_name[i] != '\0'; i++) {
                            function_name[i] = '\0';
                        }
                    }
                    bracket_count--;
                }
            }
            
            if (parenthesis_count>0 && !(char_ == ',' && !in_quote && parenthesis_count == 1) && char_!='"' && !(char_ == ' ' && (full_arg_list[full_arg_list_idx][0] == '\0' || full_arg_list[full_arg_list_idx][full_arg_list_len-1] == ',' || full_arg_list[full_arg_list_idx][full_arg_list_len-1] == ' '))) {
                full_arg_list[full_arg_list_idx][full_arg_list_len++] = char_;
            }

            if (char_ == ',' && !in_quote && parenthesis_count == 1) {
                full_arg_list_idx++;
                full_arg_list_len = 0;
            }

            if (in_return_type) {
                if (start_get_return_type) {
                    for (int i = 0; i < return_type_len; i++) {
                        return_type[i] = '\0';
                    }
                    return_type_len = 0;
                    start_get_return_type = false;
                }
                if (END_TYPE(char_)) {
                    in_return_type = false;
                } else {
                    return_type[return_type_len++] = char_;
                }
            }

            if(!in_return_type) {
                if (char_ == '\n') {
                    in_return_type = true;
                    start_get_return_type = true;
                }
            }


            if (!in_quote) {

                if (char_ == '{') { // start of code block
                    if (parenthesis_count == 0 && bracket_count == 0 && function_name[0] != '\0') {
                        in_function = true;
                        insert_hooks(file_out, return_type, function_name, full_arg_list, full_arg_list_idx, &file_modified);
                    }
                    if (finalise_hook) {
                        strcpy(hook->function_call, function_name);
                        hook->num_args = full_arg_list_idx;
                        hook->num_args++;
                        if (hook->cancelable) {
                            hook->num_args--;
                        }
                        printf("functions name: %s\n", hook->function_call);
                        for (int i = 0; i <= full_arg_list_idx; i++) {
                            printf("Arg: %s\n", full_arg_list[i]);
                        }
                        print_list_hook();
                        list_append(&list_hook, hook);
                        hook = NULL;
                        finalise_hook = false;
                    }
                    bracket_count++;
                }

                if (char_ == '(') { // start of function call
                    if (parenthesis_count == 0) {
                        for (int i = 0; i <= full_arg_list_idx; i++) {
                            int size = 0;
                            while (full_arg_list[i][size] != '\0') {
                                full_arg_list[i][size++] = '\0';
                            }
                        }
                        full_arg_list_len = 0;
                        full_arg_list_idx = 0;
                    }
                    if (parenthesis_count == 0 && bracket_count == 0) {
                        strcpy(function_name, word_name);
                    }
                    if (strcmp(word_name, HOOK_KEYWORD) == 0) {
                        printf("Hook detected\n");
                        hook = malloc(sizeof(Hook));
                        strcpy(hook->source, file_name);
                        in_hook = true;
                        in_hook_level = parenthesis_count;
                    }
                    parenthesis_count++;
                }

                if (END_OF_WORD(char_)) {
                    if (!end_of_word) {
                        fwrite(word_name, 1, word_name_len, file_out);
                    }
                    fwrite(&char_, 1, 1, file_out);
                    end_of_word = true;
                } else {
                    if (end_of_word) {
                        // printf("%s\n", word_name);
                        for (int i = 0; i < word_name_len; i++) {
                            word_name[i] = '\0';
                        }
                        word_name_len = 0;
                        end_of_word = false;
                    }
                    word_name[word_name_len++] = char_;
                }
            }
        }
    }

    save_list_hook("hook.bin");
    fclose(file);
    fclose(file_out);

    printf("File modified: %s %d\n", file_name,file_modified);

    if (!file_modified) {
        if (remove(file_out_name) == 0) {
            printf("File removed: %s\n", file_out_name);
        } else {
            printf("File not removed: %s\n", file_out_name);
            exit(1);
        }
        return file_name;
    }
    return file_out_name;
}

int main(int argc, char *argv[]) {
    char **new_arg = malloc(sizeof(char*) * argc);

    for (int i = 1; i < argc; i++) {
        if (strstr(argv[i], ".c")) {
            new_arg[i-1] = get_and_apply_hooks(argv[i]);
        } else {
            new_arg[i-1] = argv[i];
        }
    }

    new_arg[argc-1] = NULL;

    int len_command = 0;
    for (int i = 0; i < argc-1; i++) {
        len_command += strlen(new_arg[i])+1;
    }

    char *command = malloc(len_command+12);
    strcpy(command, "sh -c \"");
    int command_idx = 7;
    for (int i = 0; i < argc-1; i++) {
        for (int j = 0; j < strlen(new_arg[i]); j++) {
            command[command_idx++] = new_arg[i][j];
        }
        command[command_idx++] = ' ';
    }

    command[command_idx] = '"'; //'>';
    command[command_idx+1] = '\0'; //'>';
    // command[command_idx] = '>';
    // command[command_idx+1] = '&';
    // command[command_idx+2] = '2';
    // command[command_idx+3] = '\0';

    printf("Command: %s\n", command);
    
    return system(command);
}
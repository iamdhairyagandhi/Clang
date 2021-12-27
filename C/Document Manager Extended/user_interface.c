#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <ctype.h>
#include "document.h"

/* Command List

    1   -   add_paragraph_after
    2   -   add_line_after
    3   -   print_document
    4   -   append line
    5   -   remove_line
    6   -   load_file
    7   -   replace_text
    8   -   highlight_text
    9   -   remove_text
    10  -   save_document
    11  -   reset_document

*/

/* find_command searches for command within command using strstr */
int find_command(char* command) {
    if (strstr(command, "add_paragraph_after") != NULL) {
        return 1;
    }
    else if (strstr(command, "add_line_after") != NULL) {
        return 2;
    }
    else if (strstr(command, "print_document") != NULL) {
        return 3;
    }
    else if (strstr(command, "append_line") != NULL) {
        return 4;
    }
    else if (strstr(command, "remove_line") != NULL) {
        return 5;
    }
    else if (strstr(command, "load_file") != NULL) {
        return 6;
    }
    else if (strstr(command, "replace_text") != NULL) {
        return 7;
    }
    else if (strstr(command, "highlight_text") != NULL) {
        return 8;
    }
    else if (strstr(command, "remove_text") != NULL) {
        return 9;
    }
    else if (strstr(command, "save_document") != NULL) {
        return 10;
    }
    else if (strstr(command, "reset_document") != NULL) {
        return 11;
    }
    else if (strstr(command, "quit") != NULL || strstr(command, "exit") != NULL) {
        return 12;
    }
    else {
        printf("Invalid Command\n");
        return FAILURE;
    }
}

char* remove_quotes(char* command, char* result) {
    char* str1, * str2;

    str1 = strstr(command, "\"");
    if (str1 != NULL) {
        str2 = strstr(str1 + 1, "\"");

        if (str2 != NULL) {
            strncpy(result, str1 + 1, str2 - str1);
            result[str2 - (str1 + 1)] = '\0';

            return result;
        }
    }
    return NULL;
}
/* this function searches for excecutes commands within an input string */
int command_status_checker(Document* doc, char* command) {
    int status = FAILURE, command_int = 0, i = 0, all_spaces = 0, is_comment = 0;

    while (command[i] != 0) {
        /*printf("Printf1 %c\n", command[i]);
        */if (!isspace(command[i])) {
            all_spaces++;
        }
        if (command[i] == '#') {
            /* printf("Printf\n");
            */ is_comment = 1;
            break;
        }
        i++;
    }
    if (is_comment == 1) {
        return SUCCESS;
    }
    if (all_spaces == 0) {
        return FAILURE;
    }

    command_int = find_command(command);

    if (command_int == 1) {
        char name[MAX_STR_SIZE + 1], extra[MAX_STR_SIZE + 1];
        int val, num;

        val = sscanf(command, "%s%d%s", name, &num, extra);
        if (val == 2 && num >= 0) {

            if (add_paragraph_after(doc, num) == FAILURE) {
                printf("add_paragraph_after failed\n");
            }
            return SUCCESS;
        }
        return FAILURE;
    }
    else if (command_int == 2) {
        char name[MAX_STR_SIZE + 1], line[MAX_STR_SIZE + 1];
        char flag[MAX_STR_SIZE + 1];
        int val, samp_1, samp_2;

        val = sscanf(command, "%s%d%d%s", name, &samp_1, &samp_2, flag);
        if (val == 4 && samp_1 > 0 && samp_2 >= 0) {

            if (strchr(command, '*') != NULL) {
                strcpy(line, strchr(command, '*') + 1);

                if (add_line_after(doc, samp_1, samp_2, line) == FAILURE) {
                    printf("add_line_after failed\n");
                }
                return SUCCESS;
            }
        }
        return FAILURE;
    }
    else if (command_int == 3) {
        char name[MAX_STR_SIZE + 1], flag[MAX_STR_SIZE + 1];
        int val;

        val = sscanf(command, "%s%s", name, flag);
        if (val == 1) {

            if (print_document(doc) == FAILURE) {
                printf("print_document failed\n");
            }
            return SUCCESS;
        }
        return FAILURE;
    }
    else if (command_int == 4) {
        char name[MAX_STR_SIZE + 1], line[MAX_STR_SIZE + 1];
        char flag[MAX_STR_SIZE + 1];
        int val, num;

        val = sscanf(command, "%s%d%s", name, &num, flag);
        if (val == 3 && num > 0) {

            if (strchr(command, '*') != NULL) {
                strcpy(line, strchr(command, '*') + 1);

                if (append_line(doc, num, line) == FAILURE) {
                    printf("append_line failed\n");
                }
                return SUCCESS;
            }
        }
        return FAILURE;
    }
    else if (command_int == 5) {
        char name[MAX_STR_SIZE + 1], flag[MAX_STR_SIZE + 1];
        int val, samp_1, samp_2;

        val = sscanf(command, "%s%d%d%s", name, &samp_1, &samp_2, flag);
        if (val == 3 && samp_1 > 0 && samp_2 > 0) {

            if (remove_line(doc, samp_1, samp_2) == FAILURE) {
                printf("remove_line failed\n");
            }
            return SUCCESS;
        }
        return FAILURE;
    }
    else if (command_int == 6) {
        char name[MAX_STR_SIZE + 1], file[MAX_STR_SIZE + 1];
        char flag[MAX_STR_SIZE + 1];
        int val;

        val = sscanf(command, "%s%s%s", name, file, flag);
        if (val == 2) {

            if (load_file(doc, file) == FAILURE) {
                printf("load_file failed\n");
            }
            return SUCCESS;
        }
        return FAILURE;
    }
    /* get pointers to all four quote locations */
     /* isolate "target," and "replace" using pointer subs */
     /* else, end of checking str pointers */
    else if (command_int == 7) {
        char name[MAX_STR_SIZE + 1], * rep_str_1, * rep_str_2, * rep_str_3, * rep_str_4;
        char target[MAX_STR_SIZE + 1], replace[MAX_STR_SIZE + 1];
        char flag_a[MAX_STR_SIZE + 1], flag_b[MAX_STR_SIZE + 1];
        int val;

        val = sscanf(command, "%s%s%s", name, flag_a, flag_b);
        rep_str_1 = strstr(command, "\"");


        if (val == 3 && rep_str_1 != NULL) {
            rep_str_2 = strstr(rep_str_1 + 1, "\"");

            if (rep_str_2 != NULL) {
                rep_str_3 = strstr(rep_str_2 + 1, "\"");

                if (rep_str_3 != NULL) {
                    rep_str_4 = strstr(rep_str_3 + 1, "\"");

                    if (rep_str_4 != NULL) {

                        strncpy(target, rep_str_1 + 1, rep_str_2 - rep_str_1);
                        target[rep_str_2 - (rep_str_1 + 1)] = '\0';

                        strncpy(replace, rep_str_3 + 1, rep_str_4 - rep_str_3);
                        replace[rep_str_4 - (rep_str_3 + 1)] = '\0';

                        if (replace_text(doc, target, replace) == FAILURE) {
                            printf("remove_line failed\n");
                        }
                        return SUCCESS;
                    }
                }
            }
        }
        else {
            printf("Invalid Command\n");
            return FAILURE;
        }
    }
    else if (command_int == 8) {
        char name[MAX_STR_SIZE + 1], target[MAX_STR_SIZE + 1];
        char temp[MAX_STR_SIZE + 1], * str, * result;
        int val;

        val = sscanf(command, "%s%s", name, temp);
        str = strstr(command, "\"");

        if (val == 2 && str != NULL) {

            if ((result = remove_quotes(str, target)) != NULL) {
                highlight_text(doc, result);
                return SUCCESS;
            }
        }
        return FAILURE;
    }
    else if (command_int == 9) {
        char name[MAX_STR_SIZE + 1], target[MAX_STR_SIZE + 1];
        char temp[MAX_STR_SIZE + 1], * str, * result;
        int val;

        val = sscanf(command, "%s%s", name, temp);
        str = strstr(command, "\"");

        if (val == 2 && str != NULL) {

            if ((result = remove_quotes(str, target)) != NULL) {
                remove_text(doc, result);
                return SUCCESS;
            }
        }
        return FAILURE;
    }
    else if (command_int == 10) {
        char name[MAX_STR_SIZE + 1], file[MAX_STR_SIZE + 1];
        char flag[MAX_STR_SIZE + 1];
        int val;

        val = sscanf(command, "%s%s%s", name, file, flag);
        if (val == 2) {
            if (save_document(doc, file) == FAILURE) {
                printf("save_document failed\n");
            }
            return SUCCESS;
        }
        return FAILURE;
    }
    else if (command_int == 11) {
        char name[MAX_STR_SIZE + 1], flag[MAX_STR_SIZE + 1];
        int val;

        val = sscanf(command, "%s%s", name, flag);
        if (val == 1) {
            reset_document(doc);
            return SUCCESS;
        }
        return FAILURE;
    }
    else if (command_int == 12) {
        char name[MAX_STR_SIZE + 1], flag[MAX_STR_SIZE + 1];
        int val;

        val = sscanf(command, "%s%s", name, flag);
        if (val == 1) {
            exit(EXIT_SUCCESS);
        }
        printf("Invalid Command\n");
        return FAILURE;
    }
    /* if status = FAILURE, then the command failed */
    if (status == FAILURE) {
        printf("Invalid Command\n");
        return FAILURE;
    }
}

int main(int argc, char* argv[]) {
    int i = 0, num = 0;
    Document doc;
    FILE* input;
    char line[MAX_STR_SIZE + 1];

    if (argc == 2) {
        if ((input = fopen(argv[1], "r")) == NULL) {
            printf("%s cannot be opened\n", argv[1]);
            exit(EX_OSERR);
        }

    }
    else if (argc == 1) {

        input = stdin;

    }
    else {
        fprintf(stderr, "Usage:  Usage: user_interface\n");
        fprintf(stderr, "Usage:  Usage: user_interface <filename>\n");
        exit(EX_USAGE);
    }

    init_document(&doc, "main_document");

    while (!feof(input)) {
        num++;
        strcpy(line, "");
        if (argc == 1) {
            printf("> ");
        }
        fgets(line, MAX_STR_SIZE + 1, input);
        line[strlen(line) - 1] = 0;
        command_status_checker(&doc, line);
    }
    /* printf("No of Commands Executed:%d\n", num); */

}

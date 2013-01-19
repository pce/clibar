#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
#define DEBUG
*/
#ifndef CLI_PROMPT
#define CLI_PROMPT "cli"
#endif

#define MAX_CMD_LENGTH 64

#ifndef DEBUG
#define trace(...)
#else
#define trace(...) printf(__VA_ARGS__);
#endif


typedef void (*cliFunc) (char* text);


void listCliCmds(char* line);
void quitCmd(char* line);

typedef struct {
    const char *cmd;
    cliFunc callback;
} CliCmd;


CliCmd cliCmds[] = {
    { .cmd="help", .callback=listCliCmds },
    { "?", listCliCmds },
    { "quit", quitCmd},
    { NULL, NULL}
};


void cliAddCmd (CliCmd cmd)
{
    CliCmd *cur;
    int i = 0;
    for(cur = cliCmds; cur->callback; cur++) {
        i++;
    }
    cliCmds [i] = cmd;
    cliCmds [i + 1 ] = (CliCmd) {NULL, NULL};
}


void listCliCmds(char *line)
{
    CliCmd *cur;
    printf("\nCurrently implemented commands:\n");
    for(cur = cliCmds; cur->callback; cur++) {
        printf("%s\n", cur->cmd);
    }
}

void quitCmd(char* line)
{
    // free
    exit(EXIT_SUCCESS);
}


char* cliReadLine()
{
    char *wp = NULL;
    char *buf = NULL;
    unsigned size = 0, filled = 0;
    char c;

    while(1) {
        if(size == filled) {
            void *tmp;
            tmp = buf;
            size += 64;
            /* trace("[FUNC:cliReadLine] enlarging buffer to %d\n", size); */
            if(!(buf = realloc(buf, size * sizeof(char)))) {
                free(tmp);
                perror("realloc");
                exit(2);
            }
            wp = buf + filled;
        }
        filled++;
        c = (char)getchar();
        if (c == '\n') {
            *wp++ = '\0';
            break;
        } else {
            trace("%c\n", c);
            *wp++ = c;
        }
    }
    /* trace("[FUNC:cliReadLine] allocated %d bytes read %d chars\n", size, filled); */
    return buf;
}


void cliPopCmdOfLine(char** cmd, char* line)
{
    char tmpstr[MAX_CMD_LENGTH];
    char *ptr;
    strncpy(tmpstr, line, sizeof tmpstr);
    ptr = strtok(tmpstr, " ;");
    if (ptr)
        ; /*trace("%s", ptr); */
    else
        return;
    *cmd = (char *)malloc(strlen(ptr)+1);
    (*cmd)[strlen(ptr)] = '\n';
    strcpy(*cmd, ptr);
}


int cliLoop()
{
    int ret = 1;
    int i = 0;
    char *line = "";
    char *cmd;
    while(1) {
        printf("%s> ", CLI_PROMPT);
        /* fflush(stdout); */
        line = cliReadLine();
        cliPopCmdOfLine(&cmd, line);
        /* trace("$line:%s;\n", line); */
        if (strcmp(line, "") == 0) continue;
        for (i = 0; ; i++) {
            if (!cliCmds[i].callback) {
                printf("error: no such command\n");
                break;
            }
            if (strcmp(cmd, cliCmds[i].cmd) == 0) {
                cliCmds[i].callback(line);
                break;
            }
        }
    }
    free(line);
    return ret;
}


#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// #define DEBUG

#define CLI_PROMPT "clibar"

#define MAX_CMD_LENGTH 64

#ifndef DEBUG
#define trace(...)
#else
#define trace(...) printf(__VA_ARGS__);
#endif

#define xsprintf(str, ...) {                    \
    char* tmp_str = (str);                      \
    int size = asprintf(&(str), __VA_ARGS__);   \
    if (size == -1) {                           \
        perror("xsprintf");                     \
        exit(2);                                \
    }                                           \
    free(tmp_str);                              \
}


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

typedef struct {
    char *prompt;
} CliConfig;

CliConfig cliConfig;


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


void cliSetPrompt(char* prompt)
{
    cliConfig.prompt = prompt;
    trace("[cliSetPrompt] cliConfig.prompt: %s\n", cliConfig.prompt);
}

char* cliReadLine()
{
    char *line = NULL;
    char c;

    while(1) {
        c = (char)getchar();
        if (c == '\n') {
            break;
        } else {
            trace("%c\n", c);
            if (line == NULL) {
                xsprintf(line, "%c", c);
            } else {
                xsprintf(line, "%s%c", line, c);
            }
        }
    }
    return line;
}


void cliPopCmdOfLine(char** cmd, char* line)
{
    char tmpstr[MAX_CMD_LENGTH];
    char *ptr;
    strncpy(tmpstr, line, sizeof tmpstr);
    ptr = strtok(tmpstr, " ;");
    if (ptr)
        ;
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
    char *line = NULL;
    char *cmd = NULL;

    trace("cliConfig.prompt: %s\n", cliConfig.prompt);
    if (cliConfig.prompt == NULL) {
        cliConfig.prompt = CLI_PROMPT;
        trace("cliConfig.prompt: %s\n", cliConfig.prompt);
    }

    while(1) {
        printf("%s> ", cliConfig.prompt);
        /* fflush(stdout); */
        line = cliReadLine();
        if (line == NULL) continue;
        cliPopCmdOfLine(&cmd, line);
        trace("line: %s\n", line);
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
        free(cmd);
        free(line);
    }
    return ret;
}


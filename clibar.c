#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clibar.h"

static CliCmd cliCmds[] = {
    { .cmd="help", .callback=listCliCmds },
    { "?", listCliCmds },
    { "quit", quitCmd},
    { NULL, NULL}
};

static CliConfig cliConfig;

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
    if (ptr == NULL) return;
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
        if (!cmd) continue;
        if (strlen(line) == 0 ) continue;
        /* if (strcmp(line, "") == 0) continue; */
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
        if (cmd) free(cmd);
        free(line);
    }
    return ret;
}


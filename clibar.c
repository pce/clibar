#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clibar.h"

static CliCmd cliCmds[] = {
    { .cmd="help", .callback=listCliCmds, .doc="list all Commands" },
    { "?", listCliCmds, "list all Commands" },
    { "quit", quitCmd, "quits this session"},
    { NULL, NULL, NULL}
};

static CliState cliState;

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
    cliState.die = 1;
}


void cliSetPrompt(char* prompt)
{
    cliState.prompt = prompt;
    trace("[cliSetPrompt] prompt: %s\n", cliState.prompt);
}

char* cliReadChars()
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


char* cliCmdOfLine(char* line)
{
    char tmpstr[MAX_CMD_LENGTH];
    char *ptr;
    strncpy(tmpstr, line, sizeof tmpstr);
    ptr = strtok(tmpstr, " ;");
    if (ptr == NULL) return NULL;
    char *cmd = (char *)malloc(strlen(ptr)+1);
    cmd[strlen(ptr)] = '\n';
    strcpy(cmd, ptr);
    return cmd;
}


char* cliReadLine(char* prompt)
{
    cliState.prompt = prompt;
    printf("%s> ", cliState.prompt);
    return cliReadChars();
}

int cliLoop()
{
    int ret = 1;
    int i = 0;
    char *line = NULL;
    char *cmd = NULL;

    if (cliState.prompt == NULL) {
        cliState.prompt = CLI_PROMPT;
        trace("prompt: %s\n", cliState.prompt);
    }

    while(1) {
        printf("%s> ", cliState.prompt);
        /* fflush(stdout); */
        line = cliReadChars();
        if (line == NULL) continue;
        cmd = cliCmdOfLine(line);
        trace("line: %s\n", line);
        if (cmd == NULL) {
            continue;
        }
        if (strlen(line) == 0 ) {
            xfree(cmd);
            continue;
        }
        /* if (strcmp(line, "") == 0) continue; */
        for (i = 0; ; i++) {
            if (!cliCmds[i].callback) {
                printf("error: no such command\n");
                break;
            }
            if (strcmp(cmd, cliCmds[i].cmd) == 0) {
                cliCmds[i].callback(line);
                // cliAddHistory(line);
                break;
            }
        }
        if (cmd) xfree(cmd);
        xfree(line);
        if (cliState.die) {
            break;
        }
    }
    return ret;
}


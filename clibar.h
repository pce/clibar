#ifndef _CLIBAR_H
#define _CLIBAR_H

// #define DEBUG

#define CLI_PROMPT "clibar"

#define MAX_CMD_LENGTH 64

#ifndef DEBUG
#define trace(...)
#else
#define trace(...) printf(__VA_ARGS__);
#endif

#define xsprintf(str, ...) {                    \
    char* tmpstr = (str);                       \
    int size = asprintf(&(str), __VA_ARGS__);   \
    if (size == -1) {                           \
        perror("xsprintf");                     \
        exit(2);                                \
    }                                           \
    free(tmpstr);                               \
}

#define xfree(p) do { free(p); (p) = NULL; } while(0)

typedef void (*cliFunc) (char* line);

/* default Commands */
void listCliCmds(char* line);
void quitCmd(char* line);

typedef struct {
    const char *cmd;
    cliFunc callback;
} CliCmd;

typedef struct {
    char *prompt;
} CliConfig;


void cliAddCmd (CliCmd cmd);
void cliSetPrompt(char* prompt);
char* cliReadLine();
void cliPopCmdOfLine(char** cmd, char* line);
int cliLoop();

#endif


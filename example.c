#define _GNU_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clibar.h"

void hello (char *line)
{
    trace("%s\n", line);
    cliSetPrompt("hello");
    printf("%s\n", "World!");
}

int main(void)
{
    trace("cliConfig.prompt: %s\n", cliConfig.prompt);
    //cliSetPrompt("cli");
    cliAddCmd((CliCmd){.cmd="hello", .callback=hello});
    int ret = cliLoop();
    return ret;
}


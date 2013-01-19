#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clibar.h"

void hello (char *line)
{
    trace("%s\n", line);
    printf("%s\n", "World!");
}

int main(int argc, char **argv)
{
    cliAddCmd((CliCmd){.cmd="hello", .callback=hello});
    int ret = cliLoop();
    return ret;
}


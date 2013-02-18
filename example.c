#define _GNU_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clibar.h"

void foo (char *line)
{
    trace("%s\n", line);
    cliSetPrompt("foobar");
    char *p = strstr(line, "bar");
    if (p)
        printf("%s\n", "fee fie foe foo bar buz qux");
}

int main(void)
{
    cliAddCmd((CliCmd){.cmd="foo", .callback=foo, .doc="foo bar magic"});
    int ret = cliLoop();
    return ret;
}


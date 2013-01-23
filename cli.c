
#include "clibar.h"

void hello (char *line)
{
    trace("%s\n", line);
    cliSetPrompt("hello");
    printf("%s\n", "World!");
}

int main(int argc, char **argv)
{
    trace("cliConfig.prompt: %s\n", cliConfig.prompt);
    //cliSetPrompt("cli");
    cliAddCmd((CliCmd){.cmd="hello", .callback=hello});
    int ret = cliLoop();
    return ret;
}


clibar
======

simple command line interface 


features
--------

* command line loop
* map commands to callbacks 
  `void example_callback(char* line)` 

wishlist
--------

* parse parameter/args
* support keys (escape sequences, arrows, tabs)
* history (readline features)


example
-------

~~~
#include "clibar.h"

void hello (char *line)
{
    printf("%s\n", "World!");
}

int main(int argc, char **argv)
{
    cliAddCmd((CliCmd){.cmd="hello", .callback=hello});
    int ret = cliLoop();
    return ret;
}

~~~




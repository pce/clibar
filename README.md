clibar
======

simple command line interface 


features
--------

* simple command line interface
* add commands

wishlist
--------

* parameter/args parsing
* history (readline features)


example
-------

~~~
include "clibar.h"

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




#define _GNU_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../unity/src/unity.h"
#include "../src/clibar.h"



void foo (char *line)
{
    char *p = strstr(line, "bar");
    if (p)
        printf("%s\n", "fee fie foe foo bar buz qux");
}

void test_clibarAddCmd(void)
{
	cliAddCmd((CliCmd){.cmd="foo", .callback=foo, .doc="foo bar magic"});

	char* expected = "foo";
	const char* actual = "";

    	CliCmd *cur;

	// CliCmd* cliCmds = CliCmds();

   	for(cur = cliCmds; cur->callback; cur++) {
		actual = cur->cmd;
    	}
	TEST_ASSERT_EQUAL(expected, actual);
}

/*
void test_cliCmdOfLine(char* line)
{
	char* expected = "foo";

}
*/


int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_clibarAddCmd);
	return UNITY_END();
}

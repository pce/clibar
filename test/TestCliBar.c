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

	CliCmd* curCliCmds = CliCmds();

   	for(cur = curCliCmds; cur->callback; cur++) {
		actual = cur->cmd;
    	}
	TEST_ASSERT_EQUAL(expected, actual);
}


void test_clibarGetCmds(void)
{

	char* expected = "help";
	const char* actual = "";

    	CliCmd *cur;
	CliCmd* curCliCmds = CliCmds();

   	for(cur = curCliCmds; cur->callback; cur++) {
		actual = cur->cmd;
		break;
    	}
	TEST_ASSERT_EQUAL(expected, actual);
}




void test_cliCmdOfLine()
{
 	char* expected = "foo";
	char* curline = "foo bar";
	
	char* actual = cliCmdOfLine(curline);

	TEST_ASSERT_EQUAL_STRING_LEN(expected, actual, 3);
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected, actual, actual);

}



int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_clibarAddCmd);
	RUN_TEST(test_clibarGetCmds);
	RUN_TEST(test_cliCmdOfLine);
	return UNITY_END();
}

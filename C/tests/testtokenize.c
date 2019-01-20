#include "unity/unity.h"
#include <stdlib.h>
#include <stdio.h>
#include "../server.h"

char client_message[MSG_SIZE];
char args[MAX_ARGS][MAX_ARG_SIZE];

void setUp() {
    char str1[] = "move 4 5";
    strncpy(client_message, str1, sizeof(str1));
}

void tearDown(void) {
    // free(client_message);
}

void test_tokenization() {
    int a = 1;
    tokenize(client_message, args);
    TEST_ASSERT_EQUAL_STRING("move", args[0]);
	TEST_ASSERT_TRUE(a==1);
    // char *token;
    // token = strtok(client_message, " ");
    // printf("%d\n", token[0]);
	// TEST_ASSERT_EQUAL(token[0], args[0]);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_tokenization);
	
    return UNITY_END();
}
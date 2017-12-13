#include <unistd.h>

#include "clib.h"
#include "unity.h"

void test_ReplaceString_should_ReturnEmptyStringOnNullOrEmptyString()
{
    char *r1 = string_replace(NULL, "sequence", "replacement");
    TEST_ASSERT_EQUAL_STRING("", r1);
    free(r1);

    char *r2 = string_replace("", "sequence", "replacement");
    TEST_ASSERT_EQUAL_STRING("", r2);
    free(r2);
}

void test_ReplaceString_should_ReturnStringWithReplacements()
{
    char *r1 = string_replace("hello world", "o", "a");
    TEST_ASSERT_EQUAL_STRING("hella warld", r1);
    free(r1);

    char *r2 = string_replace("hello world hello", "hello", "");
    TEST_ASSERT_EQUAL_STRING(" world ", r2);
    free(r2);

    char *r3 = string_replace("hello world hello", "hello", "no");
    TEST_ASSERT_EQUAL_STRING("no world no", r3);
    free(r3);

    char *r4 = string_replace("hello world hello", "hello", "replacement");
    TEST_ASSERT_EQUAL_STRING("replacement world replacement", r4);
    free(r4);
}

void test_ReplaceString_should_ReturnInputStringOnEmptyOrNullSequence()
{
    char *r1 = string_replace("hello world", NULL, "replacement");
    TEST_ASSERT_EQUAL_STRING("hello world", r1);
    free(r1);

    char *r2 = string_replace("hello world", "", "replacement");
    TEST_ASSERT_EQUAL_STRING("hello world", r2);
    free(r2);
}

void test_UNUSED_should_Compile()
{
    int unused = 0;
    UNUSED(unused);
    TEST_ASSERT(1 == 1);
}

void *func_MeasureMicroseconds_should_ReturnTimeAndGivenData(void *data)
{
    int *i = (int *)data;
    while (*i < 1000000)
        (*i)++;
    return i;
}

void test_MeasureMicroseconds_should_ReturnTimeAndGivenData()
{
    int i = 0;
    unsigned long micros = 0;
    measure_microseconds(&micros, func_MeasureMicroseconds_should_ReturnTimeAndGivenData, &i);
    TEST_ASSERT_EQUAL_INT(1000000, i);
    TEST_ASSERT(micros > 0);
}

void *func_MeasureMicroseconds_should_ReturnTime(void *data)
{
    for (int i = 0; i < 1000000; i++);
    return data;
}

void test_MeasureMicroseconds_should_ReturnTime()
{
    unsigned long micros = 0;
    measure_microseconds(&micros, func_MeasureMicroseconds_should_ReturnTime, NULL);
    TEST_ASSERT(micros > 0);
}

void *onfile_TraverseDirectory_should_ReturnRightDirectoryAndFileCount(const char *path,
                                                                       const char *filename,
                                                                       void *data)
{
    if (strstr(path, ".git") == NULL) {
        (*((int *)data))++;
    }
    return data;
}

void test_TraverseDirectory_should_ReturnRightFileCount()
{

    char path[512];
    getcwd(path, 512);
    int filecount = 0;
    traverse_directory(path,
                       NULL,
                       onfile_TraverseDirectory_should_ReturnRightDirectoryAndFileCount,
                       &filecount);
    TEST_ASSERT_EQUAL_INT(12, filecount);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_ReplaceString_should_ReturnEmptyStringOnNullOrEmptyString);
    RUN_TEST(test_ReplaceString_should_ReturnStringWithReplacements);
    RUN_TEST(test_ReplaceString_should_ReturnInputStringOnEmptyOrNullSequence);
    RUN_TEST(test_UNUSED_should_Compile);
    RUN_TEST(test_MeasureMicroseconds_should_ReturnTimeAndGivenData);
    RUN_TEST(test_MeasureMicroseconds_should_ReturnTime);
    RUN_TEST(test_TraverseDirectory_should_ReturnRightFileCount);
    return UNITY_END();
}

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TEST_FILE_NAME  "./test-getline.data"


const char *DATA_1[] = {
    "Part0_0 Part0_1\n",
    "Part1_0 Part1_1\n",
    "Part2_0 Part2_1\n",
    "Part3_0 Part3_1"
};
const int LINE_NUM_1 = sizeof(DATA_1) / sizeof(char *);

const char *DATA_2[] = {
    "Part0 ",
    "Part1 ",
    "Part2 ",
    "Part3 ",
    "Part4 "
};
const int LINE_NUM_2 = sizeof(DATA_2) / sizeof(char *);


static int make_test_file();


static int test_getline_impl(size_t ln)
{
    FILE *f;
    int i;

    if (make_test_file(DATA_1, LINE_NUM_1) != 0) {
        printf("test_getline: failed to make test file\n");
        return 1;
    }

    f = fopen(TEST_FILE_NAME, "r");
    if (f == NULL) {
        printf("test_getline: failed to open temp file; error %i; %s\n", errno, strerror(errno));
        return 1;
    }

    for (i=0; i<LINE_NUM_1; ++i) {
        size_t num = ln;
        char *s = ln == 0 ? NULL : (char *)malloc(ln);
        ssize_t rc;
        if ((rc = getline(&s, &num, f)) < 0) {
            printf("test_getline: failed to read temp file; error %i; %s\n", errno, strerror(errno));
            return 1;
        }
        if (strcmp(s, DATA_1[i]) != 0) {
            printf("test_getline: expected line: '%s'\n", DATA_1[i]);
            printf("test_getline: read line:     '%s'\n", s);
            return 1;
        }
        free(s);
    }

    if (fclose(f) != 0) {
        printf("failed to close test file; error %i; %s\n", errno, strerror(errno));
        return 1;
    }

    if (unlink(TEST_FILE_NAME) != 0) {
        printf("failed to close test file; error %i; %s\n", errno, strerror(errno));
        return 1;
    }

    printf("getline - ok\n");
    return 0;
}

int test_getline()
{
    int rc;
    if ((rc = test_getline_impl(0)) != 0) return rc;
    if ((rc = test_getline_impl(1)) != 0) return rc;
    if ((rc = test_getline_impl(5)) != 0) return rc;
    if ((rc = test_getline_impl(512)) != 0) return rc;
    return 0;
}


int test_getdelim()
{
    FILE *f;
    int i;

    if (make_test_file(DATA_2, LINE_NUM_2) != 0) {
        printf("test_getdelim: failed to make test file\n");
        return 1;
    }

    f = fopen(TEST_FILE_NAME, "r");
    if (f == NULL) {
        printf("test_getdelim: failed to open temp file; error %i; %s\n", errno, strerror(errno));
        return 1;
    }

    for (i=0; i<LINE_NUM_2; ++i) {
        char *s = NULL;
        size_t num = 0;
        if (getdelim(&s, &num, ' ', f) == -1) {
            printf("test_getdelim: failed to read temp file; error %i; %s\n", errno, strerror(errno));
            return 1;
        }
        if (strcmp(s, DATA_2[i]) != 0) {
            printf("test_getdelim: expected: '%s'\n", DATA_2[i]);
            printf("test_getdelim: read:     '%s'\n", s);
            return 1;
        }
    }

    if (fclose(f) != 0) {
        printf("failed to close test file; error %i; %s\n", errno, strerror(errno));
        return 1;
    }

    if (unlink(TEST_FILE_NAME) != 0) {
        printf("failed to close test file; error %i; %s\n", errno, strerror(errno));
        return 1;
    }

    printf("getdelim - ok\n");
    return 0;
}


int make_test_file(const char *data[], int num)
{
    FILE *f;
    int i;

    f = fopen(TEST_FILE_NAME, "w");
    if (f == NULL) {
        printf("failed to open test file; error %i; %s\n", errno, strerror(errno));
        return 1;
    }

    for (i=0; i<num; ++i) {
        if (fprintf(f, "%s", data[i]) < 0) {
            printf("failed to write line %i to test file; error %i; %s\n", i, errno, strerror(errno));
            return 1;
        }
    }

    if (fclose(f) != 0) {
        printf("failed to close test file; error %i; %s\n", errno, strerror(errno));
        return 1;
    }

    return 0;
}

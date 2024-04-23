#ifndef __rexpfile_h__
#define __rexpfile_h__

enum typecheck
{
    OR,
    AND
};

struct findinfo
{
    char *file;
    int *lines;
};

struct findinfo *filechecking(char *filename, int argc, char *argv[], int pos, enum typecheck tc);

#endif
#include<stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    *((int*)0) = 42;
    return EXIT_SUCCESS;
}

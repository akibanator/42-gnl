#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int    main(void)
{
    int     fpointer;
    char    *singleLine = malloc(1 * sizeof(char));

    fpointer = open("text", 256);
    while(singleLine != NULL)
    {
        free(singleLine);
        singleLine = get_next_line(fpointer);
        printf("%s", singleLine);
    }
    return (0);
}

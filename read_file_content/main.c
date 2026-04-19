#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

    if(argc != 2)
    {
        printf("Invalid number of command line arguments. Format: read_file_content <file_name>\n");
        exit(-1);
    }

    FILE *IOBUFFfin = fopen(argv[1],"rb");

    if(IOBUFFfin == NULL)
    {
        if(errno != EACCES)
        {
            printf("Error whilst oppening file: %s !\n",argv[1]);
            exit(-5);
        }
        else
        {
            printf("File:%s does not exist relative to current path!\n",argv[1]);
            exit(-2);
        }
    }

    char CHARPline[2048] = {0};

    while(fgets(CHARPline,2048,IOBUFFfin))
    {
        printf("%s",CHARPline);
    }

    printf("\n");

    fclose(IOBUFFfin);

    return 0;
}
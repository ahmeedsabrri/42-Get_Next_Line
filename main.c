#include"get_next_line.h"

int main()
{
    int fd = open("txt",O_RDWR);
  
    char *line = get_next_line(fd);

    while(line)
    {
        printf("%s",line);
        free(line);
        line = get_next_line(fd);
    }
    free(line);
    line = get_next_line(fd);
    printf("\n");
    printf("%s",line);

}
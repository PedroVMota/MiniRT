#include "center.h"

bool ignoreInput(char **line)
{
    int i = -1;
    char *prototype = *line;
    if(!prototype)
        return true;
    else if(!ft_strcmp("\n", prototype))
        return true;
    while(prototype[++i])
        if(prototype[i] == '#')
            return true;
    return false;
}

bool fetchData(int fd)
{
    char *line;

    line = get_next_line(fd);
    if(!line)
        return false;
    if(ignoreInput(&line)) {
        free(line);
        fetchData(fd);
    }
    return false;
}


bool parseFile(char *fileName)
{
    int fd;

    if(!ft_strnstr(fileName, ".rt", ft_strlen(fileName)))
        exitProgram("Invalid rayTracing file extension\n");
    fd = open(fileName, O_RDONLY);
    if(fd == -1)
        exitProgram("Error opening file check if everything is correct\n");
    if(fetchData(fd))
        exitProgram("-> Fetching Data Error\n");
    return false;
}

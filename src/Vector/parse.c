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

static char *getIntentity(char *line, int *i)
{
    int ii = *i;
    while(line[++ii])
    {
        if(!(line[ii] == ' ' || line[ii] == '\t' || line[ii] == '\n'))
            break;
    }
    *i = ii;
    while(line[++ii])
    {
        if(!(line[ii] != ' ' && line[ii] != '\t' && line[ii] != '\n'))
            break;
    }
    return ft_substr(line, *i, (ii - *i));
}

bool generateScene();
{
    return false;
}

bool generateData(char *line)
{
    int i;
    int mode;
    char *type

    i = -1;
    type = getIntentity(line, &i);
    if(!type)
        return true;
    printf("Type: %s\n", type);
    if(!ft_strcmp(type, "C"))
        mode = CAMERA;
    else if(!ft_strcmp(type, "sp"))
        mode = SPHERE;
    else if(!ft_strcmp(type, "pl"))
        mode = PLANE;
    else if(!ft_strcmp(type, "cy"))
        mode = CYLINDER;
    else if(!ft_strcmp(type, "py"))
        mode = PYRAMID;
    else
        mode = UNKNOWN;
    if(mode != UNKNOWN)
        return generateScene(mode, line, &i);
    free(type);
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
        if(fetchData(fd))
            return true;
        return false;
    }
    if(generateData(line))
        return true;
    fetchData(fd);
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

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
    char *final;

    final = NULL;
    int ii = *i;
    while(line[++ii])
        if(!(line[ii] == ' ' || line[ii] == '\t' || line[ii] == '\n'))
            break;
    *i = ii;
    while(line[++ii])
        if (!(line[ii] != ' ' && line[ii] != '\t' && line[ii] != '\n'))
            break;
    final =  ft_substr(line, *i, (ii - *i));
    *i = ii;
    return final;
}

bool generateScene(int type, char *line, int *i)
{
    if(type == UNKNOWN)
        return reportMenssage("Invalid model type ", true, 2);
    printf("%sReceaved Caracter%s -> ", YEL, RESET);
    ((type == CYLINDER ) ? printf("Cylinder\n") : 0);
    ((type == CAMERA ) ? printf("Camera\n") : 0);
    ((type == PYRAMID ) ? printf("Pyramid\n") : 0);
    ((type == SPHERE ) ? printf("Sphere\n") : 0);
    ((type == AMBIENT ) ? printf("Ambient\n") : 0);
    ((type == POINT ) ? printf("POINT\n") : 0);
    ((type == DIRECTIONAL ) ? printf("Directional\n") : 0);

    return false;
}

bool generateData(char *line)
{
    int i;
    int mode;
    char *type;

    i = -1;
    type = getIntentity(line, &i);
    if(!type)
        return true;
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
    return generateScene(mode, line, &i);;
}

bool fetchData(int fd)
{
    char *line;

    int run = false;

    while(!run)
    {
        line = get_next_line(fd);
        if(!line)
            break;
        if(ignoreInput(&line)) {
            continue;
        }
        if(!run && generateData(line))
            run = true;
    }
    return run;
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
    {
        exitProgram("-> Fetching Data Error\n");
        return true;
    }
    return false;
}

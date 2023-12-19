#include <center.h>


bool parse_data(char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if(fd == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return true;
	}
}

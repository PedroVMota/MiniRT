
#include <center.h>

//parsing notes
bool parse_data(char *file);

int main(int ac, char **av)
{
	if( ac < 2 || ac > 2)
	{
		write(2, "Invalid number arguments\n", 19);
		return 1;
	}
	if(parse_data(av[1]))
		return 1;

}
#include <StandarLibrarys.h>

void updateError(char *msg)
{
	write(2, RED, ft_strlen(RED));
	write(2, "Error: ", 7);
	write(2, RESET, ft_strlen(RESET));
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	g_scene->error = 1;
}

int setdata(bool *ptr, bool data, int res)
{
	if(*ptr == data)
		return 2;
	*ptr = data;
	return res;
}
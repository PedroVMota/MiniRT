#include <center.h>

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

bool	float_requirements(char *s, int start, int end){
	bool	asdot;
	bool	assignal;

	asdot = false;
	assignal = false;
	if (start > end)
		return (false);
	if(start == -1 && end == -1)
	{
		start = 0;
		end = ft_strlen(s);
	}
	while (start < end && s[start])
	{
		if (s[start] == ',')
			if (start == 0 || s[start - 1] == ',' || s[start + 1] == ',')
				return (true);
		if (s[start] == '-' || s[start] == '+')
		{
			if ((start != 0 && s[start - 1] != ',') || assignal)
				return (true);
			assignal = true;
		}
		if (s[start] == '.' && setdata(&asdot, true, 0) == 2)
			return (true);
		if (!ft_isdigit(s[start]) && s[start] != '.' && s[start] != '-'	&& s[start] != '+')
			return (true);
		start++;
	}
	return (false);
}

bool	vector_requirements(char *s){
	int	commas;
	int	i;
	int	start;

	i = -1;
	start = 0;
	commas = 0;
	while (true)
	{
		if(s[++i] == '\n' || s[i])
			break ;
		if (s[i] == ',')
		{
			commas++;
			if ((i == 0) || float_requirements(s, start, i) || commas > 2 || \
				s[i + 1] == '\0' || s[i + 1] == ',')
				return (false);
			start = i + 1;
		}
		else if (s[i] == ' ')
			return (false);
	}
	if(float_requirements(s, start, i))
		return (false);
	if (commas < 2)
		return (false);
	return (true);
}

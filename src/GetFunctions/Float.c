/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:39:06 by pedro             #+#    #+#             */
/*   Updated: 2024/02/18 17:19:03 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

static int	setdata(bool *ptr, bool data, int res)
{
	if (*ptr == data)
		return (2);
	*ptr = data;
	return (res);
}

static bool	custom_char(char c)
{
	return ((!ft_isdigit(c) && c != '.' && c != '-' && \
	c != '+'));
}

bool	float_requirements(char *s, int start, int end)
{
	bool	asdot;
	bool	assignal;

	asdot = false;
	assignal = false;
	if (start > end)
		return (false);
	while (start < end && s[start] && s[start] != '\n' )
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
		if (custom_char(s[start]))
			return (true);
		start++;
	}
	return (false);
}

double	newfloat(char *s, float max, float min)
{
	double	f;

	if (float_requirements(s, 0, (int)ft_strlen(s)))
		return (uptadeerror("Invalid float value\n"), 0);
	f = ft_atof(s);
	if (f > max || f < min)
		return (uptadeerror("Invalid float range\n"), 0);
	return (f);
}

double	getfloat(char *prop, bool required, float *range, int standard_value)
{
	if ((gscene())->error)
		return (standard_value);
	if (required)
	{
		if (!prop)
		{
			uptadeerror("Field required\n");
			(gscene())->error = 2;
			return (standard_value);
		}
		return (newfloat(prop, range[0], range[1]));
	}
	return (standard_value);
}

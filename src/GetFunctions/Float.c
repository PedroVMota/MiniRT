/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:39:06 by pedro             #+#    #+#             */
/*   Updated: 2024/02/10 22:40:48 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <StandarLibrarys.h>


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

double newfloat(char *s, float max, float min)
{
	double f;

	if(float_requirements(s, 0, (int)ft_strlen(s) - 1))
	{
		updateError("Error: Invalid float value");
		g_scene->error = 1;
		return (0);
	}
	f = ft_atof(s);
	if (f > max || f < min)
	{
		updateError("Error: Invalid float range");
		return (0);
	}
	return (f);
}

double	getFloat(char *prop, bool required, float *range, int standard_value)
{
	if(required)
	{
		if(!prop){
			updateError("Field required\n");
			return standard_value;
		}
		return (newfloat(prop, range[0], range[1]));
	}
	return standard_value;
}
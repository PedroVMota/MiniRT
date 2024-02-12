/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:41:07 by pedro             #+#    #+#             */
/*   Updated: 2024/02/12 17:29:47 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

bool	float_requirements(char *s, int start, int end);

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
	printf("Everything is fine\n");
	return (true);
}


static Vec3 newvec4(char *s, float max, float min)
{
	Vec3 v;
	char **split;

	printf("%sNew Vec: %s%s\n", HBLU, s, RESET);
	if(vector_requirements(s))
	{
		updateError("Error: Invalid Vec3 value");
		return (Vec3){0,0,0};
	}
	split = ft_split(s, ',');
	v.x = ft_atof(split[0]);
	v.y = ft_atof(split[1]);
	v.z = ft_atof(split[2]);
	if (v.x > max || v.x < min || v.y > max || v.y < min || v.z > max ||
		v.z < min)
		updateError("Error: Invalid Vec out of range");
	delprops(split);
	return (v);
}

Vec3 getVec4(char *prop, bool required, float max, float min)
{
	printf("New Vec: %s\n", prop);
	if(required && !prop)
	{
		if(!g_scene)
			updateError("Expected Vec3\n");
		return ((Vec3){0,0,0});
	}
	if(g_scene->error)
		return ((Vec3){0,0,0});
	return (newvec4(prop, max, min));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:41:07 by pedro             #+#    #+#             */
/*   Updated: 2024/02/18 17:19:03 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

bool	float_requirements(char *s, int start, int end);

bool	vector_requirements(char *s)
{
	char	**props;
	int		prop;
	int		i;
	int		commas;

	commas = 0;
	prop = -1;
	i = -1;
	while (s[++i])
		if (s[i] == ',')
			commas++;
	if (commas != 2)
		return (true);
	props = ft_split(s, ',');
	if (!props)
		return (true);
	while (props[++prop])
		if (float_requirements(props[prop], 0, ft_strlen(props[prop])))
			return (delprops(&props), true);
	delprops(&props);
	if (prop != 3)
		return (true);
	return (false);
}

static t_vector	newvec4(char *s, float max, float min)
{
	t_vector	v;
	char		**split;

	if (vector_requirements(s))
	{
		uptadeerror("Error: Invalid Vec3 value\n");
		return ((t_vector){0, 0, 0});
	}
	split = ft_split(s, ',');
	v.x = ft_atof(split[0]);
	v.y = ft_atof(split[1]);
	v.z = ft_atof(split[2]);
	if (v.x > max || v.x < min || v.y > max || v.y < min || v.z > max \
	||v.z < min)
		uptadeerror("Error: Invalid Vec out of range\n");
	delprops(&split);
	return (v);
}

t_vector	getvec4(char *prop, bool required, float max, float min)
{
	if ((gscene())->error)
		return ((t_vector){0, 0, 0});
	if (required && !prop)
	{
		if (!(gscene()))
			uptadeerror("Expected Vec3\n");
		return ((t_vector){0, 0, 0});
	}
	if ((gscene())->error)
		return ((t_vector){0, 0, 0});
	if (!prop)
	{
		uptadeerror("Expected Value\n");
		(gscene())->error = 2;
		return ((t_vector){0, 0, 0});
	}
	return (newvec4(prop, max, min));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:34:23 by pedro             #+#    #+#             */
/*   Updated: 2023/12/22 16:42:48 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

void		interator(void **c, void (*f)(void *x));

bool	vector_validation(char **s)
{
	int	index;

	index = 0;
	while (s[index])
		index++;
	if (index != 3)
	{
		interator((void **)s, free);
		scene()->error = 6;
		return (true);
	}
	return (false);
}

// coma 2 index 1
bool	valid_vector(char *s)
{
	int	info[2];

	info[0] = -1;
	info[1] = 0;
	if (!s)
	{
		printf("SDASDA");
		scene()->error = 6;
		return (true);
	}
	while (s[++info[0]])
	{
		if (s[info[0]] == '-' || s[info[0]] == '+')
			s++;
		if (!ft_isdigit(s[info[0]]))
		{
			if (s[info[0]] == ',')
				info[1]++;
			else if (s[info[0]++] == '.')
				;
			else
			{
				scene()->error = 6;
				return (true);
			}
		}
	}
	return (true - (info[1] == 2 && s[info[0]] != '\0'));
}

/// @brief Generate a stack memory vector with x, y, z values
/// @param vector just the string as aparamter.
/// @note If vector isn't a valid will return a vector with 0, 0, 0 values.
t_vector	vector_generator(char *vector)
{
	char		**matrix;
	t_vector	new_vector;

	if (!valid_vector(vector))
		return ((t_vector){0, 0, 0});
	matrix = ft_splitstr(vector, ",");
	if (vector_validation(matrix))
		return ((t_vector){0, 0, 0});
	new_vector.x = atof(matrix[0]);
	new_vector.y = atof(matrix[1]);
	new_vector.z = atof(matrix[2]);
	interator((void **)matrix, free);
	return ((t_vector){new_vector.x, new_vector.y, new_vector.z});
}

t_color	color_generator(char *color)
{
	char	**matrix;
	t_color	new_color;

	if (!color)
		scene()->error = 6;
	if (!valid_vector(color))
		return ((t_color){0, 0, 0});
	matrix = ft_splitstr(color, ",");
	if (vectorgit ad_validation(matrix))
		return ((t_color){0, 0, 0});
	new_color.r = atof(matrix[0]);
	if (new_color.r > 255)
		scene()->error = 9;
	new_color.g = atof(matrix[1]);
	if (new_color.g > 255)
		scene()->error = 9;
	new_color.b = atof(matrix[2]);
	if (new_color.r > 255)
		scene()->error = 9;
	interator((void **)matrix, free);
	return ((t_color){new_color.r, new_color.g, new_color.b});
}

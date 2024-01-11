/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:34:23 by pedro             #+#    #+#             */
/*   Updated: 2023/12/24 02:16:07 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

void		*interator(char ***c, void (*f)(void *x));

bool	vector_validation(char **s)
{
	int	index;

	index = 0;
	while (s[index])
		index++;
	if (index != 3)
	{
		interator(&s, free);
		scene()->error = 6;
		return (true);
	}
	return (false);
}

static bool	check_element(int *info, char *s)
{
	if (s[info[0]] == '-' || s[info[0]] == '+')
		s++;
	{
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
	return (false);
}

bool	valid_vector(char *s)
{
	int	info[2];

	info[0] = -1;
	info[1] = 0;
	if (!s)
	{
		scene()->error = 6;
		return (true);
	}
	while (s[++info[0]])
		if (check_element(info, s))
			return (true);
	if ((info[1] == 2 && s[info[0]] != '\0'))
		return (true);
	return (true);
}

/// @brief Generate a stack memory vector with x, y, z values
/// @param vector just the string as aparamter.
/// @note If vector isn't a valid will return a vector with 0, 0, 0 values.
t_vector	vector_generator(char *vector)
{
	char		**matrix;
	t_vector	new_vector;

	if (!vector)
	{
		scene()->error = 6;
		return ((t_vector){0, 0, 0});
	}
	if (!valid_vector(vector))
		return ((t_vector){0, 0, 0});
	matrix = ft_splitstr(vector, ",");
	if (vector_validation(matrix))
		return ((t_vector){0, 0, 0});
	new_vector.x = atof(matrix[0]);
	new_vector.y = atof(matrix[1]);
	new_vector.z = atof(matrix[2]);
	interator(&matrix, free);
	return ((t_vector){new_vector.x, new_vector.y, new_vector.z});
}


t_color	color_generator(char *color)
{
	char	**matrix;
	t_color	new_color;

	if (!valid_vector(color))
		return ((t_color){0, 0, 0});
	if (!color)
	{
		scene()->error = 6;
		return ((t_color){0, 0, 0});
	}
	matrix = ft_splitstr(color, ",");
	if (vector_validation(matrix))
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
	interator(&matrix, free);
	new_color.r = new_color.r / 255.0f;
    new_color.g = new_color.g / 255.0f;
    new_color.b = new_color.b / 255.0f;
	return ((t_color){new_color.r, new_color.g, new_color.b});
}

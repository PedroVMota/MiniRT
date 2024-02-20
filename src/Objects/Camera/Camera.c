/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:31:54 by pedro             #+#    #+#             */
/*   Updated: 2024/02/20 11:26:21 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

static bool	count_args(char **props, int wtoptional, int woptional)
{
	int	i;

	i = -1;
	while (props[++i])
		;
	if (i == woptional || i == wtoptional)
		return (false);
	return (true);
}

t_cam	*newcamera(int type, char **props)
{
	t_cam	*c;

	if (count_args(&props[1], 3, 5))
		return (delprops(&props), \
			uptadeerror("Invalid arguments camera\n"), NULL);
	c = (t_cam *)newobject(sizeof(t_cam), NULL);
	c->type = type;
	c->o = getvec4(props[1], true, INT16_MAX, -INT16_MAX);
	c->d = getvec4(props[2], true, 1, -1);
	c->theta = getvec4("0,0,0", true, 1, -1);
	c->fov = getfloat(props[3], true, (float []){180, 0}, 1);
	c->aspect = (double)(gscene())->width / (double)(gscene())->height;
	c->height = tan(c->fov / 2 * M_PI / 180);
	c->width = c->aspect * c->height;
	return (delprops(&props), (t_cam *)errhandler((t_obj *)c, \
		"-> Invalid Camera\n"));
}

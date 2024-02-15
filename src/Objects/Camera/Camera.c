/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:31:54 by pedro             #+#    #+#             */
/*   Updated: 2024/02/15 10:49:03 by pedro            ###   ########.fr       */
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

	if (count_args(&props[1], 3, 3))
		return (uptadeerror("Invalid arguments camera\n"), NULL);
	c = (t_cam *)newobject(sizeof(t_cam), NULL);
	c->type = CAMERA;
	if (g_scene->error != 2)
		c->o = getvec4(props[1], true, INT16_MAX, -INT16_MAX);
	if (g_scene->error != 2)
		c->d = getvec4(props[2], true, 1, -1);
	if (g_scene->error != 2)
		c->theta = getvec4("0,0,0", true, 1, -1);
	if (g_scene->error != 2)
		c->fov = getfloat(props[3], true, (float []){180, 0}, 1);
	if (g_scene->error != 2)
		c->aspect = (double)g_scene->width / (double)g_scene->height;
	if (g_scene->error != 2)
		c->height = tan(c->fov / 2 * M_PI / 180);
	if (g_scene->error != 2)
		c->width = c->aspect * c->height;
	c->next = NULL;
	return ((t_cam *)errhandler((t_obj *)c, (void **)props,
			"-> Invalid Camera\n"));
}

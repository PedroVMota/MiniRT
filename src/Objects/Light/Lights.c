/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:28:56 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/15 17:46:57 by pedro            ###   ########.fr       */
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

static void	setup_am(char **p, t_li *l)
{
	t_vector	color;

	if(count_args(&p[1], 2, 2))
	{
		uptadeerror("Invalid arguments ambient light\n");
		g_scene->error = 2;
		return ;
	}
	l->i = getfloat(p[1], true, (float []){1, 0}, 0);
	color = getvec4(p[2], true, 255, 0);
	l->color = newrgb((int)color.x, (int)color.y, (int)color.z);
	l->next = NULL;
}

// SECTION - POINT LIGHT
static void	setup_p(char **p, t_li *l)
{
	t_vector	color;

	if(count_args(&p[1], 3, 3))
	{
		uptadeerror("Invalid arguments point light\n");
		g_scene->error = 2;
		return ;
	}
	l->o = getvec4(p[1], true, INT16_MAX, -INT16_MAX);
	l->i = getfloat(p[2], true, (float []){1, 0}, 0);
	color = getvec4(p[3], true, 255, 0);
	l->color = newrgb((int)color.x, (int)color.y, (int)color.z);
}

t_li	*newlight(int type, char **props)
{
	t_li	*l;

	l = (t_li *)newobject(sizeof(t_li), NULL);
	l->type = type;
	if (type == POINT)
		setup_p(props, l);
	else if (type == AMBIENT)
		setup_am(props, l);
	l->next = NULL;
	return ((t_li *)errhandler((t_obj *)l, "-> Invalid Light\n"));
}

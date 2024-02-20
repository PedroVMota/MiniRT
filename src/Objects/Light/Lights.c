/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:28:56 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/20 11:25:03 by pvital-m         ###   ########.fr       */
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

static t_li *setup_am(char **props)
{
	t_vector	color;

	t_li *l;
	if (count_args(&props[1], 2, 2))
		return (uptadeerror("Invalid arguments point light\n"), delprops(&props), NULL);
	l = (t_li *)newobject(sizeof(t_li), NULL);
	if(!l)
		return NULL;
	l->type = AMBIENT;
	l->i = getfloat(props[1], true, (float []){1, 0}, 0);
	color = getvec4(props[2], true, 255, 0);
	l->color = newrgb((int)color.x, (int)color.y, (int)color.z);
	l->next = NULL;
	return  delprops(&props), (t_li *)errhandler((t_obj *)l, "-> Invalid Light\n");
}

// SECTION - POINT LIGHT
static t_li	*setup_p(char **props)
{
	t_vector	color;
	t_li *l;
	if (count_args(&props[1], 3,3))
		return (uptadeerror("Invalid arguments point light\n"), delprops(&props), NULL);
	l = (t_li *)newobject(sizeof(t_li), NULL);
	if(!l)
		return NULL;
	l->type = POINT;
	l->o = getvec4(props[1], true, INT16_MAX, -INT16_MAX);
	l->i = getfloat(props[2], true, (float []){1, 0}, 0);
	color = getvec4(props[3], true, 255, 0);
	l->color = newrgb((int)color.x, (int)color.y, (int)color.z);
	l->next = NULL;
	return delprops(&props), (t_li *)errhandler((t_obj *)l, "-> Invalid Light\n");
}

t_li	*newlight(int type, char **props)
{
	if (type == POINT)
		return (setup_p(props));
	else if (type == AMBIENT)
		return (setup_am(props));
	return NULL;
}

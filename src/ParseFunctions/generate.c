/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:12:01 by pedro             #+#    #+#             */
/*   Updated: 2024/02/18 20:21:12 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

bool	distributeobject(int type, char **props)
{
	if (type == UNKNOWN)
		return (uptadeerror("Unknown object type\n"), delprops(&props), false);
	if (type == SPHERE)
		oadd((t_obj *)newsphere(type, props), \
			(void **)&((gscene())->objects));
	if (type == PLANE)
		oadd((t_obj *)newplane(type, props), (void **)&((gscene())->objects));
	if (type == CAMERA)
		oadd((t_obj *)newcamera(type, props), (void **)&((gscene())->camera));
	if (type == POINT)
		oadd((t_obj *)newlight(type, props), (void **)&((gscene())->lights));
	if (type == AMBIENT)
		oadd((t_obj *)newlight(type, props), (void **)&((gscene())->am));
	if (type == CYLINDER)
		oadd((t_obj *)newcylinder(type, props),
			(void **)&(gscene())->objects);
	if (type == PARABOLOID)
		oadd((t_obj *)newparaboloid(type, props), \
			(void **)&(gscene())->objects);
	return (true);
}

/*ANCHOR - 
	Norminette: OK
	Compilation: OK
	Tests: OK
*/
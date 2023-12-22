/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 08:54:34 by pedro             #+#    #+#             */
/*   Updated: 2023/12/22 14:16:53 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

void	report(void)
{
	if (scene()->error == 1)
		err("Error: Allocation failture");
	else if (scene()->error == 2)
		err("Error: Invalid object type");
	else if (scene()->error == 3)
		err("Error: Invalid vector origin");
	else if (scene()->error == 4)
		err("Error: Invalid vector normal");
	else if (scene()->error == 5)
		err("Error: Invalid camera fov");
	else if (scene()->error == 6)
		err("Error: Invalid vector");
	else if(scene()->error == 7)
		err("Error: light ration invalid");
	else if (scene()->error == 8)
		err("Error: Invalid light color");
	else if (scene()->error == 9)
		err("Error: Color Overflow");
	else if (scene()->error == 10)
		err("Error: Invalid diamenter");
	else if (scene()->error == 11)
		err("Eror: Unwanted characters");
	else if (scene()->error == 0)
		sucess("Scene loaded sucessfully");
}
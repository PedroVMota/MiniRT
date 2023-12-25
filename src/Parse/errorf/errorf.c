/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 08:54:34 by pedro             #+#    #+#             */
/*   Updated: 2023/12/25 16:58:34 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

void	err(char *msg)
{
	write(2, RED, ft_strlen(RED));
	write(2, "[", 1);
	write(2, msg, ft_strlen(msg));
	write(2, "]", 1);
	write(2, RESET, ft_strlen(RESET));\
	write(2, "\n", 1);
}

void	sucess(char *msg)
{
	write(2, GRN, ft_strlen(GRN));
	write(2, "[", 1);
	write(2, msg, ft_strlen(msg));
	write(2, "]", 1);
	write(2, RESET, ft_strlen(RESET));
		write(2, "\n", 1);

}

void	info(char *msg)
{
	write(2, YEL, ft_strlen(YEL));
	write(2, "[", 1);
	write(2, msg, ft_strlen(msg));
	write(2, "]", 1);
	write(2, RESET, ft_strlen(RESET));
	write(2, "\n", 1);

}

void	ft_exit(void)
{
	free(scene()->line);
	interator(&scene()->objd, free);
	remove_object_list();
	exit(1);
}

void	report(void)
{
	if (scene()->error == -1)
		err("Error: Filename invalid");
	else if (scene()->error == 1)
		err("Error: Allocation failture");
	else if (scene()->error == 2)
		err("Error: Invalid object type");
	else if (scene()->error == 3)
		err("Error: Invalid camera fov");
	else if (scene()->error == 6)
		err("Error: Invalid vector");
	else if (scene()->error == 7)
		err("Error: light ration invalid");
	else if (scene()->error == 8)
		err("Error: Invalid light color");
	else if (scene()->error == 9)
		err("Error: Color Overflow");
	else if (scene()->error == 10)
		err("Error: Invalid diamenter");
	else if (scene()->error == 11)
		err("Eror: Unwanted characters");
	else if (scene()->error == 12)
		err("Error: Invalid Light ratio");
	else if (scene()->error == 0)
		sucess("Scene loaded sucessfully");
}

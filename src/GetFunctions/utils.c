/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:10:13 by pedro             #+#    #+#             */
/*   Updated: 2024/02/18 17:32:14 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

void	uptadeerror(char *msg)
{
	if (write(2, RED, ft_strlen(RED)) == -1)
		NULL;
	if (write(2, "Error: ", 7) == -1)
		NULL;
	if (write(2, RESET, ft_strlen(RESET)) == -1)
		NULL;
	if (write(2, msg, ft_strlen(msg)) == -1)
		NULL;
	(gscene())->error = 1;
}

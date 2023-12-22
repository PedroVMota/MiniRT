/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:41:38 by pvital-m          #+#    #+#             */
/*   Updated: 2023/12/22 18:42:25 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

//parsing notes
bool	parse_data(char *file);

int	main(int ac, char **av)
{
	if (ac < 2 || ac > 2)
	{
		write(2, "Invalid number arguments\n", 19);
		return (1);
	}
	if (!ft_strnstr(av[1], ".rt", ft_strlen(av[1])))
	{
		err("Error: Invalid file format");
		return (1);
	}
	if (parse_data(av[1]))
		return (1);
}

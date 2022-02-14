/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 09:37:27 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/14 11:08:50 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	char	*path;

	path = parser_path(env);
	if (argc == 5)
	{
		printf("argc = %d\n", argc);
		start(argv, path);
	
	}
	else
		ft_printf("Error faltan Argumentos\n");
	return (0);

	while(1)
	{
		sleep(5);
	}
}

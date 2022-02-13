/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 09:37:27 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/13 12:38:05 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int i;

	i = 1;
	argv[2] = NULL;

	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	if (argc > 1)
	{
		printf("argc = %d\n", argc);
		//start(argv);
	}
	else
		ft_printf("Error\n");
	return (0);
}

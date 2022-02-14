/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 09:37:27 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/14 15:47:07 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	if (argc == 5)
	{
		printf("argc = %d\n", argc);
		start(argv, env);
	}
	else
		ft_printf("Error faltan Argumentos\n");
	return (0);
}

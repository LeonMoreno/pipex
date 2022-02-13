/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 09:37:27 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/13 16:19:50 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	char	*path;

	path = parser_path(env);
	if (argc > 1)
	{
		printf("argc = %d\n", argc);
		start(argv, path);
	}
	else
		ft_printf("Error\n");
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserPath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:07:36 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/13 16:16:25 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*parser_path(char **env)
{
	char	*line;
	char	**arg_split;
	int		i;
	int		acc;
	char	*path;

	i = 1;
	line = NULL;
	while (env[i] && line == NULL)
	{
		line = ft_strnstr(env[i], "PATH", 4);
		i++;
	}
	arg_split = ft_split(line, ':');
	i = 0;
	acc = -1;
	while (acc == -1)
	{
		path = ft_strjoin(arg_split[i], "/ls");
		acc = access(path, F_OK);
		i++;
	}
	path = ft_strjoin(arg_split[i - 1], "/");
	return (path);
}

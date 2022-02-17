/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserPath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:07:36 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/15 14:17:00 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*parser_path(char *argu, t_pipex *pipex)
{
	char	*line;
	char	**arg_split;
	int		i;

	i = 1;
	line = NULL;
	while (pipex->env[i] && line == NULL)
	{
		line = ft_strnstr(pipex->env[i], "PATH", 4);
		i++;
	}
	arg_split = ft_split(line, ':');
	return (parser_cmd(argu, arg_split));
}

char	*parser_cmd(char *argu, char **arg_split)
{
	int		i;
	int		acc;
	char	*path;

	i = 0;
	acc = -1;
	argu = ft_strjoin("/", argu);
	while (acc == -1 && arg_split[i])
	{
		path = ft_strjoin(arg_split[i], argu);
		acc = access(path, F_OK);
		i++;
	}
	if (acc == -1)
	{
		printf("Error cmd: %s no encontrado\n", argu);
		exit (-1);
	}
	return (path);
}

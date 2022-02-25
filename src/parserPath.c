/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserPath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:07:36 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/22 07:42:37 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*parser_path(char *argu, t_pipex *pipex)
{
	char	**arg_split;

	while (ft_strncmp(*pipex->env, "PATH", 4))
		pipex->env++;
	arg_split = ft_split((*pipex->env + 5), ':');
	return (parser_cmd(argu, arg_split));
}

char	*parser_cmd(char *argu, char **arg_split)
{
	int		i;
	int		acc;
	char	*path;
	char	*ag;

	i = 0;
	acc = -1;
	ag = ft_strjoin("/", argu);
	while (acc == -1 && arg_split[i])
	{
		path = ft_strjoin(arg_split[i], ag);
		acc = access(path, F_OK);
		if (acc == -1)
			ft_free(path, arg_split[i]);
		i++;
	}
	if (acc == -1)
	{
		ft_free_2(arg_split, ag);
		msg_cmd(ERR_CMD);
	}
	return (path);
}

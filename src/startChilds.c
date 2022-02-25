/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startChilds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 08:18:56 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/22 15:01:04 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	startchild1(t_pipex *pipex)
{
	char	**cmd1;
	char	*path_cmd;
	char	*argv_cmd1[4];

	close (pipex->pip1[OUT]);
	cmd1 = ft_split(pipex->agv[2], ' ');
	path_cmd = parser_path(cmd1[0], pipex);
	if (path_cmd == NULL)
		ft_free_2(cmd1, cmd1[0]);
	argv_cmd1[0] = cmd1[0];
	argv_cmd1[1] = cmd1[1];
	argv_cmd1[2] = cmd1[2];
	argv_cmd1[3] = NULL;
	dup2(pipex->fdin, STDIN_FILENO);
	dup2(pipex->pip1[IN], STDOUT_FILENO);
	close(pipex->pip1[IN]);
	execve(path_cmd, argv_cmd1, NULL);
}

void	startchild_last(t_pipex *pipex)
{
	char	**cmd2;
	char	*argv_cmd2[4];
	char	*path_cmd;

	cmd2 = ft_split(pipex->agv[pipex->arg -2], ' ');
	path_cmd = parser_path(cmd2[0], pipex);
	if (path_cmd == NULL)
		ft_free_2(cmd2, cmd2[0]);
	argv_cmd2[0] = cmd2[0];
	argv_cmd2[1] = cmd2[1];
	argv_cmd2[2] = cmd2[2];
	argv_cmd2[3] = NULL;
	dup2(pipex->pip1[OUT], STDIN_FILENO);
	close(pipex->pip1[OUT]);
	dup2(pipex->fdout, STDOUT_FILENO);
	execve(path_cmd, argv_cmd2, NULL);
}

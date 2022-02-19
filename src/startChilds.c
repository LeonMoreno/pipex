/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startChilds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 09:58:51 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/18 21:26:23 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	startchild1(t_pipex *pipex)
{
	char	**cmd1;
	char	*path_cmd;
	char	*argv_cmd1[3];

	close (pipex->pip1[OUT]);
	cmd1 = ft_split(pipex->agv[2], ' ');
	path_cmd = parser_path(cmd1[0], pipex);
	argv_cmd1[0] = cmd1[0];
	argv_cmd1[1] = cmd1[1];
	argv_cmd1[2] = NULL;
	dup2(pipex->fdin, STDIN_FILENO);
	dup2(pipex->pip1[IN], STDOUT_FILENO);
	close(pipex->pip1[IN]);
	execve(path_cmd, argv_cmd1, NULL);
}

void	startchild_n_2(int i, t_pipex *pipex)
{
	char	**cmd;
	char	*path_cmd;
	char	*argv_cmd[3];

	close(pipex->pipn[i][OUT]);
	cmd = ft_split(pipex->agv[i + 3], ' ');
	path_cmd = parser_path(cmd[0], pipex);
	argv_cmd[0] = cmd[0];
	argv_cmd[1] = cmd[1];
	argv_cmd[2] = NULL;
	dup2(pipex->pip1[OUT], STDIN_FILENO);
	close(pipex->pip1[OUT]);
	dup2(pipex->pipn[i][IN], STDOUT_FILENO);
	close(pipex->pipn[i][IN]);
	execve(path_cmd, argv_cmd, NULL);
	perror("execve Error");
}

void	startchild_n(int i, t_pipex *pipex)
{
	char	**cmd;
	char	*path_cmd;
	char	*argv_cmd[3];

	close_pipe_child_n(i, pipex);
	cmd = ft_split(pipex->agv[i + 3], ' ');
	path_cmd = parser_path(cmd[0], pipex);
	argv_cmd[0] = cmd[0];
	argv_cmd[1] = cmd[1];
	argv_cmd[2] = NULL;
	dup2(pipex->pipn[i - 1][OUT], STDIN_FILENO);
	close(pipex->pipn[i - 1][OUT]);
	dup2(pipex->pipn[i][IN], STDOUT_FILENO);
	close(pipex->pipn[i][IN]);
	execve(path_cmd, argv_cmd, NULL);
	perror("execve Error");
}

void	startchild_last(t_pipex *pipex)
{
	char	**cmd2;
	char	*argv_cmd2[3];
	char	*path_cmd;

	cmd2 = ft_split(pipex->agv[*pipex->arg -2], ' ');
	path_cmd = parser_path(cmd2[0], pipex);
	argv_cmd2[0] = cmd2[0];
	argv_cmd2[1] = cmd2[1];
	argv_cmd2[2] = NULL;
	if (pipex->last_pipe >= 0)
	{
		dup2(pipex->pipn[pipex->last_pipe][OUT], STDIN_FILENO);
		close(pipex->pipn[pipex->last_pipe][OUT]);
	}
	else
	{
		dup2(pipex->pip1[OUT], STDIN_FILENO);
		close(pipex->pip1[OUT]);
	}
	dup2(pipex->fdout, STDOUT_FILENO);
	execve(path_cmd, argv_cmd2, NULL);
}

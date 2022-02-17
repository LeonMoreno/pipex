/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startChilds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 09:58:51 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/15 22:17:51 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	startchild1(t_pipex *pipex)
{
	//printf("@@ CHiLD_01 PIPE_IN %d PIPE_OUT %d ##\n", end[1], end[0]);

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

void startchild_n_2(int i, t_pipex *pipex)
{
 // Necesito saber que parameteo estoy enviando
 // Cual argv estoy, para asi mismo saber cual ejecutar.
 // Si envio desde la FUNC q llama 3 + i;

 	char	**cmd;
	char	*path_cmd;
	char	*argv_cmd[3];

	//printf("@@ CHiLD_N_02 PIPE_IN %d PIPE_OUT %d ##\n", multi_end[1], multi_end[0]);

	close(pipex->pip1[IN]);
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

void startchild_n(int i, t_pipex *pipex)
{
 	char	**cmd;
	char	*path_cmd;
	char	*argv_cmd[3];
	//char	s[20];

	//printf("@@ Start CHILD_N PID = %d argc %d pipe_OUT = %d pipe_IN = %d ##\n", getpid(), argc, multi_end[0], multi_end[1]);
	close(pipex->pip1[IN]);
	close(pipex->pip1[OUT]);
	close(pipex->pipn[i - 1][IN]);
	close(pipex->pipn[i][OUT]);

	cmd = ft_split(pipex->agv[i + 3], ' ');

	path_cmd = parser_path(cmd[0], pipex);
	argv_cmd[0] = cmd[0];
	argv_cmd[1] = cmd[1];
	argv_cmd[2] = NULL;
	dup2(pipex->pipn[i - 1][OUT], STDIN_FILENO);
	close(pipex->pipn[i - 1][OUT]);

	//read(STDIN_FILENO, s, 30);
	//printf("CHIld_N BUFF\n%s\n", s);
	//printf("CMD = %s \n", cmd[0]);

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
	//char	s[30];

	//printf("@@ Start CHILD_N PID = %d argc %d pipe_OUT = %d pipe_IN = %d ##\n", getpid(), argc, multi_end[0], multi_end[1]);
	//read(multi_end[OUT], s, 30);
	//printf("CHIld_LAST BUFF = %s\n", s);

	cmd2 = ft_split(pipex->agv[*pipex->arg -2], ' ');

	path_cmd = parser_path(cmd2[0], pipex);
	argv_cmd2[0] = cmd2[0];
	argv_cmd2[1] = cmd2[1];
	argv_cmd2[2] = NULL;
	dup2(pipex->pipn[pipex->last_pipe][OUT], STDIN_FILENO);
	close(pipex->pipn[pipex->last_pipe][OUT]);

	dup2(pipex->fdout, STDOUT_FILENO);
	//close(*fdout);

	execve(path_cmd, argv_cmd2, NULL);
}

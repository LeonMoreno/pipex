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

void	startchild1(char **argv, int end[2], int fdin, char **env)
{
	//printf("@@ CHiLD_01 PIPE_IN %d PIPE_OUT %d ##\n", end[1], end[0]);

	char	**cmd1;
	char	*path_cmd;
	char	*argv_cmd1[3];

	close (end[OUT]);

	cmd1 = ft_split(argv[2], ' ');
	path_cmd = parser_path(cmd1[0], env);
	argv_cmd1[0] = cmd1[0];
	argv_cmd1[1] = cmd1[1];
	argv_cmd1[2] = NULL;

	dup2(fdin, STDIN_FILENO);

	dup2(end[IN], STDOUT_FILENO);
	close(end[IN]);
	execve(path_cmd, argv_cmd1, NULL);
}

void startchild_n_2(int argc, char **argv, int end[2], char **env, int multi_end[2])
{
 // Necesito saber que parameteo estoy enviando
 // Cual argv estoy, para asi mismo saber cual ejecutar.
 // Si envio desde la FUNC q llama 3 + i;

 	char	**cmd;
	char	*path_cmd;
	char	*argv_cmd[3];


	//printf("@@ CHiLD_N_02 PIPE_IN %d PIPE_OUT %d ##\n", multi_end[1], multi_end[0]);

	close(end[IN]);
	close(multi_end[OUT]);


	cmd = ft_split(argv[argc], ' ');

	path_cmd = parser_path(cmd[0], env);
	argv_cmd[0] = cmd[0];
	argv_cmd[1] = cmd[1];
	argv_cmd[2] = NULL;
	dup2(end[OUT], STDIN_FILENO);
	close(end[OUT]);

	dup2(multi_end[IN], STDOUT_FILENO);
	close(multi_end[IN]);

	execve(path_cmd, argv_cmd, NULL);
	perror("execve Error");

}

void startchild_n(int argc, char **argv, int end[2], char **env, int multi_end[2])
{
 	char	**cmd;
	char	*path_cmd;
	char	*argv_cmd[3];
	//char	s[20];

	printf("@@ Start CHILD_N PID = %d argc %d pipe_OUT = %d pipe_IN = %d ##\n", getpid(), argc, multi_end[0], multi_end[1]);


	close(end[IN]);
	close(end[OUT]);
	close((multi_end - 2)[IN]);
	close((multi_end)[OUT]);

	cmd = ft_split(argv[argc], ' ');

	path_cmd = parser_path(cmd[0], env);
	argv_cmd[0] = cmd[0];
	argv_cmd[1] = cmd[1];
	argv_cmd[2] = NULL;
	dup2((multi_end - 2)[OUT], STDIN_FILENO);
	close((multi_end - 2)[OUT]);

	//read(STDIN_FILENO, s, 30);
	//printf("CHIld_N BUFF\n%s\n", s);
	//printf("CMD = %s \n", cmd[0]);

	dup2(multi_end[IN], STDOUT_FILENO);
	close(multi_end[IN]);

	execve(path_cmd, argv_cmd, NULL);
	perror("execve Error");
}

void	startchild2(int argc, char **argv, int *fdout, char **env, int multi_end[2])
{
	char	**cmd2;
	char	*argv_cmd2[3];
	char	*path_cmd;
	//char	s[30];

	//printf("@@ Start CHILD_N PID = %d argc %d pipe_OUT = %d pipe_IN = %d ##\n", getpid(), argc, multi_end[0], multi_end[1]);

	close(multi_end[IN]);

	//read(multi_end[OUT], s, 30);
	//printf("CHIld_LAST BUFF = %s\n", s);

	*fdout = open(argv[argc -1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

	if (*fdout == -1)
		perror("Error");
	cmd2 = ft_split(argv[argc -2], ' ');

	path_cmd = parser_path(cmd2[0], env);
	argv_cmd2[0] = cmd2[0];
	argv_cmd2[1] = cmd2[1];
	argv_cmd2[2] = NULL;
	dup2(multi_end[OUT], STDIN_FILENO);
	close(multi_end[OUT]);

	dup2(*fdout, STDOUT_FILENO);
	//close(*fdout);

	execve(path_cmd, argv_cmd2, NULL);
}

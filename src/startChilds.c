/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startChilds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 09:58:51 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/14 15:48:18 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	startchild1(char **argv, int end[2], int fdin, char **env)
{
	char	**cmd1;
	char	*path_cmd;
	char	*argv_cmd1[3];

	cmd1 = ft_split(argv[2], ' ');
	path_cmd = parser_path(cmd1[0], env);
	argv_cmd1[0] = cmd1[0];
	argv_cmd1[1] = cmd1[1];
	argv_cmd1[2] = NULL;
	close (end[READ_END]);
	dup2(fdin, STDIN_FILENO);
	dup2(end[WRITE_END], STDOUT_FILENO);
	close(end[WRITE_END]);
	execve(path_cmd, argv_cmd1, NULL);
}

void	startchild2(char **argv, int end[2], int *fdout, char **env)
{
	char	**cmd2;
	char	*argv_cmd2[3];
	char	*path_cmd;

	*fdout = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*fdout == -1)
		perror("Error");
	cmd2 = ft_split(argv[3], ' ');
	path_cmd = parser_path(cmd2[0], env);
	argv_cmd2[0] = cmd2[0];
	argv_cmd2[1] = cmd2[1];
	argv_cmd2[2] = NULL;
	dup2(end[READ_END], STDIN_FILENO);
	close(end[READ_END]);
	dup2(*fdout, STDOUT_FILENO);
	execve(path_cmd, argv_cmd2, NULL);
}

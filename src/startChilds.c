/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startChilds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 09:58:51 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/13 12:22:57 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	startchild1(char **argv, int end[2], int fdin)
{
	char	**cmd1;
	char	*path_cmd1;
	char	*argv_cmd1[3];
	int		acc;

	cmd1 = ft_split(argv[2], ' ');
	argv_cmd1[0] = cmd1[0];
	argv_cmd1[1] = cmd1[1];
	argv_cmd1[2] = NULL;
	path_cmd1 = ft_strjoin(PATH, cmd1[0]);
	acc = access(path_cmd1, F_OK);
	if (acc < 0)
	{
		printf("cmd: %s no encontrado\n", cmd1[0]);
		exit (-1);
	}
	close (end[READ_END]);
	dup2(fdin, STDIN_FILENO);
	dup2(end[WRITE_END], STDOUT_FILENO);
	close(end[WRITE_END]);
	execve(path_cmd1, argv_cmd1, NULL);
}

void	startchild2(char **argv, int end[2], int *fdout)
{
	char	**cmd2;
	char	*argv_cmd2[3];
	char	*path_cmd2;
	int		acc;

	*fdout = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*fdout == -1)
		perror("Error");
	cmd2 = ft_split(argv[3], ' ');
	argv_cmd2[0] = cmd2[0];
	argv_cmd2[1] = cmd2[1];
	argv_cmd2[2] = NULL;
	path_cmd2 = ft_strjoin(PATH, cmd2[0]);
	acc = access(path_cmd2, F_OK);
	if (acc < 0)
	{
		printf("cmd: %s no encontrado\n", cmd2[0]);
		exit (-1);
	}
	dup2(end[READ_END], STDIN_FILENO);
	close(end[READ_END]);
	dup2(*fdout, STDOUT_FILENO);
	execve(path_cmd2, argv_cmd2, NULL);
}

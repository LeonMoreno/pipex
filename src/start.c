/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 09:39:48 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/13 16:12:45 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	start(char **argv, char *path)
{
	int		fdin;

	fdin = open(argv[1], O_RDONLY);
	if (fdin == -1)
	{
		perror("Error");
		exit(-1);
	}
	startfork(argv, fdin, path);
}

void	startfork(char **argv, int fdin, char *path)
{
	int		end[2];
	int		fdout;
	pid_t	child[2];
	int		status;

	pipe(end);
	child[0] = fork();
	if (child[0] == 0)
		startchild1(argv, end, fdin, path);
	else if (child[0] > 0)
	{
		close(end[WRITE_END]);
		child[1] = fork();
		if (child[1] == 0)
			startchild2(argv, end, &fdout, path);
		else if (child[1] > 0)
			close(fdout);
	}
	waitpid(child[0], &status, 0);
	waitpid(child[1], &status, 0);
}

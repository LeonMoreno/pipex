/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 21:23:22 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/18 21:31:00 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe_father(int i, t_pipex *pipex)
{
	if (i >= 0)
	{
		close(pipex->pip1[OUT]);
		close(pipex->pipn[pipex->last_pipe][IN]);
		while (i > 0)
		{
			close(pipex->pipn[i - 1][IN]);
			close(pipex->pipn[i - 1][OUT]);
			i--;
		}
	}
}

void	close_pipe_child_n(int i, t_pipex *pipex)
{
	int		y;

	y = i - 2;
	close(pipex->pip1[OUT]);
	close(pipex->pipn[i - 1][IN]);
	close(pipex->pipn[i][OUT]);
	while (y >= 0)
	{
		close(pipex->pipn[y][IN]);
		close(pipex->pipn[y][OUT]);
		y--;
	}
}

void	sort_child_n(int i)
{
	int	status;

	waitpid(0, &status, 0);
	while (i >= 0)
	{
		waitpid(0, &status, 0);
		i--;
	}
}

void	open_files(t_pipex *pipex)
{
	pipex->fdin = open(pipex->agv[1], O_RDONLY, 0644);
	if (pipex->fdin == -1)
	{
		perror("Error");
		exit(-1);
	}
	pipex->fdout = open(pipex->agv[*pipex->arg -1] \
		, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fdout == -1)
		perror("Error");
}

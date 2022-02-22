/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 21:23:22 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/22 14:54:04 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free(char *ptr1, char *ptr2)
{
	free(ptr1);
	free(ptr2);
}

void	ft_free_2(char **doble, char *ptr2)
{
	free(doble);
	free(ptr2);
}

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

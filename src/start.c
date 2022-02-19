/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 09:39:48 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/18 21:32:25 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*	Para probar y ver los procesos en el sistema:
	ps lf -- Y usar el siguiente codigo.
	while (1)
	{
		sleep(5);
		printf("Mi PID es %d\n", getpid());
	}*/
void	start(t_pipex *pipex)
{
	pid_t	child_1;

	open_files(pipex);
	pipe(pipex->pip1);
	child_1 = fork();
	if (child_1 == 0)
		startchild1(pipex);
	close(pipex->pip1[IN]);
	startfork_n(pipex);
	close(pipex->fdin);
	startfork_last(pipex);
	sort_child_n(pipex->last_pipe);

}

void	startfork_n(t_pipex *pipex)
{
	pid_t	cmds[10];
	int		i;

	i = 0;
	while ((*pipex->arg - 5) > i)
	{
		pipe(pipex->pipn[i]);
		cmds[i] = fork();
		if (i == 0 && cmds[i] == 0)
		{
			startchild_n_2(i, pipex);
			exit (0);
		}
		else if (cmds[i] == 0)
		{
			startchild_n(i, pipex);
			exit (0);
		}
		i++;
	}
	i--;
	pipex->last_pipe = i;
	close_pipe_father(i, pipex);
}

void	startfork_last(t_pipex *pipex)
{
	int	child_last;
	int	status;

	child_last = fork();
	if (child_last == 0)
		startchild_last(pipex);
	close(pipex->fdout);
	close(pipex->pipn[pipex->last_pipe][OUT]);
	waitpid(child_last, &status, 0);
	}

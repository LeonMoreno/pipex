/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 09:39:48 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/15 22:17:54 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void open_files(t_pipex *pipex)
{
	pipex->fdin = open(pipex->agv[1], O_RDONLY, 0644);
	printf("@@ fdin = %d ##\n", pipex->fdin);
	if (pipex->fdin == -1)
	{
		perror("Error");
		exit(-1);
	}
	pipex->fdout = open(pipex->agv[*pipex->arg -1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("@@ fdin = %d ##\n", pipex->fdout);
	if (pipex->fdout == -1)
		perror("Error");
}

void	start(t_pipex *pipex)
{
	pid_t	child_1;
	int		status;
	int		sort;

	printf("@@ Start___PROCES PADRE PID = %d ##\n", getpid());

	open_files(pipex);

	pipe(pipex->pip1);
	child_1 = fork();
	if (child_1 == 0)
		startchild1(pipex);
	else if (child_1 > 0)
	{
		startfork_n(pipex);
		close(pipex->fdin);
	}
	startfork_last(pipex);
	sort = waitpid(child_1, &status, 0);
	printf("## CHILD_1 PID %d, Salio con Status %d ##\n", sort, status);
}

void	startfork_n(t_pipex *pipex)
{
	pid_t	cmds[*pipex->arg - 5];
	int 	i;
	i = 0;
	while ((*pipex->arg - 5) > i)
	{
		pipe(pipex->pipn[i]);
		cmds[i] = fork();
		if (i == 0 && cmds[i] == 0)
		{
		//	printf("PRImER WHILE  i = %d\n", i);
			startchild_n_2(i, pipex);
			exit (0);
		}
		else if (cmds[i] == 0)
		{
			//printf("SeGUNDO WHILE  i = %d\n", i);
			startchild_n(i,pipex);
			exit (0);
		}
		//printf("Valor de i en WhiLE = %d\n", i);
		//printf("@@ WHILE Multi_PIPE_IN %d PIPE_OUT %d#\n", multi_end[i][0], multi_end[i][1]);
		i++;
	}
	i--;
	pipex->last_pipe = i;
	while (i >= 0)
	{
		close(pipex->pipn[i][IN]);
		close(pipex->pipn[i][OUT]);
		i--;
	}
	close(pipex->pip1[IN]);
	close(pipex->pip1[OUT]);
	close(pipex->pipn[pipex->last_pipe][IN]);
}

void	startfork_last(t_pipex *pipex)
{
		int child_last;
		int		status;
		int		sort;
		int		i;

		i = pipex->last_pipe;
		child_last = fork();
		printf("Valor Afuera de i = %d\n", i);
		if (child_last == 0)
			startchild_last(pipex);
		else if (child_last > 0)
		{
			printf("Estoy en el PAdre child_1\n");
			close(pipex->fdout);
			sort = waitpid(child_last, &status, 0);
			printf("## CHILD_1 PID %d, Salio con Status %d ##\n", sort, status);

			close(pipex->pip1[0]);
			close(pipex->pip1[1]);
			close(pipex->pipn[pipex->last_pipe][0]);
			close(pipex->pipn[pipex->last_pipe][1]);
		}

		while (i >= 0)
		{
			sort = waitpid(0, &status, 0);
			printf("## CHILD_N PID %d, Salio con Status %d ##\n", sort, status);
			i--;
		}
		sort = waitpid(child_last, &status, 0);
		printf("## CHILD_LAST PID %d, Salio con Status %d ##\n", sort, status);

		/*while (1)
		{
			sleep(5);
			printf("Mi PID es %d\n", getpid());
		}
			exit(0);
		}*/
}

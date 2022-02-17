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

void	start(int argc, char **argv, char **env)
{
	int		fdin;

	printf("@@ Start___PROCES PADRE PID = %d ##\n", getpid());
	fdin = open(argv[1], O_RDONLY, 0644);
	printf("@@ fdin = %d ##\n", fdin);

	if (fdin == -1)
	{
		perror("Error");
		exit(-1);
	}
	startfork(argc, argv, fdin, env);
}

void	startfork(int argc, char **argv, int fdin, char **env)
{
	int		end[2];
	int		fdout;
	pid_t	child[2];
	int		status;
	int		sort;
	int 	i;
	int		multi_end[5][2];

	pid_t		cmds[argc - 5];

	i = 0;
	fdout = 0;
	pipe(end);
	child[0] = fork();
	if (child[0] == 0)
		startchild1(argv, end, fdin, env);
	else if (child[0] > 0)
	{
		while ((argc - 5) > i)
		{
			pipe(multi_end[i]);

			cmds[i] = fork();
			if (i == 0 && cmds[i] == 0)
			{
			//	printf("PRImER WHILE  i = %d\n", i);
				startchild_n_2(3 + i, argv, end, env, multi_end[i]);
				exit (0);
			}

			else if (cmds[i] == 0)
			{
				//printf("SeGUNDO WHILE  i = %d\n", i);
				startchild_n(3 + i, argv, end, env, multi_end[i]);
				exit (0);
			}
			//printf("Valor de i en WhiLE = %d\n", i);
			printf("@@ WHILE Multi_PIPE_IN %d PIPE_OUT %d#\n", multi_end[i][0], multi_end[i][1]);
			i++;
		}
		i--;
		close(multi_end[i - 2][IN]);
		close(multi_end[i - 2][OUT]);
		close(end[IN]);
		close(end[OUT]);
		child[1] = fork();
		printf("Valor Afuera de i = %d\n", i);
		if (child[1] == 0)
			startchild2(argc, argv, &fdout, env, multi_end[i]);
		else if (child[1] > 0)
		{
			printf("Estoy en el PAdre child_1\n");
			close(fdout);
			//exit(0);
		}

		close(end[0]);
		close(end[1]);
		close(multi_end[i -1][0]);
		close(multi_end[i -1][1]);


	}
	sort = waitpid(child[0], &status, 0);
	printf("## CHILD_1 PID %d, Salio con Status %d ##\n", sort, status);

	while (i >= 0)
		{
			sort = waitpid(cmds[i], &status, 0);
			printf("## CHILD_N PID %d, Salio con Status %d ##\n", sort, status);
			i--;
		}


	sort = waitpid(child[1], &status, 0);
	printf("## CHILD_LAST PID %d, Salio con Status %d ##\n", sort, status);


	/*while (1)
	{
		sleep(5);
		printf("Mi PID es %d\n", getpid());
	}*/
}

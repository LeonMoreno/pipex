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

	fdin = open(argv[1], O_RDONLY);
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
			if (cmds[i] == 0)
			{
				startchild_n(3 + i, argv, end, env, multi_end[i]);
				exit (0);
			}
			i++;
		}
		//close(end[WRITE_END]);
		child[1] = fork();
		if (child[1] == 0)
			startchild2(argc, argv, end, &fdout, env, multi_end[i -1]);
		else if (child[1] > 0)
			close(fdout);
		close(end[0]);
		close(end[1]);
		close(multi_end[i -1][0]);
		close(multi_end[i -1][1]);
	}
	sort = waitpid(child[0], &status, 0);
	sort = waitpid(child[1], &status, 0);
	i--;
	while (i >= 0)
	{
		sort = waitpid(cmds[i], &status, 0);
		printf("####CHILD_N PID %d, Salio con Status %d\n", sort, status);
		i--;
	}
	
	/*while (1)
	{
		sleep(5);
		printf("Mi PID es %d\n", getpid());
	}*/
}

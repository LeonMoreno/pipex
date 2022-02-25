/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 09:37:27 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/25 16:39:56 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	startfork_last(t_pipex *pipex)
{
	int	child_last;
	int	status;

	child_last = fork();
	if (child_last == 0)
		startchild_last(pipex);
	close(pipex->fdout);
	waitpid(child_last, &status, 0);
}

void	start(t_pipex *pipex)
{
	pid_t	child_1;

	pipe(pipex->pip1);
	child_1 = fork();
	if (child_1 == 0)
		startchild1(pipex);
	close(pipex->pip1[IN]);
	close(pipex->fdin);
	startfork_last(pipex);
	close(pipex->pip1[OUT]);
}

static	void	open_files(t_pipex *pipex)
{
	pipex->fdin = open(pipex->agv[1], O_RDONLY);
	if (pipex->fdin < 0)
		msg_err(ERR_INFILE);
	pipex->fdout = open(pipex->agv[pipex->arg -1], \
		O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (pipex->fdout == -1)
		msg_err(ERR_OUTFILE);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.arg = argc;
	pipex.agv = argv;
	pipex.env = envp;
	if (argc != 5)
		return (msg(ERR_INPUT));
	open_files(&pipex);
	start(&pipex);
	return (0);
}

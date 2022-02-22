/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 09:37:27 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/22 16:05:31 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	arg_infile(char *argu, t_pipex *pipex)
{
	if (argu && !ft_strncmp("here_doc", argu, 8))
	{
		pipex->here_doc = 1;
		return (6);
	}
	else
	{
		pipex->here_doc = 0;
		return (5);
	}
}

static	void	ft_here_doc(t_pipex *pipex)
{
	char	*line[30];
	int		file;
	int		i;

	file = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (pipex->fdin < 0)
		msg_err(ERR_INFILE);
	i = 0;
	line[0] = get_next_line(0);
	while (ft_strncmp(line[i], pipex->agv[2], ft_strlen(pipex->agv[2])))
	{
		if (ft_strncmp(line[i], pipex->agv[2], ft_strlen(pipex->agv[2])))
			write (file, line[i], ft_strlen(line[i]));
		free (line[i]);
		i++;
		line[i] = get_next_line(0);
	}
	free(line[i]);
	close(file);
	pipex->fdin = open(".here_doc", O_RDONLY);
	if (pipex->fdin < 0)
		msg_err(ERR_INFILE);
}

static	void	open_files(t_pipex *pipex)
{
	if (pipex->here_doc == 0)
	{
		pipex->fdin = open(pipex->agv[1], O_RDONLY);
		if (pipex->fdin < 0)
			msg_err(ERR_INFILE);
		pipex->fdout = open(pipex->agv[pipex->arg -1], \
			O_CREAT | O_RDWR | O_TRUNC, 0000644);
		if (pipex->fdout == -1)
			msg_err(ERR_OUTFILE);
	}
	else if (pipex->here_doc == 1)
	{
		ft_here_doc(pipex);
		pipex->fdout = open(pipex->agv[pipex->arg -1], \
			O_CREAT | O_RDWR | O_APPEND, 0000644);
		if (pipex->fdout == -1)
			msg_err(ERR_OUTFILE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.arg = argc;
	pipex.agv = argv;
	pipex.env = envp;
	if (argc < arg_infile(argv[1], &pipex))
		return (msg(ERR_INPUT));
	if (pipex.here_doc == 0)
	{
		pipex.argv_1 = argv[2];
		pipex.n = 3;
	}
	else if (pipex.here_doc == 1)
	{
		pipex.argv_1 = argv[3];
		pipex.n = 4;
	}
	open_files(&pipex);
	start(&pipex);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 21:34:36 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/18 21:36:09 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# define OUT 0 /*index pipe extremo lectura */
# define IN 1 /*index pipe extremo escritura */
typedef struct s_pipex {
	int		pip1[2];
	int		pipn[5][2];
	int		last_pipe;
	int		*arg;
	char	**agv;
	char	**env;
	int		fdin;
	int		fdout;
}	t_pipex;
void	start(t_pipex *pipex);
void	open_files(t_pipex *pipex);
void	startfork_n(t_pipex *pipex);
void	startchild1(t_pipex *pipex);
void	startchild_n_2(int i, t_pipex *pipex);
void	startchild_n(int i, t_pipex *pipex);
void	startfork_last(t_pipex *pipex);
void	startchild_last(t_pipex *pipex);
void	close_pipe_father(int i, t_pipex *pipex);
void	close_pipe_child_n(int i, t_pipex *pipex);
void	sort_child_n(int i);
char	*parser_path(char *argu, t_pipex *pipex);
char	*parser_cmd(char *argu, char **arg_split);
#endif

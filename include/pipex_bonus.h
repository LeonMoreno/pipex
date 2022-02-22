/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 21:34:36 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/22 15:51:27 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/include/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

/* strerror */
# include <string.h>

# define ERR_INPUT	"Invalid number or Arguments.\n"
# define ERR_INFILE	"Invalid in-File"
# define ERR_OUTFILE	"Invalid out-File"
# define ERR_CMD		"Command not found\n"

# define OUT 0 /*index pipe extremo lectura */
# define IN 1 /*index pipe extremo escritura */
typedef struct s_pipex {
	int		pip1[2];
	int		pipn[10][2];
	int		last_pipe;
	int		arg;
	char	**agv;
	char	**env;
	char	*argv_1;
	int		n;
	int		fdin;
	int		fdout;
	int		here_doc;
}	t_pipex;
void	start(t_pipex *pipex);
void	startchild1(t_pipex *pipex);
void	startchild_n_2(int i, t_pipex *pipex);
void	startchild_n(int i, t_pipex *pipex);
void	startchild_last(t_pipex *pipex);

/* Parser CMD */
char	*parser_path(char *argu, t_pipex *pipex);
char	*parser_cmd(char *argu, char **arg_split);

/* Utils PIPEX */
void	close_pipe_father(int i, t_pipex *pipex);
void	close_pipe_child_n(int i, t_pipex *pipex);
void	sort_child_n(int i);
void	ft_free(char *ptr1, char *ptr2);
void	ft_free_2(char **doble, char *ptr2);

/* Error MSG */
int		msg(char *erro);
void	msg_err(char *erro);
void	msg_cmd(char *erro);
#endif

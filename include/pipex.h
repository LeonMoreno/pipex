#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define OUT 0 /*index pipe extremo lectura */
#define IN 1 /*index pipe extremo escritura */


typedef struct s_pipex {
	int pip1[2];
	int	pipn[5][2];
	int last_pipe;
	int *arg;
	char **agv;
	char **env;
	int	fdin;
	int	fdout;
} t_pipex;

void start(t_pipex *pipex);
void open_files(t_pipex *pipex);
void startfork_n(t_pipex *pipex);

void startchild1(t_pipex *pipex);
void startchild_n_2(int i, t_pipex *pipex);
void startchild_n(int i, t_pipex *pipex);

void	startfork_last(t_pipex *pipex);


void startchild_last(t_pipex *pipex);







char *parser_path(char *argu, t_pipex *pipex);
char *parser_cmd(char *argu, char **arg_split);
//void path_utils(char **arg_split, char **path, char **path2);

#endif

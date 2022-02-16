#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define READ_END 0 /*index pipe extremo lectura */
#define WRITE_END 1 /*index pipe extremo escritura */

void start(int argc, char **argv, char **env);
void startchild1(char **argv, int end[2], int fdin, char **env);



void startchild2(int argc, char **argv, int end[2], int *fdout, char **env, int multi_end[2]);

void startchild_n(int argc, char **argv, int end[2], char **env, int multi_end[2]);


void startfork(int argc, char **argv, int fdin, char **env);
char *parser_path(char *argu, char **env);
char *parser_cmd(char *argu, char **arg_split);
//void path_utils(char **arg_split, char **path, char **path2);

#endif

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define READ_END 0 /*index pipe extremo lectura */
#define WRITE_END 1 /*index pipe extremo escritura */

void start(char **argv, char *path);
void startchild1(char **argv, int end[2], int fdin, char *path);
void startchild2(char **argv, int end[2], int *fdout, char *path);
void startfork(char **argv, int fdin, char *path);
char *parser_path(char **env);


#endif

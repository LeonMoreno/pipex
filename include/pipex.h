#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define READ_END 0 /*index pipe extremo lectura */
#define WRITE_END 1 /*index pipe extremo escritura */
#define PATH "/usr/bin/"

void start(char **argv);
void startchild1(char **argv, int end[2], int fdin);
void startchild2(char **argv, int end[2], int *fdout);
void startfork(char **argv, int fdin);


#endif

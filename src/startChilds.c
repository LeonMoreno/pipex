/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startChilds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 09:58:51 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/15 22:17:51 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	startchild1(char **argv, int end[2], int fdin, char **env)
{
	char	**cmd1;
	char	*path_cmd;
	char	*argv_cmd1[3];

	cmd1 = ft_split(argv[2], ' ');
	path_cmd = parser_path(cmd1[0], env);
	argv_cmd1[0] = cmd1[0];
	argv_cmd1[1] = cmd1[1];
	argv_cmd1[2] = NULL;
	close (end[READ_END]);
	dup2(fdin, STDIN_FILENO);
	
	dup2(end[WRITE_END], STDOUT_FILENO);
	close(end[WRITE_END]);
	execve(path_cmd, argv_cmd1, NULL);
}

void startchild_n(int argc, char **argv, int end[2], char **env, int multi_end[2])
{
 // Necesito saber que parameteo estoy enviando
 // Cual argv estoy, para asi mismo saber cual ejecutar.
 // Si envio desde la FUNC q llama 3 + i;	

 	char	**cmd;
	char	*path_cmd;
	char	*argv_cmd[3];
	char	s[30];

	
	close(end[WRITE_END]);
	close(multi_end[READ_END]);
	printf("Child_n multi_end = %d\n", multi_end[WRITE_END]);

	cmd = ft_split(argv[argc], ' ');
		
	path_cmd = parser_path(cmd[0], env);
	argv_cmd[0] = cmd[0];
	argv_cmd[1] = cmd[1];
	argv_cmd[2] = NULL;
	dup2(end[READ_END], STDIN_FILENO);
	close(end[READ_END]);
	
	read(STDIN_FILENO, s, 30);
	printf("FICHE = %s\n", s); 
	
	dup2(multi_end[WRITE_END], STDOUT_FILENO);
	close(multi_end[WRITE_END]);	



	execve(path_cmd, argv_cmd, NULL);
	perror("execve Error");
	
}

void	startchild2(int argc, char **argv, int end[2], int *fdout, char **env, int multi_end[2])
{
	char	**cmd2;
	char	*argv_cmd2[3];
	char	*path_cmd;
	//char	s[30];

	close(end[WRITE_END]);
	close(end[READ_END]);
	close(multi_end[WRITE_END]);

	
	printf("Child2 multi_end = %d\n", multi_end[READ_END]);
	*fdout = open(argv[argc -1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	printf("Child2 multi_end = %d\n", multi_end[READ_END]);
	if (*fdout == -1)
		perror("Error");
	printf("***Child2 ***** = %d\n", multi_end[READ_END]);
	cmd2 = ft_split(argv[argc -2], ' ');

	printf("***Child2 ***** = %d\n", multi_end[READ_END]);
	

	path_cmd = parser_path(cmd2[0], env);
	argv_cmd2[0] = cmd2[0];
	argv_cmd2[1] = cmd2[1];
	argv_cmd2[2] = NULL;
	dup2(multi_end[READ_END], STDIN_FILENO);
	
	
	/*read(multi_end[READ_END], s, 30);
	printf("CHIld2 FICHE = %s\n", s); 
	printf("CHIld2 fdout = %d\n", *fdout);*/ 
	
	
	dup2(*fdout, STDOUT_FILENO);
	close(multi_end[READ_END]);
	execve(path_cmd, argv_cmd2, NULL);
}

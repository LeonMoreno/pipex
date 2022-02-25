/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 07:57:06 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/22 07:57:15 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	msg(char *erro)
{
	write(2, erro, ft_strlen(erro));
	return (1);
}

void	msg_err(char *erro)
{
	perror(erro);
	exit(1);
}

void	msg_cmd(char *erro)
{
	write(2, erro, ft_strlen(erro));
	exit(1);
}

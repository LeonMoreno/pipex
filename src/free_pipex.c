/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <leon.moreno@pm.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 10:02:52 by lmoreno           #+#    #+#             */
/*   Updated: 2022/02/20 10:04:31 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char *ptr1, char *ptr2)
{
	free(ptr1);
	free(ptr2);
}

void	ft_free_2(char **doble, char *ptr2)
{
	free(doble);
	free(ptr2);
}

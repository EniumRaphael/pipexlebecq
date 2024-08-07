/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 09:19:17 by xlebecq           #+#    #+#             */
/*   Updated: 2024/08/07 14:01:30 by xlebecq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_perror_msg(char *msg, int *fd)
{
	if (fd != NULL)
	{
		close (fd[0]);
		close (fd[1]);
	}
	perror(msg);
	exit(EXIT_FAILURE);
}

void	*free_secure(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	free_2d_array(char **array)
{
	int	i;

	if (array)
	{
		i = 0;
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}


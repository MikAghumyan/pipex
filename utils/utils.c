/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:11:30 by maghumya          #+#    #+#             */
/*   Updated: 2025/04/20 13:35:57 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	puterr(char *filename, int _errornum)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(strerror(_errornum), 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(filename, 2);
}

int	get_cmd_count(int argc, char **argv)
{
	if (strncmp((argv[1]), "here_doc", 9) == 0)
		return (argc - 4);
	return ((argc - 3));
}
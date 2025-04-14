/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:36:14 by maghumya          #+#    #+#             */
/*   Updated: 2025/04/15 01:08:15 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	heredoc_handler(char *limiter)
{
	int pipefd[2];
	char *line;
	char *limiter_nl;

	limiter_nl = ft_strjoin(limiter, "\n");
	if (pipe(pipefd) == -1)
		handle_error("Pipe failed");
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, limiter_nl, ft_strlen(limiter_nl) + 1) == 0)
			break ;
		else
		{
			write(pipefd[1], line, ft_strlen(line));
			free(line);
			get_next_line(0);
		}
	}
	free(limiter_nl);
	close(pipefd[1]);
	return (pipefd[0]);
}
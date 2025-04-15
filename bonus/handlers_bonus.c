/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:36:14 by maghumya          #+#    #+#             */
/*   Updated: 2025/04/16 00:26:42 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	**alloc_pipes(int cmd_count)
{
	int	**pipefds;
	int	i;
	int	j;

	pipefds = (int **)malloc((cmd_count - 1) * sizeof(int *));
	if (!pipefds)
		handle_error("Memory Allocation Error");
	i = 0;
	while (i < cmd_count - 1)
	{
		pipefds[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipefds[i])
		{
			j = 0;
			while (j < i)
				free(pipefds[j]);
			free(pipefds);
			handle_error("Memory Allocation Error");
		}
		i++;
	}
	return (pipefds);
}

int	heredoc_handler(char *limiter)
{
	int pipefd[2];
	char *line;
	char *limiter_nl;

	limiter_nl = ft_strjoin(limiter, "\n");
	if (pipe(pipefd) == -1)
		handle_error("Pipe failed");
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter_nl, ft_strlen(limiter_nl) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	free(limiter_nl);
	close(pipefd[1]);
	return (pipefd[0]);
}
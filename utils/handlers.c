/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:26:36 by maghumya          #+#    #+#             */
/*   Updated: 2025/04/21 18:15:05 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	handle_error(char *message, int **pipes)
{
	perror(message);
	if (pipes)
		free_pipes(pipes);
	exit(EXIT_FAILURE);
}

int	input_handler(char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		puterr(argv[1], errno);
	return (fd);
}

int	output_handler(char **argv, int argc)
{
	int	fd;
	int	o_flag;

	o_flag = O_WRONLY | O_CREAT;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		o_flag |= O_APPEND;
	else
		o_flag |= O_TRUNC;
	fd = open(argv[argc - 1], o_flag, 0644);
	if (fd == -1)
		puterr(argv[argc - 1], errno);
	return (fd);
}

char	*command_handler(char *cmd, char **envp)
{
	char	**paths;
	char	*command;
	char	*path_;
	int		i;

	paths = parse_path(envp);
	if (!paths)
		return (perror("Error parsing PATH"), NULL);
	i = 0;
	while (paths[i])
	{
		path_ = ft_strjoin(paths[i], "/");
		command = ft_strjoin(path_, cmd);
		free(path_);
		if (!access(command, F_OK) && !access(command, X_OK))
			return (free_split(paths), command);
		else if (!access(command, F_OK))
			return (free_split(paths), errno = EACCES, NULL);
		free(command);
		i++;
	}
	free_split(paths);
	return (NULL);
}
int	heredoc_handler(char *limiter)
{
	int		pipefd[2];
	char	*line;
	char	*limiter_nl;

	limiter_nl = ft_strjoin(limiter, "\n");
	if (pipe(pipefd) == -1)
		handle_error("Pipe failed", NULL);
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

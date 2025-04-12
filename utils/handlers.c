/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:26:36 by maghumya          #+#    #+#             */
/*   Updated: 2025/04/11 21:58:41 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	handle_error(char *message)
{
	perror(message);
	// printf("%s", message);
	exit(EXIT_FAILURE);
}

int	input_handler(char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		handle_error("Error opening input file");
	return (fd);
}

int	output_handler(char **argv)
{
	int	fd;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		handle_error("Error opening output file");
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
		if (!access(command, X_OK))
		{
			free_split(paths);
			return (command);
		}
		free(command);
		i++;
	}
	free_split(paths);
	return (perror("Command not found"), NULL);
}

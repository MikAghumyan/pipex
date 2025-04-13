/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:51:43 by maghumya          #+#    #+#             */
/*   Updated: 2025/04/13 22:47:34 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	make_pipe(char **argv, char **envp, int input_fd, int output_fd)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		handle_error("Pipe failed");
	pid = fork();
	if (pid == -1)
		handle_error("Fork failed");
	if (pid == 0)
	{
		close(pipefd[0]);
		if (input_fd > 0)
			exec_command(input_fd, pipefd[1], argv[2], envp);
	}
	else
	{
		close(pipefd[1]);
		exec_command(pipefd[0], output_fd, argv[3], envp);
	}
}

void	exec_command(int fd_in, int fd_out, char *cmd, char **envp)
{
	t_cmd	cmd_;

	if (dup2(fd_in, 0) == -1)
		perror("Can't read");
	if (dup2(fd_out, 1) == -1)
		perror("Can't write");
	cmd_.cmd = NULL;
	cmd_.args = ft_split(cmd, ' ');
	if (!cmd_.args)
		return ;
	if (cmd_.args[0])
		cmd_.cmd = command_handler(cmd_.args[0], envp);
	if (!cmd_.cmd)
	{
		free_split(cmd_.args);
		return ;
	}
	if (execve(cmd_.cmd, cmd_.args, envp) == -1)
		perror("Execve failed");
	free_split(cmd_.args);
	free(cmd_.cmd);
	close(fd_in);
	close(fd_out);
	return ;
}

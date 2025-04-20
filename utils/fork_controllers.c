/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_controllers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:51:43 by maghumya          #+#    #+#             */
/*   Updated: 2025/04/20 11:12:20 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	fork_heredoc(int pipefd[2], int heredoc_fd, char *argv[], char *envp[])
{
	pid_t	pid;
	int		exec_failure;

	pid = fork();
	if (pid == -1)
		handle_error("Fork failed");
	if (pid == 0)
	{
		close(pipefd[0]);
		exec_failure = exec_command(heredoc_fd, pipefd[1], argv[3], envp);
		exit(exec_failure);
	}
	else
		close(heredoc_fd);
}

void	fork_cmd_mid(int pipefd1[2], int pipefd2[2], char *cmd, char *envp[])
{
	pid_t	pid;
	int		exec_failure;

	pid = fork();
	if (pid == -1)
		handle_error("Fork failed");
	if (pid == 0)
	{
		close(pipefd1[1]);
		close(pipefd2[0]);
		exec_failure = exec_command(pipefd1[0], pipefd2[1], cmd, envp);
		exit(exec_failure);
	}
}

void	fork_cmd1(int pipefd[2], char **argv, char **envp)
{
	pid_t	pid;
	int		input_fd;
	int		exit_failure;

	pid = fork();
	if (pid == -1)
		handle_error("Fork failed");
	if (pid == 0)
	{
		close(pipefd[0]);
		input_fd = input_handler(argv);
		if (input_fd < 0)
		{
			exit(errno);
		}
		exit_failure = exec_command(input_fd, pipefd[1], argv[2], envp);
		exit(exit_failure);
	}
}

pid_t	fork_cmd2(int pipefd[2], int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		output_fd;
	int		exec_failure;

	pid = fork();
	if (pid == -1)
		handle_error("Fork failed");
	if (pid == 0)
	{
		close(pipefd[1]);
		output_fd = output_handler(argv, argc);
		if (output_fd < 0)
			exit(errno);
		exec_failure = exec_command(pipefd[0], output_fd, argv[argc - 2], envp);
		exit(exec_failure);
	}
	return (pid);
}

int	exec_command(int fd_in, int fd_out, char *cmd, char **envp)
{
	t_cmd	cmd_;

	if (dup2(fd_in, 0) == -1)
		perror("Can't read");
	if (dup2(fd_out, 1) == -1)
		perror("Can't write");
	cmd_.cmd = NULL;
	cmd_.args = ft_split(cmd, ' ');
	if (!cmd_.args)
		return (EXIT_CMD_NOT_FOUND);
	if (cmd_.args[0])
		cmd_.cmd = command_handler(cmd_.args[0], envp);
	if (!cmd_.cmd)
	{
		perror(cmd_.args[0]);
		free_split(cmd_.args);
		return (errno);
	}
	if (execve(cmd_.cmd, cmd_.args, envp) == -1)
		perror("Execve failed");
	free_split(cmd_.args);
	free(cmd_.cmd);
	close(fd_in);
	close(fd_out);
	return (errno);
}

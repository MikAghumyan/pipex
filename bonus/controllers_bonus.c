/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:51:43 by maghumya          #+#    #+#             */
/*   Updated: 2025/04/16 21:17:07 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	fork_heredoc(int pipefd[2], int heredoc_fd, char *argv[], char *envp[])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		handle_error("Pipe failed");
	if (pid == 0)
	{
		close(pipefd[0]);
		exec_command(heredoc_fd, pipefd[1], argv[3], envp);
	}
	else
		close(heredoc_fd);
}

void	fork_cmd_mid(int pipefd1[2], int pipefd2[2], char *cmd, char *envp[])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		handle_error("Pipe failed");
	if (pid == 0)
	{
		close(pipefd1[1]);
		close(pipefd2[0]);
		exec_command(pipefd1[0], pipefd2[1], cmd, envp);
	}
}

void	make_pipe_mid(int n, int **pipefds, char **argv, char **envp)
{
	int	i;

	i = 1;
	while (i < n)
	{
		if (pipe(pipefds[i]) == -1)
			handle_error("Pipe failed");
		fork_cmd_mid(pipefds[i - 1], pipefds[i], argv[i + 2], envp);
		close(pipefds[i - 1][1]);
		close(pipefds[i - 1][0]);
		free(pipefds[i - 1]);
		i++;
	}
}

void	make_pipe_bonus(int argc, char **argv, char **envp, int cmd_count)
{
	pid_t pid;
	int **pipefds;
	int status;

	pipefds = alloc_pipes(cmd_count);
	if (!pipefds)
		handle_error("Memory Allocation Error");
	if (pipe(pipefds[0]) == -1)
		handle_error("Pipe failed");
	fork_cmd1(pipefds[0], argv, envp);
	make_pipe_mid(cmd_count - 1, pipefds, argv, envp);
	pid = fork_cmd2(pipefds[cmd_count - 2], argc, argv, envp);
	close(pipefds[cmd_count - 2][1]);
	close(pipefds[cmd_count - 2][0]);
	free(pipefds[cmd_count - 2]);
	free(pipefds);
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		;
	exit(WEXITSTATUS(status));
}
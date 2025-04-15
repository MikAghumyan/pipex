/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:51:43 by maghumya          #+#    #+#             */
/*   Updated: 2025/04/16 01:33:40 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

// void	make_pipe(char **argv, char **envp)
// {
// 	pid_t	pid;
// 	int		pipefd[2];
// 	int		status1;

// 	if (pipe(pipefd) == -1)
// 		handle_error("Pipe failed");
// 	fork_cmd1(pipefd, argv, envp);
// 	fork_cmd2(pipefd, argv, envp, &pid);
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// 	waitpid(pid, &status1, 0);
// 	wait(NULL);
// 	exit(WEXITSTATUS(status1));
// }

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
		printf("Child process mid\n");
		close(pipefd1[1]);
		close(pipefd2[0]);
		exec_command(pipefd1[0], pipefd2[1], cmd, envp);
	}
}

void	make_pipe_bonus(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		**pipefds;
	int		i;
	int		cmd_count;
	int		status;
	char	c;

	cmd_count = argc - 3;
	pipefds = alloc_pipes(cmd_count);
	if (!pipefds)
		handle_error("Memory Allocation Error");
	if (pipe(pipefds[0]) == -1)
		handle_error("Pipe failed");
	fork_cmd1(pipefds[0], argv, envp);
	i = 1;
	while (i < cmd_count - 1)
	{
		if (pipe(pipefds[i]) == -1)
			handle_error("Pipe failed");
		fork_cmd_mid(pipefds[i - 1], pipefds[i], argv[i + 2], envp);
		close(pipefds[i - 1][1]);
		close(pipefds[i - 1][0]);
		free(pipefds[i - 1]);
		i++;
	}
	pid = fork_cmd2(pipefds[i - 1], argc, argv, envp);
	close(pipefds[i - 1][1]);
	close(pipefds[i - 1][0]);
	free(pipefds[i - 1]);
	free(pipefds);
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		;
	exit(WEXITSTATUS(status));
}

// void	make_pipe_bonus(char **argv, char **envp, int heredoc_fd, int cmd_count)
// {
// 	pid_t	pid;
// 	int		**pipefds;
// 	int		status;
// 	int		i;
// 	int		cmd_i;

// 	pipefds = alloc_pipes(cmd_count);
// 	if (!pipefds)
// 		handle_error("Memory Allocation Error");
// 	if (pipe(pipefds[0]) == -1)
// 		handle_error("Pipe failed");
// 	if (heredoc_fd < 0)
// 	{
// 		fork_cmd1(pipefds[0], argv, envp);
// 		cmd_i = 2;
// 	}
// 	else
// 	{
// 		fork_heredoc(pipefds[0], heredoc_fd, argv, envp);
// 		cmd_i = 3;
// 	}
// 	i = 1;
// 	while (i < cmd_count - 1)
// 	{
// 		if (pipe(pipefds[i]) == -1)
// 			handle_error("Pipe failed");
// 		fork_cmd_mid(pipefds[i - 1], pipefds[i], argv[cmd_i + i], envp);
// 		i++;
// 	}
// 	fork_cmd2(pipefds[i], &argv[cmd_i + i - 3], envp, &pid);
// 	i = 0;
// 	while (i < cmd_count - 1)
// 	{
// 		close(pipefds[i][0]);
// 		close(pipefds[i][1]);
// 		free(pipefds[i]);
// 		i++;
// 	}
// 	free(pipefds);
// 	waitpid(pid, &status, 0);
// 	while (wait(NULL) != -1)
// 		;
// 	exit(WEXITSTATUS(status));
// }

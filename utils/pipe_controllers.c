/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_controllers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:51:43 by maghumya          #+#    #+#             */
/*   Updated: 2025/04/21 21:08:54 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	make_pipe_mid(int **pipefds, t_params *params)
{
	int	i;
	int	first_cmd_i;

	if (ft_strncmp(params->argv[1], "here_doc", 9) == 0)
		first_cmd_i = 3;
	else
		first_cmd_i = 2;
	i = 1;
	while (pipefds[i])
	{
		if (pipe(pipefds[i]) == -1)
			handle_error("Pipe failed", params->pipefds);
		fork_cmd_mid(pipefds[i - 1], pipefds[i], params->argv[i + first_cmd_i],
			params);
		close(pipefds[i - 1][1]);
		close(pipefds[i - 1][0]);
		i++;
	}
}

void	make_pipe(t_params *params)
{
	pid_t	pid;
	int		**pipefds;
	int		status;

	pipefds = alloc_pipes(params->cmd_count);
	params->pipefds = pipefds;
	if (!pipefds)
		handle_error("Memory Allocation Error", NULL);
	if (pipe(pipefds[0]) == -1)
		handle_error("Pipe failed", params->pipefds);
	if (ft_strncmp(params->argv[1], "here_doc", 9) == 0)
		fork_heredoc(pipefds[0], heredoc_handler(params->argv[2]), params);
	else
		fork_cmd1(pipefds[0], params);
	make_pipe_mid(pipefds, params);
	pid = fork_cmd2(pipefds[params->pipe_count - 1], params);
	close(pipefds[params->pipe_count - 1][1]);
	close(pipefds[params->pipe_count - 1][0]);
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		;
	free_pipes(pipefds);
	exit(WEXITSTATUS(status));
}

// void	make_pipe(int argc, char **argv, char **envp)
// {
// 	pid_t	pid;
// 	int		pipefd[2];
// 	int		status1;

// 	if (pipe(pipefd) == -1)
// 		handle_error("Pipe failed");
// 	fork_cmd1(pipefd, argv, envp);
// 	pid = fork_cmd2(pipefd, argc, argv, envp);
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// 	waitpid(pid, &status1, 0);
// 	wait(NULL);
// 	exit(WEXITSTATUS(status1));
// }

void	free_pipes(int **arr)
{
	int	j;

	j = 0;
	while (arr[j])
	{
		free(arr[j]);
		arr[j] = NULL;
		j++;
	}
	free(arr);
	arr = NULL;
}

int	**alloc_pipes(int cmd_count)
{
	int	**pipefds;
	int	i;

	pipefds = (int **)malloc((cmd_count) * sizeof(int *));
	if (!pipefds)
		handle_error("Memory Allocation Error", NULL);
	i = 0;
	while (i < cmd_count - 1)
	{
		pipefds[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipefds[i])
			handle_error("Memory Allocation Error", pipefds);
		i++;
	}
	pipefds[i] = NULL;
	return (pipefds);
}

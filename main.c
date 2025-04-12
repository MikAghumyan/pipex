/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:13:57 by maghumya          #+#    #+#             */
/*   Updated: 2025/04/12 21:22:18 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		input_fd;
	int		output_fd;
	pid_t	pid;
	int		status;
	int		i;
	int		pipefd[2];

	if (argc != 5)
		handle_error("Usage: ./pipex infile cmd1 cmd2 outfile");
	input_fd = input_handler(argv);
	output_fd = output_handler(argv);
	if (pipe(pipefd) == -1)
		handle_error("Pipe failed");
	pid = fork();
	if (pid == -1)
		handle_error("Fork failed");
	if (pid == 0)
	{
		close(pipefd[0]);
		exec_command(input_fd, pipefd[1], argv[2], envp);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:13:57 by maghumya          #+#    #+#             */
/*   Updated: 2025/04/11 22:00:29 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	// t_cmd cmd;
	char **paths;
	// int fd_in;
	// int fd_out;
	// int pipefd[2];
	paths = parse_path(envp);
	if (!paths)
		handle_error("Error parsing PATH");
	printf("%s", argv[0]);
	if (argc != 5)
		handle_error("Usage: ./pipex infile cmd1 cmd2 outfile");
	input_handler(argv);
	output_handler(argv);
	printf("%s\n", command_handler(argv[2], envp));
	free_split(paths);
	return (0);
}

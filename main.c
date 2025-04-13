/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:13:57 by maghumya          #+#    #+#             */
/*   Updated: 2025/04/13 20:39:20 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	input_fd;
	int	output_fd;

	if (argc != 5)
		return (ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile\n"), 0);
	input_fd = input_handler(argv);
	output_fd = output_handler(argv);
	make_pipe(argv, envp, input_fd, output_fd);
	while (wait(NULL) != -1)
		;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:48:56 by maghumya          #+#    #+#             */
/*   Updated: 2025/04/21 21:09:02 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char		c;
	t_params	prog_params;

	if (argc < 5)
		return (ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile\n"), 0);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		if (argc < 6)
		{
			ft_printf("Usage: ./pipex here_doc LIMITER cmd1 cmd2 outfile\n");
			return (0);
		}
	}
	prog_params.argc = argc;
	prog_params.argv = argv;
	prog_params.envp = envp;
	prog_params.cmd_count = get_cmd_count(argc, argv);
	prog_params.pipe_count = prog_params.cmd_count - 1;
	make_pipe(&prog_params);
	return (0);
}

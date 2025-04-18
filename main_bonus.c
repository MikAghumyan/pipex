/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:48:56 by maghumya          #+#    #+#             */
/*   Updated: 2025/04/18 01:42:16 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	char	c;
	int		cmd_count;

	cmd_count = argc - 3;
	if (argc < 5)
		return (ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile\n"), 0);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		if (argc < 6)
		{
			ft_printf("Usage: ./pipex here_doc LIMITER cmd1 cmd2 outfile\n");
			return (0);
		}
		cmd_count--;
	}
	make_pipe_bonus(argc, argv, envp, cmd_count);
	return (0);
}

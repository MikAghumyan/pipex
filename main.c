/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:13:57 by maghumya          #+#    #+#             */
/*   Updated: 2025/04/14 16:27:21 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile\n"), 0);
	make_pipe(argv, envp);
	return (0);
}

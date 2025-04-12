/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:12:07 by maghumya          #+#    #+#             */
/*   Updated: 2025/04/11 21:58:54 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	char	*path;
}			t_cmd;

void		handle_error(char *message);
int			input_handler(char **argv);
int			output_handler(char **argv);

char		*command_handler(char *cmd, char **envp);

char		**parse_path(char **envp);
void		free_split(char **split);

#endif
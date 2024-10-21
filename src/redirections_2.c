/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:29:14 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/01 15:31:58 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_open_flags(int type)
{
	int	open_flags;

	open_flags = (type == STDOUT_REDIR) * (O_WRONLY | O_CREAT | O_TRUNC);
	open_flags += (type == STDOUT_APPEND) * (O_WRONLY | O_CREAT | O_APPEND);
	open_flags += (type == STDIN_REDIR) * (O_RDONLY);
	open_flags += (type == HERE_DOC) * (O_RDONLY);
	return (open_flags);
}

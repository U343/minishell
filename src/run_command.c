/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 11:03:09 by wanton            #+#    #+#             */
/*   Updated: 2020/01/24 11:22:40 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     run_command(char **s_arg)
{
    if ((ft_strcmp(s_arg[0], "exit()")) == 0)
        return (0);
    else
        return (1);
}
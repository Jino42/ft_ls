/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 04:55:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/23 05:00:03 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_print(t_env *e, t_list *l, int dir)
{
	t_elem *elem;
(void)dir;(void)e;

	ft_printf("\033[31mIfdir :\n\033[0m");
	while (l)
	{
		elem = l->content;
		ft_printf("%s %3li %s %s %6li %.12s \033[32m%s\033[0m\n",
				elem->mode,
				elem->nlink,
				elem->p_name,
				elem->g_name,
				elem->size,
				ctime(&(elem->atime)) + 4,
				elem->path);
		l = l->next;
	}
}

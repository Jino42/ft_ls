/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 04:55:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/24 17:55:29 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_print(t_env *e, t_list *l, int dir)
{
	t_elem *elem;
	char	*time;
	t_list	*save;
	t_list	*ret;
(void)dir;(void)e;(void)ret;

	ft_printf("\033[33m%s :\n\033[0m", ((t_elem*)e->dir->content)->path);
	while (l)
	{
		elem = l->content;
		time = ctime(&(elem->atime));
		ft_printf("%s %3li %s %s %6li %.12s \033[32m%s\033[0m\n",
				elem->mode,
				elem->nlink,
				elem->p_name,
				elem->g_name,
				elem->size,
				time + 4,
				&elem->path[elem->ind_curf]);
		save = l;
		l = l->next;
		ret = ft_lst_remove_index(&save, 0);
//		if (ret)
//			ls_free_elem(&ret);
	}
}

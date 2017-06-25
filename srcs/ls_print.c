/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 04:55:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/25 10:04:45 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_file(t_env *e, t_elem *elem)
{
	(void)e;
	ft_printf("\033[32m%s\033[0m\n",
		&elem->path[elem->ind_curf]);
}

static void		print_option_l(t_env *e, t_elem *elem)
{
	char	*time;

	(void)e;
	time = ctime(&(elem->atime));
	ft_printf("%s %3li %s %s %6li %.12s \033[32m%s\033[0m\n",
		elem->mode,
		elem->nlink,
		elem->p_name,
		elem->g_name,
		elem->size,
		time + 4,
		&elem->path[elem->ind_curf]);
}

void		ls_print(t_env *e, t_list *l, int dir)
{
	t_elem *elem;
	t_list	*save;
	t_list	*ret;
(void)dir;(void)e;(void)ret;

	ft_printf("\033[33m%s :\n\033[0m", ((t_elem*)e->dir->content)->path);
	while (l)
	{
		elem = l->content;
		if (e->flag & FLAG_L)
			print_option_l(e, elem);
		else
			print_file(e, elem);
		save = l;
		l = l->next;
		ret = ft_lst_remove_index(&save, 0);
		ret->next = NULL;
/*		if ((e->flag & FLAG_R) && ((t_elem*)ret->content)->mode[0] == 'd')
		{
			ft_printf("Enter\n");
			ft_lstadd(&e->dir, ret);
		}
		else */if (ret)
			ls_free_elem(&ret);
	}
	e->file = NULL;
}

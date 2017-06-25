/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 04:55:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/25 13:03:07 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_file(t_env *e, t_elem *elem)
{
	(void)e;
	ft_printf("%s\n",
		&elem->path[elem->ind_curf]);
}

static void		print_option_l(t_env *e, t_elem *elem)
{
	char	*time;

	(void)e;
	time = ctime(&(elem->atime));
	ft_printf("%s %3li %s  %s %6li %.12s %s",
		elem->mode,
		elem->nlink,
		elem->p_name,
		elem->g_name,
		elem->size,
		time + 4,
		&elem->path[elem->ind_curf]);
	if (elem->mode[NUM_TYPE] == 'l')
		ft_printf("%s", elem->r_lnk);
	ft_putchar('\n');
}

void		ls_print(t_env *e, t_list *l, int dir)
{
	t_elem *elem;
	t_list	*save;
	t_list	*ret;
(void)dir;(void)e;(void)ret;

//	ft_printf("\033[33m%s:\n\033[0m", ((t_elem*)e->dir->content)->path);
	if (e->cur_dir)
	ft_printf("%s:\n", ((t_elem*)e->dir->content)->path);
	else if (e->nb_arg > 1)
		ft_printf("%s:\n", ((t_elem*)e->dir->content)->path);
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

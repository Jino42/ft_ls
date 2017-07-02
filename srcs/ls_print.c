/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 04:55:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/30 11:33:00 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		ls_condition_print(t_env *e, t_list *l,
												t_size_m size_m, int dir)
{
	if (!e->cur_dir)
		print_not_here(e);
	if (dir)
	{
		print_file_init(e, l, &size_m);
		if (l && e->dir)
			ft_putchar('\n');
		return (0);
	}
	if (e->cur_dir)
		ft_printf("%s:\n", ((t_elem*)e->dir->content)->path);
	else if (e->nb_arg > 1)
		ft_printf("%s:\n", ((t_elem*)e->dir->content)->path);
	if (e->flag & FLAG_L && e->file)
		ft_printf("total %li\n", size_m.total_blocks);
	if (((t_elem*)e->dir->content)->right)
		ft_dprintf(2, "ls: %s: Permission denied\n",
				&((t_elem*)e->dir->content)->path
				[((t_elem*)e->dir->content)->ind_curf]);
	return (1);
}

void			ls_print(t_env *e, t_list *l, int dir)
{
	t_elem		*elem;
	t_list		*save;
	t_list		*ret;
	t_size_m	size_m;

	ft_bzero(&size_m, sizeof(t_size_m));
	ls_max_print(e->file, &size_m);
	if (!(ls_condition_print(e, l, size_m, dir)))
		return ;
	while (l)
	{
		elem = l->content;
		if (e->flag & FLAG_L)
			ls_print_l(e, elem, &size_m);
		else
			print_file(e, elem);
		save = l;
		l = l->next;
		ret = ft_lst_remove_index(&save, 0);
		ret->next = NULL;
		if (ret)
			ls_free_elem(&ret);
	}
	e->file = NULL;
}

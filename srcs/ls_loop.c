/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 04:51:23 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/29 11:21:33 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			is_not_cur(t_list *l)
{
	t_elem *elem;

	elem = l->content;
	if (elem->path[elem->ind_curf] == '.' &&
					elem->path[elem->ind_curf + 1] == '\0')
		return (0);
	if (elem->path[elem->ind_curf] == '.' &&
					elem->path[elem->ind_curf + 1] == '.'
			&& elem->path[elem->ind_curf + 2] == '\0')
		return (0);
	return (1);
}

static void	ls_add_dir(t_env *e)
{
	t_list *l;
	t_list *save;

	l = e->temp_dir;
	while (l)
	{
		save = l;
		l = l->next;
		if (is_not_cur(save))
			ft_lstadd(&e->dir, save);
	}
	e->temp_dir = NULL;
}

int			ls_loop(t_env *e)
{
	t_list	*ret;

	while (e->dir)
	{
		if (!(ls_get_dir(e, (t_elem*)e->dir->content)))
			;
		if (e->cur_dir)
			ft_putchar('\n');
		ls_recup_file(e, 0);
		ls_print(e, e->file, 0);
		ret = ft_lst_remove_index(&e->dir, 0);
		if (ret)
			ls_free_elem(&ret);
		ret = NULL;
		if (e->flag & FLAG_R)
			ls_add_dir(e);
		e->cur_dir++;
	}
	return (1);
}

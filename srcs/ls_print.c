/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 04:55:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/26 09:37:59 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_file(t_env *e, t_elem *elem)
{
	(void)e;
	ft_printf("%s\n",
		&elem->path[elem->ind_curf]);
}

static void		print_option_l(t_env *e, t_elem *elem, t_size_m *size_m)
{
	char	*ret_time;

	(void)e;
	ret_time = ctime((const time_t*)(&elem->atime));
	ft_printf("%s %*li %-*s  %-*s %*li %.12s %s",
		elem->mode,
		size_m->nlink_max + 1, elem->nlink,
		size_m->p_max, elem->p_name,
		size_m->g_max, elem->g_name,
		size_m->size_max + 1, elem->size,
		ret_time + 4,
		&elem->path[elem->ind_curf]);
	if (elem->mode[NUM_TYPE] == 'l')
		ft_printf("%s", elem->r_lnk);
	ft_putchar('\n');
}

static size_t	count_nb(size_t nb)
{
	size_t i;

	i = 0;
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

static void		ls_max_print(t_list *lst, t_size_m *size_m)
{
	t_elem	*elem;
	size_t	temp;

	while (lst)
	{
		elem = lst->content;
		if (elem->size > size_m->size_max)
			size_m->size_max = elem->size;
		if (elem->nlink > size_m->nlink_max)
			size_m->nlink_max = elem->nlink;
		temp = ft_strlen(elem->p_name);
		if (temp > size_m->p_max)
			size_m->p_max = temp;
		temp = ft_strlen(elem->g_name);
		if (temp > size_m->g_max)
			size_m->g_max = temp;
		size_m->total_blocks += elem->blocks;
		lst = lst->next;
	}
	size_m->size_max = count_nb(size_m->size_max);
	size_m->nlink_max = count_nb(size_m->nlink_max);
}

void			ls_print(t_env *e, t_list *l, int dir)
{
	t_elem		*elem;
	t_list		*save;
	t_list		*ret;
	t_size_m	size_m;

	(void)dir;
	ft_bzero(&size_m, sizeof(t_size_m));
	ls_max_print(e->file, &size_m);
	//ft_printf("\033[33mSize max : P[%li] G[%li] S[%i] L[%li]\n\033[0m",
	//size_m.p_max, size_m.g_max, size_m.size_max, size_m.nlink_max);
	if (e->cur_dir)
		ft_printf("%s:\n", ((t_elem*)e->dir->content)->path);
	else if (e->nb_arg > 1)
		ft_printf("%s:\n", ((t_elem*)e->dir->content)->path);
	if (e->flag & FLAG_L)
		ft_printf("total %li\n", size_m.total_blocks);
	while (l)
	{
		elem = l->content;
		if (e->flag & FLAG_L)
			print_option_l(e, elem, &size_m);
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

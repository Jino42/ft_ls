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

static void		print_not_here(t_env *e)
{
	t_list *lst;

	lst = e->not_here;
	while (lst)
	{
		ft_dprintf(2, "ls: %s: No such file or directory\n", (char*)lst->content);
		lst = lst->next;
	}
	ls_free_temp(&e->not_here);
}

static void		print_file(t_env *e, t_elem *elem)
{
	(void)e;
	ft_printf("%s\n",
		&elem->path[elem->ind_curf]);
}

static void		print_option_l(t_env *e, t_elem *elem, t_size_m *size_m)
{
	char	*ret_time;
	time_t	cur;

	(void)e;
	ret_time = ctime((const time_t*)(&elem->mtime));
	cur = time(NULL);
	//////////////MAX_YEAR
	if (cur - elem->mtime > PRINT_DATE)
		ft_strcpy(&ret_time[11], &ret_time[19]);
	else if (cur - elem->mtime < 0)
		ft_strcpy(&ret_time[10], &ret_time[22]);
	ft_printf("%s %*li %-*s  %-*s ",
		elem->mode,
		size_m->nlink_max + 1, elem->nlink,
		size_m->p_max, elem->p_name,
		size_m->g_max, elem->g_name);
	if (elem->mode[NUM_TYPE] == 'c' || elem->mode[NUM_TYPE] == 'b')
	{
		ft_printf("%*li, %*li %.*s %s",
			size_m->major_max, ((elem->st_dev >> 24)&0xff),
			size_m->minor_max, (int)((elem->st_dev) & 0xff),
			12 + size_m->years_max, ret_time + 4,
			&elem->path[elem->ind_curf]);
	}
	else
	{
		ft_printf("%*li %.*s %s",
			size_m->size_max + 1, elem->size,
			12 + size_m->years_max, ret_time + 4,
			&elem->path[elem->ind_curf]);
	}
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
		if (elem->mtime > MAX_YEARS)
			size_m->years_max = 1;
		if (((elem->st_dev >> 24)&0xff) > size_m->major_max)
			size_m->major_max = ((elem->st_dev >> 24) & 0xff);
		if ((elem->st_dev & 0xff) > size_m->minor_max)
			size_m->minor_max = (elem->st_dev & 0xff);
		size_m->total_blocks += elem->blocks;
		lst = lst->next;
	}
	size_m->size_max = count_nb(size_m->size_max);
	if (size_m->size_max == 0)
		size_m->size_max++;
	size_m->nlink_max = count_nb(size_m->nlink_max);
	size_m->minor_max = count_nb(size_m->minor_max);
	size_m->major_max = count_nb(size_m->major_max);
	if (size_m->nlink_max == 0)
		size_m->nlink_max++;
	if (size_m->major_max)
		size_m->major_max += 2;
	size_m->size_max += size_m->major_max + size_m->minor_max;
}

static void		print_file_init(t_env *e, t_list *l, t_size_m *size_m)
{
	t_elem *elem;
	t_list		*save;
	t_list		*ret;

	while (l)
	{
		elem = l->content;
		elem->ind_curf = 0;
		if (e->flag & FLAG_L)
			print_option_l(e, elem, size_m);
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
	if (!e->cur_dir)
		print_not_here(e);
	if (dir)
	{
		print_file_init(e, l, &size_m);
		if (l && e->dir)
			ft_putchar('\n');
		return ;
	}
	if (e->cur_dir)
		ft_printf("%s:\n", ((t_elem*)e->dir->content)->path);
	else if (e->nb_arg > 1)
		ft_printf("%s:\n", ((t_elem*)e->dir->content)->path);
	if (e->flag & FLAG_L && e->file)
		ft_printf("total %li\n", size_m.total_blocks);
	if (((t_elem*)e->dir->content)->right)
		ft_dprintf(2, "ls: %s: Permission denied\n", &((t_elem*)e->dir->content)->path[((t_elem*)e->dir->content)->ind_curf]);
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
//		if (ret)
//			ls_free_elem(&ret);
	}
	e->file = NULL;
}

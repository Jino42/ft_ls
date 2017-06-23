/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 04:51:23 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/23 05:44:39 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list	*ft_find_dir(t_list *l, int index)
{
	t_elem *elem;

	if (!index && l)
		return (l);
	while (l && index)
	{
		elem = l->content;

		if (elem->mode[NUM_TYPE] == 'd')
			return (l);
		index--;
		l = l->next;
	}
	return (NULL);
}

static int		ls_get_dir(t_env *e, t_elem *elem)
{
	void			*ptr;
	struct dirent	*dir;

	(void)e;
	ptr = opendir(elem->path);
	if (!ptr)
		return (0);
	ft_printf("\033[31mNEW_DIR : \n\033[0m");
	while ((dir = readdir(ptr)))
	{
		ft_printf("Path : %s Type ? %hhc\n", dir->d_name, dir->d_type);
	//	ft_lstadd(&e->temp, ft_lstnew(argv[*i], ft_strlen() + 1));
	}
	closedir(ptr);
	return (1);
}

int			ls_loop(t_env *e)
{
	int		index;
	t_list	*ret;

	ls_print(e, e->file, 0);
	ls_free_elem(&e->file);
	index = 0;
	while (e->dir)
	{
		while ((ret = ft_find_dir(e->dir, index)))
		{
			if (!(ls_get_dir(e, (t_elem*)ret->content)))
					return (0);
			ret = ft_lst_remove_index(&e->dir, index);
			if (ret)
				ls_free_elem(&ret);
			ret = NULL;
		}
	}
	return (1);
}

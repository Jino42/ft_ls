/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 04:51:23 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/25 10:21:12 by ntoniolo         ###   ########.fr       */
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

static int		ls_add_to_list(t_env *e, t_elem *elem, struct dirent *dir)
{
	char			*temp;

	if (!(e->flag & FLAG_A) && dir->d_name[0] == '.')
		return (0);
	temp = ft_sprintf("%s/%s", elem->path, dir->d_name);
	ft_lstinsert_alphabet(&e->temp, ft_lstnew(temp, ft_strlen(temp) + 1));
	ft_strdel(&temp);
	return (1);
}

static int		ls_get_dir(t_env *e, t_elem *elem)
{
	void			*ptr;
	struct dirent	*dir;

	(void)e;
	ptr = opendir(elem->path);
	if (!ptr)
		return (0);
	while ((dir = readdir(ptr)))
	{
		if (ft_strcmp(dir->d_name, ".") &&
			ft_strcmp(dir->d_name, ".."))
			ls_add_to_list(e, elem, dir);
	}
	closedir(ptr);
	return (1);
}

int			ls_loop(t_env *e)
{
	int		index;
	t_list	*ret;

	if (e->file)
	{
		ls_print(e, e->file, 0);
		ls_free_elem(&e->file);
	}
	index = 0;
	while (e->dir)
	{
		while ((ret = ft_find_dir(e->dir, index)))
		{
			if (!(ls_get_dir(e, (t_elem*)ret->content)))
					;
			ft_printf("WWD\n");
			ls_recup_file(e);
			ls_print(e, e->file, 0);
			ret = ft_lst_remove_index(&e->dir, index);
			if (ret)
				ls_free_elem(&ret);
			ret = NULL;
		}
	}
	return (1);
}

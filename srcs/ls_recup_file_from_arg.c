/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_recup_file_from_arg.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 23:47:55 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/27 07:41:48 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ls_recup_file_from_arg(t_env *e)
{
	t_list	*lst;
	t_list	*save;
	t_list	*ret;
	struct stat buff;

	lst = e->temp;
	while (lst)
	{
		ft_bzero(&buff, sizeof(struct stat));
		if (stat(((char*)lst->content), &buff) == -1)
		{
			save = lst;
			lst = lst->next;
			ft_lstinsert(&e->not_here, ft_lst_remove(&e->temp, save));
		}
		else
		{
			save = lst;
			lst = lst->next;
			ret = ls_stat_to_list(e, buff, (char*)save->content);
			save = ft_lst_remove(&e->temp, save);
			ft_memdel((void**)&save);
			if (buff.st_mode & S_IFDIR)
				ft_lstinsert(&e->dir, ret);
			else
				ft_lstinsert(&e->file, ret);
		}
	}
	ls_free_temp(&e->temp);
	if (!e->file && !e->dir)
	{
		stat(("."), &buff);
		ret = ls_stat_to_list(e, buff, ft_strdup("."));
		ft_lstinsert(&e->dir, ret);
	}
	return (1);
}

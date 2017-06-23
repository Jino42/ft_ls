/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_recup_file_from_arg.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 23:47:55 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/23 04:33:04 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list	*ls_stat_to_list(t_env *e, struct stat buff, char *path)
{
	t_elem	elem;
	struct passwd *passwd;
	struct group *group;
	t_list	*ret;

	(void)e;
	ft_bzero(&elem, sizeof(t_elem));
	ft_memset(&elem.mode, '-', sizeof(char) * 10);
	elem.path = path;
	ls_type_and_file_right(&elem, buff.st_mode);
	elem.size = buff.st_size;
	elem.atime = buff.st_atime;
	elem.nlink = buff.st_nlink;
	passwd = getpwuid(buff.st_uid);
	group = getgrgid(buff.st_gid);
	elem.p_name = passwd->pw_name;
	elem.g_name = group->gr_name;
	ret = ft_lstnew(&elem, sizeof(t_elem));
	return (ret);
}

int				ls_recup_file_from_arg(t_env *e)
{
	t_list	*lst;
	t_list	*save;
	t_list	*ret;
	struct stat buff;

	lst = e->temp;
	while (lst)
	{
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

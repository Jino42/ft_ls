/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_recup_file_from_arg.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 23:47:55 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/25 10:43:13 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	find_last_slash(t_elem *elem)
{
	int i;

	i = ft_strlen(elem->path);
	while (i)
	{
		if (elem->path[i] == '/' && elem->path[i - 1] != '\\')
			return (i + 1);
		i--;
	}
	return (i);
}

static t_list	*ls_stat_to_list(t_env *e, struct stat buff, char *path)
{
	t_elem	elem;
	struct passwd *passwd;
	struct group *group;
	t_list	*ret;

	(void)e;
	passwd = NULL;
	group = NULL;
	ft_bzero(&elem, sizeof(t_elem));
	ft_memset(&elem.mode, '-', sizeof(char) * 10);
	elem.path = path;
	ls_type_and_file_right(&elem, buff.st_mode);
	elem.ind_curf = find_last_slash(&elem);
	elem.size = buff.st_size;
	elem.atime = buff.st_atime;
	elem.nlink = buff.st_nlink;
	passwd = getpwuid(buff.st_uid);
	group = getgrgid(buff.st_gid);
	if (passwd)
		elem.p_name = ft_strdup(passwd->pw_name);
	if (group)
		elem.g_name = ft_strdup(group->gr_name);
	ret = ft_lstnew(&elem, sizeof(t_elem));
	return (ret);
}

int				ls_recup_file(t_env *e)
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
			if (buff.st_mode & S_IFDIR)
			{
				if (e->flag & FLAG_R)
				{
					ret = ls_stat_to_list(e, buff, (char*)save->content);
					ft_lstadd(&e->temp_dir, ret);
				}
				ret = ls_stat_to_list(e, buff, ft_strdup((char*)save->content));
				ft_lstinsert(&e->file, ret);
			}
			else
			{
				ret = ls_stat_to_list(e, buff, (char*)save->content);
				ft_lstinsert(&e->file, ret);
			}
			save = ft_lst_remove(&e->temp, save);
			ft_memdel((void**)&save);
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

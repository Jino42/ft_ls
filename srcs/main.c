/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 11:53:16 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/24 16:37:35 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

# define NUM_TYPE 0
# define NUM_USR 1
# define NUM_GRP 4
# define NUM_OTH 7
# define NUM_R 0
# define NUM_W 1
# define NUM_X 2
# define ALL_R 7894898

void		print_elem(t_env *e)
{
	t_list *l;
	t_list *save;
	t_elem *elem;
	char	*time;

	l = e->dir;
	ft_printf("\033[31mIfdir :\n\033[0m");
	while (l)
	{
		elem = l->content;
		ft_printf("%s %3li %s %s %6li %.12s \033[32m%s\033[0m\n",
				elem->mode,
				elem->nlink,
				elem->p_name,
				elem->g_name,
				elem->size,
				ctime(&(elem->atime)) + 4,
				elem->path);
		save = l->next;
		l = save;
	}
	l = e->file;
	ft_printf("\033[31mIffile :\n\033[0m");
	while (l)
	{
		elem = l->content;
		time = ctime(&(elem->atime));
		ft_printf("%s %3li %s %s %6li %.12s \033[32m%s\033[0m\n",
				elem->mode,
				elem->nlink,
				elem->p_name,
				elem->g_name,
				elem->size,
				time + 4,
				&elem->path[elem->ind_curf]);
				//elem->path);
		l = l->next;
	}
	l = e->not_here;
	ft_printf("\033[31mNote here : \n\033[0m");
	while (l)
	{
		ft_printf("%s\n", ((char*)(l->content)));
		save = l->next;
		l = save;
	}
	l = e->temp;
	ft_printf("\033[31mTEMP : \n\033[0m");
	while (l)
	{
		ft_printf("%s\n", ((char*)(l->content)));
		save = l->next;
		l = save;
	}
}

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int			main(int argc, char **argv)
{
	t_env	e;
	int		i;

	ft_bzero(&e, sizeof(t_env));
	pars_arg(&e, argc, argv, &i);
	ls_recup_file_from_arg(&e);
	if (!(ls_loop(&e)))
	{
		ft_putstr_fd("J'ai pas free mais : Error opendir [ls_loop]\n", 2);
		return (0);
	}

	print_elem(&e);
//	rec = ft_lst_remove_index(&e.not_here, index);
//	if (rec)
//		ls_free_temp(&rec);
	ls_free_temp(&e.temp);
	ls_free_temp(&e.not_here);
	ls_free_elem(&e.file);
	ls_free_elem(&e.dir);
	ft_bzero(&e, sizeof(t_env));
	while (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 11:53:16 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/23 05:20:35 by ntoniolo         ###   ########.fr       */
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
/*
typedef struct	s_elem
{
	char		right[11];
	size_t		size_bits;
	size_t		last_change;
	size_t		nb_nlink;
	char		*p_name;
	char		*g_name;
}				t_elem;

	(void)argc;
	void	*ptr;
	struct dirent *c;
	struct stat buf;
	struct passwd *passwd;
	struct group *group;
	char	tab[11];
	char	path[20];

	ft_bzero(&tab, sizeof(char) * 11);
	ft_bzero(&path, sizeof(char) * 20);
	ptr = opendir(argv[1]);
	if (ptr)
	{
		ft_strcpy(path, argv[1]);
		while ((c = readdir(ptr)))
		{
			ft_printf("Nombre de lien : %i\n", buf.st_nlink);
			passwd = getpwuid(buf.st_uid);
			group = getgrgid(buf.st_gid);
			ft_printf("Propriétaire : %s\n", passwd->pw_name);
			ft_printf("Nom du groupe : %s\n", group->gr_name);
			ft_printf("Taille %li\n", buf.st_size);
			ft_printf("%.12s\n", ctime(&buf.st_atime) + 4);
			ft_printf("Time : %li\n", buf.st_atime);
		}
		closedir(ptr);
	}
	else
		perror("ls :  ");
*/

void		print_elem(t_env *e)
{
	t_list *l;
	t_list *save;
	t_elem *elem;

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
		ft_printf("%s %3li %s %s %6li %.12s \033[32m%s\033[0m\n",
				elem->mode,
				elem->nlink,
				elem->p_name,
				elem->g_name,
				elem->size,
				ctime(&(elem->atime)) + 4,
				elem->path);
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
}

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

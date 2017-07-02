#include "ft_ls.h"

void		print_not_here(t_env *e)
{
	t_list *lst;

	lst = e->not_here;
	while (lst)
	{
		ft_dprintf(2, "ls: %s: No such file or directory\n",
											(char*)lst->content);
		lst = lst->next;
	}
	ls_free_temp(&e->not_here);
}

void		print_file(t_env *e, t_elem *elem)
{
	(void)e;
	ft_printf("%s\n",
			&elem->path[elem->ind_curf]);
}

void		print_file_init(t_env *e, t_list *l, t_size_m *size_m)
{
	t_elem		*elem;
	t_list		*save;
	t_list		*ret;

	while (l)
	{
		elem = l->content;
		elem->ind_curf = 0;
		if (e->flag & FLAG_L)
			ls_print_l(e, elem, size_m);
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

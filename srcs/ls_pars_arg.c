/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_pars_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 17:59:18 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/27 10:11:22 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	pars_file(t_env *e, int argc, char **argv, int *i)
{
	t_elem	elem;

	ft_bzero(&elem, sizeof(t_elem));
	while (*i < argc)
	{
		if (argv[*i][0] == 0)
		{
			ft_dprintf(2, "./ft_ls: fts_open: No such file or directory\n");
			return (0);
		}
		ft_lstinsert_alphabet(&e->temp, ft_lstnew(argv[*i],
					ft_strlen(argv[*i]) + 1), e->flag & FLAG_RV);
		e->nb_arg++;
		(*i)++;
	}
	return (1);
}

static int	ft_strallcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (1)
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (1);
}

static int	pars_flag(t_env *e, int i, char **argv)
{
	int i_in;

	i_in = 1;
	while (argv[i][i_in])
	{
		if (argv[i][i_in] == 'l')
			e->flag |= FLAG_L;
		else if (argv[i][i_in] == 'R')
			e->flag |= FLAG_R;
		else if (argv[i][i_in] == 'a')
			e->flag |= FLAG_A;
		else if (argv[i][i_in] == 't')
			e->flag |= FLAG_T;
		else if (argv[i][i_in] == 'r')
			e->flag |= FLAG_RV;
		else if (argv[i][i_in] != '1')
		{
			ft_dprintf(2, "ls: illegal option -- %c\n", argv[i][i_in]);
			ft_dprintf(2, "usage: ls [-Rlart] [file ...]\n");
			return (0);
		}
		i_in++;
	}
	return (1);
}

static int	dir_arg(t_env *e, int argc, char **argv, int *i)
{
	int	option_;

	option_ = 0;
	while (*i < argc && argv[*i][0] == '-' &&
			argv[*i][1] != '\0' && !option_)
	{
		if (!ft_strallcmp(argv[*i], "--"))
		{
			if (!option_)
				option_ = 1;
			else
				return (1);
		}
		else if (option_ && !ft_strcmp(argv[*i], "---"))
			return (1);
		else
		{
			if (!(pars_flag(e, *i, argv)))
				return (0);
		}
		(*i)++;
	}
	return (1);
}

int			pars_arg(t_env *e, int argc, char **argv, int *i)
{
	*i = 1;
	if (!(dir_arg(e, argc, argv, i)))
		return (0);
	if (!(pars_file(e, argc, argv, i)))
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   merge_sort.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/12 14:42:44 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/17 18:40:28 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static t_merge	init_val(int len)
{
	t_merge	m;

	m.i = 0;
	m.j = len / 2 + len % 2;
	m.index = 0;
	m.k = -1;
	return (m);
}

static void		merge_seq(int l, char **fs, int *t)
{
	char	*tmp_files[TMP_BUFF_SIZE];
	int		tmp_tab[TMP_BUFF_SIZE];
	t_merge	m;

	m = init_val(l);
	while (m.i < l / 2 + l % 2 || (fs[m.j] && m.j - (l / 2 + l % 2) < l / 2))
	{
		if (m.j - (l / 2 + l % 2) < l / 2 && fs[m.j] && (m.i >= l / 2 + l % 2 ||
			(t && t[m.i] > t[m.j]) || (!t && ft_strcmp(fs[m.i], fs[m.j]) > 0)))
		{
			tmp_tab[m.index] = t ? t[m.j] : 0;
			tmp_files[m.index++] = fs[m.j++];
		}
		else if (fs[m.i])
		{
			tmp_tab[m.index] = t ? t[m.i] : 0;
			tmp_files[m.index++] = fs[m.i++];
		}
	}
	while (++m.k < m.index)
	{
		fs[m.k] = tmp_files[m.k];
		if (t)
			t[m.k] = tmp_tab[m.k];
	}
}

void			merge_sort(int *t_tab, char **files, int len)
{
	if (len > TMP_BUFF_SIZE)
		return ;
	if (len < 3)
	{
		if (files && files[0] && files[1] && ((t_tab && t_tab[0] > t_tab[1])
					|| (!t_tab && ft_strcmp(files[0], files[1]) > 0)))
		{
			ft_strswap(&files[0], &files[1]);
			if (t_tab)
				ft_swap(&t_tab[0], &t_tab[1]);
		}
		return ;
	}
	merge_sort(t_tab, files, len / 2 + len % 2);
	merge_sort(t_tab ? &t_tab[len / 2 + len % 2]
		: NULL, &files[len / 2 + len % 2], len / 2);
	merge_seq(len, files, t_tab);
}

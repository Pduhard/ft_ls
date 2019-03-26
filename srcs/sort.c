/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/28 11:36:40 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/13 15:45:45 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	*get_times(char **files, const char *parent_name,
		const t_option options, const int len)
{
	char		*path;
	struct stat	info;
	int			*tab;
	int			i;
	time_t		now;

	now = time(NULL);
	i = 0;
	if (!(tab = malloc(sizeof(int) * len)))
		return (NULL);
	while (files[i])
	{
		path = ft_strjoin(parent_name, files[i]);
		lstat(path, &info);
		if (options.u || options.maj_u)
			tab[i] = options.u ? now - info.st_atime
				: now - info.st_birthtimespec.tv_sec;
		else
			tab[i] = now - info.st_mtime;
		i++;
		ft_strdel(&path);
	}
	return (tab);
}

static void	sort_by_time(char **files,
		const char *parent_name, const t_option options)
{
	int			len;
	int			seq;
	int			*t_tab;

	seq = 1;
	len = 0;
	while (files[len])
		len++;
	t_tab = get_times(files, parent_name, options, len);
	merge_sort(t_tab, files, len);
	free(t_tab);
}

static char	**build_sorted_list(int nb, t_win win,
		char **new_files, char **files)
{
	int				short_l;
	int				long_l;
	int				index;
	int				i;
	int				j;

	i = 0;
	index = -1;
	while (index < nb)
	{
		j = -1;
		long_l = 0;
		short_l = 0;
		while (++j < win.line_nbr && ++index < nb)
		{
			new_files[long_l * (win.line_size + 1)
				+ short_l * win.line_size + i] = files[index];
			short_l += long_l < nb % win.line_nbr ? 0 : 1;
			long_l += long_l < nb % win.line_nbr ? 1 : 0;
		}
		i++;
	}
	new_files[nb] = NULL;
	return (new_files);
}

static void	sort_list_for_win(char ***files,
			const int path_len, const int nb, char ***files_not_align)
{
	t_win			win;
	char			**new_files;
	int				i;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &win.win) != -1)
	{
		if (!(new_files = (char **)malloc(sizeof(char *) * (nb + 1))))
			return ;
		win.line_size = win.win.ws_col / path_len;
		if (!win.line_size)
			win.line_size = 1;
		win.line_nbr = 1;
		i = 0;
		win.rest = (nb % win.line_nbr) ? 1 : 0;
		while (nb / win.line_nbr + win.rest > win.line_size)
		{
			win.line_nbr++;
			win.rest = (nb % win.line_nbr) ? 1 : 0;
		}
		win.line_size = nb / win.line_nbr;
		win.rest_left = nb % win.line_nbr;
		*files_not_align = *files;
		*files = build_sorted_list(nb, win, new_files, *files);
	}
}

void		sort_files(const t_option options, char ***files,
			t_sort *sort, char ***files_not_aligned)
{
	int		i;
	int		j;

	j = sort->nb - 1;
	if (!options.f)
		merge_sort(NULL, *files, sort->nb);
	if (options.t && !options.f)
		sort_by_time(*files, sort->parent_name, options);
	if (options.r && !options.f)
	{
		i = 0;
		while (i < j)
			ft_strswap(&(*files)[i++], &(*files)[j--]);
	}
	if (!options.l && sort->type)
		sort_list_for_win(files,
			sort->path_len, sort->nb, files_not_aligned);
}

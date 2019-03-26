/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/28 12:20:30 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/11 13:28:33 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	get_win_param(t_win *win, const int len, const int nb)
{
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &win->win) == -1)
		return ;
	win->line_size = win->win.ws_col / len;
	if (!win->line_size)
		win->line_size = 1;
	win->line_nbr = 1;
	win->rest = (nb % win->line_nbr) ? 1 : 0;
	while (nb / win->line_nbr + win->rest > win->line_size)
	{
		win->line_nbr++;
		win->rest = (nb % win->line_nbr) ? 1 : 0;
	}
	win->line_size = nb / win->line_nbr;
	win->rest_left = nb % win->line_nbr;
}

static int	build_file_path(const char *files,
				const t_option options, const char *parent_path, char **path)
{
	int			n_len;
	int			f_len;
	struct stat info;
	char		*real_path;

	if (!options.maj_g)
		return (0);
	f_len = ft_strlen(files);
	*path = ft_strdup(files);
	real_path = ft_strjoin(parent_path, *path);
	if (lstat(real_path, &info) == -1)
	{
		ft_strdel(&real_path);
		return (0);
	}
	manage_colors(path, info);
	n_len = ft_strlen(*path);
	ft_strdel(&real_path);
	return (n_len - f_len);
}

static int	print_file(const char *files,
				const char *parent_path, const t_option options, const int len)
{
	int			f_len;
	char		*path;
	char		*str;
	int			color_mark;

	path = NULL;
	f_len = ft_strlen(files);
	color_mark = build_file_path(files, options, parent_path, &path);
	ft_putstr(path ? path : files);
	if (len - f_len > 0)
		ft_putstr((str = ft_strfillnew(' ', len - f_len)));
	ft_strdel(&path);
	ft_strdel(&str);
	return (color_mark);
}

t_flist		build_flist(char **files, const int max_length,
				const int nb, const char *parent_path)
{
	t_flist		flist;

	flist.files = files;
	flist.max_length = max_length;
	flist.nb = nb;
	flist.parent_path = (char *)parent_path;
	return (flist);
}

void		print_file_list(const t_option options,
				t_flist flist)
{
	char			*str;
	int				i;
	t_win			win;
	int				cpt;

	i = 0;
	str = NULL;
	if (options.l)
		print_detailed_list(options, flist.files, flist.parent_path);
	else
	{
		get_win_param(&win, flist.max_length, flist.nb);
		while (flist.files[i])
		{
			cpt = 0;
			while (cpt++ < win.line_size && flist.files[i])
				print_file(flist.files[i++],
					flist.parent_path, options, flist.max_length);
			if (win.rest_left-- > 0 && flist.files[i])
				print_file(flist.files[i++],
					flist.parent_path, options, flist.max_length);
			write(1, "\n", 1);
		}
	}
}

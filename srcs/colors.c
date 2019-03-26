/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   colors.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 11:34:45 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/11 13:05:30 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	set_dir_colors(const struct stat info, char **colors)
{
	if ((info.st_mode & (2)))
	{
		if ((info.st_mode & (1 << 9)))
			*colors = ft_strfjoin(*colors, ft_strdup("30;42;"));
		else
			*colors = ft_strfjoin(*colors, ft_strdup("30;43;"));
	}
	else
		*colors = ft_strfjoin(*colors, ft_strdup("1;96;"));
}

static void	set_reg_file_colors(const struct stat info, char **colors)
{
	if ((info.st_mode & ((1 << 6) | (1 << 3) | 1)))
	{
		if ((((info.st_mode >> 9) & 7) & 4))
			*colors = ft_strfjoin(*colors, ft_strdup("41;30"));
		else if ((((info.st_mode >> 9) & 7) & 2))
			*colors = ft_strfjoin(*colors, ft_strdup("46;30"));
		else
			*colors = ft_strfjoin(*colors, ft_strdup("31;"));
	}
}

void		manage_colors(char **path, const struct stat info)
{
	char	*colors;

	colors = ft_strdup("\x1b[");
	if ((info.st_mode & S_IFMT) == S_IFDIR)
		set_dir_colors(info, &colors);
	if ((info.st_mode & S_IFMT) == S_IFIFO)
		colors = ft_strfjoin(colors, ft_strdup("33;"));
	if ((info.st_mode & S_IFMT) == S_IFLNK)
		colors = ft_strfjoin(colors, ft_strdup("35;"));
	if ((info.st_mode & S_IFMT) == S_IFCHR)
		colors = ft_strfjoin(colors, ft_strdup("43;34;"));
	if ((info.st_mode & S_IFMT) == S_IFBLK)
		colors = ft_strfjoin(colors, ft_strdup("46;34;"));
	if ((info.st_mode & S_IFMT) == S_IFSOCK)
		colors = ft_strfjoin(colors, ft_strdup("32;"));
	if ((info.st_mode & S_IFMT) == S_IFREG)
		set_reg_file_colors(info, &colors);
	colors = ft_strfjoin(colors, ft_strdup("m"));
	*path = ft_strfjoin(colors, *path);
	*path = ft_strfjoin(*path, ft_strdup("\x1b[0m"));
}

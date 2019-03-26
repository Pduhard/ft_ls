/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   file_info.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 12:47:39 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/11 13:02:55 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	get_link_from_path(const char *str, char **path, const char *rights)
{
	char	buff[500];
	int		len;

	if (rights[0] == 'l')
	{
		len = (int)readlink(str, buff, 500);
		buff[len] = '\0';
		*path = ft_strfjoin(*path, ft_strjoin(" -> ", buff));
	}
}

static void	compare_files(const t_file *file, t_max *max)
{
	if (ft_intlen(file->links_nb) > max->links_nb)
		max->links_nb = ft_intlen(file->links_nb);
	if ((int)ft_strlen(file->owner) > max->owner)
		max->owner = (int)ft_strlen(file->owner);
	if (ft_intlen(file->bytes) > max->bytes)
		max->bytes = ft_intlen(file->bytes);
	if ((int)ft_strlen(file->group) > max->group)
		max->group = (int)ft_strlen(file->group);
	if ((int)ft_strlen(file->path) > max->path)
		max->path = (int)ft_strlen(file->path);
	if (file->major != -1)
		max->minmaj = 1;
}

static void	get_file_ugid(const struct stat info,
		t_file *file, const t_option options)
{
	struct passwd	*user;
	struct group	*grp;

	user = NULL;
	grp = NULL;
	user = getpwuid(info.st_uid);
	grp = getgrgid(info.st_gid);
	if (!options.g)
	{
		if (!user)
			file->owner = ft_itoa(info.st_uid);
		else
			file->owner = ft_strdup(user->pw_name);
	}
	if (!grp)
		file->group = ft_itoa(info.st_gid);
	else
		file->group = ft_strdup(grp->gr_name);
}

static void	get_file_size(const struct stat info, t_file *file)
{
	file->bytes = info.st_size;
	file->major = -1;
	file->minor = -1;
	if (S_ISCHR(info.st_mode) || S_ISBLK(info.st_mode))
		file->major = (info.st_rdev >> 24);
	if (S_ISCHR(info.st_mode) || S_ISBLK(info.st_mode))
		file->minor = (info.st_rdev & 0xFF);
}

t_file		*new_file(const char *str, t_max *max,
		const char *parent_path, const t_option options)
{
	t_file			*file;
	struct stat		info;
	char			*real_path;

	real_path = ft_strjoin(parent_path, str);
	if (lstat(real_path, &info) == -1
		|| !(file = (t_file *)malloc(sizeof(t_file))))
	{
		ft_strdel(&real_path);
		return (NULL);
	}
	ft_bzero(file, sizeof(t_file));
	file->rights = get_rights(info.st_mode, real_path, max);
	file->links_nb = info.st_nlink;
	get_file_ugid(info, file, options);
	get_file_size(info, file);
	file->date = get_date(info.st_mtime, options,
		info.st_atime, info.st_birthtimespec.tv_sec);
	file->path = ft_strdup(str);
	if (options.maj_g)
		manage_colors(&file->path, info);
	get_link_from_path(real_path, &file->path, file->rights);
	compare_files(file, max);
	ft_strdel(&real_path);
	return (file);
}

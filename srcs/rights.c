/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rights.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/28 18:03:28 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/11 07:28:21 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static char	get_file_type(const mode_t mode)
{
	if ((mode & S_IFMT) == S_IFREG)
		return ('-');
	else if ((mode & S_IFMT) == S_IFIFO)
		return ('p');
	else if ((mode & S_IFMT) == S_IFCHR)
		return ('c');
	else if ((mode & S_IFMT) == S_IFDIR)
		return ('d');
	else if ((mode & S_IFMT) == S_IFBLK)
		return ('b');
	else if ((mode & S_IFMT) == S_IFLNK)
		return ('l');
	else if ((mode & S_IFMT) == S_IFSOCK)
		return ('s');
	return ('-');
}

static void	set_rights(const mode_t mode, char *rights)
{
	int		i;
	int		grp_right;

	i = 0;
	while (i < 3)
	{
		grp_right = ((mode >> ((2 - i) * 3)) & 7);
		rights[1 + i * 3] = (grp_right & 4) ? 'r' : '-';
		rights[1 + i * 3 + 1] = (grp_right & 2) ? 'w' : '-';
		rights[1 + i * 3 + 2] = (grp_right & 1) ? 'x' : '-';
		i++;
	}
	grp_right = ((mode >> 9) & 7);
	rights[i * 3 + 1] = '\0';
	if ((grp_right & 4))
		rights[3] = rights[3] == 'x' ? 's' : 'S';
	if ((grp_right & 2))
		rights[6] = rights[6] == 'x' ? 's' : 'S';
	if ((grp_right & 1))
		rights[9] = rights[9] == 'x' ? 't' : 'T';
}

static void	set_extended_rights(const int extended_attr
				, acl_t acl, char *rights)
{
	if (extended_attr > 0)
	{
		rights[10] = '@';
		rights[11] = '\0';
	}
	if (acl)
	{
		rights[10] = '+';
		rights[11] = '\0';
		acl_free(acl);
	}
}

char		*get_rights(const mode_t mode, const char *file, t_max *max)
{
	char	*rights;
	int		extended_attr;
	acl_t	acl;

	extended_attr = 0;
	acl = 0;
	if (((extended_attr = listxattr(file, NULL, 0, XATTR_NOFOLLOW)) > 0
		|| (acl = acl_get_file(file, ACL_TYPE_EXTENDED))))
	{
		if (!(rights = (char *)malloc(12)))
			return (NULL);
	}
	else if (!(rights = (char *)malloc(11)))
		return (NULL);
	rights[0] = get_file_type(mode);
	set_rights(mode, rights);
	set_extended_rights(extended_attr, acl, rights);
	if ((int)ft_strlen(rights) > max->rights)
		max->rights = (int)ft_strlen(rights);
	return (rights);
}

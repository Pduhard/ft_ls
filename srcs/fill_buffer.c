/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_buffer.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 12:43:17 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/11 13:11:41 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	print_nb_to_buff(const long nb, char *res, int *i, int j)
{
	while ((nb || j != 1) && !(nb / j) && (j /= 10))
		res[(*i)++] = ' ';
	while (j)
	{
		res[(*i)++] = ((nb / j) % 10) + '0';
		j /= 10;
	}
}

static void	build_file_size_str(char *res, t_max max, int *i, t_file *files)
{
	int		len;
	int		j;

	if (files->major != -1)
	{
		j = 1000;
		while (max.bytes-- > 9)
			res[(*i)++] = ' ';
		print_nb_to_buff(files->major, res, i, j);
		res[(*i)++] = ',';
		print_nb_to_buff(files->minor, res, i, j);
	}
	else
	{
		len = ft_intlen(files->bytes);
		while (max.bytes-- > len)
			res[(*i)++] = ' ';
		print_nb_to_buff(files->bytes, res, i, ft_pow(10, len - 1));
	}
	res[(*i)++] = ' ';
}

static int	add_ug_to_buffer(t_file *l_files,
		const t_option options, char *res, const t_max max)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = -1;
	res[i++] = ' ';
	len = ft_strlen(l_files->owner);
	while (!options.g && ++j < max.owner + 2)
		res[i++] = j < len ? l_files->owner[j] : ' ';
	j = -1;
	len = ft_strlen(l_files->group);
	while (++j < max.group + 1)
		res[i++] = j < len ? l_files->group[j] : ' ';
	return (i);
}

int			add_file_to_buffer(char *res, const t_max max,
		t_file *l_files, const t_option options)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (l_files->rights[j])
		res[i++] = l_files->rights[j++];
	if (j == 10)
		res[i++] = ' ';
	res[i++] = ' ';
	print_nb_to_buff(l_files->links_nb, res, &i, ft_pow(10, max.links_nb - 1));
	i += add_ug_to_buffer(l_files, options, &res[i], max);
	build_file_size_str(res, max, &i, l_files);
	j = -1;
	while (l_files->date && l_files->date[++j])
		res[i++] = l_files->date[j];
	res[i++] = ' ';
	j = -1;
	while (l_files->path[++j])
		res[i++] = l_files->path[j];
	res[i++] = '\n';
	res[i] = '\0';
	return (i);
}

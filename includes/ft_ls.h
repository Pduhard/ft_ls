/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/28 07:33:22 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/12 15:31:55 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/xattr.h>
# include <fcntl.h>
# include <errno.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <sys/acl.h>
# include <uuid/uuid.h>
# include <sys/ioctl.h>
# define SUPP_FLAGS "GRUadfglrtu"
# define USAGE "usage: ./ft_ls [-GRUadfglrtu] [file ...]\n"
# define TMP_BUFF_SIZE 32000

typedef struct		s_option
{
	int				maj_g;
	int				maj_r;
	int				maj_u;
	int				a;
	int				d;
	int				f;
	int				g;
	int				l;
	int				r;
	int				t;
	int				u;
}					t_option;

typedef struct		s_file
{
	char			*rights;
	int				links_nb;
	char			*owner;
	char			*group;
	long			bytes;
	char			*date;
	char			*path;
	struct s_file	*next;
	struct stat		info;
	int				minor;
	int				major;
}					t_file;

typedef struct		s_max
{
	int				path;
	int				rights;
	int				links_nb;
	int				owner;
	int				group;
	int				bytes;
	int				minmaj;
	int				nb_files;
}					t_max;

typedef struct		s_sort
{
	char			*parent_name;
	int				path_len;
	int				nb;
	int				type;
}					t_sort;

typedef struct		s_data
{
	struct s_option	options;
	char			**files;
	int				*fds;
	int				*types;
}					t_data;

typedef struct		s_win
{
	int				line_size;
	int				line_nbr;
	struct winsize	win;
	int				rest_left;
	int				rest;
}					t_win;

typedef struct		s_flist
{
	char			*parent_path;
	int				max_length;
	int				nb;
	char			**files;
}					t_flist;

typedef struct		s_merge
{
	int				i;
	int				j;
	int				index;
	int				k;
}					t_merge;

t_data				*init_data(int argc, char **argv);
t_sort				init_sort_arg(char *parent_name,
						int path_len, int nb, int type);
int					list_errorfiles(t_data *data);
int					list_argvfiles(t_data *data);
t_flist				build_flist(char **files, const int max_length,
						const int nb, const char *parent_path);
void				print_file_list(t_option options, t_flist flist);
void				print_detailed_list(t_option options,
						char **files, const char *parent_path);
t_file				*new_file(const char *str, t_max *max,
						const char *parent_path, const t_option options);
char				*get_date(const time_t m_time, const t_option options,
						const time_t a_time, const time_t b_time);
char				*get_rights(const mode_t mode,
						const char *file, t_max *max);
void				display_dir(const char *dir_name,
						const t_option options, DIR *rep);
int					add_file_to_buffer(char *res, const t_max max,
						t_file *l_files, const t_option options);
void				add_file(char *file, int type,
						t_data *data, t_option options);
void				manage_colors(char **path, const struct stat info);
int					check_comp(const char *str1, const char *str2, int opt_f);
void				sort_files(const t_option options, char ***files,
						t_sort *sort, char ***files_not_align);
void				sort_argv(char **argv, int i, t_data *data);
void				merge_sort(int *t_tab, char **files, int len);
void				free_all(t_data *data, char **path);
void				free_file(t_file **file);
void				free_dir(char **file_list, char **new_path,
						char **list_to_recurse);

#endif

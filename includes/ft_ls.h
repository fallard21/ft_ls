/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 21:03:52 by fallard           #+#    #+#             */
/*   Updated: 2020/08/16 01:23:39 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <sys/xattr.h>	// getxattr
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <stdio.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <unistd.h>
# include <sys/sysmacros.h>
# include <sys/ioctl.h>

# define KEYS "lRartcuisSfog1"
# define LRLINK "readlink"
# define LMALLOC "malloc"
# define LLSTAT "lstat"
# define LSPATH 1500

# define BAD_KEY 1
# define BAD_PARAMETER 2
# define NO_FILE 3
# define DIR_PERM 4
# define LINK_PERM 5

typedef struct stat		t_stat;
typedef struct dirent	t_dir;
typedef struct group	t_grp;
typedef struct passwd	t_pw;
typedef struct winsize	t_win;

/*
** -t - mtime
** -c - ctime
** -u - atime
*/

typedef struct		s_col
{
	char			**args;
	int				*lens;
	size_t			*ib;
	int				size;
	int				col;
	int				row;
	int				width;
	int				space;
	int				prev;
	int				m;
}					t_col;

typedef struct		s_file
{
	t_stat			sb;
	int				fmajor;
	int				fminor;
	char			*uid_name;
	char			*gid_name;
	char			*name;
	char			path[LSPATH];
	char			*link;
	struct s_file	*next;
}					t_file;

typedef struct		s_ls
{
	int				count_args;

	int				flag_args;
	int				flag_path;
	int				flag_perm;
	int				key_l;
	int				key_up_r;
	int				key_a;
	int				key_r;
	int				key_t;

	int				key_c;
	int				key_u;
	int				key_i;
	int				key_s;
	int				key_up_s;
	int				key_f;
	int				key_o;
	int				key_g;
	int				key_one;

	uint16_t		tty_width;

	DIR				*dir;
	t_dir			*lread;
	t_stat			sb;
	t_grp			*gr_gid;
	t_pw			*pw_uid;
	t_file			*args;
}					t_ls;

typedef struct		s_data
{
	t_file			*head;
	t_col			col;
	char			path[LSPATH];
	int				spec_file;
	int				size;
	int				*width;
}					t_data;

/*
** >----------------< PARSING ARGUMENTS >----------------<
*/
int					parse_args_to_keys(t_ls *ls, int ac, char **av);
void				parse_args_to_file(t_ls *ls, int ac, char **av);
void				update_keys(t_ls *ls, char *del, int key);
int					init_keys(t_ls *ls, char *argv);
int					find_key(char key);

/*
** >----------------< GET DIR INFO >----------------<
*/
t_data				get_data(t_ls *ls, t_file *head, char *path, char *dir);
t_file				*get_dir_files(t_ls *ls, char *fpath);
t_file				*new_file(t_ls *ls, char *path, char *name);
void				get_lstat(t_ls *ls, t_file *tmp, char *fpath);
void				get_symbolic_link(t_file *tmp, char *fpath);
int					list_size(t_file *head);
int					*get_width_arr(t_file *head);
void				fix_path(char *path);
void				init_path(char *add, char *path, char *dir, int flag);
void				display_path(t_ls *ls, char *fpath);

/*
** >----------------< D0 LS >----------------<
*/
void				do_ls(t_ls *ls);
void				display_arguments(t_ls *ls, t_file *root);
void				display_dir(t_ls *ls, char *path, char *name);

/*
** >----------------< SORTING >----------------<
*/
t_file				*sort(t_ls *ls, t_file *head);
t_file				*sort_list(int (*cmp)(t_file*, t_file*), t_file *head);
t_file				*reverse_list(t_file *head);
int					cmp_size(t_file *left, t_file *right);
int					cmp_name(t_file *left, t_file *right);
int					cmp_atime(t_file *left, t_file *right);
int					cmp_ctime(t_file *left, t_file *right);
int					cmp_mtime(t_file *left, t_file *right);

/*
** >----------------< DISPLAY >----------------<
*/
void				display_files(t_ls *ls, t_data data);
void				display_key_l(t_ls *ls, t_data data);
void				display_one_column(t_ls *ls, t_data *data);
void				display_total(t_ls *ls, t_file *head);
void				display_error(char *file, int flag);
void				error_exit(t_ls *ls, char *file, int flag);

/*
** >----------------< COLUMNS DISPLAY >----------------<
*/
void				display_column(t_ls *ls, t_data *data);
void				print_column(t_ls *ls, t_data *data, t_col *col, int row);
int					get_row(t_ls *ls, t_data *data);

/*
** >----------------< EXTENDED DISPLAY >----------------<
*/
void				display_chmod(t_file *tmp);
void				display_users(t_ls *ls, t_file *head, int *width);
void				display_size(t_data data, t_file *f, int *width);
void				display_time(t_ls *ls, t_file *tmp);
void				display_name(t_ls *ls, t_file *current);

/*
** >----------------< MEMORY >----------------<
*/
void				ft_exit(char *error);
int					free_split(char ***str);
void				free_list(t_file **head);
int					free_data(t_data *data);
int					free_col(t_col *col);

#endif

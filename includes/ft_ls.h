/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 21:03:52 by fallard           #+#    #+#             */
/*   Updated: 2020/08/15 04:52:32 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>	// stat
# include <dirent.h>		// readdir
# include <errno.h>		// perror
# include <sys/xattr.h>	// getxattr
# include <pwd.h>		// getpwuid
# include <grp.h>		// getgrid
# include <time.h>		// ctime
# include <stdio.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <unistd.h>
# include <sys/sysmacros.h>	//major minor

# include <sys/ioctl.h>
# include <termios.h>

# define KEYS "lRartcuisSfog1"
# define LRLINK "readlink"
# define LMALLOC "malloc"
# define LLSTAT "lstat"
# define LSPATH 4096

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
// -isScu
// -AF ?
// -go 
// -1

// -t - mtime
// -c - ctime
// -u - atime

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

	int				key_c;		// bonus
	int				key_u;		// bonus
	int				key_i;		// bonus
	int				key_s;		// bonus
	int				key_up_s;	// bonus
	int				key_f;		// bonus
	int				key_o;		// bonus
	int				key_g;		// bonus
	int				key_one;	// bonus 

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
	t_file		*head;
	t_col		col;
	char		path[LSPATH];
	int			spec_file;
	int			size;
	int			*width;
}					t_data;

void	get_symbolic_link(t_file *tmp, char *fpath);
t_data	get_data(t_ls *ls, t_file *head, char *path, char *dir);

int		parse_args_to_keys(t_ls *ls, int ac, char **av);
void	parse_args_to_file(t_ls *ls, int ac, char **av);
void	update_keys(t_ls *ls, char *del, int key);
int		init_keys(t_ls *ls, char *argv);
int		find_key(char key);

t_file	*get_dir_files(t_ls *ls, char *fpath);
t_file	*new_file(t_ls *ls, char *path, char *name);
int		save_file_info(t_ls *ls, t_file *tmp, char *name);
void	fix_path(char *path);
void	init_path(char *add, char *path, char *dir, int flag);

void	choosing_ls(t_ls *ls);
void	ls_only_args(t_ls *ls);
void	ls_print_dir(t_ls *ls, char *dir_name);
void	ls_print_reg(t_ls *ls, t_file *head);

void	display_arguments(t_ls *ls, t_file *root);

void	test_ls(t_ls *ls, char *path, char *dirname);
void	display_dir(t_ls *ls, char *path, char *name);
void	display_path(t_ls *ls, char *fpath);

void	display_key_l(t_ls *ls, t_data data);
void	display_name(t_ls *ls, t_file *current);
void	print_link(t_file *file);
void	display_size(t_data data, t_file *f, int *width);
void	display_time(t_ls *ls, t_file *tmp);
void	display_chmod(t_file *tmp);
void	display_users(t_ls *ls, t_file *head, int *width);


void	ft_exit(char *error);
int		free_split(char ***str);
void	free_list(t_file **head);
int		free_data(t_data *data);
int		free_col(t_col *col);

void	display_column(t_ls *ls, t_data *data);
void	print_column(t_ls *ls, t_data *data, t_col *col, int row);
int		get_row(t_ls *ls, t_data *data);
void	display_one_column(t_ls *ls, t_data *data);

char	get_type(mode_t mode);

t_file	*sort_list(int (*cmp)(t_file*, t_file*), t_file *head);
t_file	*reverse_list(t_file *head);
int		cmp_size(t_file *left, t_file *right);
int		cmp_name(t_file *left, t_file *right);
int		cmp_atime(t_file *left, t_file *right);
int		cmp_ctime(t_file *left, t_file *right);
int		cmp_mtime(t_file *left, t_file *right);
t_file	*sort(t_ls *ls, t_file *head);

int		*get_width_arr(t_file *head);


void	parse_keys_args(t_ls *ls, int argc, char **argv);
int		parse_file_args(t_ls *ls, int argc, char **argv);
void	choosing_ls(t_ls *ls);

void	display_error(char *file, int flag);
void	error_exit(t_ls *ls, char *file, int flag);

void	do_ls(t_ls *ls);
void	do_ls_args(t_ls *ls, t_file *head);
void	display_total(t_ls *ls, t_file *head);

void	display_files(t_ls *ls, t_data data);

int		list_size(t_file *head);

t_data	*update_data(t_ls *ls, t_data **upd, t_file *new);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 21:03:52 by fallard           #+#    #+#             */
/*   Updated: 2020/08/09 03:59:45 by fallard          ###   ########.fr       */
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
	int				size;
	int				col;
	int				row;
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
	char			path[PATH_MAX];
	struct s_file	*next;
}					t_file;

typedef struct		s_ls
{
	int				count_file;
	int				count_dir;
	int				count_link;

	int				flag_args;

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
	int				key_f;		// bonus ??
	int				key_o;		// bonus
	int				key_g;		// bonus
	int				key_one;	// bonus 

	uint16_t		tty_width;

	DIR				*dir;
	t_dir			*lol;
	t_stat			sb;
	t_grp			*gr_gid;
	t_pw			*pw_uid;
	t_file			*args;
	
}					t_ls;

typedef struct		s_data
{
	t_file		*head;
	t_col		col;
	char		path[PATH_MAX];
	int			spec_file;
	int			size;
	int			*width;
	int			permission;
}					t_data;

t_data	get_data(t_ls *ls, t_file *head, char *path, char *dir);
void	run_ls(t_ls *ls, char *path, char *dirname);

int		parse_args_to_keys(t_ls *ls, int ac, char **av);
int		parse_args_to_file(t_ls *ls, int ac, char **av);
void	update_keys(t_ls *ls, char *del, int key);
int		init_keys(t_ls *ls, char *argv);
int		find_key(char key);

t_file	*get_dir_files(t_ls *ls, char *path, char *dir_name);
t_file	*new_file(t_ls *ls, char *path, char *name);
int		save_file_info(t_ls *ls, t_file *tmp, char *name);

void	choosing_ls(t_ls *ls);
void	ls_only_args(t_ls *ls);
void	ls_print_dir(t_ls *ls, char *dir_name);
void	ls_print_reg(t_ls *ls, t_file *head);

void	display_file_from_args(t_ls *ls, t_data *root);

void	test_ls(t_ls *ls, char *path, char *dirname);
void	display_dir(t_ls *ls, char *path, char *name);
void	display_path(char *path);

void	display_name(t_ls *ls, t_file *current);
void	print_link(t_file *file);
void	display_size(t_data data, t_file *f, int *width);
void	display_time(t_ls *ls, t_file *tmp);
void	display_chmod(t_file *tmp);
void	display_users(t_ls *ls, t_file *head, int *width);


void	ft_exit();
int		free_split(char ***str);
int		free_list(t_file **head);
int		free_data(t_data *data);

int		print_column(t_ls *ls, t_data data);
void	print_one_column(t_file *head);
//void	calculate_column(t_ls *ls, t_file *head);
//int		get_column(char **args);
//void	print_column(t_col *col, int row);
//int		get_max_width(t_col *col, int j, int row);
//char	**list_to_char(t_col *col, t_file *head);
//int		*get_lens_of_args(t_col *col);
//int		get_row(t_ls *ls, t_col *col);
//int		get_sum_width(t_col *col, int row);

void	print_list(t_file *head);


char	get_type(mode_t mode);

t_file	*sort_list(int (*cmp)(t_file*, t_file*), t_file *head);
t_file	*reverse_list(t_file *head);
int		cmp_size(t_file *left, t_file *right);
int		cmp_name(t_file *left, t_file *right);
int		cmp_atime(t_file *left, t_file *right);
int		cmp_ctime(t_file *left, t_file *right);
int		cmp_mtime(t_file *left, t_file *right);
t_file	*sort(t_ls *ls, t_file *head);

size_t	width_uid_gid(t_file *head, int flag);
size_t	width_nlink(t_file *head, int flag);
int		*get_width_arr(t_file *head);

int		width_num(size_t num);
void	ls_max(int current, int *width);

void	parse_keys_args(t_ls *ls, int argc, char **argv);
int		parse_file_args(t_ls *ls, int argc, char **argv);
void	choosing_ls(t_ls *ls);

void	print_key_l(t_ls *ls, t_data data);

void	print_error(t_ls *ls, char *file, int flag);

void	do_ls(t_ls *ls, t_file *head, char *dir);
void	do_ls_args(t_ls *ls, t_file *head);
void	print_total(t_file *head);

void	display_files(t_ls *ls, t_data data);

int		list_size(t_file *head);

void	split_list(t_file **dirs, t_file **others, t_file **head);

t_data	*update_data(t_ls *ls, t_data **upd, t_file *new);

#endif

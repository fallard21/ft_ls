/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 21:03:52 by fallard           #+#    #+#             */
/*   Updated: 2020/07/28 00:41:18 by fallard          ###   ########.fr       */
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

# include <sys/ioctl.h>
# include <termios.h>

# define KEYS "lRart"
# define ACCESS "ls: cannot access '%s': %s\n"

typedef struct stat		t_stat;
typedef struct dirent	t_dir;
typedef struct group	t_grp;
typedef struct passwd	t_pw;
typedef struct winsize	t_win;
// -ismScu
// -AF ?
// -go 

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
	//ino_t			inode;
	//blkcnt_t		blocks;
	//mode_t			mode;
	//nlink_t			nlink;
	//uid_t			uid;
	char			*uid_name;
	//gid_t			gid;
	char			*gid_name;
	//off_t			size;
	//time_t			mtime;
	//dev_t			dev;
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
	int				flag_keys;

	int				key_l;
	int				key_up_r;
	int				key_a;
	int				key_r;
	int				key_t;
	int				key_i;
	int				key_s;
	int				key_up_s;
	int				key_f;	// ?

	uint16_t		tty_width;
	int				tty_flag;

	DIR				*dir;
	t_dir			*lol;
	t_stat			sb;
	t_grp			*gr_gid;
	t_pw			*pw_uid;
	t_file			*args;
	t_file			*dirs;
	t_file			*others;
}					t_ls;

int		parse_args_to_keys(t_ls *ls, int ac, char **av);
int		parse_args_to_file(t_ls *ls, int ac, char **av);
int		init_keys(t_ls *ls, char *argv);
int		find_key(char key);

t_file	*get_dir_files(t_ls *ls, char *dir_name);
t_file	*new_file(t_ls *ls, char *dirname, char *filename);
int		save_file_info(t_ls *ls, t_file *tmp, char *name);

int		ls_without_args(t_ls *ls);

void	choosing_ls(t_ls *ls);
void	ls_only_args(t_ls *ls);
void	ls_print_dir(t_ls *ls, char *dir_name);
void	ls_print_reg(t_ls *ls, t_file *head);

void	ls_print_args(t_ls *ls, t_file *head);

void	print_link(t_ls *ls, char *file);

void	ft_exit();
int		free_split(char ***str);
int		free_list(t_file **head);

int		print_column(t_ls *ls, t_file *head);

//void	calculate_column(t_ls *ls, t_file *head);
//int		get_column(char **args);
//void	print_column(t_col *col, int row);
//int		get_max_width(t_col *col, int j, int row);
//char	**list_to_char(t_col *col, t_file *head);
//int		*get_lens_of_args(t_col *col);
//int		get_row(t_ls *ls, t_col *col);
//int		get_sum_width(t_col *col, int row);

void	print_list(t_file *head);

void	put_chmod(mode_t mode);
char	get_type(mode_t mode);

t_file	*sort_list(int (*cmp)(t_file*, t_file*), t_file *head);
t_file	*reverse_list(t_file *head);
int		cmp_size(t_file *left, t_file *right);
int		cmp_name(t_file *left, t_file *right);
int		cmp_mtime(t_file *left, t_file *right);
t_file	*sort(t_ls *ls, t_file *head);

size_t	width_uid_gid(t_file *head, int flag);
size_t	width_nlink(t_file *head, int flag);
int		*get_width_arr(t_file *head);

void	put_time(time_t ntime);

void	parse_keys_args(t_ls *ls, int argc, char **argv);
int		parse_file_args(t_ls *ls, int argc, char **argv);
void	choosing_ls(t_ls *ls);

void	print_key_l(t_ls *ls, t_file *head);

void	print_error(t_ls *ls, char *file, int flag);

void	do_ls(t_ls *ls, t_file *head, char *dir);
void	do_ls_args(t_ls *ls, t_file *head);
void	print_total(t_file *head);

void	main_print(t_ls *ls, t_file *head);

int		list_size(t_file *head);

void	split_list(t_ls *ls, t_file *head);



#endif

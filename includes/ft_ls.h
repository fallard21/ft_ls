/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tima <tima@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 17:12:52 by tima              #+#    #+#             */
/*   Updated: 2020/07/09 04:48:58 by tima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>	// stat
#include <dirent.h>		// readdir
#include <errno.h>		// perror
#include <sys/xattr.h>	// getxattr
#include <pwd.h>		// getpwuid
#include <grp.h>		// getgrid
#include <time.h>		// ctime
#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>

# define FLAGS 1
# define FILES 2

typedef struct stat t_stat;
typedef struct dirent t_dir;
typedef struct group t_grp;
typedef struct passwd t_pw;

// -ismScu
// -AF ?

typedef struct		s_file
{
	ino_t			inode;
	blkcnt_t		blocks;
	mode_t			mode;
	nlink_t			nlink;
	uid_t			uid;
	char			*uid_name;
	gid_t			gid;
	char			*gid_name;
	off_t			size;
	time_t			ctime;
	//dev_t			dev;
	char			*name;
	char			*path;
	struct s_file	*next;
}					t_file;

typedef struct		s_ls
{
	int				flag;
	int				flag_l;
	int				flag_R;
	int				flag_a;
	int				flag_r;
	int				flag_t;
	
	char			**word;
	DIR				*dir;
	t_dir			*lol;
	t_stat			sb;
	t_grp			*gr_gid;
	t_pw			*pw_uid;
	t_file			*args;
}					t_ls;


void	ft_parse_args(t_ls *ls, int argc, char **argv);
int		parse_keys(t_ls *ls, char *keys);

t_file	*next_file(char *argv);
t_file 	*new_file(t_ls *ls, char *name);

void	ft_exit();
void	free_split(char ***str);


void    print_list(t_file *head);


void	put_chmod(mode_t mode);
void	init_chmod(char *res, int chmod[3], mode_t mode);
char	get_type(mode_t mode);

void	free_list(t_file **head);

t_file	*sort_list(int (*cmp)(t_file*, t_file*), t_file *head);
t_file	*reverse_list(t_file *head);
int		cmp_size(t_file *left, t_file *right);
int		cmp_name(t_file *left, t_file *right);
int		cmp_time(t_file *left, t_file *right);



size_t	width_gid_uid(t_file *head, int flag);
size_t	width_nlink(t_file *head, int flag);


void	put_time(time_t ntime);

void	parse_flag_args(t_ls *ls, int argc, char **argv);
void	parse_file_args(t_ls *ls, int argc, char **argv);

#endif
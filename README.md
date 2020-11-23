# FT_LS
Recoding `ls` - the unix command for listing a directory.

## Project overview
### Mandatory part
* `l` - long listing format
* `R` - print subdirectories recursively
* `a` - print hidden files
* `r` - reverse sort
* `t` - sort by time (default last modified time)
* Manage `stickybit`, `setgid`, `setuid`
### Bonus part
* `c` - show last change time
* `u` - show last access time
* `i` - print file index
* `s` - print the allocated size of each file, in blocks
* `S` - sort by file size
* `f` - print without any sort
* `o` - hide group user
* `g` - hide owner user
* `1` - one column output
* Manage `multiple column` format (not flag `-l`)
* Manage print `multiple column` depending on `terminal size`

## How to download ?
	git clone https://github.com/fallard21/ft_ls.git ~/ft_ls
	cd ~/ft_ls

## How to use ?
1.  Build program with `make -C .`
2.  Use `./ft_ls`

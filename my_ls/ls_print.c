/*
** ls_print.c for my_ls in /home/chapui_s/travaux/my_ls
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Sat Nov 30 22:35:13 2013 chapui_s
** Last update Tue Mar 17 04:15:17 2015 chapui_s
*/

#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <dirent.h>
#include "my_ls.h"

char	*print_year(time_t *time_arg)
{
  char	*times;
  int	i;

  i = 0;
  times = ctime(time_arg);
  while (times[i] != ' ')
    i = i + 1;
  i = i + 1;
  times = times + i;
  i = 0;
  while (times[i++] != ' ');
  i = i + 1;
  while (times[i++] != ' ');
  times[i] = ' ';
  i = i + 1;
  while (times[i + 8] >= '0' && times[i + 8] <= '9')
  {
    times[i] = times[i + 8];
    i = i + 1;
  }
  times[i] = 0;
  return (times);
}

int		print_device(t_max_size *max, struct stat *res_stat,
			     char *file_name, int g)
{
  struct passwd	*info_uid;
  struct group	*info_grp;

  info_uid = getpwuid(res_stat->st_uid);
  info_grp = getgrgid(res_stat->st_gid);
  if (g == 0)
  {
    my_printf(" %*d %-*s %-*s %4d, %3d %s %s",
	      max->nb_links, res_stat->st_nlink, max->user, (info_uid) ?
	      (info_uid->pw_name) : (0), max->grp, (info_grp) ?
	      (info_grp->gr_name) : (0), major(res_stat->st_rdev),
	      minor(res_stat->st_rdev), cut_time(&res_stat->st_mtime),
	      cut_name(file_name));
  }
  else
  {
    my_printf(" %*d %-*s %4d, %3d %s %s",
	      max->nb_links, res_stat->st_nlink, max->grp, (info_grp) ?
	      (info_grp->gr_name) : (0), major(res_stat->st_rdev),
	      minor(res_stat->st_rdev), cut_time(&res_stat->st_mtime),
	      cut_name(file_name));
  }
  return (0);
}

int		print_file(t_max_size *max, struct stat *res_stat,
			   char *file_name, int g)
{
  struct passwd	*info_uid;
  struct group	*info_grp;

  info_uid = getpwuid(res_stat->st_uid);
  info_grp = getgrgid(res_stat->st_gid);
  if (g == 0)
  {
    my_printf(" %*d %-*s %-*s %*llu %s %s",
              max->nb_links, res_stat->st_nlink, max->user, (info_uid) ?
	      (info_uid->pw_name) : (0), max->grp, (info_grp) ?
	      (info_grp->gr_name) : (0), max->size_file, res_stat->st_size,
              cut_time(&res_stat->st_mtime), cut_name(file_name));
  }
  else
  {
    my_printf(" %*d %-*s %*llu %s %s",
	      max->nb_links, res_stat->st_nlink, max->grp, (info_grp) ?
	      (info_grp->gr_name) : (0), max->size_file, res_stat->st_size,
              cut_time(&res_stat->st_mtime), cut_name(file_name));
  }
  return (0);
}

int		print_directories(t_max_size *max, struct stat *res_stat,
			   char *file_name, int g)
{
  struct passwd	*info_uid;
  struct group	*info_grp;

  info_uid = getpwuid(res_stat->st_uid);
  info_grp = getgrgid(res_stat->st_gid);
  print_permissions(res_stat->st_mode);
  if (g == 0)
  {
    my_printf(" %*d %-*s %-*s %*llu %s %s",
              max->nb_links, res_stat->st_nlink, max->user, (info_uid) ?
	      (info_uid->pw_name) : (0), max->grp, (info_grp) ?
	      (info_grp->gr_name) : (0), max->size_file, res_stat->st_size,
              cut_time(&res_stat->st_mtime), file_name);
  }
  else
  {
    my_printf(" %*d %-*s %*llu %s %s",
	      max->nb_links, res_stat->st_nlink,
              max->grp, (info_grp) ? (info_grp->gr_name) : (0),
	      max->size_file, res_stat->st_size,
              cut_time(&res_stat->st_mtime), file_name);
  }
  return (0);
}

unsigned int	print_block_allocated(char *dir_name)
{
  unsigned int	block_allocated;
  struct stat	res_stat;
  struct dirent	*read_dir;
  char		*name_with_path;
  DIR		*dir;

  if ((dir = opendir(dir_name)) == NULL)
    return (-1);
  block_allocated = 0;
  while ((read_dir = readdir(dir)))
  {
    if ((name_with_path = str_cat(dir_name, read_dir->d_name)) == NULL)
      return (-1);
    if ((lstat(name_with_path, &res_stat)) == 0)
      if (read_dir->d_name[0] != '.')
	block_allocated += res_stat.st_blocks;
  }
  closedir(dir);
  my_printf("total %lld\n", block_allocated / 2);
  return (0);
}

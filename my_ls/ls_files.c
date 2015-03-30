/*
** ls_files.c for my_ls in /home/chapui_s/travaux/my_ls
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Sat Nov 30 22:46:51 2013 chapui_s
** Last update Tue Mar 17 22:29:05 2015 chapui_s
*/

#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <stdlib.h>
#include <dirent.h>
#include "my_ls.h"

int		prepare_info_file(t_options *options,
				  t_list_file *tmp,
				  t_max_size *max)
{
  struct stat	res_stat;
  struct passwd	*info_uid;
  struct group	*info_grp;

  (void)options;
  if ((tmp->infos = (t_infos_file*)my_malloc(sizeof(t_infos_file))) == NULL)
    return (-2);
  if ((lstat(tmp->name, &res_stat)) == -1)
  {
    disp_error(tmp->name, 1);
    return (-1);
  }
  tmp->infos->permissions = res_stat.st_mode;
  tmp->infos->size_nb_links = size_nb(res_stat.st_nlink);
  info_uid = getpwuid(res_stat.st_uid);
  tmp->infos->size_user = my_strlen(info_uid->pw_name);
  info_grp = getgrgid(res_stat.st_gid);
  tmp->infos->size_group = my_strlen(info_grp->gr_name);
  tmp->infos->size_file = size_nb(res_stat.st_size);
  tmp->infos->modif_date = ctime(&(res_stat.st_mtime));
  (major(res_stat.st_rdev) != 0) ? (max->size_file = 9) : (0);
  cut_name(tmp->name);
  get_max(max, tmp->infos);
  return (0);
}

int		disp_infos_file(t_options *options, t_list_file *file,
				t_max_size *max)
{
  struct stat	r_stat;

  if ((lstat(file->name, &r_stat)) == -1)
    return (0);
  if (options->d == 1 && options->l == 1)
    print_directories(max, &r_stat, file->name, options->g);
  else if ((options->l == 1 || options->g == 1) && major(r_stat.st_rdev) == 0)
  {
    print_permissions(file->infos->permissions);
    if ((print_file(max, &r_stat, file->name, options->g)) == -1)
      return (-1);
  }
  else if ((options->l == 1 || options->g == 1) && major(r_stat.st_rdev) != 0)
  {
    print_permissions(file->infos->permissions);
    if ((print_device(max, &r_stat, file->name, options->g)) == -1)
      return (-1);
  }
  else
    my_printf("%s", (options->d == 0) ? (cut_name(file->name)) : (file->name));
  if (options->l == 1 && S_ISLNK(r_stat.st_mode))
    write_lnk(&r_stat, file->name);
  my_putchar('\n');
  return (0);
}

int		ls_regulars_files(t_options *options,
				  t_list_file *list_file,
				  int is_cut)
{
  t_list_file	*tmp;
  t_max_size	*max;
  char		*name_tmp;

  max = (t_max_size*)0;
  if ((max = init_max(max)) == NULL)
    return (-1);
  tmp = list_file;
  while (tmp)
  {
    if (prepare_info_file(options, tmp, max) == -2)
      return (-1);
    tmp = tmp->next;
  }
  tmp = list_file;
  while (tmp)
  {
    (is_cut == 1) ? (name_tmp = cut_name(tmp->name)) : (name_tmp = tmp->name);
    if ((name_tmp[0] != '.' && name_tmp[1] != '.') || options->d == 1)
      if ((disp_infos_file(options, tmp, max)) == -1)
	return (-1);
    tmp = tmp->next;
  }
  free(max);
  return (0);
}

int		ls_files_in_args(t_options *options, t_list_file *list_file)
{
  t_list_file	*tmp;
  t_list_file	*files;
  struct stat	res_stat;
  int		nb_good_files;

  tmp = list_file;
  files = NULL;
  nb_good_files = 0;
  while (tmp)
  {
    lstat(tmp->name, &res_stat);
    if (!(S_ISDIR(res_stat.st_mode)))
    {
      if ((lstat(tmp->name, &res_stat)) != -1)
        if (!(S_ISDIR(res_stat.st_mode)))
          nb_good_files = nb_good_files + 1;
      if ((push_file(options, &files, tmp->name, res_stat.st_mtime)) == -1)
        return (-1);
    }
    tmp = tmp->next;
  }
  if ((ls_regulars_files(options, files, 1)) == -1)
    return (-1);
  free_list_file(&files);
  return (nb_good_files);
}

int		write_lnk(struct stat *res_stat, char *file_name)
{
  char		*link_name;

  link_name = (char*)my_malloc(sizeof(char) * res_stat->st_size + 1);
  if (link_name == NULL)
    return (-1);
  link_name[res_stat->st_size] = 0;
  if ((readlink(file_name, link_name, res_stat->st_size + 1)) == -1)
  {
    disp_error(file_name, 3);
    free(link_name);
    return (0);
  }
  my_putstr(" -> ");
  my_putstr(link_name);
  free(link_name);
  return (0);
}

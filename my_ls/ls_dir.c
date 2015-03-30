/*
** ls_dir.c for my_ls in /home/chapui_s/travaux/my_ls
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Sat Nov 30 22:56:49 2013 chapui_s
** Last update Tue Mar 17 04:05:46 2015 chapui_s
*/

#include <sys/types.h>
#include <dirent.h>
#include "my_ls.h"

void	print_dir_name(char *dir_name)
{
  int	i;

  i = 0;
  while (dir_name[i])
  {
    if (dir_name[i + 1] != '\0' || i == 0)
      my_putchar(dir_name[i]);
    i = i + 1;
  }
  if (i > 1 && dir_name[i - 1] != '.')
    my_putchar(dir_name[i - 1]);
  my_putchar(':');
  my_putchar('\n');
}

int	finish_ls_directory(t_options *options,
			    t_list_file *list_files_dir,
			    char *dir_name)
{
  if ((ls_regulars_files(options, list_files_dir, 1)) == -1)
    return (-1);
  if (options->R == 1)
    if ((recurs_ls(options, dir_name, list_files_dir)) == -1)
      return (-1);
  free_list_file(&list_files_dir);
  return (0);
}

int	gere_options_dir(t_options *options,
			 int is_first,
			 char *dir_name,
			 int test_args)
{
  if (is_first >= 2  && test_args > 1)
    my_putchar('\n');
  if (options->R == 1 || test_args > 1)
    print_dir_name(dir_name);
  if (options->l == 1)
    if ((signed)(print_block_allocated(dir_name)) == -1)
      return (-1);
  return (0);
}

int		ls_directory(t_options *options,
			     char *dir_name,
			     int is_first,
			     int test_args)
{
  struct dirent	*read_dir;
  struct stat	res_stat;
  t_list_file	*list_files_dir;
  char		*name_with_path;
  DIR		*dir;

  if ((dir = opendir(dir_name)) == NULL)
    return (-1);
  if ((gere_options_dir(options, is_first, dir_name, test_args)) == -1)
    return (-1);
  list_files_dir = NULL;
  while ((read_dir = readdir(dir)))
  {
    if ((name_with_path = str_cat(dir_name, read_dir->d_name)) == NULL)
      return (-1);
    lstat(name_with_path, &res_stat);
    if (push_file(options, &list_files_dir, name_with_path, res_stat.st_mtime)
        == -1)
      return (-2);
  }
  closedir(dir);
  if ((finish_ls_directory(options, list_files_dir, dir_name)) == -1)
    return (-2);
  return (0);
}

int		disp_the_directory(t_options *options,
				   t_list_file *list_file)
{
  t_list_file	*tmp;
  struct stat	res_stat;
  t_list_file	*file_and_dir;
  DIR		*dir;

  tmp = list_file;
  file_and_dir = NULL;
  while (tmp)
  {
    if ((dir = opendir(tmp->name)) == NULL
        || (lstat(tmp->name, &res_stat) == -1))
      disp_error(tmp->name, 2);
    else
      if ((push_file(options, &file_and_dir, tmp->name, res_stat.st_mtime))
          == -1)
        return (-1);
    tmp = tmp->next;
  }
  if ((ls_regulars_files(options, file_and_dir, 0)) == -1)
    return (-1);
  free_list_file(&file_and_dir);
  return (0);
}

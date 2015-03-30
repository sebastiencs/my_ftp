/*
** ls_print.c for my_ls in /home/chapui_s/travaux/my_ls
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Sat Nov 30 22:35:13 2013 chapui_s
** Last update Sun Dec  1 15:12:12 2013 chapui_s
*/

#include <sys/types.h>
#include "my_ls.h"

void	finish_permissions(mode_t st_mode)
{
  my_putchar((st_mode & S_IRGRP) ? ('r') : ('-'));
  my_putchar((st_mode & S_IWGRP) ? ('w') : ('-'));
  if ((st_mode & S_ISGID) && !(st_mode & S_IXGRP))
    my_putchar('S');
  else if ((st_mode & S_ISGID) && (st_mode & S_IXGRP))
    my_putchar('s');
  else
    my_putchar((st_mode & S_IXGRP) ? ('x') : ('-'));
  my_putchar((st_mode & S_IROTH) ? ('r') : ('-'));
  my_putchar((st_mode & S_IWOTH) ? ('w') : ('-'));
  if ((st_mode & S_ISVTX) && !(st_mode & S_IXOTH))
    my_putchar('T');
  else if ((st_mode & S_ISVTX) && (st_mode & S_IXOTH))
    my_putchar('t');
  else
    my_putchar((st_mode & S_IXOTH) ? ('x') : ('-'));
}

void	print_permissions(mode_t st_mode)
{
  if (S_ISDIR(st_mode) && !(S_ISLNK(st_mode)))
    my_putchar('d');
  else if (S_ISLNK(st_mode))
    my_putchar('l');
  else if (S_ISCHR(st_mode))
    my_putchar('c');
  else if (S_ISBLK(st_mode))
    my_putchar('b');
  else if (S_ISFIFO(st_mode))
    my_putchar('p');
  else if (S_ISSOCK(st_mode))
    my_putchar('s');
  else
    my_putchar('-');
  my_putchar((st_mode & S_IRUSR) ? ('r') : ('-'));
  my_putchar((st_mode & S_IWUSR) ? ('w') : ('-'));
  if ((st_mode & S_ISUID) && !(st_mode & S_IXUSR))
    my_putchar('S');
  else if ((st_mode & S_ISUID) && (st_mode & S_IXUSR))
    my_putchar('s');
  else
    my_putchar((st_mode & S_IXUSR) ? ('x') : ('-'));
  finish_permissions(st_mode);
}

/*
** ls_cut.c for my_ls in /home/chapui_s/travaux/my_ls
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Sat Nov 30 23:05:21 2013 chapui_s
** Last update Tue Mar 17 04:04:51 2015 chapui_s
*/

#include "my_ls.h"

char		*cut_time(time_t *time_arg)
{
  static int	time_actual;
  int		i;
  int		nb_two_dots;
  char		*times;
  static time_t	*test;

  i = 0;
  nb_two_dots = 0;
  if (time_actual == 0)
    time_actual = time(test);
  if ((((unsigned int)*time_arg + 15778463) <= (unsigned)time_actual)
      || (time_actual + 3600) <= *time_arg)
    return (print_year(time_arg));
  times = ctime(time_arg);
  while (times[i] != ' ')
    i = i + 1;
  times = times + i + 1;
  while (times[i] && nb_two_dots < 2)
  {
    if (times[i] == ':' && nb_two_dots == 1)
      times[i] = '\0';
    if (times[i++] == ':')
      nb_two_dots = nb_two_dots + 1;
  }
  return (times);
}

char	*cut_name(char *name)
{
  int	i;

  i = 0;
  if (name[1] == 0)
    return (name);
  while (name[i])
    i = i + 1;
  while (name[i] != '/' && i > 0)
    i = i - 1;
  if (i != 0 && name[i + 1] != '\0')
    return (name + i + 1);
  return (name);
}

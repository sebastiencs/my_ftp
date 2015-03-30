/*
** ls_utils.c for my_ls in /home/chapui_s/travaux/my_ls
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Mon Nov 25 18:46:34 2013 chapui_s
** Last update Sun Dec  1 00:00:59 2013 chapui_s
*/

#include <stdlib.h>
#include <unistd.h>

void	my_putchar(char c)
{
  write(1, &c, 1);
}

void	my_putstr(char *str)
{
  int	i;

  i = 0;
  if (str == NULL)
    return ;
  while (str[i])
  {
    my_putchar(str[i]);
    i = i + 1;
  }
}

void	my_putchar_error(char c)
{
  write(2, &c, 1);
}

void	my_putstr_error(char *str)
{
  int	i;

  i = 0;
  while (str[i])
  {
    my_putchar_error(str[i]);
    i = i + 1;
  }
}

int	size_nb(unsigned long long nb)
{
  int	size;

  size = 1;
  while (nb >= 10)
  {
    nb = nb / 10;
    size = size + 1;
  }
  return (size);
}

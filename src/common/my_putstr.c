/*
** my_putstr.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 19 16:21:08 2015 chapui_s
** Last update Thu Mar 19 16:21:41 2015 chapui_s
*/

#include "common.h"

int		my_putstr(char *s)
{
  write(1, s, strlen(s));
  return (0);
}

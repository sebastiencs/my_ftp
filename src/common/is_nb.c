/*
** is_nb.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 19 16:02:10 2015 chapui_s
** Last update Thu Mar 19 16:02:31 2015 chapui_s
*/

#include "common.h"

int		is_nb(char *s)
{
  if (!s)
    return (-1);
  while (*s)
  {
    if (*s < '0' || *s > '9')
      return (-1);
    s += 1;
  }
  return (1);
}

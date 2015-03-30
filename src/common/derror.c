/*
** derror.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Mar 16 07:37:20 2015 chapui_s
** Last update Mon Mar 16 09:27:32 2015 chapui_s
*/

#include <stdio.h>

int			derrorn(const char *s)
{
  puts(s);
  return (-1);
}

int			derror(const char *s)
{
  perror(s);
  return (-1);
}

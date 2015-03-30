/*
** my_malloc.c for my_ls in /home/chapui_s/travaux/my_ls
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Mon Nov 25 21:32:02 2013 chapui_s
** Last update Tue Mar 17 04:14:45 2015 chapui_s
*/

#include <stdlib.h>
#include "my_ls.h"

void	*my_malloc(size_t size)
{
  void	*ptr;

  ptr = malloc(size);
  if (ptr == NULL)
    my_putstr_error("Could not alloc\n");
  return (ptr);
}

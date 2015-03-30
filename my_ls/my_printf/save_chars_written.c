/*
** save_chars_written.c for my_printf in /home/chapui_s/travaux/my_printf/new
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Sun Nov 17 11:25:57 2013 chapui_s
** Last update Sat Nov 30 12:32:22 2013 chapui_s
*/

#include "my_printf.h"

unsigned int	save_chars(t_tmp_arg *tmp, unsigned int chars_to_save)
{
  *(tmp->chars_to_save) = chars_to_save;
  return (0);
}

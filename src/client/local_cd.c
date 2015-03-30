/*
** local_cd.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar 22 15:46:55 2015 chapui_s
** Last update Sun Mar 22 15:57:16 2015 chapui_s
*/

#include "client.h"

int		local_cd(t_client *client, char *true_cmd, char *param)
{
  char		buffer[PATH_MAX];

  (void)true_cmd;
  (void)client;
  if (!chdir(param))
  {
    memset(buffer, 0, PATH_MAX);
    getcwd(buffer, PATH_MAX - 1);
    printf("\"%s\"\n", buffer);
  }
  else
  {
    perror("error");
  }
  return (0);
}

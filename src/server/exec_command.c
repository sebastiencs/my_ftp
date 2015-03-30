/*
** exec_command.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar 17 22:25:34 2015 chapui_s
** Last update Tue Mar 17 22:25:53 2015 chapui_s
*/

#include "server.h"

t_cmd			g_cmd[] =
{
  { "USER ", set_user, 0 },
  { "PASS ", password, 0 },
  { "PASV\r\n", enter_passive_mode, 1 },
  { "LIST ", list_directory, 1 },
  { "LIST\r\n", list_directory, 1 },
  { "CWD ", change_dir, 1 },
  { "CWD\r\n", change_dir, 1 },
  { "CDUP\r\n", change_dir_up, 1 },
  { "QUIT\r\n", quit, 1 },
  { "PWD\r\n", get_dir, 1 },
  { "DELE ", delete, 1 },
  { "HELP ", help, 1 },
  { "RETR ", send_file, 1 },
  { "STOR ", receive_file, 1 },
  { "TYPE ", get_type, 1 },
  { "HELP\r\n", help, 1 },
  { "NOOP\r\n", noop, 1 },
  { "SYST\r\n", send_syst, 0 },
  { (char*)0, (void*)0, 0 }
};

char			*clean_param(char *s)
{
  int			i;

  i = strlen(s);
  if (i >= 2)
  {
    if (s[i - 1] == '\n' && s[i - 2] == '\r')
      s[i - 2] = 0;
  }
  return (s);
}

int			check_syntax_param(t_user *user, char *s)
{
  int			i;

  if (!s)
    return (-1);
  i = strlen(s);
  if (i > 2 && (s[i - 1] != '\n' || s[i - 2] != '\r'))
  {
    send_reply(user->fd, 501, (char*)0);
    return (-1);
  }
  return (0);
}

int			exec_command(t_user *user)
{
  char			*param;
  int			i;

  i = 0;
  if (check_syntax_param(user, user->buffer) == -1)
    return (0);
  while (g_cmd[i].name
	 && strncmp(g_cmd[i].name, user->buffer, strlen(g_cmd[i].name)))
    i += 1;
  if (g_cmd[i].name)
  {
    if ((g_cmd[i].need_logged_in == 1 && user->status == LOGGED_IN)
	|| g_cmd[i].need_logged_in == 0)
    {
      param = clean_param(user->buffer + strlen(g_cmd[i].name));
      (g_cmd[i].func)(user, param);
    }
    else
      send_reply(user->fd, 530, "Not logged in.");
  }
  else
    send_reply(user->fd, 502, (char*)0);
  return (0);
}

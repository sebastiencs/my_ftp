/*
** client.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Mar 16 06:36:56 2015 chapui_s
** Last update Sun Mar 22 17:54:32 2015 chapui_s
*/

#include "client.h"

t_cmds		cmds[] =
{
  { "LIST", "ls", list_dir },
  { "USER", "user", send_user },
  { "PASS", "pass", send_password },
  { "CWD", "cd", change_dir },
  { "CDUP", "cdup", change_dir_up },
  { "QUIT", "quit", quit_client },
  { "QUIT", "close", quit_client },
  { "DELE", "rm", delete_file },
  { "PWD", "pwd", get_cur_dir },
  { "HELP", "help", help },
  { "NOOP", "noop", noop },
  { "RETR", "get", get_file },
  { "STOR", "put", put_file },
  { "LCD", "lcd", local_cd },
  { "LPWD", "lpwd", local_pwd },
  { "LLS", "lls", local_ls },
  { (char*)0, (char*)0, NULL }
};

char		*find_cmd(char *buffer,
			  int (**fct)(t_client *, char*, char *),
			  char **param)
{
  int		i;

  i = 0;
  while (cmds[i].read_cmd
	 && strncmp(buffer, cmds[i].read_cmd, strlen(cmds[i].read_cmd)))
  {
    i += 1;
  }
  *fct = (void*)0;
  if (cmds[i].read_cmd)
  {
    *fct = cmds[i].func;
    *param = buffer + strlen(cmds[i].read_cmd) + 1;
  }
  return (cmds[i].true_cmd);
}

int		exec_command(t_client *client, char *buffer)
{
  int		(*fct)(t_client *, char *, char *);
  char		*true_cmd;
  char		*param;

  if ((true_cmd = find_cmd(buffer, &fct, &param)) && fct)
  {
    fct(client, true_cmd, param);
  }
  else
  {
    printf("Unknown command '%s'\n", client->tab_cmd[0]);
  }
  return (0);
}

void		free_tab(char **tab)
{
  int		i;

  i = 0;
  while (tab && tab[i])
  {
    free(tab[i]);
    i += 1;
  }
  free(tab);
}

int		talk_to_server(t_client *client)
{
  char		buffer[1024];

  while (client->run)
  {
    my_putstr("my_ftp > ");
    if (get_command(client, buffer) == -1)
    {
      return (-1);
    }
    if (strlen(buffer) > 0 && exec_command(client, buffer) == -1)
    {
      return (-1);
    }
    free_tab(client->tab_cmd);
  }
  return (0);
}

int		main(int argc, char **argv)
{
  t_client	client;
  int		value;

  memset(&client, 0, sizeof(client));
  if (get_info_client(&client, argc, argv) == -1)
    return (-1);
  if (connect_to_server(&client) == -1)
    return (-1);
  manage_sigint(&client);
  signal(SIGINT, catch_sigint);
  client.run = 1;
  client.debug = 1;
  client.mode = PASSIVE;
  if (identification(&client) == -1)
    return (-1);
  value = talk_to_server(&client);
  return (value);
}

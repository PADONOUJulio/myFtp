/*
** EPITECH PROJECT, 2022
** zrfegd
** File description:
** ezrfe
*/

#include "myftp.h"

void add_link(int i, list **ls)
{
    list *tmp = malloc(sizeof(list));
    tmp->fds = i;
    tmp->link = false;
    tmp->next = NULL;
    tmp->auth = false;
    tmp->pass = false;
    tmp->inter = false;
    tmp->str = malloc(sizeof(int) * PATH_MAX);
    if (*ls == NULL)
    {
        *ls = tmp;
        return;
    }
    else
    {
        list *c = *ls;
        while (c->next != NULL)
        {
            c = c->next;
        }
        c->next = tmp;
    }
}

void init(list **lst)
{
    for (int i = 0; i < 30; i++)
    {
        add_link(0, lst);
    }
}

void print(list **lst)
{
    list *tmp = *lst;
    while (tmp != NULL)
    {
        printf("%d\n", tmp->fds);
        tmp = tmp->next;
    }
}

int readd(int n_fds, char **buffer)
{
    char c;
    int i = 0, n;
    char *str = *buffer;
    while ((n = read(n_fds, &c, 1)) == 1)
    {
        if (n == 0)
            return 0;
        if (c == '\0' || c == '\n')
            break;
        str[i] = c;
        i++;
    }
    return 1;
}

int check_cmd(char *str)
{
    int e = 0;
    int t[14];

    t[0] = strncasecmp("USER", str, 4) == 0 ? 1 : 2;
    t[1] = strncasecmp("PASS", str, 4) == 0 ? 1 : 2;
    t[2] = strncasecmp("CWD", str, 3) == 0 ? 1 : 2;
    t[3] = strncasecmp("CDUP", str, 4) == 0 ? 1 : 2;
    t[4] = strncasecmp("QUIT", str, 4) == 0 ? 1 : 2;
    t[5] = strncasecmp("DELE", str, 4) == 0 ? 1 : 2;
    t[6] = strncasecmp("PWD", str, 3) == 0 ? 1 : 2;
    t[7] = strncasecmp("PASV", str, 4) == 0 ? 1 : 2;
    t[8] = strncasecmp("PORT", str, 4) == 0 ? 1 : 2;
    t[9] = strncasecmp("HELP", str, 4) == 0 ? 1 : 2;
    t[10] = strncasecmp("NOOP", str, 4) == 0 ? 1 : 2;
    t[11] = strncasecmp("RETR", str, 4) == 0 ? 1 : 2;
    t[12] = strncasecmp("STOR", str, 4) == 0 ? 1 : 2;
    t[13] = strncasecmp("LIST", str, 4) == 0 ? 1 : 2;
    while (e < 14)
    {
        if (t[e] == 1)
            return 1;
        else
            e++;
    }
    return 0;
}
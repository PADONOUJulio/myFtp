/*
** EPITECH PROJECT, 2022
** zer
** File description:
** ezrfd
*/

#include "myftp.h"

static int socket_;
static struct sockaddr_in address;

void set_struct(int port, struct sockaddr_in *ad)
{
    struct sockaddr_in address;
    (*ad).sin_family = AF_INET;
    (*ad).sin_addr.s_addr = INADDR_ANY;
    (*ad).sin_port = htons(port);
}

int create_socket(int port)
{
    int opt = true;
    int addrlen, new_socket, activity, i, valread, sd;
    char buffer[1025];
    if ((socket_ = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    set_struct(port, &address);
    if (bind(socket_, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(socket_, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    return (socket_);
}

char *get_path()
{
    char *cwd = malloc(sizeof(char) * PATH_MAX);
    if (getcwd(cwd, sizeof(char) * PATH_MAX) != NULL)
    {
        return cwd;
    }
    else
    {
        perror("getcwd() error");
    }
    return NULL;
}

fd_set accpt(int *activity, int max, int new_socket, char *buffer, char *message, int addrlen, fd_set readfds, list **lst)
{
    if ((new_socket = accept(socket_, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    else
    {
        write(new_socket, "220 Welcome\r\n", 13);
        list *tmp = *lst;
        bool e = false;
        for (; tmp != NULL; tmp = tmp->next)
        {
            if (tmp->fds == 0)
            {
                tmp->fds = new_socket;
                tmp->link = true;
                strcpy(tmp->str, message);
                e = true;
                break;
            }
        }
    }
    return readfds;
}

int core(int wx, char **av)
{
    list *lst = NULL;
    init(&lst);
    int opt = true;
    int addrlen = sizeof(address);
    fd_set readfds;
    int max, sd, activity, new_socket, valread;
    char buffer[1025];
    char *curr_dir;
    if (enter_dir(&curr_dir,av) == 84 || wx <= 0)
        return 84;
    create_socket(wx);
    while (1)
    {
        char *cmd = malloc(1024);
        FD_ZERO(&readfds);
        FD_SET(socket_, &readfds);
        max = socket_;
        list *tmp = lst;
        for (; tmp != NULL; tmp = tmp->next)
        {
            sd = tmp->fds;
            if (sd > 0)
                FD_SET(sd, &readfds);
            if (sd > max)
                max = sd;
        }
        tmp = NULL;
        tmp = lst;
        activity = select(max + 1, &readfds, NULL, NULL, NULL);
        if ((activity < 0) && (errno != EINTR))
        {
            printf("select error");
        }
        if (FD_ISSET(socket_, &readfds))
        {
            readfds = accpt(&activity, max, new_socket, buffer, curr_dir, addrlen, readfds, &lst);
        }
        else
        {
            for (; tmp != NULL; tmp = tmp->next)
            {
                sd = tmp->fds;
                if (FD_ISSET(sd, &readfds))
                {
                    if (valread = readd(tmp->fds, &cmd) == 1)
                    {

                        handle_com(cmd, tmp);
                        free(cmd);
                    }
                    else
                    {
                        printf("close\n");
                        close(sd);
                    }
                }
            }
        }
    }
    return 0;
}

int main(int ac, char **av)
{
    return (core(atoi(av[1]), av));
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct list {
	char *str;
	int q;
	struct list *next;
};

char *make_buff_zero(char *buff, int j)
{
	int i;
	for (i = 0; i <= j; i++)
		buff[i] = '\0';
	return buff;
}

char *make_buff_bigger(char *buff)
{
	char *new_buff = malloc(sizeof(char) * (strlen(buff)) * 2);
	int i;
	for (i = 0; i < strlen(buff); i++)
		new_buff[i] = buff[i];
	return new_buff;
}

char *add_to_buff(char *buff, int c, int i)
{
	if (i == strlen(buff) - 1)
		buff = make_buff_bigger(buff);
	buff[i] = c;
	return buff;
}

int cmprstr(char *str1, char *str2)
{
	int i;
	if (strlen(str1) != strlen(str2))
		return 0;
	for (i = 0; i < strlen(str1); i++)
		if (str1[i] != str2[i])
			return 0;
	return 1;
}

int in_list(struct list *head, char *str)
{
	struct list *tmp = head;
	while (tmp) {
		if (cmprstr(tmp->str, str))
			return 1;
		tmp = tmp->next;
	}
	return 0;
}

struct list *add_to_list(struct list *head, char *buff)
{
	struct list *tmp;
	if (!in_list(head, buff)) {
		tmp = malloc(sizeof(*tmp));
		tmp->str = malloc(sizeof(char) * strlen(buff));
		strcpy(tmp->str, buff);
		tmp->q = 1;
		tmp->next = head;
		return tmp;
	} else {
		tmp = head;
		while (!cmprstr(tmp->str, buff))
			tmp = tmp->next;
		(tmp->q)++;
		return head;
	}
}

struct list *find_max(struct list *head)
{
	struct list *tmp = head;
	struct list *res = malloc(sizeof(*res));
	res->str = malloc(sizeof(char));
	res->q = 0;
	res->next = NULL;
	while (tmp) {
		if (tmp->q > res->q) {
			res->q = tmp->q;
			free(res->str);
			res->str = malloc(sizeof(char) * strlen(tmp->str));
			strcpy(res->str, tmp->str);
		}
		tmp = tmp->next;
	}
	return res;
}

void start(struct list *head)
{
	//struct list *tmp = head;
	struct list *lst = malloc(sizeof(*lst));
	int i = 10;
	while (i--) {
		lst = find_max(head);
		printf("%s --- %d\b", lst->str, lst->q);
	}
}

void print_list(struct list *head)
{
	if (!head)
		return;
	else if (!head->next)
		printf("%s, %d\n", head->str, head->q);
	else {
		print_list(head->next);
		printf("%s, %d\n", head->str, head->q);
	}

}

int main()
{
	int c, i = 0, n = 8;
	char *buff = malloc(sizeof(char) * n);
	struct list *head = NULL;
	buff = make_buff_zero(buff, n);
	while ((c = getchar()) != EOF) {
		if ((c == ' ') || (c == '\n') || (c == '\t')) {
			if (i)
				head = add_to_list(head, buff);
			buff = make_buff_zero(buff, i);
			i = 0;
		} else
			buff = add_to_buff(buff, c, i++);
	}
	if (buff[0] != '\0')
		head = add_to_list(head, buff);
	printf("\n");
	start(head);
	print_list(head);
	return 0;
}
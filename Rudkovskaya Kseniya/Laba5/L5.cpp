#include <stdio.h>
#include <malloc.h>

/* Stack and function */
struct stack
{
	char data;
	struct stack* next;
};

struct stack* stack_push(struct stack* h, char ndata)
{
	struct stack* temp = NULL;

	if (!(temp = (struct stack*)malloc(sizeof(struct stack))))
	{
		printf("not enought memory(stack)");
	}

	temp->data = ndata;
	temp->next = h;
	h = temp;
	return h;
}

struct stack* stack_add_few_node(struct stack* h, char* str)
{
	int i = 0;

	while (str[i])
	{
		h = stack_push(h, str[i++]);
	}

	return h;
}

struct stack* stack_pop(struct stack* h)
{
	if (!h)
	{
		printf("it's empty");
		return NULL;
	}

	struct stack* temp = h;
	h = h->next;
	free(temp);
	return h;
}

void stack_output(struct stack* h)
{
	struct stack* temp = h;

	if (!h)
	{
		printf("empty");
		return;
	}

	while (temp)
	{
		printf("%c", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

struct stack* add_stack_to_stack(struct stack* h, struct stack* additional)
{
	struct stack* p = additional;

	while (p)
	{
		h = stack_push(h, p->data);
		p = p->next;
	}

	return h;
}

struct stack* stack_free(struct stack* h)
{
	struct stack* temp;

	while (h)
	{
		temp = h;
		h = h->next;
		free(temp);
	}

	return h;
}

struct stack* stack_sort(struct stack* h)
{
	struct stack* temp_stack = NULL;

	while (h)
	{
		char temp = h->data;
		h = stack_pop(h);

		while (temp_stack && temp_stack->data < temp)
		{
			h = stack_push(h, temp_stack->data);
			temp_stack = stack_pop(temp_stack);
		}
		temp_stack = stack_push(temp_stack, temp);
	}
	return temp_stack;
}

/* Bidirectional cyclic list and functions*/
struct list
{
	struct stack* data;
	struct list* next;
	struct list* prev;
};

struct list* list_add(struct list* lst, struct stack* data)
{
	struct list* temp = NULL, * p = NULL;
	if (!(temp = (struct list*)malloc(sizeof(struct list))))
	{
		printf("not enough memory(list)");
	}

	temp->data = data;

	if (!lst)
	{
		lst = temp;
		lst->next = lst;
		lst->prev = lst;
	}
	else
	{
		p = lst->next;
		lst->next = temp;
		temp->next = p;
		temp->prev = lst;
		p->prev = temp;
	}

	return temp;
}

struct list* list_del(struct list* lst)
{
	lst->prev->next = lst->next;
	lst->next->prev = lst->prev;
	stack_free(lst->data);
	free(lst);
	return lst->prev;
}

void list_output(struct list* lst)
{
	struct list* p;
	p = lst;

	do
	{
		stack_output(p->data);
		p = p->next;
	} while (p != lst);
}

struct list* list_free(struct list* lst, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		lst = list_del(lst);
	}

	return lst;
}

struct stack* lists_stacks_to_stack(struct list* lst, struct stack* st)
{
	struct list* p;
	p = lst;

	do
	{
		st = add_stack_to_stack(st, p->data);
		p = p->next;
	} while (p != lst);

	return st;
}

int main(void)
{
	printf("\n");
	struct list* lst = NULL;
	int amount = 3;
	char** word = NULL;

	if (!(word = (char**)malloc(amount * sizeof(char*))))
	{
		printf("not enough memory");
		return -1;
	}

	struct stack* st;

	int i;
	for (i = 0; i < amount; i++)
	{
		word[i] = "hello" + i;
		st = NULL;
		st = stack_add_few_node(st, word[i]);
		st = stack_sort(st);
		stack_output(st);
		lst = list_add(lst, st);
	}

	free(word);

	struct stack* res = NULL;
	res = lists_stacks_to_stack(lst, res);
	res = stack_sort(res);
	stack_output(res);

	list_free(lst, amount);
	stack_free(res);
	return 0;
}
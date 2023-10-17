#include "shell.h"
/**
 * add_node - adds node at star
 * @head: pointer to head
 * @str: field of node
 * @num: index of node
 *
 * Return: list size
 */
list_t *add_node(list_t **head, const char *str, int num)
{
list_t *new;

if (!head)
return (NULL);
new = malloc(sizeof(list_t));
if (!new)
return (NULL);
_memset((void *)new, 0, sizeof(list_t));
new->num = num;
if (str)
{
new->str = _strdup(str);
if (!new->str)
{
free(new);
return (NULL);
}
}
new->next = *head;
*head = new;
return (new);
}
/**
 * add_node_end - adds node at end
 * @head: pointer to head
 * @str: field in node
 * @num:index of node
 *
 * Return: list size
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
list_t *new_nd, *node;

if (!head)
return (NULL);
node = *head;
new_nd = malloc(sizeof(list_t));
if (!new_nd)
return (NULL);
_memset((void *)new_nd, 0, sizeof(list_t));
new_nd->num = num;
if (str)
{
new_nd->str = _strdup(str);
if (!new_nd->str)
{
free(new_nd);
return (NULL);
}
}
if (node)
{
while (node->next)
node = node->next;
node->next = new_nd;
}
else
*head = new_nd;
return (new_nd);
}
/**
 * print_list_str - print only str elements
 * @h: first node pointer
 *
 * Return: list size
 */
size_t print_list_str(const list_t *h)
{
size_t w = 0;

while (h)
{
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
w++;
}
return (w);
}
/**
 * delete_node_at_index - at specific index node is deletd
 * @head: pointer to head
 * @index: node index to delete
 *
 * Return: success 1
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
list_t *node, *prev_nd;
unsigned int w = 0;

if (!head || !*head)
return (0);
if (!index)
{
node = *head;
*head = (*head)->next;
free(node->str);
free(node);
return (1);
}
node = *head;
while (node)
{
if (w == index)
{
prev_nd->next = node->next;
free(node->str);
free(node);
return (1);
}
w++;
prev_nd = node;
node = node->next;
}
return (0);
}
/**
 * free_list - all nodes get freed
 * @head_ptr: pointer to head
 *
 * Return: nothing
 */
void free_list(list_t **head_ptr)
{
list_t *node, *next_nd, *head;

if (!head_ptr || !*head_ptr)
return;
head = *head_ptr;
node = head;

while (node)
{
next_nd = node->next;
free(node->str);
free(node);
node = next_nd;
}

*head_ptr = NULL;
}

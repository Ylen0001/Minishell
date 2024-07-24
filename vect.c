/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:00:05 by ylenoel           #+#    #+#             */
/*   Updated: 2024/07/24 12:14:59 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct t_list {
	char *data;
	struct t_list *next;
} s_list;

typedef struct t_vector { 
	char **data;
	size_t size;
	size_t capacity;
} s_vector;

t_vector *init_vector(void) {
	t_vector *self = malloc(1 * sizeof(t_vector));
	self->data = malloc(10 * sizeof(char *));
	self->size = 0;
	self->capacity = 10;
}


void list_remove(t_list **list) {
	t_list current = *list;

	while (current) {
		cureent->next;
	}
	free(current);
}

void vector_append(t_vector *self, char *data) {
	if (size + 1 > capacity) {
		self->capacity *= 2;
		realloc(self->data, self->capacity);
	}
	self->data[size] = data;
	self->size += 1;
}

void vector_remove(t_vector *self) {
	free(self->data[size]);
	self->data[size] = NULL;
	self->size -= 1;
}

int main(void) {
	t_list list;

	list = list_init();

	t_vector *vect;

	vect = init_vector();
	vector_append(vect, "salope");

	list_append(&list, list_new("data"));
	list_remove(&list);

	int i = 0;

	while (i < vect->size) {
		vect->data[i];
	}


}

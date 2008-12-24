//Maciej Pacut
#pragma once
#include <malloc.h>
#include <stdio.h>

struct List
{
  struct List* tl;
  int data;
};

struct List* concat(struct List* old_head);

void iterate(struct List* lst, void (*fun)(struct List*));
void printList(struct List* lst);

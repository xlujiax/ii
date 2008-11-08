#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

struct List
{
  struct List* tl;
  int data;
};

struct List* concat(struct List* old_head);
struct List* reverse(struct List* hd);
struct List* append(struct List* a, struct List* b);
void iterate(struct List* lst, void (*fun)(struct List*));
struct List* filter(struct List* hd, int (*fun)(int, int), int param);
void print_int(struct List* lst);
void cleanup(struct List* lst);

void print_list(struct List*);
struct List* generate_lst(int sz);

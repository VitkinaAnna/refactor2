#pragma once

#include <stdbool.h>

enum attribute_meta_type {
  meta_integer,
  meta_float,
  meta_double,
  meta_char,
};

struct attribute_type {
  enum attribute_meta_type meta_type;
  unsigned size; // 0 if not set
};

struct attribute {
  char *name;
  struct attribute_type type;
};

struct attribute_list {
  struct attribute head;
  struct attribute_list *tail;
};

struct attribute_name_list {
  char *head;
  struct attribute_name_list *tail;
};

struct dataset {
  char *name;
  bool is_owner_single;
  char *owner_name;
  bool is_member_single;
  char *member_name;
  struct attribute_name_list *unique_attributes;
  struct attribute_list *attribute_list;
  char *reverse_name; // NULL if not set
};

struct dataset_list {
  struct dataset head;
  struct dataset_list *tail;
};

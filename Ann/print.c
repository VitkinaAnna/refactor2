#include <stdio.h>
#include "dataset.h"

#include "print.h"

void print_dataset(struct dataset dataset) {
  printf("dataset:\n");
  printf("  name: %s\n", dataset.name);
  printf("  is_owner_single: %hhd\n", dataset.is_owner_single);
  printf("  owner_name: %s\n", dataset.owner_name);
  printf("  is_member_single: %hhd\n", dataset.is_member_single);
  printf("  member_name: %s\n", dataset.member_name);
  printf("  unique_attributes:\n");
  for (struct attribute_name_list *unique_attributes_iterator = dataset.unique_attributes; unique_attributes_iterator != NULL; unique_attributes_iterator = unique_attributes_iterator->tail) {
      char *attribute_name = unique_attributes_iterator->head;
      printf("    * %s\n", attribute_name);
  }
  printf("  attribute_list:\n");
  for (struct attribute_list *attribute_list_iterator = dataset.attribute_list; attribute_list_iterator != NULL; attribute_list_iterator = attribute_list_iterator->tail) {
      struct attribute attribute = attribute_list_iterator->head;
      printf("    * name: %s\n", attribute.name);
      printf("      type: meta_type:  %d\n", attribute.type.meta_type);
      printf("      type: size:  %u\n", attribute.type.size);
  }
  printf("  reverse_name: %s\n", dataset.reverse_name == NULL ? "NULL" : dataset.reverse_name);
  printf("\n");
}

void print_dataset_list(struct dataset_list *dataset_list) {
  printf("--- dataset_list: ---\n");
  for(struct dataset_list *dataset_list_iterator = dataset_list; dataset_list_iterator != NULL; dataset_list_iterator = dataset_list_iterator->tail)
    print_dataset(dataset_list_iterator->head);
  printf("---------------------\n");
}

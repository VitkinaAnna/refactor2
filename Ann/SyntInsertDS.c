#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataset.h"
#include "parser.tab.h"

#include "SyntInsertDS.h"

// insert `new_dataset` into `dataset_list`
// return value:
// * true if inserted,
// * false if there is already a dataset with such name
bool SyntInsertDS_single(struct dataset_list **dataset_list, struct dataset new_dataset) {
  for(struct dataset_list *dataset_list_iterator = *dataset_list; dataset_list_iterator != NULL; dataset_list_iterator = dataset_list_iterator->tail)
    if (!strcmp(dataset_list_iterator->head.name, new_dataset.name)) {
      //fprintf(stderr, "SyntInsertDS_single: dataset '%s' is already present\n", new_dataset.name);
      //return false;
    }
  struct dataset_list *new_item = malloc(sizeof(struct dataset_list));
  new_item->head = new_dataset;
  new_item->tail = *dataset_list;
  *dataset_list = new_item;
  fprintf(stderr, "SyntInsertDS_single: dataset '%s' have been successfully inserted\n", new_dataset.name);
  return true;
}

// insert each dataset from `new_dataset_list` into `dataset_list`
// return value: number of inserted datasets
int SyntInsertDS_multiple(struct dataset_list **dataset_list, struct dataset_list *new_dataset_list) {
  int result = 0;
  for(struct dataset_list *new_dataset_list_iterator = new_dataset_list; new_dataset_list_iterator != NULL; new_dataset_list_iterator = new_dataset_list_iterator->tail)
    if (SyntInsertDS_single(dataset_list, new_dataset_list_iterator->head))
      result++;
  fprintf(stderr, "SyntInsertDS_multiple: successfully inserted %d datasets\n", result);
  return result;
}

extern FILE *yyin;

// read new datasets from file `filename` and insert them into `dataset_list`
// return value:
// * -2 if failed to open file,
// * -1 if failed to parse file contents,
// * otherwise number of inserted datasets
int SyntInsertDS_file(struct dataset_list **dataset_list, const char *filename) {
  fprintf(stderr, "SyntInsertDS_file: reading datasets from file '%s'\n", filename);
  yyin = fopen(filename, "r");
  if (yyin == NULL) {
    perror(filename);
    return -2;
  }
  struct dataset_list *new_dataset_list;
  if (yyparse(&new_dataset_list)) {
    return -1;
  }
  fclose(yyin);
  yyin = stdin;
  return SyntInsertDS_multiple(dataset_list, new_dataset_list);
}
#include <stdio.h>
#include "dataset.h"

void yyerror(struct dataset_list **dataset_list, const char *message) {
  fprintf(stderr, "%s\n", message);
}

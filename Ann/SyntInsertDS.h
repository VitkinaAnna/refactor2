#pragma once

#include "dataset.h"

// insert `new_dataset` into `dataset_list`
// return value:
// * true if inserted,
// * false if there is already a dataset with such name
bool SyntInsertDS_single(struct dataset_list **dataset_list, struct dataset new_dataset);

// insert each dataset from `new_dataset_list` into `dataset_list`
// return value: number of inserted datasets
int SyntInsertDS_multiple(struct dataset_list **dataset_list, struct dataset_list *new_dataset_list);

// read new datasets from file `filename` and insert them into `dataset_list`
// return value:
// * -2 if failed to open file,
// * -1 if failed to parse file contents,
// * otherwise number of inserted datasets
int SyntInsertDS_file(struct dataset_list **dataset_list, const char *filename);
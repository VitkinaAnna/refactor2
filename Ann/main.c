#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Include bool type
#include "dataset.h"
#include "parser.tab.h"
#include "SyntInsertDS.h"
#include "print.h"

// Usage: ./main file1 file2 ...

struct unnamed_attribute {
    enum attribute_meta_type meta_type;
    unsigned index;
    struct unnamed_attribute *next;
};

struct dataset_type {
    char *name;
    bool is_owner_single;
    char *owner_name;
    bool is_member_single;
    char *member_name;
    struct attribute_name_list *unique_attributes; // List of unique attributes
    struct unnamed_attribute *un_attributes; // List of unnamed attributes
    char *reverse_name;
    int num_datasets;
    struct dataset_list *datasets; // Linked list of datasets
};

struct dataset_type_list {
    struct dataset_type *head;
    struct dataset_type_list *next;
};

// Function prototypes
void Save_DS(struct dataset_type *type, struct dataset *dataset);
void FInsertDS(struct dataset_type_list **head, struct dataset_type *type);
void print_dataset_type_list(struct dataset_type_list *list);

#include <stdbool.h>

// Function to compare two dataset types
bool compare_dataset_types(struct dataset_type type1, struct dataset_type type2);


int main(int argc, char **argv) {
    struct dataset_list *dataset_list = NULL;
    struct dataset_list *second_dataset_list = NULL;
    struct dataset_type_list *dataset_type_list = NULL;

    // Parse dataset files and build dataset lists
    for (int i = 1; i < argc; i++) {
        // Parse the first file normally
        if (i == 1) {
            SyntInsertDS_file(&dataset_list, argv[i]);
        }
        // For the second file, parse and add dataset types without checking for existing ones
        else {
            SyntInsertDS_file(&second_dataset_list, argv[i]);
        }
    }

    // Iterate through datasets from dataset_list
    struct dataset_list *current_dataset = dataset_list;
    while (current_dataset != NULL) {
        // Create a new dataset_type from dataset
        struct dataset_type *new_dataset_type = (struct dataset_type *)malloc(sizeof(struct dataset_type));
        new_dataset_type->name = current_dataset->head.name;
        new_dataset_type->is_owner_single = current_dataset->head.is_owner_single;
        new_dataset_type->owner_name = current_dataset->head.owner_name;
        new_dataset_type->is_member_single = current_dataset->head.is_member_single;
        new_dataset_type->member_name = current_dataset->head.member_name;
        new_dataset_type->unique_attributes = current_dataset->head.unique_attributes;

        // Iterate through attributes
        struct attribute_list *current_attr = current_dataset->head.attribute_list;
        while (current_attr != NULL) {
            // Create a new unnamed attribute
            struct unnamed_attribute *new_unnamed_attr = (struct unnamed_attribute *)malloc(sizeof(struct unnamed_attribute));
            new_unnamed_attr->meta_type = current_attr->head.type.meta_type;
            new_unnamed_attr->index = new_dataset_type->num_datasets; // Indexes can be 0, 1, 2...
            new_unnamed_attr->next = NULL;

            // Add the new unnamed attribute to the end of the list
            if (new_dataset_type->un_attributes == NULL) {
                new_dataset_type->un_attributes = new_unnamed_attr;
            } else {
                struct unnamed_attribute *current_unnamed_attr = new_dataset_type->un_attributes;
                while (current_unnamed_attr->next != NULL) {
                    current_unnamed_attr = current_unnamed_attr->next;
                }
                current_unnamed_attr->next = new_unnamed_attr;
            }

            // Move to the next attribute
            current_attr = current_attr->tail;
        }


        new_dataset_type->reverse_name = current_dataset->head.reverse_name;
        new_dataset_type->num_datasets = 0; // Initially, this type contains no datasets
        new_dataset_type->datasets = NULL; // No datasets initially

        // Check if the new_dataset_type is in dataset_type_list
        struct dataset_type_list *current_type = dataset_type_list;
        bool found = false;
        while (current_type != NULL) {
            if (compare_dataset_types(*(current_type->head), *new_dataset_type)) {
                // If it is in list, add dataset to found type using Save_DS
                Save_DS(current_type->head, &(current_dataset->head));
                found = true;
                break;
            }
            current_type = current_type->next;
        }

        // If not found, insert new_dataset_type using FInsertDS()
        if (!found) {
            FInsertDS(&dataset_type_list, new_dataset_type);
            Save_DS(new_dataset_type, &(current_dataset->head));
        }

        // Move to the next dataset
        current_dataset = current_dataset->tail;
    }

    // Process the second dataset list
    current_dataset = second_dataset_list;
    while (current_dataset != NULL) {
        struct dataset_type *new_dataset_type = (struct dataset_type *)malloc(sizeof(struct dataset_type));
        new_dataset_type->name = current_dataset->head.name;
        new_dataset_type->is_owner_single = current_dataset->head.is_owner_single;
        new_dataset_type->owner_name = current_dataset->head.owner_name;
        new_dataset_type->is_member_single = current_dataset->head.is_member_single;
        new_dataset_type->member_name = current_dataset->head.member_name;
        new_dataset_type->unique_attributes = current_dataset->head.unique_attributes;
        new_dataset_type->reverse_name = current_dataset->head.reverse_name;
        new_dataset_type->num_datasets = 0;
        new_dataset_type->datasets = NULL;

        // Insert new dataset type without checking for existing ones
        FInsertDS(&dataset_type_list, new_dataset_type);

        // Save the dataset to the new dataset type
        //Save_DS(new_dataset_type, &(current_dataset->head));

        // Move to the next dataset
        current_dataset = current_dataset->tail;
    }
    // Print the dataset_type_list
    print_dataset_type_list(dataset_type_list);

    return 0;
}


// Function to print the dataset type list
void print_dataset_type_list(struct dataset_type_list *list) {
    struct dataset_type_list *current_type = list;
    while (current_type != NULL) {
        printf("Dataset Type: %s\n", current_type->head->name);
        printf("Owner: %s\n", current_type->head->owner_name);
        printf("Is Owner Single: %s\n", current_type->head->is_owner_single ? "true" : "false");
        printf("Member: %s\n", current_type->head->member_name);
        printf("Is Member Single: %s\n", current_type->head->is_member_single ? "true" : "false");
        printf("Reverse Name: %s\n", current_type->head->reverse_name);
        printf("Number of Datasets: %d\n", current_type->head->num_datasets);
        
        // Print Unique Attributes if available
        printf("Unique Attributes:\n");
        struct attribute_name_list *unique_attr = current_type->head->unique_attributes;
        while (unique_attr != NULL) {
            printf("- %s\n", unique_attr->head);
            unique_attr = unique_attr->tail;
        }

        // Print Unnamed Attributes if available
        printf("Unnamed Attributes:\n");
        struct unnamed_attribute *unnamed_attr = current_type->head->un_attributes;
        while (unnamed_attr != NULL) {
            printf("- Meta Type: %d, Index: %d\n", unnamed_attr->meta_type, unnamed_attr->index);
            unnamed_attr = unnamed_attr->next;
        }

        printf("\n");

        // Print associated datasets
        printf("Datasets:\n");
        print_dataset_list(current_type->head->datasets);

        printf("\n");

        // Move to the next dataset type
        current_type = current_type->next;
    }
}

// Function to compare two dataset types
bool compare_dataset_types(struct dataset_type type1, struct dataset_type type2) {
    //printf("Comparing dataset types...\n");

    // Compare names
    if (strcmp(type1.name, type2.name) != 0) {
        //printf("Names don't match.\n");
        return false;
    }

    // Compare reverse names
    if (strcmp(type1.reverse_name, type2.reverse_name) != 0) {
        //printf("Reverse names don't match.\n");
        return false;
    }

    // Compare owner
    if (strcmp(type1.owner_name, type2.owner_name) != 0) {
       // printf("Owner names don't match.\n");
        return false;
    }

    // Compare member
    if (strcmp(type1.member_name, type2.member_name) != 0) {
       // printf("Member names don't match.\n");
        return false;
    }

    // Compare unique attributes (assuming both lists are sorted)
    struct attribute_name_list *attr1 = type1.unique_attributes;
    struct attribute_name_list *attr2 = type2.unique_attributes;
    while (attr1 != NULL && attr2 != NULL) {
        if (strcmp(attr1->head, attr2->head) != 0) {
           // printf("Unique attributes don't match.\n");
            return false;
        }
        attr1 = attr1->tail;
        attr2 = attr2->tail;
    }
    if (attr1 != NULL || attr2 != NULL) {
       // printf("Different number of unique attributes.\n");
        return false;
    }

    // Compare unnamed attributes (assuming both lists are sorted)
    struct unnamed_attribute *unnamed_attr1 = type1.un_attributes;
    struct unnamed_attribute *unnamed_attr2 = type2.un_attributes;
    while (unnamed_attr1 != NULL && unnamed_attr2 != NULL) {
        if (unnamed_attr1->meta_type != unnamed_attr2->meta_type ||
            unnamed_attr1->index != unnamed_attr2->index) {
           // printf("Unnamed attributes don't match.\n");
            return false;
        }
        unnamed_attr1 = unnamed_attr1->next;
        unnamed_attr2 = unnamed_attr2->next;
    }
    if (unnamed_attr1 != NULL || unnamed_attr2 != NULL) {
       // printf("Different number of unnamed attributes.\n");
        return false;
    }

    // All attributes match
    return true;
}

// Function to save dataset to a dataset type
void Save_DS(struct dataset_type *type, struct dataset *dataset) {
    // Allocate memory for a new dataset_list node
    struct dataset_list *new_dataset_node = (struct dataset_list *)malloc(sizeof(struct dataset_list));
    if (new_dataset_node == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Set the dataset in the new node
    new_dataset_node->head = *dataset;
    new_dataset_node->tail = NULL;

    // If the dataset list of the type is empty, set the new node as the head
    if (type->datasets == NULL) {
        type->datasets = new_dataset_node;
    } else {
        // Otherwise, find the last node and append the new node
        struct dataset_list *current_node = type->datasets;
        while (current_node->tail != NULL) {
            current_node = current_node->tail;
        }
        current_node->tail = new_dataset_node;
    }

    // Increment the number of datasets in the type
    type->num_datasets++;
}

// Function to insert dataset type into the dataset type list
void FInsertDS(struct dataset_type_list **head, struct dataset_type *type) {
    // Allocate memory for a new dataset_type_list node
    struct dataset_type_list *new_type_node = (struct dataset_type_list *)malloc(sizeof(struct dataset_type_list));
    if (new_type_node == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Set the dataset type in the new node
    new_type_node->head = type;
    new_type_node->next = NULL;

    // If the list is empty, set the new node as the head
    if (*head == NULL) {
        *head = new_type_node;
    } else {
        // Otherwise, find the last node and append the new node
        struct dataset_type_list *current_node = *head;
        while (current_node->next != NULL) {
            current_node = current_node->next;
        }
        current_node->next = new_type_node;
    }
}



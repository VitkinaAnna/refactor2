%{
  #include <stdio.h>
  #include "dataset.h"

  int yylex(void);
  void yyerror(struct dataset_list **dataset_list, const char *);
%}

%define api.value.type union
%parse-param {struct dataset_list **result}

%token SET IS OWNER SINGLE MEMBER UNIQUE ATTRIBUTE REVERSE LEFT_PAREN RIGHT_PAREN COMMA SEMICOLON INTEGER FLOAT DOUBLE CHAR ERROR
%token <char *> IDENTIFIER
%token <long> NUMBER

%nterm <struct dataset_list *> dataset_list
%nterm <struct dataset> dataset
%nterm <struct attribute_list *> attribute_list dangling_comma_attribute_list optional_attributes
%nterm <struct attribute> attribute
%nterm <struct attribute_type> attribute_type
%nterm <struct attribute_name_list *> attribute_name_list optional_unique
%nterm <bool> optional_single
%nterm <char *> optional_reverse

%%

input: dataset_list {
  *result = $dataset_list;
};

dataset_list: {
  $$ = NULL;
} | dataset_list dataset {
  $$ = malloc(sizeof(struct dataset_list));
  $$->head = $dataset;
  $$->tail = $1;
};

dataset: SET IDENTIFIER IS OWNER optional_single IDENTIFIER MEMBER optional_single IDENTIFIER optional_unique optional_attributes optional_reverse SEMICOLON {
  $$.name = $2;
  $$.is_owner_single = $5;
  $$.owner_name = $6;
  $$.is_member_single = $8;
  $$.member_name = $9;
  $$.unique_attributes = $10;
  $$.attribute_list = $11;
  $$.reverse_name = $12;
}
;

optional_single: /* Empty */
{ $$ = false; }
| SINGLE
{ $$ = true; }
;

optional_unique: /* Empty */
{ $$ = NULL; }
| UNIQUE attribute_name_list
{ $$ = $2; }
;

attribute_name_list: IDENTIFIER {
  $$ = malloc(sizeof(struct attribute_name_list));
  $$->head = $1;
  $$->tail = NULL;
}
| attribute_name_list COMMA IDENTIFIER {
  $$ = malloc(sizeof(struct attribute_name_list));
  $$->head = $3;
  $$->tail = $1;
}
;

optional_attributes: /* Empty */
{ $$ = NULL; }
| ATTRIBUTE attribute_list
{ $$ = $2; }
;

optional_reverse: /* Empty */
{ $$ = NULL; }
| REVERSE IDENTIFIER
{ $$ = $2; }
;

attribute_list: {
  $$ = NULL;
} | dangling_comma_attribute_list attribute {
  $$ = malloc(sizeof(struct attribute_list));
  $$->head = $attribute;
  $$->tail = $dangling_comma_attribute_list;
};

dangling_comma_attribute_list: {
  $$ = NULL;
} | dangling_comma_attribute_list attribute COMMA {
  $$ = malloc(sizeof(struct attribute_list));
  $$->head = $attribute;
  $$->tail = $1;
};

attribute: IDENTIFIER attribute_type {
  $$.name = $IDENTIFIER;
  $$.type = $attribute_type;
};

attribute_type: INTEGER {
  $$.meta_type = meta_integer;
  $$.size = 0;
} | FLOAT {
  $$.meta_type = meta_float;
  $$.size = 0;
} | DOUBLE {
  $$.meta_type = meta_double;
  $$.size = 0;
} | CHAR LEFT_PAREN NUMBER RIGHT_PAREN {
  $$.meta_type = meta_char;
  $$.size = $NUMBER;
};

%%

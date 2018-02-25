%token DIGIT PLUS MINUS
%%
str: number sign number { $$ = $1 + $2*$3; /*printf("%d\n", $$);*/ } | 
     str sign number { $$ = $1 + $2*$3; printf("%d\n", $$); }
number: DIGIT { $$ = $1 } |
	number DIGIT { $$ = $1 * 10 + $2; }
sign: PLUS { $$ = 1; } |
	  MINUS { $$ = -1; }

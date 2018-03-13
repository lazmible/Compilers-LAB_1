typedef union	
{
	class Variable     *  _var   ;
	class PolynomEntry *  _pe    ;
	class Polynom      *  _poly  ;
	int                   num    ;
	char                  let    ;
	char               *  str    ;
} YYSTYPE;
#define	DIGIT	258
#define	LETTER	259
#define	PRINT	260


extern YYSTYPE yylval;

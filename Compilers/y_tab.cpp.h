typedef union	
{
	class Variable     *  _var   ;
	class PolynomEntry *  _pe    ;
	class Polynom      *  _poly  ;
	int                   num    ;
	char                  let    ;
	const char         *  str    ;
} YYSTYPE;
#define	DIGIT	258
#define	LETTER	259
#define	PRINT	260
#define	IDENTIFIER	261
#define	DECLARATION	262
#define	ASSIGN	263
#define	SEMICOLON	264
#define	PLUS	265
#define	MINUS	266
#define	MULTIPLE	267
#define	BAD	268
#define	UMINUS	269


extern YYSTYPE yylval;

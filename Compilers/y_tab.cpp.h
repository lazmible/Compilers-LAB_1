typedef union	
{
	class Variable     *  _var   ;
	class PolynomEntry *  _pe    ;
	class Polynom      *  _poly  ;
	int                 num      ;
	char                let      ;
} YYSTYPE;
#define	DIGIT	258
#define	LETTER	259


extern YYSTYPE yylval;

%token <float> FLOAT
%token <int> INT
%token V
%token F
%token EOE              /* End Of Expression */
%token NEWLINE
%start main             /* entry point */
%type <Model.line list> main   /* the parser will return an Abstract Syntax Tree */
%%
main:
    expr NEWLINE EOE  { [$1] }
  | expr NEWLINE main { $1 :: $3 }
;
expr:
  | V FLOAT FLOAT FLOAT { Model.Vertex ($2,$3,$4) }
  | F INT INT INT       { Model.Face ($2,$3,$4) }
;

%%

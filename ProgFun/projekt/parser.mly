%token <float> FLOAT
%token <int> INT
%token V
%token F
%token EOE
%token NEWLINE
%start main
%type <Model.line list> main
%%
main:
  | information NEWLINE EOE  { [$1] }
  | information NEWLINE main { $1 :: $3 };

information:
  | V FLOAT FLOAT FLOAT { Model.Vertex ($2,$3,$4) }
  | F INT INT INT       { Model.Face ($2,$3,$4) };

%%

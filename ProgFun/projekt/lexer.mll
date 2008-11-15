{
open Parser
}
let integer = ['0'-'9']+
let float = '-'* ['0'-'9']* '.' ['0'-'9']+
let comment = '#' [^ '\n']* '\n'?

rule token = parse
  | integer as num      { INT (int_of_string num) }
  | float as num        { FLOAT (float_of_string num) }
  | 'v'                 { V }
  | 'f'                 { F }
  | ' '                 { token lexbuf }
  | '\n'                { NEWLINE }
  | comment             { token lexbuf }
  | "usemtl Material\n" { token lexbuf }
  | "s off\n"           { token lexbuf }
  | eof                 { EOE }

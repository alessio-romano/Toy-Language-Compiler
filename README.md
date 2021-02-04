# README

After revisiting the [Toy language](http://www.graysage.com/cg/Compilers/Toy/index.html) for the [Amiga Machine](https://en.wikipedia.org/wiki/Amiga), some customizations were made to the original language in order to produce a new version of Toy.
This project's aim is to produce a Compiler for this new (and improved) version of Toy.<br/>

# LEXICAL ANALYSIS
JFlex was the main tool used for generating a Lexer out of the following lexical specifications:
```
        SEMI  ';'
       COMMA  ','
          ID  'Any sequence of letters, digits and underscores, starting with a letter or an underscore'
      RETURN  '->'
         INT  'int'
      STRING  'string'
       FLOAT  'float'
        BOOL  'bool'
        LPAR  '('
        RPAR  ')'
       COLON  ':'
        PROC  'proc'
        CORP  'corp'
        VOID  'void'
          IF  'if'
        THEN  'then'
        ELIF  'elif'
          FI  'fi'
        ELSE  'else'
       WHILE  'while'
          DO  'do'
          OD  'od'
        READ  'readln'
       WRITE  'write'
      ASSIGN  ':='
        PLUS  '+'
       MINUS  '-'
       TIMES  '*'
         DIV  '/'
          EQ  '='
          NE  '<>'
          LT  '<'
          LE  '<='
          GT  '>'
          GE  '>='
         AND  '&&'
          OR  '||'
         NOT  '!'
        NULL  'null'
        TRUE  'true'
       FALSE  'false'
   INT_CONST  'any integer number (sequence of decimal digits)'
 FLOAT_CONST  'any floating point number
STRING_CONST  'any string between " (double quotes)'
```

As its necessary for generating a Lexer, all lexical specifications have been turned in _regular expressions_, written in the ```lexer.flex``` file


# SYNTAX ANALYSIS
Coupled with JFlex, CUP was the main tool used for generating the Parser out of the following syntax specifications:

```
        Program := VarDeclList ProcList
    VarDeclList := VarDecl VarDeclList
                | /* empty */
        VarDecl := Type IdListInit SEMI
           Type := INT
                | BOOL
                | FLOAT
                | STRING
     IdListInit := ID
                | IdListInit COMMA ID
                | ID ASSIGN Expr
                | IdListInit COMMA ID ASSIGN Expr
       ProcList := Proc
                | Proc ProcList
           Proc := PROC ID LPAR ParamDeclList RPAR ResultTypeList COLON ProcBody
                | PROC ID LPAR RPAR ResultTypeList COLON ProcBody
       ProcBody := VarDeclList StatList RETURN ReturnExprs CORP SEMI
                | VarDeclList RETURN ReturnExprs CORP SEMI
  ParamDeclList := ParDecl
                | ParamDeclList SEMI ParDecl
        ParDecl := Type ParIdList
      ParIdList := ID
                | ParIdList COMMA ID
 ResultTypeList := ResultType
                | ResultType COMMA ResultTypeList
     ResultType := Type
                | VOID
       StatList := Stat SEMI
                | Stat SEMI StatList
           Stat := IfStat
                | WhileStat
                | ReadlnStat
                | AssignStat
                | CallProc
         IfStat := IF Expr THEN StatList ElifList Else FI
       ElifList := Elif ElifList
                | /* empty */
           Elif := ELIF Expr THEN StatList
           Else := ELSE StatList
                | /* empty */
      WhileStat := WHILE StatList RETURN Expr DO StatList OD
                | WHILE Expr DO StatList OD
     ReadlnStat := READ LPAR IdList RPAR
         IdList := ID
                | IdList COMMA ID
      WriteStat := WRITE LPAR ExprList RPAR
      ssignStat := IdList ASSIGN ExprList
       CallProc := ID LPAR ExprList RPAR
                | ID LPAR RPAR
    ReturnExprs := ExprList
                | /* empty */
       ExprList := Expr
                | Expr COMMA ExprList
           Expr := NULL
                | TRUE
                | FALSE
                | INT_CONST
                | FLOAT_CONST
                | STRING_CONST
                | ID
                | MINUS Expr
                | Expr PLUS Expr
                | Expr MINUS Expr
                | Expr TIMES Expr
                | Expr DIV Expr
                | NOT Expr
                | Expr AND Expr
                | Expr OR Expr
                | Expr GT Expr
                | Expr GE Expr
                | Expr LT Expr
                | Expr LE Expr
                | Expr EQ Expr
                | Expr NE Expr
                | CallProc

```

As its necessary for generating a Parser, all the previous specifications have been completed using _semantic actions_ for each production of the previous grammar, written
in the ```parser.cup``` file

# SEMANTIC ANALYSIS
Some semantic checks were made in order to follow some of the constraints given by the intermediate language itself.
For example, the ```main``` function in C doesn't allow strings, characters, or any return values different from ```int``` in its signature.
All type-checking rules used in this phase are documented through _inference rules_, written in the documentation file.
Most common checks (e.g. single declaration of a ``` main ``` procedure) were also included in this phase.

# CODE GENERATION
The code generation phase uses the C language as its intermediate-code-representation for Toy.
A C-language file is generated for any input file containing a Toy program which follows all lexical, syntactical and semantic constraints.
The generated C-language file is then compiled using _gcc_ to produce an executable file, corresponding to the input Toy-language file.

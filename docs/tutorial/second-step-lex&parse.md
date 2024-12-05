# Step 2 - The beginner of compiler: Lex & Parse

This step, we need to know what does user input, and how to deal with it.

But before that, we need to know basic information of compiler.

## What is compiler?
A compiler is a computer program that translates computer code
written in one programming language(the source language) 
into another language (the target language).

It is primarily used for programs that translate source code from a
high-level programming language to a low-level programming language 
(e.g. assembly language, object code, or machine code) to create an executable program.

For dap's compiler: it is a util that translate the source code which is for human to read
to a sequence of '1' and '0' which is "read" by computer.

Nowadays, a compiler almost has three parts: **frontend**, **middleend**, **backend**.

1. The **frontend** is the part of the compiler that translates the source code into a sequence of tokens.

    it will include three parts:
    Most commonly, the frontend is broken into three phases:
    **lexical analysis** (also known as lexing or scanning),
    **syntax analysis** (also known as scanning or parsing), and **semantic analysis**.
    (this comes from wikipedia)
    
    And this is what we need to know in this step.

2. The **middleend** is the part of the compiler that translates the source code into a sequence of **intermediate code**.

    The middle end, also known as optimizer, performs optimizations on the 
    intermediate representation in order toimprove the performance and the quality of 
    the produced machine code

3. The **backend** is the part of the compiler that translates the intermediate code into machine code.

    The back end is responsible for the CPU architecture specific optimizations and for 
    code generation

have a look at the following flow:

the source code: 
```c++
int main() {
    return 0;
}
```

it will be translated into tokens (we will talk more about this in next section):
`
'int', 'main', '(', ')', '{', 'return', '0', ';', '}'
`

and then translated into intermediate code:
```asm
define i32 @main() #0 {
entry:
  ret i32 0
}
```

finally translated into machine code:
```asm
1010101011010101010101...
```

now we know what is compiler. let us go to the detail.

## what is **Lex**?

Lex is short for lexical analysis, which is the first step in the compilation process.
During this stage, the source code is read and converted into a sequence of tokens. 
Each token represents a fundamental component of the source code, such as keywords,
identifiers, operators, or literals. The primary goal of lexical analysis is to identify
these components and prepare the input for the subsequent parsing (Parse) stage.    

So, what dose **token** mean?

In an easy way to understand it, which might be a little bit confusing,
the token is the words and symbols that you write in source code.

like a cpp code: 
```c++
int main() {
    return 0;
}
```
`int` is a token, `main` is a token, `(` is a token, `)` is a token, `{` is a token, 
`}` is a token, `return` is a token, `0` is a token, `;` is a token.

now you may know what is token: 
token is a word or a symbol in source code. maybe a space could be considered as a token,
that depends on how do you define in your language.

## what is **Parse**?

Parse is short for syntax analysis, which is the second step in the compilation process.
During this stage, the sequence of tokens produced by the lexical analysis is analyzed.
It will check whether the sequence of tokens conforms to the rules of the programming language.

e.g.: 
    I said 'I ate food'; and the compiler will know: Oh, he said a sentence.
    however, if I said: 'I food ate'; the compiler can only know that I speak something. What is it? 
    The compiler can not know.

Then, how to parse a sequence of tokens?

we will talk about it in next section - how to deal with parse.

## what is **Semantic**?
Semantic analysis is the third step in the compilation process.
In fact, semantic analysis is the process of checking the meaning of the program.

e.g.:
    I said 'I ate food'; and the compiler will know: Oh, he said a sentence, and he expressed that
    he ate something.
    however, if I said: 'I food ate'; the compiler can only know that I speak something. What is it?
    The compiler can not know, not even the meaning.

Semantic analysis has many important checking aspects beyond simply determining whether 
the meaning of a statement makes sense:
- Type checking: in many programming languages, variables are of type, for example, 
    if you define int num = 10; in C++, the semantic analysis phase will check whether 
    the value on the right hand side of the assignment operation (10 in this case) 
    matches the type (int type) declared for the variable (num). 
    If there is a code like float f = “abc”;, the compiler will report an
    error because you can't assign a string to a variable of a floating-point number type, 
    which is a type mismatch.
- Scope checking: This involves the scoping of variables, functions, and so on. 
    For example, a local variable defined inside a function is not directly accessible
    outside the function.


## how to deal with lex?

We will use `flex` to deal with lex.
And i recommand you to download a extension called "Lex" written by @luniclynx on vscode.

what is flex?
Flex (Fast Lexical Analyzer Generator) is a tool for generating lexical analyzers (lexers).
It is a regular expression-based lexical analyzer generator, mainly used to break the input
character stream into a series of words (tokens) according to predefined rules.

`flex` can convert a file which contains regular expressions into a C program that can be used to 
tokenize a stream of characters.    

let's take a look at flex file:

```flex
%{
#include <stdio.h>
#define MAX_LENGTH 100
%}

digit [0-9]

%%

{digit}+ {
    printf("Matched digit sequence: %s\n", yytext);
    // More processing about digit sequence can be done here, such as converting to numeric type, etc.
}

[a-zA-Z]+ {
    printf("Matched alphabet sequence: %s\n", yytext);
}

"//".*  {
    // Ignore C-style single-line comments
}

"/*"([^*]|\*+[^*/])*\*+"/" {
    // Ignore C-style multi-line comments
}

%%

int main() {
    yylex();
    return 0;
}
```

The Flex lexical file mainly consists of three parts: the definition part, the rule part,
and the user code part.

(1) Definition Part
This part is usually located at the beginning of the lexical file and is used to define some 
global variables, macros, and names of regular expression patterns, etc. For example, it can 
define some include files, declare global variables, or define names for commonly used 
regular expression patterns for more convenient reference in the rule part.

```c
%{
#include <stdio.h>
#define MAX_LENGTH 100
%}

digit [0-9]

```
In the above example, the content between %{ and %} is a C language code segment.
Here, the standard input-output header file is included and a macro MAX_LENGTH is defined.
And digit is a defined regular expression name, representing the number [0-9].
(2) Rule Part
This is the core part of the Flex lexical file, which is used to define various word 
patterns (patterns) and corresponding actions (actions). Each rule consists of a regular
expression pattern and a C language code block. When the input stream matches a certain 
pattern, the corresponding code block will be executed.

```C++
{digit}+ {
printf("Matched digit sequence: %s\n", yytext);
// More processing about digit sequence can be done here, such as converting to numeric type, etc.
}

[a-zA-Z]+ {
printf("Matched alphabet sequence: %s\n", yytext);
}

"//".*  {
// Ignore C-style single-line comments
}

"/*"([^*]|\*+[^*/])*\*+"/" {
// Ignore C-style multi-line comments
}
```

In these rules, for example, {digit}+ means matching a sequence consisting of one or more 
digits. When the match is successful, the code in the following curly braces will be executed,
printing out the matched digit sequence. [a-zA-Z]+ is to match a sequence consisting of one
or more letters and print it accordingly. For comment processing, rules for matching 
single-line comments // and multi-line comments /* */ are defined respectively, and the
comment contents are directly ignored in the action part.

(3) User Code Part
This part is located at the end of the lexical file and mainly contains some additional
user-defined functions and the main function. These functions can be called in the action 
code of the rule part to complete more complex functions.

```C++
int main() {
yylex();
return 0;
}
```

Here, a simple main function is defined. Among them, yylex() is the lexical analysis 
function generated by Flex. Calling it starts the lexical analysis of the input stream.

> ps: you can refer to the code generatedd by flex: [lex.yy.c](./lex.yy.c)
> 
> you can see many functions defined in the file, such as yy_create_buffer(), 
> and so on. If you are intrested in the details, you can refer to the source code.

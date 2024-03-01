
#include <tokenizer.h>
#include <parser.h>
#include <codegen.h>
#include <symtable.h>


class Xcc{
public:
    Xcc(){};
    ~Xcc(){};
    string src;

    void load(string file_name);
    void compile();

    Tokenizer tokenizer;
    Parser parser;

};

#include <common.h>

#ifndef _SYMBOL_H_
#define _SYMBOL_H_

class Variable
{
public:
    Type type;
    string name;
    int offset;
    int value;
    Variable(Type type, string name, int offset, int value)
    {
        this->type = type;
        this->name = name;
        this->offset = offset;
        this->value = value;
    }
    Variable(Type type, string name, int value)
    {
        this->type = type;
        this->name = name;
        this->value = value;
        this->offset = 0;
    }
    Variable(Type type, string name)
    {
        this->type = type;
        this->name = name;
        this->offset = 0;
        this->value = 0;
    }
    Variable()
    {
    }
};

class SymTable
{
public:
    unordered_map<string, Variable> table;

    bool add(Type type, string name);
    bool add(Type type, string name, int value);
    bool add(Type type, string name, int value, int offset);

    bool get(string name, int &value);
};

class Function
{
public:
    Type return_type;
    string name;
    int stack_size;
    vector<AST_node *> params;
    SymTable sym_table;
    vector<AST_node *> stmts;

    int get_offset(string name);
    int get_value(string name);
    Function()
    {
    }
};

#endif //_SYMBOL_H_
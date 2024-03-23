#include <symtable.h>

bool SymTable::add(Type type, string name)
{
    if (table.find(name) != table.end())
    {
        return false;
    }
    table[name] = Variable(type, name);
    return true;
}

bool SymTable::add(Type type, string name, int value)
{
    if (table.find(name) != table.end())
    {
        return false;
    }
    table[name] = Variable(type, name, value);
    return true;
}

bool SymTable::add(Type type, string name, int value, int offset)
{
    if (table.find(name) != table.end())
    {
        return false;
    }
    table[name] = Variable(type, name, value, offset);
    return true;
}

bool SymTable::get(string name, int &value)
{
    if (table.find(name) != table.end())
    {
        value = table[name].value;
        return true;
    }

    return false;
}

int Function::get_offset(string name)
{
    return sym_table.table[name].offset;
}

int Function::get_value(string name)
{
    return sym_table.table[name].value;
}
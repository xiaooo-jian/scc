#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdarg.h>
using namespace std;


#ifndef _TOKEN_H_
#define _TOKEN_H_

enum TokenType{
    Tok_num, 
    Tok_iden,   //
    Tok_plus,   // +
    Tok_minus,  // -
    Tok_mul,    // *
    Tok_div,    // /
    Tok_lbak,   // (
    Tok_rbak,   // )
    Tok_eq,     // ==
    Tok_neq,    // !=
    Tok_
};

struct Token{
    TokenType type;
    string value;
    int line;
    int col;

    Token(){

    };

    Token(TokenType type,string value,int line,int col){
        this->type = type;
        this->value = value;
        this->line = line;
        this->col = col;
    };
};


enum AST_type{
    AST_None,
    AST_Primary,
    AST_Express,
    AST_Multiply,
    AST_Divide,
    AST_Mins,
    AST_Add,
    AST_Num,
    AST_Eq,
    AST_Neq,
};

struct AST_node{
    AST_node* left;
    AST_node* right;
    int val;
    AST_type type;
    AST_node(){};
};



// #define __DEBUG

#ifdef __DEBUG
    #define LOG(format, ...) \
                printf("[%s:%d->%s]" format, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
    #define LOG(format, ...)
#endif

# define ERROR(format, ...) \
                printf("[%s:%d->%s]" format, __FILE__, __LINE__, __func__, ##__VA_ARGS__);exit(1);



#endif
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdarg.h>
#include <assert.h>
#include <unordered_map>
using namespace std;


#ifndef _TOKEN_H_
#define _TOKEN_H_

enum TokenType{
    Tok_num, 
    Tok_ident,   //
    Tok_plus,   // +
    Tok_minus,  // -
    Tok_mul,    // *
    Tok_div,    // /
    Tok_lbak,   // (
    Tok_rbak,   // )
    Tok_eq,     // ==
    Tok_neq,    // !=
    Tok_leq,     // >
    Tok_req,     // <
    Tok_lt,     // >=
    Tok_rt,     // <=
    Tok_seg,    // ;
    Tok_assign, // =
    Tok_lcul, // { 
    Tok_rcul, // }
    Tok_addr,  // &
    Tok_comma, // ,
    Tok_return,
    Tok_if,
    Tok_else,
    Tok_for,
    Tok_while,
    Tok_int,
    Tok_eof,
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


enum TypeKind
{
    TY_void,
    TY_char,
    TY_int,
    TY_point
};
struct Type{
    TypeKind ty;
    Type* base;
    Type(){

    }
    Type(TypeKind ty,Type* base = nullptr){
        this->ty = ty;
        this->base = base;
    }
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
    AST_leq,     // >
    AST_req,     // <
    AST_lt,     // >=
    AST_rt,     // <=
    AST_Assign, // =
    AST_val,    //变量
    AST_Expr,
    AST_Block,
    AST_Return,
    AST_If,
    AST_For,
    AST_While,
    AST_Ref,
    AST_Addr,
};

struct AST_node{
    AST_node* left;
    AST_node* right;
    int val;
    string name;
    AST_type type;
    vector<AST_node*> init;
    AST_node* cond;
    AST_node* expr;
    vector<AST_node*> then;
    vector<AST_node*> els;

    vector<AST_node*> childs;

    Type* op_type;

    AST_node(const AST_node& node){
        this->left = node.left;
        this->right = node.right;
        this->val = node.val;
        this->type = node.type;
        this->name = node.name;
        this->childs = vector<AST_node*>(node.childs);
        this->cond = node.cond;
        this->then = vector<AST_node*>(node.then);
        this->els = vector<AST_node*>(node.els);
        this->op_type = op_type;
    };
    AST_node(){
        val = 0;
    }
    // ~AST_node(){
    //     delete left;
    //     delete right;
    // }
};


void typeAdd(vector<AST_node*>& nodes);
void typeAdd(AST_node* node);


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
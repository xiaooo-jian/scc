#include <common.h>
#include <symtable.h>

class Codegen{
public:
    int depth=0;
    vector<Function*> funcs;
    Function* func;
    ofstream outFile;
    int align(int n, int align);
    void iden_offset();

    vector<string> args_reg;

    void codegen(string filename);
    
    void codegenPrimary(AST_node* node);
    void codegenAddMinsExpr(AST_node* node);
    void codegenMultDivExpr(AST_node* node);
    void codegenExpression(AST_node* node);

    void codegenStmt(vector<AST_node*> stmts);
    void codegenExpr(AST_node * node);
    void codegenAddr(AST_node* node);

    void load(int value);   
    void add(int r1);
    void sub(int r1,int r2);
    void mul(int r1,int r2);
    void div(int r1,int r2);

    void push();
    void pop(string arg) ;


    void codegen_init();
    void codegen_end();

    void codegen_print(const char * str); 

    Codegen(){
        args_reg = vector<string>({"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"});
    }
};
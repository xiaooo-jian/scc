#include <common.h>
#include <symtable.h>


class Parser
{
public:
    Parser(){
        cur = 0;
    };
    ~Parser(){};
    // vector<Token> tokens;
    vector<Token> tokens;

    int cur;

    Function* parse();
    // void parse();

    Function* parserFunction();
    vector<AST_node*> parserStmt(int times= 0);

    AST_node* parserExprStmt();
    AST_node* parserIfStmt();
    // vector<AST_node*> parserStmt(int);
    AST_node* parserExpression();
    AST_node* parserEqualExpr();
    AST_node* parserCompareExpr();
    AST_node* parserAddMinsExpr();
    AST_node* parserMulDivExpr();
    AST_node* parserUnaryExpr();
    AST_node* parserPrimary();



    bool match(TokenType type);
    void skip(TokenType type);
    void parserDisplay(AST_node *node,int);
};


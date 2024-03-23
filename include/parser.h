#include <common.h>
#include <symtable.h>

class Parser
{
public:
    Parser()
    {
        cur = 0;
    };
    ~Parser(){};
    // vector<Token> tokens;
    vector<Token> tokens;

    int cur;

    vector<Function *> parse();
    // void parse();

    Function *parserFunction();
    vector<AST_node *> parserStmt(int times = 0);

    AST_node *parserExprStmt();
    AST_node *parserExpression();
    AST_node *parserEqualExpr();
    AST_node *parserCompareExpr();
    AST_node *parserAddMinsExpr();
    AST_node *parserMulDivExpr();
    AST_node *parserUnaryExpr();
    AST_node *parserPrimary();

    void new_ident(AST_node *node);
    bool match(TokenType type);
    void skip(TokenType type);
    void parserDisplay(AST_node *node, int);
};

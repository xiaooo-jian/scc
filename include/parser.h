#include <common.h>



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

    void parse();
    // void parse();

    AST_node* root;
    AST_node* parserEqualExpr();
    AST_node* parserCompareExpr();
    AST_node* parserExpression();
    AST_node* parserAddMinsExpr();
    AST_node* parserMulDivExpr();
    AST_node* parserUnaryExpr();
    AST_node* parserPrimary();



    bool match(TokenType type);

    void parserDisplay(AST_node *node);
};


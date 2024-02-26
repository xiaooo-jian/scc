#include <parser.h>

bool Parser::match(TokenType type)
{
    if (tokens[cur].type == type)
    {
        return true;
    }
    return false;
}

AST_node *Parser::parserExpression()
{
    AST_node *node = parserAddMinsExpr();
    return node;
};

AST_node *Parser::parserAddMinsExpr()
{
    LOG("AddMinsExpr\n");
    AST_node *node = new AST_node;
    node->left = parserMulDivExpr();
    if (match(Tok_plus) || match(Tok_minus))
    {
        node->type = match(Tok_plus) ? AST_Add : AST_Mins;
        cur++;
        node->right = parserAddMinsExpr();
    }
    return node;
}

AST_node *Parser::parserMulDivExpr()
{
    LOG("MulDivExpr\n");
    AST_node *node = new AST_node;
    node->left = parserPrimary();
    if (match(Tok_mul) || match(Tok_div))
    {
        node->type = match(Tok_mul) ? AST_Multiply : AST_Divide;
        cur++;
        node->right = parserMulDivExpr();
    }
    return node;
}

AST_node *Parser::parserPrimary()
{
    LOG("primary\n");
    // cout << tokens[cur].value << endl;
    AST_node *node = new AST_node;

    if (match(Tok_num))
    {
        node->type = AST_Num;
        node->val = atoi(tokens[cur].value.c_str());
        cur++;
    }
    else if(match(Tok_lbak)){
        cur ++;
        node = parserExpression();
        if(match(Tok_rbak)){
            cur++;
        }
    }
    else
    {
        // TODO: error
        ERROR("parser error for get %d",tokens[cur]);
        exit(1);
    }
    return node;
}


void Parser::parse()
{
    cur = 0;
    root = parserExpression();
}

void Parser::parserDisplay(AST_node *node){
    if(node->right){
        parserDisplay(node->right);
    }
    if (node->left)
    {
        parserDisplay(node->left);
    }
      
    cout << node->val << " type:" << node->type << endl;
}
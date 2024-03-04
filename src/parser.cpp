#include <parser.h>
#include <symtable.h>
bool Parser::match(TokenType type)
{
    if (tokens[cur].type == type)
    {
        return true;
    }
    return false;
}

void Parser::skip(TokenType type){
    if (tokens[cur].type == type)
    {
        cur++;
        return ;
    }
    ERROR("Expect %d but get %d", type,tokens[cur].type);

}


SymTable *cur_table ;

Function* Parser::parserFunction(){
    Function *func = new Function();
    cur_table = (SymTable*)&(func->sym_table);
    func->stmts = parserStmt();
    return func;
}

vector<AST_node*> Parser::parserStmt(){
    
    vector<AST_node*> roots;
    while(tokens[cur].type != Tok_eof){
        AST_node *node;
        if(match(Tok_return)){
            cur++;
            node = parserExprStmt();
            node->type = AST_Return;

        }else{
            node = parserExprStmt();
            node->type = AST_Expr;
        }
        roots.push_back(node);           
        skip(Tok_seg);
    }
    return roots;
}

AST_node* Parser::parserExprStmt(){
    LOG("ExprStmt\n");
    AST_node *node = new AST_node;
    if(match(Tok_ident) && tokens[cur+1].type == Tok_assign){
        if(!cur_table->add(TY_int,tokens[cur].value)){
            ERROR("Redefined variable %s",tokens[cur].value.c_str());
        }
        string name = tokens[cur].value;
        
        cur++;
        skip(Tok_assign);
        node->left = parserExpression();
        node->left->type = AST_Assign;
        node->left->name = name;

        // if (!cur_table->add(TY_int,node->name,parserExpression()->val)){
        //     ERROR("Redefined variable %s",node->name.c_str());
        // }
    }else{
        node = parserExpression();
    }
    return node;
}


AST_node *Parser::parserExpression()
{
    LOG("Expression\n");
    AST_node *node = new AST_node;
    node->left =parserEqualExpr(); //不增加这一个节点的话在codegen时会被跳过
    return node;
};


AST_node* Parser::parserEqualExpr(){
    LOG("EqualExpr\n");
    AST_node *node = new AST_node;
    node->left =  parserCompareExpr();
    if(match(Tok_eq) || match(Tok_neq)){
        node->type = match(Tok_eq) ? AST_Eq : AST_Neq;
        cur++;
        node->right = parserEqualExpr();
    }
    return node;
}

AST_node* Parser::parserCompareExpr(){
    LOG("CompareExpr\n");
    AST_node *node = new AST_node;
    node->left =  parserAddMinsExpr();
    if(match(Tok_leq) || match(Tok_req) || match(Tok_lt) || match(Tok_rt)){
        node->type = match(Tok_leq) ? AST_leq : match(Tok_req) ? AST_req:  match(Tok_lt) ? AST_lt:AST_rt;
        cur++;
        node->right = parserCompareExpr();
    }
    return node;
}

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
    node->left = parserUnaryExpr();
    if (match(Tok_mul) || match(Tok_div))
    {
        node->type = match(Tok_mul) ? AST_Multiply : AST_Divide;
        cur++;
        node->right = parserMulDivExpr();
    }
    return node;
}

AST_node* Parser::parserUnaryExpr(){
    LOG("Unary\n");
    
    int op = 1;
    while(match(Tok_minus) || match(Tok_plus)){
        if(match(Tok_minus)){
            op *= -1;
            cur++;
        }else if(match(Tok_plus)){
            cur++;
        }
    }
    AST_node *node = parserPrimary();
    node->val = op * node->val;
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
    else if(match(Tok_ident)){
        node->name = tokens[cur].value;
        node->type = AST_val;
        if(!cur_table->get(node->name,node->val)){
            ERROR("variable [%s] not defined \n",node->name.c_str());
        }
        cur ++;
    }
    else 
    {
        cout << tokens[cur].type <<endl;
        ERROR("parser error for get [%s] \n",tokens[cur].value.c_str());

    }
    return node;
}


Function* Parser::parse()
{
    cur = 0;

    return parserFunction();

}

void Parser::parserDisplay(AST_node *node,int n=0){
    if(!node) return ;
    
    // if(node->right){
        parserDisplay(node->right,n+1);
    // }
    // if (node->left)
    // {
        parserDisplay(node->left,n+1);
    // }
      
    cout << string(n,' ') << node->val << " type:" << node->type << endl;
}
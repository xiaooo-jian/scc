#include <common.h>

void typeAdd(AST_node *node)
{
    if (!node || node->op_type)
        return;

    typeAdd(node->left);
    typeAdd(node->right);
    typeAdd(node->init);
    typeAdd(node->cond);
    typeAdd(node->expr);

    typeAdd(node->then);
    typeAdd(node->els);
    typeAdd(node->childs);

    switch (node->type)
    {
    case AST_Add:
    case AST_Mins:
    case AST_Multiply:
    case AST_Divide:
    case AST_Assign:
    case AST_None:
        if (node->left)
            node->op_type = node->left->op_type;
        break;
    case AST_Eq:
    case AST_Neq:
    case AST_leq:
    case AST_req:
    case AST_lt:
    case AST_rt:
    case AST_val:
    case AST_Num:
    case AST_Func:
        node->op_type = new Type(TY_int);
        break;
    case AST_Ref:
        if (node->left->op_type->ty == TY_point)
            node->op_type = node->left->op_type->base;
        else
            node->op_type = new Type(TY_int);
        break;
    case AST_Addr:
        node->op_type = new Type(TY_point, node->left->op_type);
        break;
    default:
        break;
    }
}

void typeAdd(vector<AST_node *> &nodes)
{

    if (nodes.size() == 0)
    {
        return;
    }
    for (auto node : nodes)
    {

        typeAdd(node);
    }
}
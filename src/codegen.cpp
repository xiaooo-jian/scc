#include <codegen.h>

// void Codegen::codegen_print(const char * str){

// }

void Codegen::codegen_init()
{
    outFile << "\t.globl main\n";
    outFile << "main:\n";
}

void Codegen::codegen_end()
{
    outFile << "\tret\n";
}

void Codegen::load(int value)
{
    outFile << "\tmov\trax, " << value << endl;
}

void Codegen::add(int r1)
{
    outFile << "\tadd\trax, " << r1 << endl;
}

// void Codegen::codegenExpression(AST_node * node){
//     codegenAddMinsExpr(node->left);
// }

// void Codegen::codegenAddMinsExpr(AST_node * node){
// int val1;
// val1 = codege
// }

void Codegen::push()
{
    outFile << "\tpush\t%rax" << endl;
}

void Codegen::pop(string arg)
{
    outFile << "\tpop\t" << arg << endl;
}

void Codegen::codegenExpr(AST_node *node)
{

    if (node->type == AST_Num)
    {
        outFile << "\tmov\t$" << node->val << ", \t%rax\n";
        return;
    }

    if (node->right != NULL)
    {
        codegenExpr(node->right);
        if(node->type != AST_None)
            push();
    }
    if (node->left != NULL)
    {
        codegenExpr(node->left);
        if(node->type != AST_None)
            pop("%rdi");
    }


    switch (node->type)
    {
    case AST_Add:
        outFile << "\tadd %rdi, %rax\n";
        break;
    case AST_Mins:
        outFile << "\tsub %rdi, %rax\n";
        break;
    case AST_Multiply:
        outFile << "\timul %rdi, %rax\n";
        break;
    case AST_Divide:
        outFile << "\tcqo\n"
                << "\tidiv %rdi\n";
        break;

    case AST_Eq:
        outFile << "\tcmp %rdi, %rax\n";
        outFile << "\tsete %al\n";
        outFile << "\tmovzb %al, %rax\n";
        break;
    case AST_Neq:
        outFile << "\tcmp %rdi, %rax\n";
        outFile << "\tsetne %al\n";
        outFile << "\tmovzb %al, %rax\n";
        break;
    case AST_None:
        break;
    default:
        cout << "error in codegenexpr\n";
    }
}

void Codegen::codegen(string filename)
{
    outFile.open(filename);
    if (!outFile.is_open())
    {
        cout << "Create the assembly file error!" << endl;
        return;
    }

    codegen_init();
    codegenExpr(root);
    codegen_end();
}
struct node 
{
    int value;
    struct node *left, *right; 
};
// 一个数组，数组长度不低于二叉树的高度，为了简便起见，这里假设是一百,
// 自己使用得时候可以改成动态数组(或链表)

int vec_left[100] = {0};
 
// 显示二叉树的函数，只要调用Display(root, 0)即可
void Display(struct node* root, int ident)
{
    if(ident > 0)
    {
        for(int i = 0; i < ident - 1; ++i)
        {
            printf(vec_left[i] ? "│   " : "    ");
        }
        printf(vec_left[ident-1] ? "├── " : "└── ");
    }
 
    if(! root)
    {
        printf("(null)\n");
        return;
    }
 
    printf("%d\n", root->value);
    if(!root->left && !root->right)
    {
        return;
    }
 
    vec_left[ident] = 1;
    Display(root->left, ident + 1);
    vec_left[ident] = 0;
    Display(root->right, ident + 1);

}
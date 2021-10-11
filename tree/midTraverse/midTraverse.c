#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TOCHAR(x) x[0]
#define CREATENEWNODE(x) struct treeNode *node##x = createTreeNode(TOCHAR(#x));
#define SPLICENODES(x,y,z) { \
    if (nodeNULL != node##y && nodeNULL != node##x) node##y->left = node##x; \
    if (nodeNULL != node##y && nodeNULL != node##z) node##y->right = node##z; \
}

#define STACKMAXLENGTH 128

struct treeNode {
    char            value;
    struct treeNode *left;
    struct treeNode *right;
};

static struct treeNode *nodeNULL = NULL;
static struct treeNode *nodeStack[STACKMAXLENGTH] = { 0 };
static int stackIndex = -1;

struct treeNode *createTreeNode(char v)
{
    struct treeNode *newNode = (struct treeNode *)malloc(sizeof(struct treeNode));
    if (0 == newNode) {
        return NULL;
    }
    memset(newNode, 0x0, sizeof(struct treeNode));
    newNode->value = v;
    return newNode;
}

static void dumpNodeInfo(struct treeNode *root)
{
    if (root) {
        printf("%c", root->value);
    }
}

void midTraverseTreeRecurse(struct treeNode *root) 
{
    if (0 == root) {
        return ;
    }

    midTraverseTreeRecurse(root->left);
    dumpNodeInfo(root);
    midTraverseTreeRecurse(root->right);
}

static void stackPush(struct treeNode *node)
{
    nodeStack[++stackIndex] = node;
}

static struct treeNode *statckPop()
{
    return nodeStack[stackIndex--];
}

static int stackEmpty()
{
    return (stackIndex == -1 ? 0 : 1);
}

static void PushAllLeftNodesToStack(struct treeNode *root)
{
    while (root) {
        stackPush(root);
        root = root->left;
    }
}

void midTraverseTreeNoRecurse(struct treeNode *root)
{
    struct treeNode *curNode = root;

    // push all left nodes to stack
    PushAllLeftNodesToStack(curNode);

    do {
        // print mid node info
        dumpNodeInfo((curNode = statckPop()));

        // if right node exist, recurse right tree
        if (curNode->right) {
            curNode = curNode->right;
            // push all left nodes to stack
            PushAllLeftNodesToStack(curNode);
        }
    } while (stackEmpty());
}

int main(int argc, char *argv[])
{
    CREATENEWNODE(A);
    CREATENEWNODE(B);
    CREATENEWNODE(C);
    CREATENEWNODE(D);
    CREATENEWNODE(E);
    CREATENEWNODE(F);
    CREATENEWNODE(G);
    CREATENEWNODE(H);
    CREATENEWNODE(I);

    SPLICENODES(B, A, C);
    SPLICENODES(D, B, F);
    SPLICENODES(G, C, I);
    SPLICENODES(E, F, NULL);
    SPLICENODES(NULL, G, H);
    
    midTraverseTreeRecurse(nodeA);
    printf("\n");
    midTraverseTreeNoRecurse(nodeA);
    printf("\n");

    return 0;
}
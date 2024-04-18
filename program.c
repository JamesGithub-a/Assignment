#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode* bst_construct(int* inOrder, int* postOrder, int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd)
        return NULL;

    struct TreeNode* root = createNode(postOrder[*postIndex]);
    (*postIndex)--;

    int inIndex;
    for (inIndex = inStart; inIndex <= inEnd; inIndex++) {
        if (inOrder[inIndex] == root->val)
            break;
    }

    root->right = bst_construct(inOrder, postOrder, inIndex + 1, inEnd, postIndex);
    root->left = bst_construct(inOrder, postOrder, inStart, inIndex - 1, postIndex);

    return root;
}

void printBFS(struct TreeNode* root) {
    if (root == NULL)
        return;

    struct TreeNode* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct TreeNode* curr = queue[front++];
        printf("%d ", curr->val);

        if (curr->left)
            queue[rear++] = curr->left;
        if (curr->right)
            queue[rear++] = curr->right;
    }
}

int main() {
    int inOrder[] = {5, 10, 15, 20, 25, 30, 45};
    int postOrder[] = {5, 15, 10, 25, 45, 30, 20};
    int n = sizeof(inOrder) / sizeof(inOrder[0]);
    int postIndex = n - 1;

    struct TreeNode* root = bst_construct(inOrder, postOrder, 0, n - 1, &postIndex);

    printf("BFS traversal of the constructed BST:\n");
    printBFS(root);

    return 0;
}

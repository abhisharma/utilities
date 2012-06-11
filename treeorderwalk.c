/* This program traverses a binary search tree without using recursion */

// Required Includes
#include "stdio.h"
#include "stdlib.h"


// Data structures
struct tNode
{
	int key;
	struct tNode *left;
	struct tNode *right;
	struct tNode *parent;
};

typedef struct tNode treeNode;
#define  MAX_SIZE  100

// Initialize tree node
treeNode* InitNode(int key)
{
	treeNode *node = (treeNode*) malloc(sizeof(treeNode));
	node->left = node->right = node->parent = NULL;
	node->key = key;
	return node;	
}

// Insert node in tree based on key
treeNode* InsertNode(treeNode *root, int key)
{
	if (root == NULL)
	{
	       // Empty tree
		root = InitNode(key);
	}
	else
	{
		treeNode *cur = root;
		treeNode *p = NULL;
		// Find correct position
		while (cur != NULL)
		{
			p = cur;
			if (key < cur->key)
				cur = cur->left;
			else
				cur = cur->right;
		}
		// Now insert
		treeNode *t = InitNode(key);
		t->parent = p;
		if (key < p->key) p->left = t;
		else p->right = t;		
	}
	return root;
}


treeNode* CreateTree()
{
	treeNode *root = NULL;
	int n = 0;
	int value = 0;
	printf("\nEnter number of nodes in tree(Max 100) ");
	scanf("%d", &n);
	printf("\nEnter nodes\n");
	
	while (n-- > 0)
	{
		scanf("%d", &value);
		root = InsertNode(root, value);
	}
	return root;
}

// Stack implementation
treeNode *stack[MAX_SIZE];
int curPos = 0;

int isEmpty()
{
	return curPos < 0 ? 1 : 0;
}

void push(treeNode *k)
{
	stack[curPos++] = k;
}

treeNode* pop()
{
	return isEmpty() ? NULL : stack[--curPos];
}

// In order walk in which root is printed between left and right childen
void InOrderWalk(treeNode *root)
{
	push(root);
	
	treeNode *x = root->left;
	
	while(!isEmpty())
	{
		while (x != NULL)
		{
			push(x);
			x = x->left;
		}

		do
		{
			x = pop();
			if (x != NULL) printf("\n%d", x->key);
		} while (x!= NULL && x->right == NULL);

		if (x != NULL) x = x->right;	
	}
	printf("\n");

}

// Preorder walk in which root is printed before left and right child
void PreOrderWalk(treeNode *root)
{
	push(root);
	while (!isEmpty())
	{
		treeNode *x = pop();
		if (x != NULL) printf("\n%d", x->key);	
		if (x->right != NULL) push(x->right);
		if (x->left != NULL) push(x->left);
	}
	printf("\n");	
}

// Post order walk in which root is printed after left and right children
void PostOrderWalk(treeNode *root)
{
	push(root);
	
	treeNode *x = root->left;
	
	while(!isEmpty())
	{
		while (x != NULL)
		{
			push(x);
			x = x->left;
		}

		x = pop();

		if (x != NULL)
		{
		        // Check right subtree
			if (x->right != NULL)
			{
				push(x);
				x = x->right;
			}
			else
			{
				while(1)
				{		
					printf("\n%d", x->key);
					treeNode *oldX = x;
					x = pop();
					if (x != NULL)
					{
						if (oldX->parent != NULL && oldX->parent->right == oldX) continue;
						push(x);
						x = x->right;
					}
					break;
				}
			}
		}

	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	treeNode *root = CreateTree();
	printf("\nInorder traversal is following:");
	InOrderWalk(root);
	printf("\nPreorder traversal is following:");
	PreOrderWalk(root);
	printf("\nPostorder traversal is following:");
	PostOrderWalk(root);

	return 0;	
}

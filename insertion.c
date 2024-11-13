#include <stdio.h>
#include <stdlib.h>
struct node
{
  int data;
  struct node *left;
  struct node *right;
  int height;
};
int max(int a, int b)
{
  return a > b ? a : b;
}
int getHeight(struct node *root)
{
  if (root == NULL)
    return 0;

  return root->height;
}
int getBalanceFactor(struct node *root)
{
  if (root == NULL)
    return 0;

  return getHeight(root->left) - getHeight(root->right);
}
struct node* getSuccessor(struct node* curr)
{
  curr = curr->right;
  while(curr!=NULL && curr->left!=NULL)
  {
    curr=curr->left;
  }

  return curr;
}
struct node *nnode(int data)
{
  struct node *nnode = (struct node *)malloc(sizeof(struct node));
  nnode->data = data;
  nnode->left = NULL;
  nnode->right = NULL;
  nnode->height = 1;

  return nnode;
}
struct node *rotateRight(struct node *x)
{
  struct node *y = x->left;
  struct node *T2 = y->right;

  y->right = x;
  x->left = T2;

  x->height = 1 + max(getHeight(x->left), getHeight(x->right));
  y->height = 1 + max(getHeight(y->left), getHeight(y->right));

  return y;
}
struct node *rotateLeft(struct node *y)
{
  struct node *x = y->right;
  struct node *T2 = x->left;

  x->left = y;
  y->right = T2;

  x->height = 1 + max(getHeight(x->left), getHeight(x->right));
  y->height = 1 + max(getHeight(y->left), getHeight(y->right));

  return x;
}
struct node *insert(struct node *root, int data)
{
  if (root == NULL)
    return nnode(data);

  if (data < root->data)
  {
    root->left = insert(root->left, data);
  }
  else if (data > root->data)
  {
    root->right = insert(root->right, data);
  }
  else
  {
    return root;
  }

  root->height = 1 + max(getHeight(root->left), getHeight(root->right));

  int balance = getBalanceFactor(root);

  if (balance > 1 && data < root->left->data)
  {
    return rotateRight(root);
  }
  if (balance < -1 && data > root->right->data)
  {
    return rotateLeft(root);
  }
  if (balance > 1 && data > root->left->data)
  {
    root->left = rotateLeft(root->left);
    return rotateRight(root);
  }
  if (balance < -1 && data < root->right->data)
  {
    root->right = rotateRight(root->right);
    return rotateLeft(root);
  }

  return root;
}
struct node *delete(struct node *root, int data)
{
  if (root == NULL)
  {
    return root;
  }

  if (data < root->data)
  {
    root->left = delete (root->left, data);
  }
  else if (data > root->data)
  {
    root->right = delete (root->right, data);
  }
  else
  {
    if (root->left == NULL)
    {
      return root->right;
    }
    else if (root->right == NULL)
    {
      return root->left;
    }
    else
    {
      struct node *succ = getSuccessor(root);
      root->data = succ->data;
      root->right = delete (root->right, succ->data);

      return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalanceFactor(root);

    if (balance > 1 && data < root->left->data)
    {
      return rotateRight(root);
    }
    if (balance < -1 && data > root->right->data)
    {
      return rotateLeft(root);
    }
    if (balance > 1 && data > root->left->data)
    {
      root->left = rotateLeft(root->left);
      return rotateRight(root);
    }
    if (balance < -1 && data < root->right->data)
    {
      root->right = rotateRight(root->right);
      return rotateLeft(root);
    }

    return root;
  }
}
void inorder(struct node *root)
{
  if (root != NULL)
  {
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
  }
}
int main()
{
  struct node *root = NULL;
  root=insert(root, 20);
  root=insert(root, 80);
  root=insert(root, 60);
  root=insert(root, 10);
  root=insert(root, 70);
  root=insert(root, 40);
  root=insert(root, 30);

  inorder(root);
  printf("\n");

  root=delete(root, 70);

  inorder(root);
}
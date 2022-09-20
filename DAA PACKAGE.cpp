#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;
class Scheduling
{
   public:
   string jobid;
   int running_time;
   int total_exec;
};
Scheduling s1[100];
typedef struct RBT
{
  int data;
  int index;
  int color;
  RBT* left;
  RBT* right;
  RBT* parent;
}RBT;
typedef RBT *ptr;
class RedBlack
{
  private:
  ptr n;
  ptr root;
  void newNode(ptr node,ptr parent);
  void insertBalance(ptr k);
  int searchify(ptr node,int key);
  void deleteBalance(ptr node);
  void parents(ptr node1,ptr node2);
  void del1(ptr node,int key);
  void preOrder1(ptr node);
  void inOrder1(ptr node);
  void postOrder1(ptr node);
  void print1(ptr root,string s,bool last);
  public:
  RedBlack();
  int numCount=0;
  int ftc;
  void LL(ptr node);
  void ins(int key);
  void RR(ptr node);
  ptr minimum(ptr node);
  ptr maximum(ptr node);
  ptr successor(ptr x);
  ptr predecessor(ptr x);
  int depth1(ptr x);
  void preorder(){preOrder1(this->root);}
  void inorder(){inOrder1(this->root);}
  void postorder(){postOrder1(this->root);}
  int searchTree(int k) {return searchify(this->root, k);}
  ptr getRoot(){return this->root;}
  void del(int data){del1(this->root, data);}
  void print() {if (root) {print1(this->root, "", true);}}
  int depth() {return depth1(this->root);}
};
int RedBlack::depth1(ptr x)
{

    try
	{
		int totalDepth = 0;
		if (x!=nullptr)
		{
			int leftDepth = depth1(x->left);
			int rightDepth = depth1(x->right);
			int y = max(leftDepth, rightDepth);
			totalDepth = y + 1;
		}
		return totalDepth;
	}
	catch (exception_ptr& e)
	{
		cout << "Something happened and you broke the pointer... -_-" << endl;

	}
	return 0;
}
RedBlack::RedBlack()
{
    n=new RBT;
    n->color=0;
    n->left=n->right=n->parent= nullptr;
    root=n;
}
void RedBlack::newNode(ptr node,ptr parent)
{
    node->data=-1;
    node->parent=parent;
    node->left=node->right=nullptr;
    node->color=0;
}
void RedBlack::preOrder1(ptr node)
{
    if(node!=n)
    {
        cout<<node->data<<" "<<endl;
        preOrder1(node->left);
        preOrder1(node->right);
    }
}
void RedBlack::postOrder1(ptr node)
{
    if(node!=n)
    {
        postOrder1(node->left);
        postOrder1(node->right);
        cout<<node->data<<" "<<endl;
    }
}
void RedBlack::inOrder1(ptr node)
{
    if(node!=n)
    {
        inOrder1(node->left);
        cout<<node->data<<" "<<endl;
        inOrder1(node->right);
    }
}
int RedBlack::searchify(ptr s,int key)
{
    try
	{
		if ((s->data != key))
		{
			ftc++;
			if (s->data > key)
				searchify(s->left,key);
			else if(s->data<key)
				searchify(s->right,key);

		}
		else if(s->data==key)
    {
             int i;
             cout<<"Found"<<endl;
             cout<<"Job ID: "<<s1[s->index].jobid<<endl;
             cout<<"Running Time: "<<s1[s->index].running_time<<endl;
             cout<<"Total Execution: "<<s1[s->index].total_exec<<endl;
    }
        else
            cout<<"No found"<<endl;
		return ftc;
	}
	catch (exception_ptr& e)
	{
		cout << "Something happened and you broke the pointer... -_-" << endl;
	}
	return 0;
}
void RedBlack::deleteBalance(ptr node) {
    ptr r;
    while (node != root && node->color ==0) {
      if (node == node->parent->left) {
        r = node->parent->right;
        if (r->color == 1) {
          r->color = 0;
          node->parent->color = 1;
          LL(node->parent);
          r = node->parent->right;
        }

        if (r->left->color == 0 && r->right->color == 0) {
          r->color = 1;
          node = node->parent;
        } else {
          if (r->right->color == 0) {
            r->left->color = 0;
            r->color = 1;
            RR(r);
            r = node->parent->right;
          }

          r->color = node->parent->color;
          node->parent->color = 0;
          r->right->color = 0;
          LL(node->parent);
          node = root;
        }
      } else {
        r = node->parent->left;
        if (r->color == 1) {
          r->color = 0;
          node->parent->color = 1;
          RR(node->parent);
          r = node->parent->left;
        }

        if (r->right->color == 0 && r->right->color == 0) {
          r->color = 1;
          node = node->parent;
        } else {
          if (r->left->color == 0) {
            r->right->color = 0;
            r->color = 1;
            LL(r);
            r = node->parent->left;
          }

          r->color = node->parent->color;
          node->parent->color = 0;
          r->left->color = 0;
          RR(node->parent);
          node = root;
        }
      }
    }
    node->color = 0;
}
void RedBlack::parents(ptr node1,ptr node2)
{
    if(node1->parent==nullptr)
        root=node2;
    else if(node1==node1->parent->left)
        node1->parent->left=node2;
    else
        node1->parent->right=node2;
    node2->parent=node1->parent;
}
void RedBlack::del1(ptr node,int key)
{
    ptr z = n;
    ptr x, y;
    while (node != n) {
      if (node->data == key) {
        z = node;
      }

      if (node->data <= key) {
        node = node->right;
      } else {
        node = node->left;
      }
    }

    if (z == n) {
      cout << "Key not found in the tree" << endl;
      return;
    }

    y = z;
    int y_original_color = y->color;
    if (z->left == n) {
      x = z->right;
      parents(z, z->right);
    } else if (z->right == n) {
      x = z->left;
      parents(z, z->left);
    } else {
      y = minimum(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z) {
        x->parent = y;
      } else {
        parents(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }

      parents(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    delete z;
    if (y_original_color == 0) {
      deleteBalance(x);
    }
  }
void RedBlack::insertBalance(ptr k) {
    ptr u;
    while (k->parent->color == 1) {
      if (k->parent == k->parent->parent->right) {
        u = k->parent->parent->left;
        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->left) {
            k = k->parent;
            RR(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          LL(k->parent->parent);
        }
      } else {
        u = k->parent->parent->right;

        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->right) {
            k = k->parent;
            LL(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          RR(k->parent->parent);
        }
      }
      if (k == root) {
        break;
      }
    }
    root->color = 0;
}
void RedBlack::print1(ptr root, string s, bool last) {
    if (root != n) {
      cout << s;
      if (last) {
        cout << "R----";
        s += "   ";
      } else {
        cout << "L----";
        s += "|  ";
      }

      string sColor = root->color ? "RED" : "BLACK";
      cout << root->data << "(" << sColor << ")" << endl;
      print1(root->left, s, false);
      print1(root->right, s, true);
    }
}
ptr RedBlack::minimum(ptr node)
{
    while (node->left != n)
    {
      node = node->left;
    }
    return node;
}

ptr RedBlack::maximum(ptr node)
{
    while (node->right != n)
    {
      node = node->right;
    }
    return node;
}
ptr RedBlack::successor(ptr x)
{
    if (x->right != n)
    {
      return minimum(x->right);
    }

    ptr y = x->parent;
    while (y != n && x == y->right)
    {
      x = y;
      y = y->parent;
    }
    return y;
}

ptr RedBlack::predecessor(ptr x)
{
    if (x->left != n)
    {
      return maximum(x->left);
    }

    ptr y = x->parent;
    while (y != n && x == y->left)
    {
      x = y;
      y = y->parent;
    }

    return y;
}
void RedBlack::LL(ptr x) {
    ptr y = x->right;
    x->right = y->left;
    if (y->left != n) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

void RedBlack::RR(ptr x)
{
    ptr y = x->left;
    x->left = y->right;
    if (y->right != n) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

// Inserting a node
void RedBlack::ins(int key)
{
    static int count=0;
    numCount++;
    ptr node = new RBT;
    node->parent = nullptr;
    node->data = key;
    node->left = n;
    node->right = n;
    node->color = 1;
    node->index=count;
    count++;
    ptr y = nullptr;
    ptr x = this->root;

    while (x != n) {
      y = x;
      if (node->data < x->data) {
        x = x->left;
      } else if(node->data > x->data) {
        x = x->right;
      }
      else
        return;
    }

    node->parent = y;
    if (y == nullptr) {
      root = node;
    } else if (node->data < y->data) {
      y->left = node;
    } else {
      y->right = node;
    }

    if (node->parent == nullptr) {
      node->color = 0;
      return;
    }

    if (node->parent->parent == nullptr) {
      return;
    }

    insertBalance(node);
}
int main()
{
		RedBlack r1;
    s1[0].jobid="J104";s1[0].running_time=11;s1[0].total_exec=100;
    s1[1].jobid="J102";s1[1].running_time=12;s1[1].total_exec=110;
    s1[2].jobid="J103";s1[2].running_time=13;s1[2].total_exec=200;
    s1[3].jobid="J101";s1[3].running_time=14;s1[3].total_exec=160;
    s1[4].jobid="J108";s1[4].running_time=15;s1[4].total_exec=180;
    s1[5].jobid="J119";s1[5].running_time=16;s1[5].total_exec=120;
    s1[6].jobid="J110";s1[6].running_time=20;s1[6].total_exec=140;
    s1[7].jobid="J167";s1[7].running_time=26;s1[7].total_exec=132;
    s1[8].jobid="J208";s1[8].running_time=98;s1[8].total_exec=190;
    s1[9].jobid="J019";s1[9].running_time=29;s1[9].total_exec=200;
    int i;
    for(i=0;i<11;i++)
    {
      r1.ins(s1[i].running_time);
    }
    r1.inorder();
    //EXECUTION ALGORITHM
    r1.searchTree(26);
    r1.del(26);
    r1.inorder();

}


#include <iostream>
using namespace std;
//1=red,0=bleack;
struct Node{
  double key;
  Node *parent;
  Node *left;
  Node *right;
  int color;
};
//создаем указатель на структуру 
typedef Node *NodePtr;

class RBtree{
private:
	//через него будем указывать на корневой элемент
  NodePtr root;
  //через него будем создавать пустые листы (для удобства)
  NodePtr TNULL;
  //инициализируем нулевой элемент
  void nullnode(NodePtr node, NodePtr parent){
    node->key = 0;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->color = 0;
  }
  //функция для сохранения RB-свойств и глубины вызывается из функции вставки 
  void fix(NodePtr new_node){
    NodePtr temp;
    while (new_node->parent->color == 1){
    	//если отец елемента справа 
      if (new_node->parent == new_node->parent->parent->right){
        temp = new_node->parent->parent->left;
        if (temp->color == 1){
          temp->color = 0;
          new_node->parent->color = 0;
          new_node->parent->parent->color = 1;
          new_node = new_node->parent->parent;
        }
        else{
          if (new_node == new_node->parent->left){
            new_node = new_node->parent;
            rrotate(new_node);
          }
          new_node->parent->color = 0;
          new_node->parent->parent->color = 1;
          lrotate(new_node->parent->parent);
        }
      }
      else{
        temp = new_node->parent->parent->right;

        if (temp->color == 1){
          temp->color = 0;
          new_node->parent->color = 0;
          new_node->parent->parent->color = 1;
          new_node = new_node->parent->parent;
        }
        else{
          if (new_node == new_node->parent->right){
            new_node = new_node->parent;
            lrotate(new_node);
          }
          new_node->parent->color = 0;
          new_node->parent->parent->color = 1;
          rrotate(new_node->parent->parent);
        }
      }
      if (new_node == root){
        break;
      }
    }
    root->color = 0;
  }
  //функция вывода дерева на экран
  void printhelp(NodePtr root){
    if (root != TNULL){
      string sColor = root->color ? "RED" : "BLACK";
      cout << root->key << "(" << sColor << ")" << endl;
      printhelp(root->left);
      printhelp(root->right);
    }
  }

public:
	//конструктор
  RBtree(){
    TNULL = new Node;
    TNULL->color = 0;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
  }
  	//функция для выполнения условий указанных в вариантах заданий
  int serch(double key){
    bool check=false;
    NodePtr node=this->root;
    tryagain:
    while(node->key>key){
      check=true;
      if(node->key==key){
        cout << "there is an element in the tree" << "color is (";
        if(node->color==1){
          cout << "RED)" << endl;
          return 0;
        }
        else{
          cout << "BLACK)"<< endl;
          return 0;
        }
      }
      if(node->left!=TNULL){
        node=node->left;
      }
      else{
        cout << "there is NO an element in the tree" << endl;
        return 0;
      }
    }
    while(node->key<=key){
      check=true;
      if(node->key==key){
        cout << "there is an element in the tree" << "color is (";
        if(node->color==1){
          cout << "RED)" << endl;
          return 0;
        }
        else{
          cout << "BLACK)"<< endl;
          return 0;
        }
      }
      if(node->right!=TNULL){
        node=node->right;
      }
      else{
        cout << "there is NO an element in the tree" << endl;
        return 0;
      }
    }
    if(check!=false){
      goto tryagain;
    }
    cout << "there is NO an element in the tree" << endl;
    return 0;
  }
  	//функция для выполнения условий указанных в вариантах заданий
   void min_for(){
    NodePtr node=this->root;
    while (node->left != TNULL){
      node = node->left;
    }
    cout << "min=" << node->key << "(";
    if(node->color==1){
      cout << "RED)"<< endl;
    }
    else{
      cout << "BLACK)"<< endl; 
    }
  }
  //функция левого вращения
  void lrotate(NodePtr x){
    NodePtr y = x->right;
    x->right = y->left;
    if (y->left != TNULL){
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr){
      this->root = y;
    }
    else if (x == x->parent->left){
      x->parent->left = y;
    }
    else{
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }
	//функция правого вращения
  void rrotate(NodePtr x){
    NodePtr y = x->left;
    x->left = y->right;
    if (y->right != TNULL){
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr){
      this->root = y;
    }
    else if (x == x->parent->right){
      x->parent->right = y;
    }
    else{
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }
  //функция вставки(отсюда вызывается функция исправления )
  void insert(double key){
    NodePtr node = new Node;
    node->parent = nullptr;
    node->key = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = 1;

    NodePtr y = nullptr;
    NodePtr x = this->root;

    while (x != TNULL){
      y = x;
      if (node->key < x->key){
        x = x->left;
      }
      else{
        x = x->right;
      }
    }

    node->parent = y;
    if (y == nullptr){
      root = node;
    }
    else if (node->key < y->key){
      y->left = node;
    }
    else{
      y->right = node;
    }

    if (node->parent == nullptr){
      node->color = 0;
      return;
    }

    if (node->parent->parent == nullptr){
      return;
    }
    fix(node);
  }

  void show(){
    if (root)
    {
      printhelp(this->root);
    }
  }
};

int main(){
  RBtree answer;
  int n;
  double m;
  cout << "input size" << endl;
  cin >> n;
  int *arr=new int[n];
  cout << "input sequence N" << endl;
  for(int i=0;i<n;i++){
    tryM:
    cin >> m;
    for(int j=0;j<n;j++){
      if(arr[j]==m){
        cout << "already in the tree" << endl;
        goto tryM;
      }
    }
    arr[i]=m;
    answer.insert(m);
    answer.show();
    answer.min_for();  
  }
  for(int i=0;i<n;i++){
    arr[i]=0;
  }
  cout << "input size M" << endl;
  cin >> n;
  cout << "input sequence M" << endl;
  for(int i=0;i<n;i++){
    tryN:
    cin >> m;
    for(int j=0;j<n;j++){
      if(arr[j]==m){
        cout << "already in the tree" << endl;
        goto tryN;
      }
    }
    answer.serch(m);
  }
  return 0;
}
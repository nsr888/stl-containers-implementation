#include <iostream>
#include <queue>
#include <unordered_map>

struct Node {
    Node *left;
    Node *right;
    int data;
    int height;
};

class AVL {
public:
    AVL(){
        this->root = NULL;
    };
    ~AVL(){};

    void display() {
        printTree(this->root, "", false);
    };
    void insert(int data) {
        this->root = insert(this->root, data);
    };
    void remove(int data) {
        this->root = deleteNode(this->root, data);
    };
private:
    struct Node * root;
    struct Node* insert(struct Node *r,int data){
        if(r==NULL){
            struct Node *n;
            n = new struct Node;
            n->data = data;
            r = n;
            r->left = r->right = NULL;
            r->height = 1; 
            return r;             
        }
        else{
            if(data < r->data)
            r->left = insert(r->left,data);
            else
            r->right = insert(r->right,data);
        }
        r->height = calheight(r);
        if(bf(r)==2 && bf(r->left)==1){
            r = llrotation(r);
        }
        else if(bf(r)==-2 && bf(r->right)==-1){
            r = rrrotation(r);
        }
        else if(bf(r)==-2 && bf(r->right)==1){
            r = rlrotation(r);
        }
        else if(bf(r)==2 && bf(r->left)==-1){
            r = lrrotation(r);
        }        
        return r;
    }

    struct Node * deleteNode(struct Node *p,int data){
        if(p->left == NULL && p->right == NULL){
                if(p==this->root)
                    this->root = NULL;
            delete p;
            return NULL;
        }
        struct Node *q;
        if(p->data < data){
            p->right = deleteNode(p->right,data);
        }
        else if(p->data > data){
            p->left = deleteNode(p->left,data);
        }
        else{
            if(p->left != NULL){
                q = inpre(p->left);
                p->data = q->data;
                p->left=deleteNode(p->left,q->data);
            }
            else{
                q = insuc(p->right);
                p->data = q->data;
                p->right = deleteNode(p->right,q->data);
            }
        }
        if(bf(p)==2 && bf(p->left)==1){ p = llrotation(p); }                  
        else if(bf(p)==2 && bf(p->left)==-1){ p = lrrotation(p); }
        else if(bf(p)==2 && bf(p->left)==0){ p = llrotation(p); }
        else if(bf(p)==-2 && bf(p->right)==-1){ p = rrrotation(p); }
        else if(bf(p)==-2 && bf(p->right)==1){ p = rlrotation(p); }
        else if(bf(p)==-2 && bf(p->right)==0){ p = llrotation(p); }
        return p;
    }
    int calheight(struct Node *p){
        if(p->left && p->right){
        if (p->left->height < p->right->height)
            return p->right->height + 1;
        else return  p->left->height + 1;
        }
        else if(p->left && p->right == NULL){
           return p->left->height + 1;
        }
        else if(p->left ==NULL && p->right){
           return p->right->height + 1;
        }
        return 0;
    }
    int bf(struct Node *n){
        if(n->left && n->right){
            return n->left->height - n->right->height; 
        }
        else if(n->left && n->right == NULL){
            return n->left->height; 
        }
        else if(n->left== NULL && n->right ){
            return -n->right->height;
        }
        return 0;
    }

    struct Node * llrotation(struct Node *n){
        struct Node *p;
        struct Node *tp;
        p = n;
        tp = p->left;

        p->left = tp->right;
        tp->right = p;

        return tp; 
    }


    struct Node * rrrotation(struct Node *n){
        struct Node *p;
        struct Node *tp;
        p = n;
        tp = p->right;

        p->right = tp->left;
        tp->left = p;

        return tp; 
    }


    struct Node * rlrotation(struct Node *n){
        struct Node *p;
        struct Node *tp;
        struct Node *tp2;
        p = n;
        tp = p->right;
        tp2 =p->right->left;

        p -> right = tp2->left;
        tp ->left = tp2->right;
        tp2 ->left = p;
        tp2->right = tp; 
        
        return tp2; 
    }
    struct Node * lrrotation(struct Node *n){
        struct Node *p;
        struct Node *tp;
        struct Node *tp2;
        p = n;
        tp = p->left;
        tp2 =p->left->right;

        p -> left = tp2->right;
        tp ->right = tp2->left;
        tp2 ->right = p;
        tp2->left = tp; 
        
        return tp2; 
    }

     struct Node* inpre(struct Node* p){
        while(p->right!=NULL)
            p = p->right;
        return p;    
    }

    struct Node* insuc(struct Node* p){
        while(p->left!=NULL)
            p = p->left;
        return p;    
    }

    /* print tree for testing only */
    void printTree(Node *node, std::string prefix, bool isLeft) {
        if (node != nullptr) {
            std::cout << prefix;
            std::cout << (isLeft ? "├──" : "└──" );
            std::cout << node->data << std::endl;
            printTree(node->left, prefix + (isLeft ? "│   " : "    "), true);
            printTree(node->right, prefix + (isLeft ? "│   " : "    "), false);
        }
    }
    
};


int main(){

    AVL b;

    b.insert(33);
    b.insert(13);
    b.insert(53);
    b.insert(9);
    b.insert(21);
    b.insert(61);
    b.insert(8);
    b.insert(11);
    b.display();
    b.remove(13);
    b.display();
  
}

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class lexicon{
public:
    lexicon():root(nullptr){

        fre=1;
    }
    ~lexicon() {
        purge(root);
    }

    void insert(const string &s){
        if(root == nullptr){
            root = new node;
            root->left = nullptr;
            root->right = nullptr;
            root->data = s;
            root->freq=fre;

        }else {


            insertt(s, root, fre);
        }
    }

    int lookup(const string &s) const {
        node *p = root;
        int ans = 0;
        while(p!=nullptr){
            if(s < p->data){
                p=p->left;
            }else if(s > p->data){
                p=p->right;
            }else{
                ans = p->freq;
                break;
            }
        }
        return ans;
    }
    int depth(const string &s) const {
        node *p = root;
        int depth = -1; int d=0;
        while(p!=nullptr){

            if(s < p->data){
                d++;
                p=p->left;
            }else if(s > p->data){
                d++;
                p=p->right;
            }else{
                depth = d;
                break;
            }
        }
        return depth;
    }
    void replace(const string &s1, const string &s2){
        if(remove(root, s1, root, true)){
            insert(s2);
        }
    }

    friend ostream &operator << (ostream &out, const lexicon &l) {
        //out << l.root->data << "\n";

        printt(l.root, out);
        return out;

    }
protected:
    struct node{
        string data;
        int freq{};
        node *left{}, *right{};
    };
    void purge(node *&r){
        if(r==nullptr) return;
        if(r->left == nullptr && r->right == nullptr){
            delete r;
        }else{
            purge(r->left);
            purge(r->right);
            delete r;
        }
    }
    void insertt(const string &s, node *&p, int how){

        if(p->data == s){
            p->freq+=how;
        }else if(p->data > s){
            if(p->left == nullptr){
                node *t = new node;
                t->data = s;
                t->freq=how;
                t->left = t->right = nullptr;
                p->left =t;
            }else{
                insertt(s,p->left, how);
            }
        }else{
            if(p->right == nullptr){
                node *t = new node;
                t->data = s;
                t->freq=how;
                t->left = t->right = nullptr;
                p->right =t;
            }else{
                insertt(s,p->right, how);
            }
        }
        fre=1;
    }
    bool remove(node *t, const string &s, node *&previous, bool rl){
        if(t==nullptr){
            return false;
        }
        if(t->data > s){
            return remove(t->left, s, t, false);
        }else if(t->data < s){
            return remove(t->right, s, t, true);
        }else{
            fre=t->freq;
            if(t == root) {


                if(t->left == nullptr && t->right == nullptr){

                    root = nullptr;
                    delete t;

                }else if(t->left == nullptr){
                    root = t->right;
                    delete t;
                }else if(t->right == nullptr){
                    root = t->left;
                    delete t;

                }else{
                    node *ff =t->left;
                    node *prev = t;
                    while(ff->right!=nullptr){
                        prev =ff;
                        ff=ff->right;
                    }
                    t->data=ff->data;
                    t->freq=ff->freq;
                    if(prev!=t){
                        prev->right = nullptr;}
                    else{
                        t->left=nullptr;
                    }
                    delete ff;

                }
            }
            else if(t->right == nullptr && t->left == nullptr){

                if(rl){
                    previous->right = nullptr;
                    delete t;
                }else{
                    previous->left = nullptr;
                    delete t;
                }

            }else if(t->left == nullptr){
                if(rl){
                    previous->right = t->right;
                }else{
                    previous->left = t->right;
                }
                delete t;
            }else if(t->right == nullptr){
                if(rl){
                    previous->right = t->left;
                }else{
                    previous->left = t->left;
                }
                delete t;
            }else{
                node *ff =t->left;
                node *prev = t;
                while(ff->right!=nullptr){
                    prev =ff;
                    ff=ff->right;
                }
                t->data=ff->data;
                t->freq=ff->freq;
                if(prev!=t){
                    prev->right = nullptr;}
                else{
                    t->left=nullptr;
                }
                delete ff;

            }
            return true;
        }
    }
    static void printt(node *t, ostream &out){
        if(t!=nullptr){
            printt(t->left, out);
            out << t->data << " " << t->freq << "\n";
            printt(t->right, out);
        }
    }
    node *root;
    int fre;
};

int main() {
    lexicon l;
    l.insert("the");
    l.insert("boy");
    l.insert("and");
    l.insert("the");
    l.insert("wolf");

    cout << l;
    cout << l.lookup("and") << " " << l.depth("and") << "\n";
    cout << l.lookup("boy") << " " << l.depth("boy") << "\n";
    cout << l.lookup("the") << " " << l.depth("the") << "\n";
    cout << l.lookup("wolf") << " " << l.depth("wolf") << "\n";
    cout << l.lookup("dummy") << " " << l.depth("dummy") << "\n";
    l.replace("and", "dummy");
    cout << l.lookup("wolf") << " " << l.depth("wolf") << "\n";
    cout << l.lookup("dummy") << " " << l.depth("dummy") << "\n";
    l.replace("boy", "dummy");
    cout << l.lookup("wolf") << " " << l.depth("wolf") << "\n";
    cout << l.lookup("dummy") << " " << l.depth("dummy") << "\n";
    l.replace("the", "dummy");
    cout << l.lookup("wolf") << " " << l.depth("wolf") << "\n";

    return 0;
}

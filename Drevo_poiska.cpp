#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
// функции вывода для print4, оставил их для себя(с помощью них делела пероворот)

template<typename T> std::string toString(const T &t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

template<typename T2>
struct treeNode
{
    treeNode* left;
    treeNode* right;
    T2 value;
    int height;
    
    treeNode(T2 value)
    {
        this->left = nullptr;
        this->right = nullptr;
        this->value = value;
        this->height = 1;
    }
    ~treeNode()
    {
        this->left = nullptr;
        this->right = nullptr;
        this->height = 0;
    }
    
    
};

template <typename T2>
struct avlTree
{
    treeNode <T2> * root;
    
    avlTree()
    {
        root = nullptr;
    }
    
    ~avlTree()
    {
        
        root = emptyTree(root);
    }
    
    treeNode <T2>* emptyTree(treeNode <T2>* n)
    {
        
        if (!n) return nullptr;
        if (n->left) emptyTree(n->left);
        if (n->right) emptyTree(n->right);
        
        free(n->left);
        n->left = nullptr;
        free(n->right);
        n->right = nullptr;
        
        return nullptr;
    }
    
    int getMax(int a, int b)
    {
        if (a > b) return a;
        return b;
    }
    
    int height(treeNode <T2>* n)
    {
        if (!n) return 0;
        return n->height;
    }
    
    int balanceFactor(treeNode<T2>* n)
    {
        return height(n->right)-height(n->left);
    }
    
    treeNode<T2>* rotateRight(treeNode<T2>* n)
    {
        treeNode<T2>* tmp = n->left;
        n->left = tmp->right;
        tmp->right = n;
        
        n->height = getMax (height(n->left), height(n->right)) + 1;
        tmp->height = getMax (height(tmp->left), height(tmp->right)) + 1;
        
        return tmp;
    }
    
    treeNode<T2>* rotateLeft(treeNode<T2>* n)
    {
        treeNode<T2>* tmp = n->right;
        n->right = tmp->left;
        tmp->left = n;
        
        n->height = getMax (height(n->left), height(n->right)) + 1;
        tmp->height = getMax (height(tmp->left), height(tmp->right)) + 1;
        
        return tmp;
    }

public: void addNode (T2 value)
    {
        root = addNode(root, value);
    }

private: treeNode<T2>* addNode(treeNode<T2>* n, T2 value)
    {
        if( !n ) return new treeNode<T2>(value);
        if( value<n->value )
            n->left = addNode(n->left,value);
        else
            n->right = addNode(n->right,value);
        
        n->height = getMax (height(n->left), height(n->right)) + 1;
        
        if( balanceFactor(n)>1 )
        {
            if( balanceFactor(n->right) < 0 )
                n->right = rotateRight(n->right);
            return rotateLeft(n);
        }
        if( balanceFactor(n)<-1 )
        {
            if( balanceFactor(n->left) > 0  )
                n->left = rotateLeft(n->left);
            return rotateRight(n);
        }
        return n;
        
    }

public: void print(){ print( root);}
private: void print (treeNode<T2>* n)
    {
        if (!n) return;
        print(n->left);
        std::cout << n->value << " ";
        print(n->right);
    }

public: void print2(){ print2(0, root);}
private: void print2 (int level, treeNode<T2>* n)
    {
        if (!n) return;
        print2(level + 1, n->left);
        for (int i = 0; i < level; i++)
        { std::cout << "  "; }
        std::cout << n->value << std::endl;
        print2(level + 1, n->right);
        
    }

public: void print3(){ print3(0, root);}
private: void print3 (int level, treeNode<T2>* n)
    {
        if (!n) return;
        print3(level + 1, n->right);
        for (int i = 0; i < level; i++)
        { std::cout << "  "; }
        
        std::cout << n->value << std::endl;
        print3(level + 1, n->left);
    }
    

private: void print4(int level, treeNode<T2>* n, std::string & str)
    {
        if (!n) return;
        
        print4(level + 1, n->left, str);
        for (int i = 0; i < level; i++)
        { str = str + "   " + "  "; }
        
        str = str + toString(n->value) + "\n";
        print4(level + 1, n->right, str);
    }

public: void print4()
    {
        std::string str;
        
        print4(0, root, str);
        
        int lineCount = 1;
        int charCount = 0;
        int maxCharCount = 1;
        
        for (int i = 0; i < (str.size()); i++)
        {
            if (str[i] == '\n')
            {
                lineCount++;
                if (maxCharCount < charCount) {maxCharCount = charCount;}
                charCount = 0;
            }
            else charCount++;
        }
        
        std::string * input = new std::string [lineCount];
        char ** output = new char * [maxCharCount] ;
        for (int i = 0; i < maxCharCount; i++)
        {
            output[i] = new char[lineCount];
            for (int j = 0; j < lineCount; j++)
                output[i][j] = ' ';
        }
        int prevLine = 0;
        int curLine = 0;
        int i = 0, j = 0;
        
        for ( i = 0; i < (str.size()); i++)
        {
            if (str[i] == '\n')
            {
                input[curLine] = str.substr(prevLine, (i - prevLine));
                curLine++;
                prevLine = i+1;
            }
        }
        
        j = 0;
        for (int k = 0; k < lineCount; k++ )
        {
            std::string line = input[k];
            for (char c : line)
            {
                output[j][k] = c;
                j++;
            }
            j=0;
        }
        
        delete [] input;
        
        std::string ** s = new std::string * [maxCharCount];
        for (int i = 0 ; i < maxCharCount; i++)
        {
            s[i]= new std::string  [lineCount];
            for (int j = 0; j < lineCount; j ++)
            {
                s[i][j] = "";
            }
        }
        
        for(int i=0; i<maxCharCount; i++){
            for(int j=0;j<lineCount; j++)
            {
                int k = 0;
                int f = 0;
                
                while ( k+i < maxCharCount && output[i+k][j] != ' ')
                {
                    s[i][j] = s[i][j] + output[i+k][j];
                    output[i+k][j] = ' ';
                    
                    k++;
                }
            }
        }
        
        for(int i=0; i < maxCharCount; i++)
        
        {
            for(int j=0; j < lineCount; j++)
            {
                std::cout << s[i][j] << "\t";
            }
            
            std::cout << std::endl;
        }
        std::cout << "------------------------------------------------------------------------------------------------------------------------------------" <<std::endl;
        delete [] output;
        delete [] s;
        
    }

private: treeNode<T2>* findMin(treeNode<T2> * n)
    {
        if(n == nullptr)
            return nullptr;
        else if(n->left == nullptr)
            return n;
        else
            return findMin(n->left);
    }

public: void deleteNode(T2 value)
    {
        root = deleteNode(root, value);
    }

private: treeNode<T2>* deleteNode(treeNode<T2>* n, T2 value)
    {
        treeNode<T2>* temp;
        if(n == nullptr)
            return nullptr;
        
        else if(value < n->value)
            n->left = deleteNode( n->left, value);
        else if(value > n->value)
            n->right = deleteNode(n->right,value );
        else if(n->left && n->right)
        {
            temp = findMin(n->right);
            n->value = temp->value;
            n->right = deleteNode(n->right, n->value);
        }
        else
        {
            temp = n;
            if(n->left == nullptr)
                n = n->right;
            else if(n->right == nullptr)
                n = n->left;
            delete temp;
        }
        if(n == nullptr)
            return n;
        
        n->height = getMax(height(n->left), height(n->right))+1;
        
        if( balanceFactor(n)>1 )
        {
            if( balanceFactor(n->right) < 0 )
                n->right = rotateRight(n->right);
            return rotateLeft(n);
        }
        if( balanceFactor(n)<-1 )
        {
            if( balanceFactor(n->left) > 0  )
                n->left = rotateLeft(n->left);
            return rotateRight(n);
        }
        return n;
    }
};

struct userType
{
    int x, y;
    
    userType()
    {
        userType(0,0);
    }
    userType(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    
    bool operator==(const userType & ut)
    {
        if ((this->x == ut.x) && (this->y == ut.y)) { return true;};
        
        return false;
    }
    
    bool operator!=(const userType & ut)
    {
        if ((this->x != ut.x) || (this->y != ut.y)) { return true;};
        
        return false;
    }
    
    bool operator<(const userType & ut)
    {
        if ((this->x < ut.x) && (this->y < ut.y)) { return true;};
        
        return false;
    }
    
    bool operator>(const userType & ut)
    {
        if ((this->x > ut.x) && (this->y > ut.y)) { return true;};
        
        return false;
    }
};

std::ostream & operator<< (std::ostream& os, const userType& ut)
{
    os << "(" << ut.x << "," << ut.y << ")";
    return os;
}

std::istream & operator>> (std::istream& is, userType& ut)
{
    is >> ut.x;
    is >> ut.y;
    return is;
}



int main ()
{
    int l = 0;
    int k1;
    userType k;
    avlTree <userType>* tree = new avlTree<userType>();
    avlTree <int>* tree2 = new avlTree<int>();
    
    for (int i = 1; i <= 15 ; i++)
    {
        tree2->addNode(i);
        tree2->print4();
    }
    
    std::cout << "If you won't delete element turn 1" << std::endl;
    std::cin >> l;
    while (l==1)
    {
        std::cout << "Enter element: ";
        std::cin >> k1;
        tree2->deleteNode(k1);
        tree2->print4();
        std::cout << "If you won't continue turn 1, else turn any other value" << std::endl;
        std::cin >> l;
    }
    
    std::cout << "userType" << std::endl;
    
    for (int i = 1; i <= 15 ; i++)
    {
        userType ut (i,i);
        tree->addNode(ut);
        tree->print4();
    }
    
    std::cout << "If you won't delete element turn 1" << std::endl;
    std::cin >> l;
    while (l==1)
    {
        std::cout << "Enter element: ";
        std::cin >> k;
        tree->deleteNode(k);
        tree->print4();
        std::cout << "If you won't continue turn 1, else turn any other value" << std::endl;
        std::cin >> l;
    }
    delete tree;
    delete tree2;
    return 0;
}

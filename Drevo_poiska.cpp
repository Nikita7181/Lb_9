#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

template<typename T> std::string toString(const T &t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

struct treeNode
{
    treeNode* left;
    treeNode* right;
    int value;
    int height;
    
    treeNode(int value)
    {
        this->left = NULL;
        this->right = NULL;
        this->value = value;
        this->height = 1;
    }
    ~treeNode()
    {
        this->left = NULL;
        this->right = NULL;
        this->value = 0;
        this->height = 0;
    }
};


struct avlTree
{
    treeNode * root;
    
    avlTree()
    {
        root = NULL;
    }
    
    int getMax(int a, int b)
    {
        if (a > b) return a;
        return b;
    }
    
    int height(treeNode* n)
    {
        if (!n) return 0;
        return n->height;
    }
    
    int balanceFactor(treeNode* n)
    {
        return height(n->right)-height(n->left);
    }
    
    treeNode* rotateRight(treeNode* n)
    {
        treeNode* tmp = n->left;
        n->left = tmp->right;
        tmp->right = n;
        
        n->height = getMax (height(n->left), height(n->right)) + 1;
        tmp->height = getMax (height(tmp->left), height(tmp->right)) + 1;
        
        return tmp;
    }
    
    treeNode* rotateLeft(treeNode* n)
    {
        treeNode* tmp = n->right;
        n->right = tmp->left;
        tmp->left = n;
        
        n->height = getMax (height(n->left), height(n->right)) + 1;
        tmp->height = getMax (height(tmp->left), height(tmp->right)) + 1;
        
        return tmp;
    }

public: void addNode (int value)
    {
        root = addNode(root, value);
    }

private: treeNode* addNode(treeNode* n, int value)
    {
        if( !n ) return new treeNode(value);
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
private: void print (treeNode* n)
    {
        if (!n) return;
        print(n->left);
        std::cout << n->value << " ";
        print(n->right);
    }

public: void print2(){ print2(0, root);}
private: void print2 (int level, treeNode* n)
    {
        if (!n) return;
        print2(level + 1, n->left);
        for (int i = 0; i < level; i++)
        { std::cout << "  "; }
        std::cout << n->value << std::endl;
        print2(level + 1, n->right);
        
        
    }

public: void print3(){ print3(0, root);}
private: void print3 (int level, treeNode* n)
    {
        if (!n) return;
        print3(level + 1, n->right);
        for (int i = 0; i < level; i++)
        { std::cout << "  "; }
        
        std::cout << n->value << std::endl;
        print3(level + 1, n->left);
        
        
    }


private: void print4(int level, treeNode * n, /*std::ostream & os*/ std::string & str)
    {
        if (!n) return;
        
        print4(level + 1, n->left, str);
        for (int i = 0; i < level; i++)
        { str = str + "   "; }
        
        str = str + toString(n->value) + "\n";
        print4(level + 1, n->right, str);
    }

public: void print4()
    {
        std::string str;
        
        print4(0, root, str);
        
        //std::cout << str;
        
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
        //std::cout << "lineCount: " << lineCount << std::endl << "maxCharCount: " << maxCharCount;
        
        std::string input[lineCount];
        char ** output = new char * [maxCharCount] ; //[maxCharCount][lineCount]
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
        
        
        i = 0;
        j = 0;
        for (std::string line : input)
        {
            for (char c : line)
            {
                output[j][i] = c;
                j++;
            }
            i++;
            j=0;
        }
        
        for(int i=0; i<maxCharCount-1; i++){
            for(int j=0;j<lineCount; j++)
            {
                if (output[i][j] != ' ' && output[i+1][j] != ' ')
                {
                    output[i][j+1] = output[i+1][j];
                    output[i+1][j] = ' ';
                }
            }
        }
        
        for(int j=0; j<maxCharCount; j++){
            for(int i=0;i<lineCount-1; i++)
            {
                if (output[j][i] != ' ' && output[j][i+1] != ' ')
                {
                    std::cout << "\t" << output[j][i] << output[j][i+1] << "\t";
                    i++;
                }
                else
                    std::cout << "\t" << output[j][i];
                
            }
            
            std::cout << std::endl;
        }
        std::cout << "------------------------------------------------------------------------------------------------------------------------------------" <<std::endl;
        delete [] output;
        output = NULL;
        
    }

private: treeNode* findMin(treeNode * n)
    {
        if(n == NULL)
            return NULL;
        else if(n->left == NULL)
            return n;
        else
            return findMin(n->left);
    }

public: void deleteNode(int value)
    {
        root = deleteNode(root, value);
    }

private: treeNode* deleteNode(treeNode* n, int value)
    {
        treeNode* temp;
        if(n == NULL)
            return NULL;
        
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
            if(n->left == NULL)
                n = n->right;
            else if(n->right == NULL)
                n = n->left;
            delete temp;
        }
        if(n == NULL)
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






int main ()
{
    int k = 0;
    avlTree * tree = new avlTree();
    for (int i = 1; i <= 14 ; i++)
    {
        tree->addNode(i);
        tree->print4();
    }
    std::cout << "Enter element: ";
    std::cin >> k;
    tree->deleteNode(k);
    tree->print4();
    std::cout << "Enter element: ";
    std::cin >> k;
    tree->deleteNode(k);
    tree->print4();
    std::cout << "Enter element: ";
    std::cin >> k;
    tree->deleteNode(k);
    tree->print4();
    return 0;
}

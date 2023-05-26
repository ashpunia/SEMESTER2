/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree; 

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////

template <class T>
class BPlusTree 
{
public:
    // Constructors & Destructor
    BPlusTree(int s) 

    {
        m_root = NULL;
        m_degree = s;
    }
    //copy constructor
    BPlusTree(const BPlusTree<T>& old) 
    {
        m_degree = old.m_degree;
        m_root = copy_tree(old.m_root, NULL);
    }
    //overloading the operator
    BPlusTree<T>& operator=(const BPlusTree<T>& old) 
    {
        if (&old != this)
        {
            this->destroy_tree(m_root);
            m_root = this->copy_tree(old.m_root, NULL);
            m_degree = old.m_degree;
        }
        return *this;
    }
    //cute little destructor
    ~BPlusTree() 
    {
        this->destroy_tree(m_root);
        m_root = NULL;
    }
    
    // Find & Insert (recursive ones)
    BPlusTreeNode<T>* find(const T& key) const { return find(key, m_root); }
    void insert(const T& key) { insert(key, m_root, NULL); }
    
    // Print sideways
    void print_sideways(std::ostream& outfile) const 
    {
        print_sideways(outfile, m_root, 0);
    }

    void print_BFS(std::ostream& outfile) const;
private:
    BPlusTreeNode<T>* m_root;
    int m_degree;
    
    // Private helper functions
    BPlusTreeNode<T>* copy_tree(BPlusTreeNode<T>* old_root,
                                BPlusTreeNode<T>* the_parent);
    void destroy_tree(BPlusTreeNode<T>* p);
    BPlusTreeNode<T>* find(const T& key, BPlusTreeNode<T>* p) const;
    void create_new_parent(BPlusTreeNode<T>*& p);
    void insert_key(const T& key,
                 BPlusTreeNode<T>*& p,
                 BPlusTreeNode<T>* the_parent,
                 unsigned int i);
    void insert(const T& key,
                BPlusTreeNode<T>*& p,
                BPlusTreeNode<T>* the_parent);
    void print_sideways(std::ostream& outfile, BPlusTreeNode<T>* p, int level) const;
};

//this is for my copy constructor, it copies the tree
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::copy_tree(BPlusTreeNode<T>* old_root,
                                          BPlusTreeNode<T>* the_parent) 
{
    // Base case
    if (old_root == NULL) return NULL;
    
    // Dynamically allocate new node and
    BPlusTreeNode<T>* tmp = new BPlusTreeNode<T>();
    
    // Copy children nodes recursively
    for (unsigned int i = 0; i < old_root->children.size(); ++i)
        tmp->children.push_back(copy_tree(old_root->children[i], tmp));
    
    // Everything else
    tmp->keys = old_root->keys;
    tmp->parent = the_parent;
    
    // Finish for one tree
    return tmp;
}

//destroys my tree
template <class T>
void BPlusTree<T>::destroy_tree(BPlusTreeNode<T>* p) 
{
    // Base case
    if (p == NULL) return;
    
    // Delete recursively
    for (unsigned int i = 0; i < p->children.size(); ++i)
        destroy_tree(p->children[i]);
    
    delete p;
}

//find the node in the tree that I'm looking for
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::find(const T& key, BPlusTreeNode<T>* p) const 
{
    // return NULL if tree is empty
    if (this->m_root == NULL) return NULL;
    
    // Find recursively
    unsigned int i = 0;
    for (; i < p->keys.size(); ++i) 
    {
        if (key < p->keys[i]) 
        { // key in left child node or does not exist
            if (p->is_leaf()) return p;
            else return find(key, p->children[i]);
        }
    }
    if (p->is_leaf()) return p; // key does not exist
    else return find(key, p->children[i]); // key might in rightmost child node
}

//This function creates a new parent node for a B+ tree when the current root node is full. 
//It splits the keys and children of the full root node into two halves, 
//creates a new child node to hold the second half, and creates a new parent node to 
//hold the first half and the new child node. The new parent node becomes the new root of the B+ tree.
template <class T>
void BPlusTree<T>::create_new_parent(BPlusTreeNode<T>*& p) 
{
    // Calculate two nodes' size
    unsigned int first_half = p->keys.size() / 2;
    unsigned int second_half;
    if (p->is_leaf())
        second_half = p->keys.size() - first_half;
    else second_half = p->keys.size() - first_half - 1;
    
    // create new child node and split keys
    BPlusTreeNode<T>* new_child = new BPlusTreeNode<T>();
    while (new_child->keys.size() != second_half) 
    {
        new_child->keys.insert(new_child->keys.begin(), p->keys.back());
        p->keys.pop_back();
    }
    
    // split children nodes for non-leaf node
    if (!p->is_leaf()) 
    {
        while (new_child->children.size() != new_child->keys.size() + 1) 
        {
            new_child->children.insert(new_child->children.begin(),
                                       p->children.back());
            new_child->children.front()->parent = new_child;
            p->children.pop_back();
        }
    }
    
    // create new parent node
    BPlusTreeNode<T>* new_parent = new BPlusTreeNode<T>();
    p->parent = new_parent;
    new_child->parent = new_parent;
    if (p->is_leaf()) new_parent->keys.push_back(new_child->keys.front());
    else 
    {
        new_parent->keys.push_back(p->keys.back());
        p->keys.pop_back();
    }
    new_parent->children.push_back(p);
    new_parent->children.push_back(new_child);
    this->m_root = new_parent;
}

template <class T>
void BPlusTree<T>::insert_key(const T& key, BPlusTreeNode<T>*& p, BPlusTreeNode<T>* the_parent, unsigned int i)
 {

    // If p is not a leaf node, search for the child node that the new key should be inserted into
    if (!p->is_leaf()) 
    {
        // Recursively call the insert function on the child node
        insert(key, p->children[i], p);

        // If the child node has too many keys (exceeds the degree limit of the tree), split it
        if (p->children[i]->keys.size() >= this->m_degree) 
        {
            // Calculate the sizes of the two resulting nodes
            unsigned int first_half = p->children[i]->keys.size() / 2;
            unsigned int second_half;
            if (p->children[i]->is_leaf())
                second_half = p->children[i]->keys.size() - first_half;
            else second_half = p->children[i]->keys.size() - first_half - 1;

            // Create a new node to hold the second half of the keys and children
            BPlusTreeNode<T>* new_child = new BPlusTreeNode<T>();
            new_child->parent = p;

            // Move the second half of the keys from the original node to the new node
            while (new_child->keys.size() != second_half) 
            {
                new_child->keys.insert(new_child->keys.begin(), p->children[i]->keys.back());
                p->children[i]->keys.pop_back();
            }

            // If the original node is not a leaf node, move the second half of the children to the new node
            if (!p->children[i]->is_leaf()) 
            {
                while (new_child->children.size() != new_child->keys.size() + 1) 
                {
                    new_child->children.insert(new_child->children.begin(),
                        p->children[i]->children.back());
                    new_child->children.front()->parent = new_child;
                    p->children[i]->children.pop_back();
                }
            }

            // Extract the key from the new child node that should be inserted into the parent node's keys vector
            T parent_key(p->children[i]->keys.back());
            if (p->children[i]->is_leaf())
                parent_key = new_child->keys.front();
            else
                p->children[i]->keys.pop_back();

            // Insert the parent key and the new child node into the parent node's keys and children vectors
            typename std::vector<T>::iterator keys_itr = p->keys.begin();
            typename std::vector<BPlusTreeNode<T>*>::iterator children_itr;
            children_itr = p->children.begin();
            p->keys.insert(keys_itr + i, parent_key);
            p->children.insert(children_itr + i + 1, new_child);
        }

        // If p does not have a parent and has too many keys, create a new parent node to maintain balance
        if (the_parent == NULL && p->keys.size() >= this->m_degree)
            create_new_parent(p);
    }

    // If p is a leaf node, insert the new key into its keys vector in sorted order
    else 
    {
        typename std::vector<T>::iterator itr = p->keys.begin();
        p->keys.insert(itr + i, key);

        // If p does not have a parent and has too many keys, create a new parent node to maintain balance
        if (the_parent == NULL && p->keys.size() >= this->m_degree)
            create_new_parent(p);
    }
}

//This function inserts a new key into a B+ tree. It checks if the tree is empty, 
//and if it is, it creates a new root node with the new key. Otherwise, 
//it searches through the tree's leaves to find the position where the new key should be 
//inserted, and then inserts the key into the appropriate leaf node.

template <class T>
void BPlusTree<T>::insert(const T& key,
                          BPlusTreeNode<T>*& p,
                          BPlusTreeNode<T>* the_parent) 
{
    // If B+ tree is empty, dynamically allocate a new node.
    if (this->m_root == NULL) 
    {
        this->m_root = new BPlusTreeNode<T>();
        this->m_root->keys.push_back(key);
        return;
    }
    
    // Check each keys to find key in tree's leaves
    unsigned int i = 0;
    for (; i < p->keys.size(); ++i) 
    {
        if (key < p->keys[i]) 
        {
            insert_key(key, p, the_parent, i);
            return;
        }
    }
    insert_key(key, p, the_parent, i);
}

// PrintSideways() print B+ tree using in-order traversal
template <class T>
void BPlusTree<T>::print_sideways(std::ostream& outfile, BPlusTreeNode<T>* p, int level) const 
{
    // Check: If tree is empty
    if (this->m_root == NULL) 
    {
        outfile << "Tree is empty." << std::endl;
        return;
    }

    // Compute splitted size
    unsigned int left = p->children.size() / 2;
    unsigned int right = p->children.size() - left;

    // traverse left child
    for (unsigned int i = 0; i < left; ++i) 
    {
        print_sideways(outfile, p->children[i], level + 1);
    }

    // print key vector
    for (int i = 0; i < level; ++i) 
    {
        outfile << '\t';
    }
    outfile << p->keys[0];
    for (unsigned int i = 1; i < p->keys.size(); ++i) 
    {
        outfile << ',' << p->keys[i];
    }
    outfile << std::endl;

    // traverse right child
    for (unsigned int i = left; i < left + right; ++i) 
    {
        print_sideways(outfile, p->children[i], level + 1);
    }
}


template <class T>
void BPlusTree<T>::print_BFS(std::ostream& outfile) const 
{
    // Check: If tree is empty
    if (this->m_root == NULL) 
    {
        outfile << "Tree is empty." << std::endl;
        return;
    }
    //Then, it initializes a queue of BPlusTreeNode pointers with the root node, 
    //and a vector of levels, starting at 0. It loops over the queue 
    //until it's empty, removing the first element each iteration.
    std::vector<BPlusTreeNode<T>*> queue;
    queue.push_back(this->m_root);
    std::vector<int> levels;
    levels.push_back(0);
    
    int last_level = 0;
    while (queue.size() != 0) 
    {
        // get and remove the first element from queue
        BPlusTreeNode<T>* current(queue.front());
        queue.erase(queue.begin());
        int level(levels.front());
        levels.erase(levels.begin());
        
        //spacing
        if (level == last_level && level > 0) outfile << '\t';
        else if (level != last_level) outfile << std::endl;
        
        // print key vector
        outfile << current->keys[0];
        for (unsigned int i = 1; i < current->keys.size(); ++i)
            outfile << ',' << current->keys[i];
        
        // append current node's children to queue
        for (unsigned int i = 0; i < current->children.size(); ++i) 
        {
            queue.push_back(current->children[i]);
            levels.push_back(level + 1);
        }
        
        last_level = level;
    }
    outfile << std::endl;
}

#endif

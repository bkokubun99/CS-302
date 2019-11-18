#include <cstdlib>
#include <iostream>
using namespace std;

template <class Type>
class LL
{
    struct node
    {
        Type item;
        node * next;
        node * prev;
    };
    
public:
    class iterator
    {
    public:
        friend class LL;
        iterator();
        iterator(node*);
        Type operator*();
        iterator operator++(int);
        iterator operator--(int);
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;
    private:
        node * current;
    };
    
    LL();
    LL(const LL&);
    const LL& operator=(const LL&);
    ~LL();
    iterator begin() const;
    iterator end() const;
    void headRemove();
    void tailRemove();
    bool isEmpty() const;
    void headInsert(const Type&);
    void tailInsert(const Type&);
    void update(const iterator&, const Type&);
private:
    node * head;
    node * tail;
};

/*******************************************************************************
*                   Iterator Implementation                                    *
*******************************************************************************/

//Default constructor that sets current to NULL
template <class Type>
LL<Type>::iterator::iterator()
{
    current = NULL;
}

//Constructor that sets current to the pointer passed into the function
template <class Type>
LL<Type>::iterator::iterator(node * pointer)
{
    current = pointer;
}

//Overloads a unary operator, returns the item field of the node object
//that current points to
template <class Type>
Type LL<Type>::iterator::operator*()
{
    return current->item;
}

//Overloads a unary operator, moves the current pointer over to the next
//node of the linked list
template <class Type>
typename LL<Type>::iterator LL<Type>::iterator::operator++(int)
{
    current = current->next;
    return *this;
}

//Overloads a unary operator, moves the current pointer over to the
//previous node of the linked list
template <class Type>
typename LL<Type>::iterator LL<Type>::iterator::operator--(int)
{
    current = current->prev;
    return *this;
}

//Overloads the binary equals operator, returns TRUE if the iterator on
//the left side of the operator points to the same node as the iterator
//on the right side, returns FALSE otherwise
template <class Type>
bool LL<Type>::iterator::operator==(const iterator& rhs) const
{
    if(this->current == rhs.current)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Overloads the binary NOT equals operator, returns FALSE if the iterator on
//the left side of the operator points to the same node as the iterator
//on the right side, TRUE otherwise
template <class Type>
bool LL<Type>::iterator::operator!=(const iterator& rhs) const
{
    if (this->current == rhs.current)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/*******************************************************************************
*                       LL Implementation                                      *
*******************************************************************************/

//Default Constructor that sets an empty linked list
template <class Type>
LL<Type>::LL()
{
    tail = NULL;
    head = NULL;
}

//Copy constructor, performs a deep copy of the LL object passed in
template <class Type>
LL<Type>::LL(const LL& copy)
{
    
}

//Assignment operator, performs a deep copy of the LL object passed
//in the object on the right hand side of the assignment operator
template <class Type>
const LL<Type>& LL<Type>::operator=(const LL& rhs)
{
    if (this != &rhs)
    {
        
    }
    return *this;
}

//Destructor that deallocates the linked list
template <class Type>
LL<Type>::~LL()
{
    while(!isEmpty())
    {
        headRemove();
    }
}

//Returns an iterator object that points to the first node in the list
template <class Type>
typename LL<Type>::iterator LL<Type>::begin() const
{
    iterator it_temp;
    it_temp.current = head;
    return it_temp;
    
}

//Returns an iterator object that points to the last node in the list
template <class Type>
typename LL<Type>::iterator LL<Type>::end() const
{
    iterator it_temp;
    it_temp.current = tail;
    return it_temp;
}

//Removes the front node in the linked list
template <class Type>
void LL<Type>::headRemove()
{
    if(isEmpty()) return;             //If Empty list
    
    if (head == tail && (!isEmpty())) //If list has one element
    {
        delete head;
        head = NULL;
        tail = NULL;
    }
    
    if(head != tail && (!isEmpty()))  //If list has more than one element
    {
        head = head->next;
        delete head->prev;
        head->prev = NULL;
    }
}

//Removes the end mode in the linked list
template <class Type>
void LL<Type>::tailRemove()
{
    if(isEmpty()) return;              //If Empty List
    
    if (tail == head && (!isEmpty()))  //If list has one element
    {
        delete tail;
        head = NULL;
        tail = NULL;
    }
    
    if(tail != head && (!isEmpty()))  //If list has more than one element
    {
        tail = tail->prev;
        delete tail->next;
        tail->next = NULL;
    }
}

//Returns true if the list is empty and false otherwise
template <class Type>
bool LL<Type>::isEmpty() const
{
    
    if(head == NULL && tail == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Inserts a new node to the front of the list and sets this node's item
//field to the value passed into the function
template <class Type>
void LL<Type>::headInsert(const Type& element)
{
    node* temp_node = new node;         //Creating temporary node
    if(isEmpty())                        //If list is empty
    {
        head = temp_node;
        tail = temp_node;
        head->prev = NULL;
        tail->next = NULL;
    }
    
    if(head == tail && (!isEmpty()))    //If list has one element
    {
        temp_node->next = head;
        temp_node->prev = NULL;
        head->prev = temp_node;
        head = temp_node;
    }
    if(head != tail && (!(isEmpty())))    //If list has more than one element
    {
        temp_node->next = head;
        temp_node->prev = NULL;
        head->prev = temp_node;
        head = temp_node;
    }
}
       
//Inserts a new node to the end of the list and sets this node's item
//field to the value passed into the function
template <class Type>
void LL<Type>::tailInsert(const Type& element)
{
    node* temp_node = new node;            //Creating temporary node
    if(isEmpty())                        //If list is empty
    {
        tail = temp_node;
        head = temp_node;
        head->prev = NULL;
        tail->next = NULL;
    }
    if(tail == head && (!isEmpty()))    //If list has one element
    {
        temp_node->prev = tail;
        temp_node->next = NULL;
        tail->next = temp_node;
        tail = temp_node;
    }
    if(tail != head && (!isEmpty()))    //If list has more than one element
    {
        temp_node->prev = tail;
        temp_node->next = NULL;
        tail->next = temp_node;
        tail = temp_node;
    }
}

//Reassigns a value of the node that the iterator object points with
//the value passed in the second parameter
template <class Type>
void LL<Type>::update(const LL<Type>::iterator& it, const Type& element)
{
    it.current->item = element;
}

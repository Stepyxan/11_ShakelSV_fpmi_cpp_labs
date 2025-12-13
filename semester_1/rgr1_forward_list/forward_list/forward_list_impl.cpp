#include "forward_list_impl.h"

// default constructor
ForwardList::ForwardList() : front_(nullptr), size_(0) {}

// copy constructor
ForwardList::ForwardList(const ForwardList& rhs) : front_(nullptr), size_(0) {
    Node* cur = rhs.front_;
    Node* prev = nullptr;
    while(cur) {
        Node* new_node = new Node(cur->value_);
        if (front_) {
            prev->next_ = new_node;
        }
        else {
            front_ = new_node;
        }
        cur = cur->next_;
        prev = new_node;
        ++size_;
    }
}

// Constructs a ForwardList with `count` copies of elements with value `value`.
ForwardList::ForwardList(size_t count, int32_t value) : front_(nullptr), size_(0) {
    for (size_t i = 0; i < count; i++) {
        PushFront(value);
    }
}

// Constructs a ForwardList with std::initializer_list<int32_t>
ForwardList::ForwardList(std::initializer_list<int32_t> init)
    :  front_(nullptr), size_(0) {
    for (auto it = std::rbegin(init); it != std::rend(init); it++) {
        PushFront(*it);
    }
}

// operator= overloading
ForwardList& ForwardList::operator=(const ForwardList& rhs) {
    if (this == &rhs) {
        return *this;
    }
    Clear();
    Node* cur = rhs.front_;
    Node* prev = nullptr;
    while(cur) {
        Node* new_node = new Node(cur->value_);
        if (front_) {
            prev->next_ = new_node;
        }
        else {
            front_ = new_node;
        }
        cur = cur->next_;
        prev = new_node;
        ++size_;
    }
    return *this;
}

// destructor
ForwardList::~ForwardList() {
    Clear();
}

// insert new element on the top of the list
void ForwardList::PushFront(int32_t value) {
    Node* new_node = new Node(value);
    new_node->next_ = front_;
    front_ = new_node;
    size_++;
}

// delete first element of the list
void ForwardList::PopFront() {
    if (front_ == nullptr) {
        throw "Error: Forward list is empty\n";
    }
    Node* new_front = front_->next_;
    delete front_;
    front_ = new_front;
    size_--;
}

// remove every occurence of an element in the list
// whose value equals to param `value`,
// the remaining elements must remain in the same order
void ForwardList::Remove(int32_t value) {
    while (front_ && front_->value_ == value) {
        PopFront();
    }
    if (!front_) {
        return;
    }
    Node* prev = front_;
    Node* cur = prev->next_;
    while (cur) {
        if (cur->value_ == value) {
            --size_;
            prev->next_ = cur->next_;
            delete cur;
            cur = prev->next_; 
        }
        else {
            prev = cur;
            cur = cur->next_;
        }
    }
}

// erases all the elements
void ForwardList::Clear() {
    while(front_) {
        PopFront();
    }
}

// find list's element by the `value`
// returns true, if element exists
// otherwise, returns false
bool ForwardList::FindByValue(int32_t value) {
    Node* cur = front_;
    while (cur) {
        if (cur->value_ == value) {
            return true;
        }
        cur = cur->next_;
    }
    return false;
}

// print list's elements to stream separated by space
void ForwardList::Print(std::ostream& out) {
    Node* cur = front_;
    while(cur) {
        if (cur == front_) {
            out << cur->value_;
        }
        else {
            out << " " << cur->value_;;
        }
        cur = cur->next_;
    }
}

// get first element of the list
int32_t ForwardList::Front() const {
    if (front_ == nullptr) {
        throw "Error: Forward list is empty\n";
    }
    return front_->value_;
}

// get size of the list
size_t ForwardList::Size() const {
    return size_;
}
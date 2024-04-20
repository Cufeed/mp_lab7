#include "SkipList.h"
template<class TValue>
SkipList<TValue>::Node::Node(const reference Value, size_type MaxLevel, spNode Previous): Value(Value), Previous(Previous)
{
    Next.resize(MaxLevel);
}

template<class TValue>
SkipList<TValue>::spNode SkipList<TValue>::Node::PreviousOnLevel(size_type level) const
{
    if (!Previous.expired()) { return Previous.lock(); }
    return spNode;
}

template<class TValue>
SkipList<TValue>::spNode SkipList<TValue>::Node::NextOnLevel(size_type level) const
{
    if (level < Next.size() && !Next[level].expired()) { return Next[level].lock(); }
    return spNode();
}

template<class TValue>
SkipList<TValue>::Iterator::Iterator(const iterator& it): List(it.List), Node(it.Node) {}

template<class TValue>
SkipList<TValue>::Iterator::Iterator(SkipList<TValue>& list, spNode node): List(list), Node(node) {}

template<class TValue>
typename SkipList<TValue>::Iterator& SkipList<TValue>::Iterator::operator=(const Iterator& other)
{
    if (this != &other) { Node = other.Node; }
    return *this;
}

template<class TValue>
SkipList<TValue>::Iterator::operator bool() { return Node != nullptr; }

template<class TValue>
typename SkipList<TValue>::iterator& SkipList<TValue>::Iterator::operator++()
{
    if (Node) { Node = Node->NextOnLevel(0); }
    return *this;
}

template<class TValue>
typename SkipList<TValue>::iterator& SkipList<TValue>::Iterator::operator--()
{
    if (Node) { Node = Node->PreviousOnLevel(0); }
    return *this;
}

template<class TValue>
SkipList<TValue>::iterator SkipList<TValue>::Iterator::operator++(int)
{
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template<class TValue>
SkipList<TValue>::iterator SkipList<TValue>::Iterator::operator--(int)
{
    Iterator temp = *this;
    --(*this);  
    return temp;
}

template<class TValue>
typename SkipList<TValue>::iterator& SkipList<TValue>::Iterator::operator+=(size_type n)
{
    while (n > 0 && Node) {
        Node = Node->NextOnLevel(0);
        n--;
    }
    return *this;
}

template<class TValue>
typename SkipList<TValue>::iterator& SkipList<TValue>::Iterator::operator-=(size_type n)
{
    while (n > 0 && Node) {
        Node = Node->PreviousOnLevel(0);
        n--;
    }
    return *this;
}

template<class TValue>
SkipList<TValue>::reference SkipList<TValue>::Iterator::operator*()
{
    assert(Node.lock() != nullptr); 
    return Node.lock()->Value;
}

template<class TValue>
SkipList<TValue>::SkipList(size_type MaxLevel, double Probability, pointer Arr, size_type ArrSize)
{
}

template<class TValue>
SkipList<TValue>::SkipList(const SkipList& other)
{
}

template<class TValue>
SkipList<TValue>& SkipList<TValue>::operator=(const SkipList& other)
{
    return *this;
}

template<class TValue>
SkipList<TValue>::iterator SkipList<TValue>::begin() const
{
    return iterator(const_cast<SkipList<TValue>&>(*this), this->Start);
}

template<class TValue>
SkipList<TValue>::iterator SkipList<TValue>::end() const
{
    return iterator(const_cast<SkipList<TValue>&>(*this), this->End.lock());
}

template<class TValue>
SkipList<TValue>::iterator SkipList<TValue>::find(const reference value) const noexcept
{
    return iterator();
}

template<class TValue>
SkipList<TValue>::size_type SkipList<TValue>::size() const noexcept
{
    return length;
}

template<class TValue>
bool SkipList<TValue>::empty() const noexcept
{
    return length == 0;
}

template<class TValue>
void SkipList<TValue>::clear() const noexcept
{
}

template<class TValue>
void SkipList<TValue>::insert(const reference value) noexcept
{
}

template<class TValue>
void SkipList<TValue>::remove(const reference value) noexcept
{
}

template<class TValue>
std::ostream& operator<<(std::ostream& os, SkipList<TValue>& list)
{
    return os;
}

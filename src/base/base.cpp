#include "base.h"


Polynomial* base::get_head() {
    return this->head;
}

void base::insert_back(Polynomial *&pol) {
    if (tail == nullptr) {
        tail = pol;
        head = pol;
        ++sz;
        return;
    }
    pol->setPrev(tail);
    tail->setNext(pol);
    tail = pol;
    ++sz;
}

void base::remove(Polynomial *&pol) {
    Polynomial *ptr = pol;
    if (ptr == nullptr)
        return;
    --sz;
    if (ptr->getPrev() == nullptr) {
        if (head == nullptr) return;

        ptr = head->getNext();
        if (ptr != nullptr)
            ptr->setPrevNull();
        else
            tail = nullptr;

        delete head;
        head = ptr;
        return;
    }

    if (ptr->getNext() == nullptr) {
        if (tail == nullptr) return;

        ptr = tail->getPrev();
        if (ptr != nullptr)
            ptr->setNextNull();
        else
            head = nullptr;

        delete tail;
        tail = ptr;
        return;
    }

    Polynomial *left = ptr->getPrev();
    Polynomial *right = ptr->getNext();
    left->setNext(right);
    right->setPrev(left);

    delete ptr;
}

std::string base::toString() {
    std::string ans;
    for (Polynomial *l = this->head; l != nullptr; l=l->getNext()) {
        ans += l->toString();
        ans += '\n';
    }
    return ans;
}

Polynomial *base::get(int id) {
    try {
        if (id >= this->sz || id < 0) {
            throw "Incorrect id";
        }
        Polynomial *curr = this->head;
        for (int i = 0; i < id; ++i) {
            curr = curr->getNext();
        }
        return curr;
    } catch (const char* c) {
        throw;
    }
}

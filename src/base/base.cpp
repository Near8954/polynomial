#include "base.h"


polynomial* base::get_head() {
    return this->head;
}

void base::insert_back(polynomial *&pol) {
    if (tail == nullptr) {
        tail = pol;
        head = pol;
        ++sz;
        return;
    }
    pol->set_prev(tail);
    tail->set_next(pol);
    tail = pol;
    ++sz;
}

void base::remove(polynomial *&pol) {
    polynomial *ptr = pol;
    if (ptr == nullptr)
        return;
    --sz;
    if (ptr->get_prev() == nullptr) {
        if (head == nullptr) return;

        ptr = head->get_next();
        if (ptr != nullptr)
            ptr->set_prev_null();
        else
            tail = nullptr;

        delete head;
        head = ptr;
        return;
    }

    if (ptr->get_next() == nullptr) {
        if (tail == nullptr) return;

        ptr = tail->get_prev();
        if (ptr != nullptr)
            ptr->set_next_null();
        else
            head = nullptr;

        delete tail;
        tail = ptr;
        return;
    }

    polynomial *left = ptr->get_prev();
    polynomial *right = ptr->get_next();
    left->set_next(right);
    right->set_prev(left);

    delete ptr;
}

std::string base::to_string() {
    std::string ans;
    for (polynomial *l = this->head; l != nullptr; l=l->get_next()) {
        ans += l->to_string();
        ans += '\n';
    }
    return ans;
}

polynomial *base::get(int id) {
    try {
        if (id >= this->sz) {
            throw "Incorrect id";
        }
        polynomial *curr = this->head;
        for (int i = 0; i < id; ++i) {
            curr = curr->get_next();
        }
        return curr;
    } catch (const char* c) {
        throw;
    }
}

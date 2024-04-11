#include "polynomial.h"

node *merge(node *&L, node *&r) {
    if (L == nullptr) return r;
    if (r == nullptr) return L;
    node *cur = nullptr;
    if (*L > *r) {
        cur = r;
        r = r->next;
    } else {
        cur = L;
        L = L->next;
    }
    node *beg = cur;
    while (L != nullptr && r != nullptr) {
        if (*L <= *r) {
            cur->next = L;
            cur->next->prev = cur;
            cur = cur->next;
            L = L->next;
        } else {
            cur->next = r;
            cur->next->prev = cur;
            cur = cur->next;
            r = r->next;
        }
    }
    if (L != nullptr) {
        cur->next = L;
        cur->next->prev = cur;
        cur = cur->next;
    }
    if (r != nullptr) {
        cur->next = r;
        cur->next->prev = cur;
        cur = cur->next;
    }
    return beg;
}


void mergeSort(node *&L, int sz) {
    if (sz <= 1) {
        return;
    }
    int m = sz / 2;
    node *curr = L;
    for (int i = 0; i < m; ++i) {
        curr = curr->next;
    }
    node *r = curr;
    curr->prev->next = nullptr;
    r->prev = nullptr;
    mergeSort(L, m);
    mergeSort(r, sz - m);
    L = merge(L, r);
}



polynomial::polynomial() {
    head = nullptr;
    tail = nullptr;
}

polynomial::~polynomial(){
    for (auto l = this->head; l != nullptr; l=l->next) {
        auto curr = l;
        this->remove(curr);
    }
}

polynomial::polynomial(std::string s) {
    std::string cp = s;
    std::string curr;
    for (int i = 0; i < cp.size(); ++i) {
        if (s[i] == '-' || s[i] == '+' && !curr.empty()) {
            node *nd = new node(curr);
            this->insert_back(nd);
            curr.clear();
        }
        curr += s[i];
    }
    if (!curr.empty()) {
        node *nd = new node(curr);
        this->insert_back(nd);
        curr.clear();
    }
}

polynomial::polynomial(polynomial &pol) {
    if (pol.sz == 0) {

    }
}

std::string polynomial::to_string() {
    std::string ans;
    for (node *t = this->head; t != nullptr; t = t->next) {
        if (t->k > 0 && t != this->head) {
            ans += '+';
            ans += t->to_string();
        } else {
            ans += t->to_string();
        }
    }
    return ans;
}


void polynomial::insert_back(node *&e) {
    if (tail == nullptr) {
        tail = e;
        head = e;
        ++sz;
        return;
    }
    e->prev = tail;
    tail->next = e;
    tail = e;
    ++sz;
}

void polynomial::remove(node *&it) {
    node *ptr = it;
    if (ptr == nullptr)
        return;
    --sz;
    if (ptr->prev == nullptr) {
        if (head == nullptr) return;

        ptr = head->next;
        if (ptr != nullptr)
            ptr->prev = nullptr;
        else
            tail = nullptr;

        delete head;
        head = ptr;
        return;
    }

    if (ptr->next == nullptr) {
        if (tail == nullptr) return;

        ptr = tail->prev;
        if (ptr != nullptr)
            ptr->next = nullptr;
        else
            head = nullptr;

        delete tail;
        tail = ptr;
        return;
    }

    node *left = ptr->prev;
    node *right = ptr->next;
    left->next = right;
    right->prev = left;

    delete ptr;
}

void polynomial::polysorb() {
    mergeSort(this->head, sz);
}

void polynomial::normalize() {
    this->polysorb();
    if (this->head == nullptr) {
        return;
    }

    for (auto l = this->head; l->next != nullptr;) {
        node *next = l->next;
        if (l->powers == next->powers) {
            l->k += next->k;
            remove(next);
            continue;
        }
        l = l->next;
    }
}

/*std::ostream &operator<<(std::ostream &os, const polynomial &p) {
    for (node *t = p.head; t != nullptr; t = t->next) {
        if (t->k > 0 && t != p.head) {
            os << '+' << *t;
        } else {
            os << *t;
        }
    }
    return os;
}*/

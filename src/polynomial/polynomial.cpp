#include "polynomial.h"

node* merge(node* l, node* r) {
    if (l == nullptr) return r;
    if (r == nullptr) return l;
    node* cur;
    if (*l > *r) {
        cur = l;
        l = l->next;
    } else {
        cur = r;
        r = r->next;
    }
    node* beg = cur;
    while (l != nullptr && r != nullptr) {
        if (*l > *r) {
            cur->next = l;
            cur->next->prev = cur;
            cur = cur->next;
            l = l->next;
        } else {
            cur->next = r;
            cur->next->prev = cur;
            cur = cur->next;
            r = r->next;
        }
    }
    if (l != nullptr) {
        cur->next = l;
        cur->next->prev = cur;
    }
    if (r != nullptr) {
        cur->next = r;
        cur->next->prev = cur;
    }
    return beg;
}

void mrgsort(node*& l, int n) {
    if (n <= 1) return;
    int m = n / 2;
    node* cur = l;
    for (int i = 0; i < m; ++i) {
        cur = cur->next;
    }
    node* r = cur;
    cur->prev->next = nullptr;
    cur->prev = nullptr;
    mrgsort(l, m);
    mrgsort(r, n - m);
    l = merge(l, r);
}


polynomial::polynomial() {
    head = nullptr;
    tail = nullptr;
}

polynomial::~polynomial() {
    for (auto l = this->head; l != nullptr; l = l->next) {
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

// TODO make copy constructor
polynomial::polynomial(const polynomial &pol) {
    if (pol.head == nullptr) {
        next = nullptr;
        prev = nullptr;
        head = nullptr;
        tail = nullptr;
        sz = 0;
        return;
    } else {
        next = nullptr;
        prev = nullptr;
        sz = 0;
        for (auto el = pol.head; el != nullptr; el = el->next) {
            node* nd = new node(*el);
            insert_back(nd);
        }
    }
}

std::string polynomial::to_string() {
    std::string ans;
    for (node *t = this->head; t != nullptr; t = t->next) {
        if (t->k == 0 && t != this->head) {
            ans += "0";
        } else if (t->k > 0 && t != this->head) {
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
    if (it == nullptr) {
        return;
    }
    if (it->prev == nullptr && it->next == nullptr) { // Если вершина одна
        delete it;
        --sz;
        return;
    }
    if (it->prev == nullptr) { // Если вершина - head
        head = it->next;
        head->prev = nullptr;
        --sz;
        delete it;
        return;
    }
    if (it->next == nullptr) { // Если вершина - tail
        tail = it->prev;
        tail->next = nullptr;
        --sz;
        delete it;
        return;
    }
    --sz;
    it->prev->next = it->next; // Если просто вершина с двумя соседями
    it->next->prev = it->prev;
    delete it;
}

void polynomial::polysorb() {
    mrgsort(this->head, sz);
}

void polynomial::normalize() {
    this->polysorb();
    if (this->head == nullptr) {
        return;
    }
    for (auto l = this->head; l->next != nullptr;) {
        node *nxt = l->next;
        if (l->powers == nxt->powers) {
            l->k += nxt->k;
            remove(nxt);
            continue;
        }
        l = l->next;
    }
    for (auto l = head; l != nullptr; l=l->next) {
        if (l->k == 0) {
            l->powers.assign(26, 0);
        }
    }
    sz = 0;
    tail = nullptr;
    for (auto l = head; l != nullptr; l = l->next) {
        tail = l;
        ++sz;
    }
}

polynomial polynomial::operator+(const polynomial &pol) {
    polynomial cp;
    for (auto tmp = pol.head; tmp != nullptr; tmp = tmp->next) {
        auto nd = (new node(*tmp));
        cp.insert_back(nd);
    }
    for (auto tmp = this->head; tmp != nullptr; tmp = tmp->next) {
        auto nd = (new node(*tmp));
        cp.insert_back(nd);
    }
    cp.normalize();
    return cp;
}

bool polynomial::operator==(const polynomial &pol) {
    if (this->sz != pol.sz) {
        return false;
    }
    for (auto t1 = this->head, t2 = pol.head; t1 != nullptr && t2 != nullptr; t1=t1->next, t2=t2->next) {
        if (*t1 != *t2) {
            return false;
        }
    }
    return true;
}

void polynomial::insert_back(const polynomial& pol) {
    if (this->tail == nullptr) {}
    this->tail->next = pol.head;
    pol.head->prev = this->tail;
    node* tmp = this->head;
    sz += pol.sz;
    for (;tmp->next != nullptr; tmp = tmp->next) {}
    this->tail = tmp;
}

polynomial polynomial::operator*(const polynomial &pol) {
    polynomial ans;
    for (auto t1 = head; t1 != nullptr; t1=t1->next) {
        for (auto t2 = pol.head; t2 != nullptr; t2 = t2->next) {
            auto nd = new node((*t1)*(*t2));
            ans.insert_back(nd);
        }
    }
    return ans;
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

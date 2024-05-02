#include "polynomial.h"

int64_t power(int64_t x, int64_t y) {
    if (y == 0)
        return 1;
    else {
        int64_t halfPower = power(x, y / 2);
        if (y % 2 == 0)
            return halfPower * halfPower;
        else
            return x * halfPower * halfPower;
    }
}

Node *merge(Node *l, Node *r) {
    if (l == nullptr) return r;
    if (r == nullptr) return l;
    Node *cur;
    if (*l > *r) {
        cur = l;
        l = l->next;
    } else {
        cur = r;
        r = r->next;
    }
    Node *beg = cur;
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

void mrgsort(Node *&l, int n) {
    if (n <= 1) return;
    int m = n / 2;
    Node *cur = l;
    for (int i = 0; i < m; ++i) {
        cur = cur->next;
    }
    Node *r = cur;
    cur->prev->next = nullptr;
    cur->prev = nullptr;
    mrgsort(l, m);
    mrgsort(r, n - m);
    l = merge(l, r);
}

Polynomial::Polynomial() {
    head = nullptr;
    tail = nullptr;
}

Polynomial::~Polynomial() {
    Node *curr = this->head;
    while (curr != nullptr) {
        Node *next = curr->next;
        this->remove(curr);
        curr = next;
    }
}

Polynomial::Polynomial(std::string s) {
    std::string cp = s;
    std::string curr;
    for (int i = 0; i < cp.size(); ++i) {
        if (s[i] == '-' || s[i] == '+' && !curr.empty()) {
            Node *nd = new Node(curr);
            insert_back(nd);
            curr.clear();
        }
        curr += s[i];
    }
    if (!curr.empty()) {
        Node *nd = new Node(curr);
        insert_back(nd);
        curr.clear();
    }
}

Polynomial::Polynomial(const Polynomial &pol) {
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
            Node *nd = new Node(*el);
            nd->next = nullptr;
            nd->prev = nullptr;
            insert_back(nd);
        }
    }
}


void Polynomial::insert_back(Node *&e) {
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

void Polynomial::insert_back(const Polynomial &pol) {
    if (this->tail == nullptr) {}
    this->tail->next = pol.head;
    pol.head->prev = this->tail;
    Node *tmp = this->head;
    sz += pol.sz;
    for (; tmp->next != nullptr; tmp = tmp->next) {}
    this->tail = tmp;
}

void Polynomial::remove(Node *&it) {
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

void Polynomial::sort() {
    mrgsort(this->head, sz);
}

void Polynomial::normalize() {
    this->sort();
    if (this->head == nullptr) {
        return;
    }
    for (auto l = this->head; l->next != nullptr;) {
        Node *nxt = l->next;
        if (l->powers == nxt->powers) {
            l->coefficient += nxt->coefficient;
            remove(nxt);
            continue;
        }
        l = l->next;
    }
    for (auto l = head; l != nullptr; l = l->next) {
        if (l->coefficient == 0) {
            l->powers.assign(26, 0);
        }
    }
    sz = 0;
    tail = nullptr;
    for (auto l = head; l != nullptr; l = l->next) {
        tail = l;
        ++sz;
    }
    if (tail != nullptr && head != nullptr && head != tail && tail->coefficient == 0) {
        tail = tail->prev;
        remove(tail->next);
        sz = 0;
    }
}

int64_t Polynomial::getValueInPoint(std::vector<int64_t> &vars) {
    int64_t ans = 0;
    for (auto curr = head; curr != nullptr; curr = curr->next) {
        int64_t tmp = 1;
        for (int i = 0; i < 26; ++i) {
            tmp *= power(vars[i], curr->powers[i]);
        }
        tmp *= curr->coefficient;
        ans += tmp;
    }
    return ans;
}


Polynomial Polynomial::getDerivative(int n, char x) {
    auto tmp = new Polynomial(*this);
    Polynomial ans;
    bool check = false;
    for (auto curr = head; curr != nullptr; curr=curr->next) {
        if (curr->powers[x-'a']) {
            check = true;
        }
    }
    if (!check) {
        throw "Incorrect variable";
    }
    if (n <= 0) {
        throw "Incorrect n";
    }
    for (int i = 0; i < n; ++i) {
        for (auto curr = tmp->head; curr != nullptr; curr = curr->next) {
            auto nd = new Node(curr->getDerivative(x));
            ans.insert_back(nd);
        }
        delete tmp;
        tmp = new Polynomial(ans);
        ans = Polynomial();
    }
    tmp->normalize();
    return *tmp;
}

Polynomial Polynomial::operator+(const Polynomial &pol) {
    Polynomial cp;
    for (auto tmp = pol.head; tmp != nullptr; tmp = tmp->next) {
        auto nd = (new Node(*tmp));
        cp.insert_back(nd);
    }
    for (auto tmp = this->head; tmp != nullptr; tmp = tmp->next) {
        auto nd = (new Node(*tmp));
        cp.insert_back(nd);
    }
    cp.normalize();
    return cp;
}

Polynomial Polynomial::operator*(const Polynomial &pol) {
    Polynomial ans;
    for (auto t1 = head; t1 != nullptr; t1 = t1->next) {
        for (auto t2 = pol.head; t2 != nullptr; t2 = t2->next) {
            auto nd = new Node((*t1) * (*t2));
            ans.insert_back(nd);
        }
    }
    return ans;
}

bool Polynomial::operator==(const Polynomial &pol) {
    if (this->sz != pol.sz) {
        return false;
    }
    for (auto t1 = this->head, t2 = pol.head; t1 != nullptr && t2 != nullptr; t1 = t1->next, t2 = t2->next) {
        if (*t1 != *t2) {
            return false;
        }
    }
    return true;
}

static int64_t sum(std::vector<int64_t> &v) {
    int ans = 0;
    for (auto e: v) {
        ans += e;
    }
    return ans;
}

std::vector<int64_t> Polynomial::getRoots() {
    for (auto curr = head; curr != nullptr; curr = curr->next) {
        int cnt = 0;
        for (auto e: curr->powers) {
            if (e) {
                ++cnt;
            }
        }
        if (cnt > 1) {
            throw "Wrong number of vars";
        }
    }
    std::set<int> ans;
    for (int64_t i = -tail->coefficient; i <= tail->coefficient; ++i) {
        int tmp = 0;
        if (i != 0 && tail->coefficient % i == 0) {
            for (auto curr = head; curr != nullptr; curr = curr->next) {
                tmp += curr->coefficient * power(i, sum(curr->powers));
            }
            if (tmp == 0) {
                ans.insert(i);
            }
        }
    }
    for (int64_t i = tail->coefficient; i <= -tail->coefficient; ++i) {
        int tmp = 0;
        if (i != 0 && tail->coefficient % i == 0) {
            for (auto curr = head; curr != nullptr; curr = curr->next) {
                tmp += curr->coefficient * power(i, sum(curr->powers));
            }
            if (tmp == 0) {
                ans.insert(i);
            }
        }
    }
    if (sum(tail->powers)) {
        ans.insert(0);
    }
    std::vector<int64_t> out;
    for (auto e: ans) {
        out.push_back(e);
    }
    return out;
}


std::string Polynomial::toString() {
    std::string ans;
    for (Node *t = this->head; t != nullptr; t = t->next) {
        if (t->coefficient == 0 && t != this->head) {
            ans += "0";
        } else if (t->coefficient > 0 && t != this->head) {
            ans += '+';
            ans += t->toString();
        } else {
            ans += t->toString();
        }
    }
    return ans;
}

void Polynomial::setNext(Polynomial *&pol) {
    this->next = pol;
}

void Polynomial::setNextNull() {
    this->next = nullptr;
}

void Polynomial::setPrev(Polynomial *&pol) {
    this->prev = pol;
}

void Polynomial::setPrevNull() {
    this->prev = nullptr;
}

Polynomial *Polynomial::getNext() {
    return this->next;
}

Polynomial *Polynomial::getPrev() {
    return this->prev;
}

int Polynomial::size() {
    return this->sz;
}

Node *Polynomial::getHead() {
    return this->head;
}

Node *Polynomial::getTail() {
    return this->tail;
}

Polynomial Polynomial::operator-(const Polynomial &pol) {
    Polynomial cp;
    for (auto tmp = pol.head; tmp != nullptr; tmp = tmp->next) {
        auto nd = (new Node(*tmp));
        cp.insert_back(nd);
    }
    for (auto tmp = cp.head; tmp != nullptr; tmp = tmp->next) {
        tmp->coefficient *= -1;
    }
    for (auto tmp = this->head; tmp != nullptr; tmp = tmp->next) {
        auto nd = (new Node(*tmp));
        cp.insert_back(nd);
    }
    cp.normalize();
    return cp;
}

Polynomial Polynomial::operator/(Polynomial divisor) {
    Polynomial ans;
    Polynomial tmp = *this;
    while (tmp.size() > 0) {
        Node *curr = tmp.head;
        Node *div = divisor.head;
        if (curr->coefficient % div->coefficient != 0) {
            throw "Wrong division";
        }
        int64_t coef = curr->coefficient / div->coefficient;
        std::vector<int64_t> powers(26);
        for (int i = 0; i < 26; ++i) {
            powers[i] = curr->powers[i] - div->powers[i];
        }
        Node *nd = new Node();
        nd->coefficient = coef;
        nd->powers = powers;
        ans.insert_back(nd);
        Polynomial tmp2;
        Node *nd2 = new Node();
        nd2->coefficient = coef;
        nd2->powers = powers;
        tmp2.insert_back(nd2);
        Polynomial tmp3 = divisor * tmp2;
        tmp = tmp - tmp3;
    }
    return ans;
}


void Polynomial::clear() {
    Node *curr = this->head;
    while (curr != nullptr) {
        Node *next = curr->next;
        this->remove(curr);
        curr = next;
    }
}

Polynomial &Polynomial::operator=(const Polynomial &pol) {
    if (this == &pol) {
        return *this;
    }
    this->clear();
    if (pol.head == nullptr) {
        next = nullptr;
        prev = nullptr;
        head = nullptr;
        tail = nullptr;
        sz = 0;
        return *this;
    } else {
        next = nullptr;
        prev = nullptr;
        sz = 0;
        for (auto el = pol.head; el != nullptr; el = el->next) {
            Node *nd = new Node(*el);
            nd->next = nullptr;
            nd->prev = nullptr;
            insert_back(nd);
        }
    }
    return *this;
}

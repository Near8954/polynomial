#include "node.h"

const int ALPHABET_SIZE = 26;

std::pair<int64_t, std::vector<int64_t>> check(const std::string &s) {
    double k = 1.0;
    if (s.empty()) {
        return {0, std::vector<int64_t>(ALPHABET_SIZE, 0)};
    }
    std::string num;
    int state = 0;
    bool sign = false;
    char var = 'Z';
    std::vector<int64_t> pows;
    pows.resize(26);
    try {
        for (char i: s) {
            if (state == 0) {
                if (isdigit(i)) {
                    state = 1;
                    num += i;
                } else if (i >= 'a' && i <= 'z') {
                    state = 2;
                    var = i;
                } else if (i == '-' || i == '+') {
                    if (i == '-') {
                        sign = !sign;
                    }
                } else {
                    throw WrongMonomial("unexpected symbol ", i);
                }
            } else if (state == 1) {
                if (isdigit(i)) {
                    state = 1;
                    num += i;
                } else if (i >= 'a' && i <= 'z') {
                    state = 2;
                    k = std::stoi(num);
                    var = i;
                    num.clear();
                } else if (i == '-' || i == '+') {
                    throw WrongMonomial("incorrect sign place ", i);
                } else {
                    throw WrongMonomial("unexpected symbol ", i);
                }
            } else if (state == 2) {
                if (isdigit(i)) {
                    throw WrongMonomial("expected num found ", i);
                } else if (i >= 'a' && i <= 'z') {
                    if (num.empty()) {
                        pows[var - 'a'] += 1;
                    } else {
                        pows[var - 'a'] += std::stoi(num);
                        num.clear();
                    }
                    var = i;
                } else if (i == '^') {
                    state = 3;
                } else if (i == '-' || i == '+') {
                    throw WrongMonomial("incorrect sign place", i);
                } else {
                    throw WrongMonomial("unexpected symbol ", i);
                }
            } else if (state == 3) {
                if (isdigit(i)) {
                    num += i;
                } else if (i >= 'a' && i <= 'z') {
                    state = 2;
                    if (num.empty()) {
                        throw WrongMonomial("var in power ", i);
                    } else {
                        pows[var - 'a'] += std::stoi(num);
                        var = i;
                        num.clear();
                    }
                } else if (i == '^') {
                    throw WrongMonomial("double power ", i);
                } else if (i == '-' || i == '+') {
                    throw WrongMonomial("incorrect sign place", i);
                } else {
                    throw WrongMonomial("unexpected symbol ", i);
                }
            }
        }
        if (var == 'Z') {
            k = std::stoi(num);
        }
        if (state == 3 && num.empty()) {
            throw WrongMonomial("incorrect power", 'Z');
        }
        if (num.empty() && var != 'Z') {
            pows[var - 'a'] += 1;
        }
        if (!num.empty() && var != 'Z') {
            pows[var - 'a'] += std::stoi(num);
        }
        if (sign) {
            k *= -1;
        }
    } catch (const WrongMonomial &mn) {
        throw;
    }
    return {k, pows};
}

Node::Node() {
    powers.resize(ALPHABET_SIZE);
    coefficient = 1.0;
    prev = nullptr;
    next = nullptr;
}

Node::Node(const Node &t) {
    coefficient = t.coefficient;
    powers = t.powers;
    prev = t.prev;
    next = t.next;
};

Node::Node(std::string s) {
    prev = nullptr;
    next = nullptr;
    powers.resize(ALPHABET_SIZE);
    auto nd(check(s));
    powers = nd.second;
    coefficient = nd.first;
};

static int64_t sum(std::vector<int64_t> &v) {
    int ans = 0;
    for (auto e: v) {
        ans += e;
    }
    return ans;
}

std::string Node::toString() {
    std::string ans;
    if (coefficient != 1 || (sum(powers) == 0)) {
        ans += std::to_string((int) this->coefficient);
    }
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (this->powers[i] != 0) {
            ans += char(i + 'a');
            if (this->powers[i] != 1) {
                ans += '^';
                ans += std::to_string((int) this->powers[i]);
            }
        }
    }
    return ans;
}

bool Node::operator<(Node &nd) {
    for (int i = 0; i < 26; ++i) {
        if (this->powers[i] < nd.powers[i]) return true;
        else if (this->powers[i] > nd.powers[i]) return false;
    }
    return (this->coefficient < nd.coefficient);
}

bool Node::operator==(Node &nd) {
    if (this->coefficient != nd.coefficient) {
        return false;
    }
    for (int i = 0; i < 26; ++i) {
        if (this->powers[i] != nd.powers[i]) {
            return false;
        }
    }
    return true;
}

bool Node::operator!=(Node &nd) {
    return !(*this == nd);
}

bool Node::operator>(Node &nd) {
    return (!(*this < nd) && !(*this == nd));
}

bool Node::operator<=(Node &nd) {
    return ((*this < nd) || (*this == nd));
}

Node Node::operator*(Node &nd) {
    Node ans;
    for (int i = 0; i < powers.size(); ++i) {
        ans.powers[i] += powers[i];
    }
    for (int i = 0; i < nd.powers.size(); ++i) {
        ans.powers[i] += nd.powers[i];
    }
    ans.coefficient = coefficient * nd.coefficient;
    if (ans.coefficient == 0) {
        ans.powers.clear();
    }
    return ans;
}

Node Node::getDerivative(char x) {
    Node ans;
    ans.coefficient = coefficient;
    if (!powers[x - 'a']) {
        ans.coefficient = 0;
        return ans;
    }
    ans.powers = powers;
    ans.coefficient *= ans.powers[x - 'a'];
    --ans.powers[x - 'a'];
    return ans;
}

Node Node::operator/(Node &nd) {
    Node ans;
    for (int i = 0; i < powers.size(); ++i) {
        ans.powers[i] = powers[i] - nd.powers[i];
    }
    ans.coefficient = coefficient / nd.coefficient;
    if (ans.coefficient == 0) {
        ans.powers.clear();
    }
    return ans;
}



/*std::ostream &operator<<(std::ostream &os, const node &nd) {
    os << nd.k;
    for (int i = 0; i < 26; ++i) {
        if (nd.powers[i] != 0) {
            os << char(i + 'a') << '^' << nd.powers[i];
        }
    }
    return os;
}*/


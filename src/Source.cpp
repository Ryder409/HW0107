#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

struct PolyNode {
    int coef;
    int expon;
    PolyNode* link;
};

PolyNode* avail = nullptr;

PolyNode* getNode() {
    PolyNode* node;
    if (avail) {
        node = avail;
        avail = avail->link;
    }
    else
        node = new PolyNode;
    return node;
}

PolyNode* pread(int coef, int expon, PolyNode* list) {
    PolyNode* ptr, * newp;
    newp = getNode();
    newp->coef = coef;
    newp->expon = expon;
    newp->link = nullptr;

    if (list == nullptr) {
        list = newp;
    }
    else {
        ptr = list;
        while (ptr->link != nullptr) {
            ptr = ptr->link;
        }
        ptr->link = newp;
    }
    return list;
}

void pwrite(PolyNode* list) {
    PolyNode* temp = list;
    while (temp != nullptr) {
        if (temp->link != nullptr) {
            cout << temp->coef << "x^" << temp->expon << " + ";
        }
        else {
            cout << temp->coef << "x^" << temp->expon;
        }
        temp = temp->link;
    }
    cout << endl;
}

PolyNode* padd(PolyNode* a, PolyNode* b) {
    PolyNode* result = nullptr;
    PolyNode* ptr_a = a;
    PolyNode* ptr_b = b;

    while (ptr_a != nullptr && ptr_b != nullptr) {
        if (ptr_a->expon > ptr_b->expon) {
            result = pread(ptr_a->coef, ptr_a->expon, result);
            ptr_a = ptr_a->link;
        }
        else if (ptr_a->expon < ptr_b->expon) {
            result = pread(ptr_b->coef, ptr_b->expon, result);
            ptr_b = ptr_b->link;
        }
        else {
            int sum = ptr_a->coef + ptr_b->coef;
            if (sum != 0) {
                result = pread(sum, ptr_a->expon, result);
            }
            ptr_a = ptr_a->link;
            ptr_b = ptr_b->link;
        }
    }

    while (ptr_a != nullptr) {
        result = pread(ptr_a->coef, ptr_a->expon, result);
        ptr_a = ptr_a->link;
    }

    while (ptr_b != nullptr) {
        result = pread(ptr_b->coef, ptr_b->expon, result);
        ptr_b = ptr_b->link;
    }

    return result;
}

PolyNode* psub(PolyNode* a, PolyNode* b) {
    PolyNode* result = nullptr;
    PolyNode* ptr_a = a;
    PolyNode* ptr_b = b;

    while (ptr_a != nullptr && ptr_b != nullptr) {
        if (ptr_a->expon > ptr_b->expon) {
            result = pread(ptr_a->coef, ptr_a->expon, result);
            ptr_a = ptr_a->link;
        }
        else if (ptr_a->expon < ptr_b->expon) {
            result = pread(-ptr_b->coef, ptr_b->expon, result);
            ptr_b = ptr_b->link;
        }
        else {
            int diff = ptr_a->coef - ptr_b->coef;
            if (diff != 0) {
                result = pread(diff, ptr_a->expon, result);
            }
            ptr_a = ptr_a->link;
            ptr_b = ptr_b->link;
        }
    }

    while (ptr_a != nullptr) {
        result = pread(ptr_a->coef, ptr_a->expon, result);
        ptr_a = ptr_a->link;
    }

    while (ptr_b != nullptr) {
        result = pread(-ptr_b->coef, ptr_b->expon, result);
        ptr_b = ptr_b->link;
    }

    return result;
}

PolyNode* pmult(PolyNode* a, PolyNode* b) {
    PolyNode* result = nullptr;
    PolyNode* ptr_a = a;
    PolyNode* ptr_b = b;

    while (ptr_a != nullptr) {
        ptr_b = b;
        while (ptr_b != nullptr) {
            int coef = ptr_a->coef * ptr_b->coef;
            int expon = ptr_a->expon + ptr_b->expon;
            result = pread(coef, expon, result);
            ptr_b = ptr_b->link;
        }
        ptr_a = ptr_a->link;
    }

    return result;
}

PolyNode* inputPolynomial() {
    PolyNode* poly = nullptr;
    int coef, expon;
    char more;

    do {
        cout << "Enter coefficient: ";
        cin >> coef;
        cout << "Enter exponent: ";
        cin >> expon;

        poly = pread(coef, expon, poly);

        cout << "Do you want to enter another term? (y/n): ";
        cin >> more;
    } while (more == 'y' || more == 'Y');

    return poly;
}

int main() {
    PolyNode* a = nullptr;
    PolyNode* b = nullptr;
    PolyNode* c;
    float x;

    // Input polynomial A
    cout << "Enter polynomial A:" << endl;
    a = inputPolynomial();

    // Input polynomial B
    cout << "Enter polynomial B:" << endl;
    b = inputPolynomial();

    // Display polynomial A
    cout << "Polynomial A: ";
    pwrite(a);

    // Display polynomial B
    cout << "Polynomial B: ";
    pwrite(b);

    // Add polynomials
    c = padd(a, b);
    cout << "A + B = ";
    pwrite(c);

    // Subtract polynomials
    c = psub(a, b);
    cout << "A - B = ";
    pwrite(c);

    // Multiply polynomials
    c = pmult(a, b);
    cout << "A * B = ";
    pwrite(c);

    return 0;
}

// header files
#include "Polynomial.h"
#include <sstream>
#include <cmath>
#include <map>

using namespace std;

// internal structure for polynomial term
struct Node
{
    int coeff;  // coefficient of term
    int exp;    // exponent of term
    Node *next; // pointer to next node

    // constructor to initialize node
    Node(int c, int e) : coeff(c), exp(e), next(nullptr) {}
};

// global data for storing polynomial linked lists
static int nextID = 0;
static map<const Polynomial *, Node *> registry;

// helper function to get head node for a polynomial
static Node *&getHead(const Polynomial *p)
{
    // if polynomial not found in map, initialize it with nullptr
    if (!registry.count(p))
        registry[p] = nullptr;
    return registry[p];
}

// helper function to copy a linked list
static Node *copyList(Node *src)
{
    if (!src)
        return nullptr;

    Node *head = new Node(src->coeff, src->exp);
    Node *tail = head;

    for (Node *cur = src->next; cur; cur = cur->next)
    {
        tail->next = new Node(cur->coeff, cur->exp);
        tail = tail->next;
    }

    return head;
}

// helper function to clear (delete) all nodes in a linked list
static void clearList(Node *head)
{
    while (head)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

// insert a term into the polynomial in correct descending order
void Polynomial::insertTerm(int coefficient, int exponent)
{
    // ignore if coefficient is zero or exponent is invalid
    if (coefficient == 0 || exponent < 0)
        return;

    Node *&head = getHead(this);
    Node *newNode = new Node(coefficient, exponent);

    // if list is empty or new exponent is largest, insert at front
    if (!head || exponent > head->exp)
    {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node *cur = head;
    Node *prev = nullptr;

    // move until correct position is found (descending order)
    while (cur && cur->exp > exponent)
    {
        prev = cur;
        cur = cur->next;
    }

    // if exponent already exists, just add coefficients
    if (cur && cur->exp == exponent)
    {
        cur->coeff += coefficient;

        // if coefficient becomes zero, remove the term
        if (cur->coeff == 0)
        {
            if (prev)
                prev->next = cur->next;
            else
                head = cur->next;
            delete cur;
        }

        delete newNode; // newNode not needed
    }
    else
    {
        // insert new node at correct position
        newNode->next = cur;
        if (prev)
            prev->next = newNode;
        else
            head = newNode;
    }
}

// convert polynomial to string form like "3x^2 + 2x + 1"
string Polynomial::toString() const
{
    Node *head = getHead(this);

    // if no terms, return 0
    if (!head)
        return "0";

    ostringstream out;
    bool first = true;
    Node *cur = head;

    // go through each node and build the string
    while (cur)
    {
        int c = cur->coeff;
        int e = cur->exp;

        // skip zero coefficients
        if (c == 0)
        {
            cur = cur->next;
            continue;
        }

        // handle sign (+ or -)
        if (!first)
            out << (c > 0 ? " + " : " - ");
        else if (c < 0)
            out << "-";

        first = false;

        int absC = abs(c);

        // print coefficient only if not 1 or -1 (unless exponent = 0)
        if (!(absC == 1 && e != 0))
            out << absC;

        // print variable part
        if (e > 0)
        {
            out << "x";
            if (e > 1)
                out << "^" << e;
        }

        cur = cur->next;
    }

    return out.str();
}

// add two polynomials and return a new result polynomial
Polynomial Polynomial::add(const Polynomial &other) const
{
    Polynomial result;
    Node *head1 = getHead(this);
    Node *head2 = getHead(&other);
    Node *&headR = getHead(&result);

    Node *p1 = head1;
    Node *p2 = head2;
    Node **tail = &headR;

    // merge both polynomials in sorted order
    while (p1 || p2)
    {
        if (p2 == nullptr || (p1 && p1->exp > p2->exp))
        {
            *tail = new Node(p1->coeff, p1->exp);
            p1 = p1->next;
        }
        else if (p1 == nullptr || p2->exp > p1->exp)
        {
            *tail = new Node(p2->coeff, p2->exp);
            p2 = p2->next;
        }
        else
        {
            int sum = p1->coeff + p2->coeff;
            if (sum != 0)
                *tail = new Node(sum, p1->exp);
            p1 = p1->next;
            p2 = p2->next;
        }

        // move tail pointer forward if node was added
        if (*tail)
            tail = &((*tail)->next);
    }

    return result;
}

// multiply two polynomials using distributive property
Polynomial Polynomial::multiply(const Polynomial &other) const
{
    Polynomial result;
    Node *head1 = getHead(this);
    Node *head2 = getHead(&other);

    // multiply every term of one polynomial with every term of the other
    for (Node *a = head1; a; a = a->next)
        for (Node *b = head2; b; b = b->next)
            result.insertTerm(a->coeff * b->coeff, a->exp + b->exp);

    return result;
}

// find derivative of polynomial (apply power rule)
Polynomial Polynomial::derivative() const
{
    Polynomial result;
    Node *head1 = getHead(this);

    // for each term: d/dx (a*x^n) = (a*n)*x^(n-1)
    for (Node *cur = head1; cur; cur = cur->next)
        if (cur->exp > 0)
            result.insertTerm(cur->coeff * cur->exp, cur->exp - 1);

    return result;
}
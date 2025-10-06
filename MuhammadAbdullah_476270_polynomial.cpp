// header files
#include "Polynomial.h"
#include <map>
#include <sstream>
#include <cmath>

using namespace std;

// Internal structure to store polynomial terms
class PolynomialImpl
{
public:
    map<int, int> terms;
};

// Helper function that returns internal data structure of a given Polynomial object
static PolynomialImpl &getImpl(Polynomial *p)
{

    static map<Polynomial *, PolynomialImpl> storage;
    return storage[p];
}

// Insert a term into the polynomial
void Polynomial::insertTerm(int coefficient, int exponent)
{
    PolynomialImpl &impl = getImpl(this);
    if (coefficient == 0)
        return; // skip adding zero terms

    // Add coefficient if term already exists, otherwise create new one
    impl.terms[exponent] += coefficient;

    // If the coefficient becomes zero after addition, remove that term
    if (impl.terms[exponent] == 0)
        impl.terms.erase(exponent);
}

// Convert polynomial to readable string form
string Polynomial::toString() const
{
    const PolynomialImpl &impl = getImpl(const_cast<Polynomial *>(this));
    if (impl.terms.empty())
        return "0"; // return 0 for empty polynomial

    ostringstream oss;
    bool first = true;

    // Iterate from highest to lowest exponent
    for (auto it = impl.terms.rbegin(); it != impl.terms.rend(); ++it)
    {
        int exp = it->first;
        int coeff = it->second;

        // Handle sign display
        if (!first)
            oss << (coeff > 0 ? " + " : " - ");
        else if (coeff < 0)
            oss << "-";
        first = false;

        // Display term with correct format
        int absCoeff = abs(coeff);
        if (exp == 0)
            oss << absCoeff; // constant term
        else if (exp == 1)
        {
            if (absCoeff != 1)
                oss << absCoeff;
            oss << "x";
        }
        else
        {
            if (absCoeff != 1)
                oss << absCoeff;
            oss << "x^" << exp;
        }
    }
    return oss.str();
}

// Add two polynomials
Polynomial Polynomial::add(const Polynomial &other) const
{
    Polynomial result;
    PolynomialImpl &r = getImpl(&result);

    const PolynomialImpl &a = getImpl(const_cast<Polynomial *>(this));
    const PolynomialImpl &b = getImpl(const_cast<Polynomial *>(&other));

    // Copy all terms from first polynomial
    r.terms = a.terms;

    // Add matching terms from the second polynomial
    for (auto &kv : b.terms)
    {
        r.terms[kv.first] += kv.second;
        if (r.terms[kv.first] == 0)
            r.terms.erase(kv.first);
    }
    return result;
}

// Multiply two polynomials
Polynomial Polynomial::multiply(const Polynomial &other) const
{
    Polynomial result;
    PolynomialImpl &r = getImpl(&result);

    const PolynomialImpl &a = getImpl(const_cast<Polynomial *>(this));
    const PolynomialImpl &b = getImpl(const_cast<Polynomial *>(&other));

    // Multiply each term of 'a' with each term of 'b'
    for (auto &kv1 : a.terms)
    {
        for (auto &kv2 : b.terms)
        {
            int exp = kv1.first + kv2.first;     // add exponents
            int coeff = kv1.second * kv2.second; // multiply coefficients
            r.terms[exp] += coeff;
            if (r.terms[exp] == 0)
                r.terms.erase(exp);
        }
    }
    return result;
}

// Compute derivative of the polynomial
Polynomial Polynomial::derivative() const
{
    Polynomial result;
    PolynomialImpl &r = getImpl(&result);
    const PolynomialImpl &a = getImpl(const_cast<Polynomial *>(this));

    // Apply power rule: d/dx [c*x^n] = n*c*x^(n-1)
    for (auto &kv : a.terms)
    {
        if (kv.first > 0)
            r.terms[kv.first - 1] = kv.second * kv.first;
    }
    return result;
}

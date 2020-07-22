#include <iostream>
#include "polynomial.h"

int main() {

    Polynomial p1;
    // testing Change Coefficient method accurately insert and remove terms.
    p1.changeCoefficient( 1, 1 );
    p1.changeCoefficient( 3, 3 );
    p1.changeCoefficient( 2.2, 2 );
    cout << "Testing change coeffient/insert/remove methods" << endl;
    cout << endl;
    cout << "expected results: 3x^3 + 2.2x^2 + 1x" << endl;
    cout << "actual p1 = " << p1 << endl;
    p1.changeCoefficient( 0, 2 );
    cout << "expected results: 3x^3 + 1x" << endl;
    cout << "actual p1 = " << p1 << endl;
    cout << endl;

    //testing assignment operators

    cout << "Testing assignment operators" << endl;
    cout << endl;
    Polynomial p2 = p1;
    cout << "expected results p2 = p1; both = 3x^3 + 1x" << endl;
    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;
    p1 += p2;
    cout << "expected results p1 += p2 =  6x^3 + 2x" << endl;
    cout << "p1 = " << p1 << endl;
    p1 -= p2;
    cout << "expected results p1 += p2 =  3x^3 + 1x" << endl;
    cout << "p1 = " << p1 << endl;
    cout << endl;

    // testing copy constructor

    Polynomial p3 = Polynomial(p1);
    cout << "expected results p3 = Polynomial(p1) =  3x^3 + 1x" << endl;
    cout << "p3 = " << p3 << endl;
    cout << endl;


    // testing bool statements
    cout << "Testing Bool " << endl;
    cout << endl;
    bool test = p1 == p2;
    cout << "expected results p1 == p2 = 1" << endl;
    cout << test << endl;
    cout << "expected results p1 != p2 = 0" << endl;
    test = p1 != p2;
    cout << test << endl;
    cout << endl;

    cout << "p1.degree = expected = 3 " << endl;
    cout << "p1.degree = " << p1.degree() << endl;

    cout << "p1.coeffecient(3) = expected = 3 " << endl;
    cout << "p1.coeffecient(3) = " << p1.coefficient(3) << endl;


    return 0;
}
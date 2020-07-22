//
// Created by Tony Tran on 11/17/19.
//

#ifndef POLYNOMIAL_POLYNOMIAL_H
#define POLYNOMIAL_POLYNOMIAL_H
#include <iostream>
#include <string>


using namespace std;

class Polynomial {// Overloaded <<: prints Cn * x^n + Cn-1 * X^n-1 + ... C1 * X + C0
private:
    int size;
    struct Term {
        // a term on the sparce polynomial
        double coeff;   // the coefficient of each term
        int power;      // the degree of each term
        struct Term *prev;     // a pointer to the previous higher term
        struct Term *next;     // a pointer to the next lower term
    };
    bool remove( Term* pos );     // # terms in the sparce polynomial


public:
    Term *head;     // a pointer to the doubly-linked circular list of
    // sparce polynomial
    friend ostream& operator<<( ostream &output, const Polynomial& p );
    Polynomial( );    // Constructor: the default is a 0-degree polynomial with 0.0 coefficient public: Member functions
    Polynomial( const Polynomial& p );
    ~Polynomial( );
    int degree( ) const; // returns the higheset degree of a polynomial
    int degreeLow( ) const; // return the lowest degree of the polynomial
    double coefficient( const int power ) const;// returns the coefficient of the x^power term.
    bool changeCoefficient( const double newCoefficient, const int power ); // replaces the coefficient of the x^power term Arithmetic operators
    Polynomial operator+( const Polynomial& p )const;
    Polynomial operator-( const Polynomial& p )const;

    bool operator==( const Polynomial& p ) const;    // Boolean comparison operators
    bool operator!=( const Polynomial& p ) const;

    Polynomial& operator=( const Polynomial& p );    // Assignment operators
    Polynomial& operator+=( const Polynomial& p );
    Polynomial& operator-=( const Polynomial& p );
    void clear();
    bool isEmpty() const;
    void print() const;
    bool insert(const double newCoefficient, const int power );
    bool insertAdd(const double newCoefficient, const int power );
    bool insertSubtract(const double newCoefficient, const int power );
    int getSize() const;
    void removeEmptyCoeff();
};

#endif //POLYNOMIAL_POLYNOMIAL_H

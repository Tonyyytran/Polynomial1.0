//
// Created by Tony Tran on 11/20/19.
//

#include "polynomial.h"


Polynomial::Polynomial(){
    head = new Term;// 0th node is a dummy.
    head->next = head;
    head->prev = head;
    size = 0;
}
Polynomial::Polynomial( const Polynomial &rhs ) {
    head = new Term;             // create a dummy
    head->next = head;
    head->prev = head;// then assign rhs to this.  *this = rhs;
    size = 0;
    if ( rhs.isEmpty() )
        return;
    Term *Current = rhs.head->next;
    while( Current != rhs.head) { //stops when reaching header because circularly linked
        insert(Current->coeff, Current->power);
        Current = Current -> next;
    }

}

Polynomial::~Polynomial( ) {
    clear( );                                       // delete items starting 1st
    delete head;                                  // delete a dummy (at 0th).
}

bool Polynomial::isEmpty( ) const {
    return head->next == head;
}
void Polynomial::clear( ) {
    while ( !isEmpty( ) ) {
        Term *node = head->next;    // find the 1st object
        remove( node );
    }
}

bool Polynomial::remove( Term* pos ) {
    Term *deleteNode = pos;
    if ( isEmpty()) // list is empty
        return false;
    deleteNode->prev->next = deleteNode->next;
    deleteNode->next->prev = deleteNode->prev;
    delete deleteNode;     // deallocate
    size--;
    return true;
}

void Polynomial::removeEmptyCoeff(){
    Term *current = head->next;
    while ( current->next != head){
        if (current->coeff == 0)
            remove(current);
        current = current->next;
    }
}



bool Polynomial::insert(const double newCoefficient, const int power )  {
    Term *current = head;// find an indexed object
    Term *newPtr = new Term;  // allocate space
    newPtr->power = power;                                 // fix pointers
    newPtr->coeff = newCoefficient;
    while(current->next->power > newPtr->power)
        current = current->next; // move down the power list
    if (newPtr->power == current->next->power) {
        remove(current->next);
        insert(newCoefficient, power);
    }
    else {
        newPtr->next = current->next;
        current->next = newPtr;
        newPtr->next->prev = newPtr;
        newPtr->prev = current;
    }
    size++;
    return true;
}
bool Polynomial::insertAdd(const double newCoefficient, const int power ) {
    Term *current = head;// find an indexed object
    Term *newPtr = new Term;  // allocate space
    newPtr->power = power;                                 // fix pointers
    newPtr->coeff = newCoefficient;
    while(current->next->power > newPtr->power)
        current = current->next; // move down the power list
    if (current->next->power == newPtr->power) {
        current->next->coeff = current->next->coeff + newPtr->coeff;
    }
    else {
        newPtr->next = current->next;
        current->next = newPtr;
        newPtr->next->prev = newPtr;
        newPtr->prev = current;
        size++;
    }
    return true;
}
bool Polynomial::insertSubtract(const double newCoefficient, const int power) {
    Term *current = head;// find an indexed object
    Term *newPtr = new Term;  // allocate space
    newPtr->power = power;                                 // fix pointers
    newPtr->coeff = newCoefficient;
    while(current->next->power > newPtr->power)
        current = current->next; // move down the power list
    if (current->next->power == newPtr->power) {
        current->next->coeff = current->next->coeff - newPtr->coeff;
    }
    else {
        newPtr->next = current->next;
        current->next = newPtr;
        newPtr->next->prev = newPtr;
        newPtr->prev = current;
        size++; // increase size, although subtract it will add extra term
    }
    return true;
}
void Polynomial::print() const { // print the list
    string out;
    Term *Current = head->next;
    while(Current != head) {
        cout << Current->coeff << "x^" << Current->power<<endl;
        Current = Current->next;
    }
}

int Polynomial::degree() const{ // return the highest degree polynomial
    if ( isEmpty()){
        return 0;
    }
    return head->next->power;
}

int Polynomial::degreeLow( ) const{ // return the lowest degree polynomial
    Term * Current = head->next;
    while(Current->next != head)
        Current = Current->next;
    return Current->power;
}

double Polynomial::coefficient( const int power ) const{
    if ( isEmpty()){
        return 0.0;
    }
    Term *Current = head->next;
    while(Current != head) {
        if ( Current->power == power)
            return Current->coeff;
        Current = Current->next;
    }
    return 0.0;
}

int Polynomial::getSize() const {
    return size;
}

bool Polynomial::changeCoefficient( const double newCoefficient, const int power ){
    return insert(newCoefficient, power);
}

ostream& operator<<( ostream &output, const Polynomial& p ) {
    for(int i = p.degree(); i >= p.degreeLow(); i-- ){
        if (p.coefficient(i) != 0){
            if ( i != p.degree()) {
                if (i == 1)
                    output << " + " << p.coefficient(i) << "x";
                else
                    output << " + " << p.coefficient(i) << "x^" << i;
            }
            else{
                if (i == 1)
                    output << p.coefficient(i) << "x";
                else
                    output << p.coefficient(i) << "x^" << i ;
            }

        }
    }
    return output;
}
Polynomial Polynomial::operator+( const Polynomial& p )const{
    Polynomial temp = *this;
    Term *Current = p.head->next;
    while( Current != p.head) { //stops when reaching header because circularly linked
        temp.insertAdd(Current->coeff, Current->power);
        Current = Current -> next;
    }
    return temp;
}
Polynomial Polynomial::operator-( const Polynomial& p ) const{
    Polynomial temp = *this;
    Term *Current = p.head->next;
    while( Current != p.head) { //stops when reaching header because circularly linked
        temp.insertSubtract(Current->coeff, Current->power);
        Current = Current -> next;
    }
    return temp;
}

Polynomial& Polynomial::operator=( const Polynomial& p ){
    if ( head == p.head )
        return *this;
    this->clear();
    Term *Current = p.head->next;
    while( Current != p.head) { //stops when reaching header because circularly linked
        this->insert(Current->coeff, Current->power);
        Current = Current -> next;
    }
    return *this;
}

bool Polynomial::operator==( const Polynomial& p ) const{   // Boolean comparison operators
    if (degree() == p.degree() && getSize() == p.getSize()){
        Term *current = head->next;
        Term *currentP = p.head->next;
        while(current != head){
            if ( current->coeff != currentP->coeff || current->power != currentP->power)
                return false;
            current = current->next;
            currentP = currentP->next;
        }
        return true;
    }
    return false;
}

bool Polynomial::operator!=( const Polynomial& p ) const{   // Boolean comparison operators
    if (degree() == p.degree() && getSize() == p.getSize()){
        Term *current = head->next;
        Term *currentP = p.head->next;
        while(current != head){
            if ( current->coeff != currentP->coeff || current->power != currentP->power)
                return true;
            current = current->next;
            currentP = currentP->next;
        }
        return false;
    }
    return true;
}

Polynomial& Polynomial::operator+=( const Polynomial& p ){
    Term *Current = p.head->next;
    while( Current != p.head) { //stops when reaching header because circularly linked
        insertAdd(Current->coeff, Current->power);
        Current = Current -> next;
    }
    return *this;
}

Polynomial& Polynomial::operator-=( const Polynomial& p ){
    Term *Current = p.head->next;
    while( Current != p.head) { //stops when reaching header because circularly linked
        insertSubtract(Current->coeff, Current->power);
        Current = Current -> next;
    }
    return *this;
}
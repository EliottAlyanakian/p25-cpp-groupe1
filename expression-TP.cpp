/*

implement a hierarchy of classes for arithmetic expression manipulations:
    - the classes holds, evaluates and prints arithmetic expressions
    - print in infix, prefix or postfix notation

Additional work:
   - note that the postfix notation is also called Reverse Polish notation (RPN)
   - it is a mathematical notation in which operators follow their operands
   - this notation does not need any parentheses i.e. this notation is non ambigu
   - => you can read (easily) RPN expressions using a stacks
  implement a code to read RPN expression and store them with your class objects
  RPN arithmetic expression are passed as main command-line arguments

./main 87 12 - + 75 -
*/

#include <iostream>
#include <vector>
#include <stdexcept>

class Expression
{
public:
    virtual int eval()
    {
        return 0;
    }
    virtual void print() {};
};

class Constant : public Expression
{
private:
    int value;

public:
    Constant(int v) : value(v)
    {
    }
    int eval()
    {
        return value;
    }
    void print()
    {
        std::cout << value;
    }
};

class UnaryMinus : public Expression
{
private:
    Expression &expr; // l'element d'expression que je veux mettre en negatif
public:
    UnaryMinus(Expression &e) : expr(e)
    {
    }
    int eval()
    {
        return -expr.eval();
    }
    void print()
    {
        expr.print(); // utliser la fonction print adapter à l'objet expr
        std::cout << " -";
    }
};

class Plus : public Expression
{
private:
    Expression &x;
    Expression &y;

public:
    Plus(Expression &l, Expression &r) : x(l), y(r)
    {
    }
    int eval()
    {
        return x.eval() + y.eval();
    }
    void print()
    {
        x.print();
        std::cout << " ";
        y.print();
        std::cout << "+";
    }
};
class Minus : public Expression
{
    Expression &x;
    Expression &y;

public:
    Minus(Expression &l, Expression &r) : x(l), y(r)
    {
    }
    int eval()
    {
        return x.eval() - y.eval();
    }
    void print()
    {
        x.print();
        y.print();
        std::cout << " -";
    }
};

class Divide : public Expression
{
    Expression &x;
    Expression &y;

public:
    Divide(Expression &l, Expression &r) : x(l), y(r)
    {
    }
    int eval()
    {
        int denom = y.eval();
        if (denom == 0)
        {
            throw std::runtime_error("on ne peut pas diviser par 0");
        }
        return x.eval() / denom;
    }
    void print()
    {
        x.print();
        y.print();
        std::cout << " /";
    }
};

int main()
{
    try
    {
        // Constant c1(12), c2(-87), c3(23); // try it (-87 is not an unsigned int)
        Constant c1(12), c2(87), c3(75);

        c1.print(); // affiche 12
        std::cout << std::endl;
        std::cout << "eval " << c1.eval() << std::endl; // affiche 12

        UnaryMinus u1(c1);
        u1.print(); // affiche 12 -
        std::cout << std::endl;
        std::cout << "eval " << u1.eval() << std::endl; // affiche -12

        Plus p1(c2, u1);
        p1.print(); // affiche 87 12 -+
        std::cout << std::endl;
        std::cout << "eval " << p1.eval() << std::endl; // affiche 75

        Minus m1(p1, c3);
        m1.print(); // 87 12 -+75 -
        std::cout << std::endl;
        std::cout << "eval " << m1.eval() << std::endl; // affiche 0

        Divide d1(p1, m1);
        std::cout << std::endl;
        std::cout << d1.eval() << std::endl; // throws an instance of 'std::runtime_error'

        std::vector<Expression *> expr;
        expr.push_back(&c1);
        expr.push_back(&c2);
        expr.push_back(&c3);
        // parcourez le vecteur
    }
    catch (std::runtime_error &e)
    {
        // affiche zero divide error
        std::cout << e.what() << std::endl;
    }
    return 0;
}

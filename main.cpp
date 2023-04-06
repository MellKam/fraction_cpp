#include <iostream>

class Fraction
{
private:
  int numerator;
  int denominator;

  /*
    Get greatest common divisor of two integers using the Euclidean algorithm
  */
  int get_gcd(int a, int b)
  {
    if (b == 0)
      return a;
    return this->get_gcd(b, a % b);
  }

public:
  Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator)
  {
    if (denominator == 0)
    {
      throw std::invalid_argument("Denominator cannot be zero.");
    }
  }

  Fraction(int numerator) : numerator(numerator), denominator(1) {}

  Fraction &reduce()
  {
    int gcd = this->get_gcd(this->numerator, this->denominator);
    this->numerator /= gcd;
    this->denominator /= gcd;
    return *this;
  }

  Fraction add(int n) const
  {
    return Fraction(
               this->numerator + n * this->denominator,
               this->denominator)
        .reduce();
  }

  Fraction add(const Fraction &f) const
  {
    return Fraction(
               this->numerator * f.denominator + f.numerator * this->denominator,
               this->denominator * f.denominator)
        .reduce();
  }

  Fraction subtract(int n) const
  {
    return Fraction(
               this->numerator - n * this->denominator,
               this->denominator)
        .reduce();
  }

  Fraction subtract(const Fraction &f) const
  {
    return Fraction(
               this->numerator * f.denominator - f.numerator * this->denominator,
               this->denominator * f.denominator)
        .reduce();
  }

  Fraction divide(int n) const
  {
    if (n == 0)
    {
      throw std::invalid_argument("Unable to divide by zero.");
    }
    return Fraction(
               this->numerator,
               this->denominator * n)
        .reduce();
  }

  Fraction divide(const Fraction &f) const
  {
    return Fraction(
               this->numerator * f.denominator,
               this->denominator * f.numerator)
        .reduce();
  }

  Fraction multiply(int n) const
  {
    return Fraction(
               this->numerator * n,
               this->denominator)
        .reduce();
  }

  Fraction multiply(const Fraction &f) const
  {
    return Fraction(
               this->numerator * f.numerator,
               this->denominator * f.denominator)
        .reduce();
  }

  const Fraction &print() const
  {
    std::cout << this->numerator << "/" << this->denominator << std::endl;
    return *this;
  }

  double evaluate() const
  {
    return (double)numerator / denominator;
  }

  const Fraction &print_evaluated() const
  {
    std::cout << this->evaluate() << std::endl;
    return *this;
  }
};

int main()
{
  Fraction f1(10, 2);
  Fraction f2(1, 2);

  f1.print(); // 10/2
  f2.print(); // 1/2

  try
  {
    Fraction a(1, 0);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl; // Denominator cannot be zero.
  }

  f1.add(f2).print();      // 11/2
  f1.multiply(f2).print(); // 5/2

  f1.reduce().print();                     // 5/1
  std::cout << f1.evaluate() << std::endl; // 5

  Fraction({1, 10000}).print_evaluated(); // 0.0001

  Fraction(50, 25)
      .add({100, 25})
      .multiply({2, 1})
      .add({4, 8})
      .multiply({10, 2})
      .print_evaluated(); // 62.5

  Fraction(10, 5).divide({2, 1}).print(); // 1/1

  Fraction(8, 3).add(2).multiply(2).divide(2).print(); // 14/3

  Fraction(1).divide(2).multiply(4).print_evaluated(); // 2

  try
  {
    Fraction(1).divide(0);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl; // Unable to divide by zero.
  }

  Fraction(5).subtract(2).subtract({2, 3}).print(); // 7/3

  return 0;
}
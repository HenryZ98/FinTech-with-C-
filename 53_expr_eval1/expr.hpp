#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

class Expression {
public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression: public Expression {
private:
  long num;
public:
  NumExpression(long input) {
    num = input;
  };
  virtual std::string toString() const {
    std::ostringstream ss;
    ss << num;
    std::string ans = ss.str();
    return ans;
  }
  virtual ~NumExpression() {}
};

class OPExpression: public Expression {
private:
  const char * op;
  Expression * lhs;
  Expression * rhs;
public:
  OPExpression(const char *Op, Expression * num1, Expression * num2) {
    op = Op;
    lhs = num1;
    rhs = num2;
  }
  virtual std::string toString() const {
    std::ostringstream ans;
    ans << "(" << lhs->toString() << " " << op << " " << rhs->toString() << ")";
    return ans.str();
  }
  virtual ~OPExpression() {
    delete lhs;
    delete rhs;
  }
};

class PlusExpression : public OPExpression{
public:
  PlusExpression(Expression * lhs, Expression * rhs): OPExpression("+",lhs,rhs){}
};

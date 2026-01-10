#include <iostream>
#include <string>

class StringValidator
{
protected:
  std::string password;
public:
  virtual ~StringValidator() {};
  StringValidator() {};
  StringValidator(std::string password) : password(password) {};
  virtual bool isValid(std::string input) = 0;
};

class ExactValidator : public StringValidator {
public:
	ExactValidator(std::string password) : StringValidator(password) {};
	bool isValid(std::string input) override;
};

bool ExactValidator::isValid(std::string input)
{
	return (input == password);
}

class DummyValidator : public StringValidator {
public:
	bool isValid(std::string input) override;
};

bool DummyValidator::isValid(std::string input)
{
  return true;
}

void printValid(StringValidator &validator, std::string input)
{
  std::cout << "The string '" << input << "' is "
       << (validator.isValid(input) ? "valid" : "invalid") << std::endl;
}

int main()
{
  DummyValidator dummy;
  printValid(dummy, "hello");
  ExactValidator exact("secret");
  printValid(exact, "hello");
  printValid(exact, "secret");
  return 0;
}

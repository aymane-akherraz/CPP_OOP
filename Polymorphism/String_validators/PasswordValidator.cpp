#include <iostream>
#include <string>

using namespace std;

class StringValidator
{
public:
	virtual ~StringValidator() {};
	virtual bool isValid(string input) = 0;
};

class PatternValidator : public StringValidator
{
private:
	string pattern;
public:
	PatternValidator(string pattern) : pattern(pattern) {};
	bool isValid(string input) override;
};

bool PatternValidator::isValid(string input)
{
	int (*p)(int);
	if (pattern == "D")
		p = isdigit;
	else if (pattern == "A")
		p = isupper;
	else if (pattern == "a")
		p = islower;
	else if (pattern == "?")
		p = ispunct;
	int i = 0;
	while (input[i])
	{
		if (p(input[i]))
			return true;
		i++;
	}
	return false;
}

class MinLengthValidator : public StringValidator
{
private:
	size_t min;
public:
	MinLengthValidator(size_t min) : min(min) {};
    bool isValid(string input) override;
};

bool MinLengthValidator::isValid(string input)
{
	return (input.length() >= min);
}

class MaxLengthValidator : public StringValidator
{
private:
	size_t max;
public:
	MaxLengthValidator(size_t max) : max(max) {};
    bool isValid(string input) override;
};

bool MaxLengthValidator::isValid(string input)
{
	return (input.length() <= max);
}

class LengthValidator : public StringValidator
{
public:
	LengthValidator(int min, int max);
	bool isValid(string input) override;
private:
	MinLengthValidator min_validator;
	MaxLengthValidator max_validator;
};

LengthValidator::LengthValidator(int min, int max):
  min_validator(min), max_validator(max)
{
}

bool LengthValidator::isValid(string input)
{
  return ( min_validator.isValid(input)
        && max_validator.isValid(input) );
}

class PasswordValidator : public StringValidator
{
public:
	PasswordValidator();
	bool isValid(string input) override;
private:
	LengthValidator len_validator;
	PatternValidator lower_validator;
	PatternValidator upper_validator;
	PatternValidator digit_validator;
	PatternValidator punct_validator;
};

PasswordValidator::PasswordValidator() :
		len_validator(8, 10),
		lower_validator("a"),
		upper_validator("A"),
		digit_validator("D"),
		punct_validator("?")
{
}

bool PasswordValidator::isValid(string input)
{
	return (len_validator.isValid(input)
			&& lower_validator.isValid(input)
			&& upper_validator.isValid(input)
			&& digit_validator.isValid(input)	
			&& punct_validator.isValid(input));
}

void printValid(StringValidator &validator, string input)
{
  cout << "The string '" << input << "' is "
       << (validator.isValid(input) ? "valid" : "invalid");
}

int main()
{
	PasswordValidator validator;
	printValid(validator, "P4ssw[]rd");
	cout << endl;	
	printValid(validator, "qwerty");
	cout << endl;	
}

#include <iostream>
#include <string>

using namespace std;

class StringValidator
{
protected:
	string pattern;
public:
	virtual ~StringValidator() {};
	StringValidator() {};
	StringValidator(string pattern) : pattern(pattern) {};
	virtual bool isValid(string input) = 0;
};

class MinLengthValidator : public StringValidator
{
private:
	size_t min;
public:
	MinLengthValidator(size_t min) : min(min) {};
    virtual bool isValid(string input) override;
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
    virtual bool isValid(string input) override;
};

bool MaxLengthValidator::isValid(string input)
{
	return (input.length() <= max);
}

class PatternValidator : public StringValidator
{
public:
	PatternValidator(string pattern) : StringValidator(pattern) {};
	static bool check_match(char p, char c);
	bool isValid(string input) override;
};

bool PatternValidator::check_match(char p, char c)
{
	if (p == 'D')
		return isdigit(c);
	else if (p == 'A')
		return isalpha(c);
	else if (islower(p))
		return (tolower(c) == p);
	else if (p == '?')
		return true;
	else if (ispunct(p))
		return (p == c);
	return false;
}

bool PatternValidator::isValid(string input)
{
	int i = 0;

	while (input[i])
	{
		int j = 0;
		while (pattern[j] && input[i + j] && check_match(pattern[j], input[i + j]))
		{
			j++;
		}
		if (j == pattern.length())
			return true;
		i++;
	}
	return false;
}

void printValid(StringValidator &validator, string input)
{
	cout << "The string '" << input << "' is "
       << (validator.isValid(input) ? "valid" : "invalid") << endl;
}

int main()
{
	cout << "MinLengthValidator" << endl;
	MinLengthValidator min(6);
	printValid(min, "hello");
	printValid(min, "welcome");
	cout << endl;

	cout << "MaxLengthValidator" << endl;
	MaxLengthValidator max(6);
	printValid(max, "hello");
	printValid(max, "welcome");
	cout << endl;
	cout << "PatternValidator" << endl;
	PatternValidator digit("e-D");
	printValid(digit, "There are-2 types of sentences in the world");
	printValid(digit, "valid and invalid ones");
	cout << endl;
	return 0;
}

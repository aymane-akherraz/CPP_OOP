#include <iostream>

using namespace std;

class Piece
{
public:
	virtual bool can_move(const string& from, const string& to) = 0;
protected:
	static bool is_valid_position(const string& pos);
};

bool Piece::is_valid_position(const string& pos)
{
	return (pos.length() == 2 && pos[0] >= 'a' && pos[0] <= 'h'
			&& pos[1] >= '1' && pos[1] <= '8');
}

class Man : public Piece
{
public:
	bool can_move(const string& from, const string& to) override;
};

bool Man::can_move(const string& from, const string& to)
{
	if (is_valid_position(from) && is_valid_position(to))
	    return (abs(to[0] - from[0]) == 1 && (to[1] - from[1]) == 1);
	return false;
}

class King : public Piece
{
public:
	bool can_move(const string& from, const string& to) override;
};

bool King::can_move(const string& from, const string& to)
{
	if (is_valid_position(from) && is_valid_position(to))
	    return (abs(to[0] - from[0]) == abs(to[1] - from[1]));
	return false;
}

int main()
{
	Piece *pieces[] = { new Man(), new King(), new Man() };
	cout.setf(ios::boolalpha);	
	cout << pieces[0]->can_move("b1", "c2") << endl;
	cout << pieces[1]->can_move("b1", "d3") << endl;
	cout << pieces[2]->can_move("b1", "d3") << endl;
}

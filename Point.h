#ifndef POINT_H
#define POINT_H
class Point
{
private:
	int x, y;

public:
	Point();
	Point(int xParam, int yParam);

	void setX(int xParam);
	void setY(int yParam);

	int getX();
	int getY();

	Point& operator=(Point const& pointParam);
	bool operator==(Point const& pointParam);

	bool operator>=(Point const& pointParam);
	bool operator<=(Point const& pointParam);

	void print();
};

#endif // !POINT_H

#ifndef POINT_H
#define POINT_H
class Point
{
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
private:
	int x, y;
};

#endif // !POINT_H

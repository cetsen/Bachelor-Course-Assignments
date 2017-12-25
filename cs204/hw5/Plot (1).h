//Sena Necla Çetin 21120	CS201L-A2	HW5		April 16, 2017

struct Point
{
	int x;
	double y;
};

class Plot
{
private:
	int size;
	Point point;
	
public:
	int index;
	Point *arrayptr;
	Plot(); 
	Plot(int number);
	Plot(const Plot &);  
	~Plot();  
	void Plot::deleteAll(); 
	void Plot::createClone(const Plot & plot);
	Plot Plot::operator + (const Point & point);
	Plot Plot::operator - (const Point & rhs); 
	Plot & Plot::operator = (const Plot & rhs);  
	bool Plot::operator == (const Plot & rhs);  
	const Plot & Plot::operator += (const Plot & rhs);  
	Plot & Plot::operator -= (const Point & rhs);  
	int Plot::GetSize();
	Point Plot::GetIndexedPoint(int index) const;
	int Plot::FindXIndex(const Point & p) const;
};


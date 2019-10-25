#ifndef LS_h
#define LS_h
class LeastSquare {
	double a, b, r_2;

public:
	LeastSquare(const std::vector <double>& x, const std::vector<double>& y)
	{
		if (x.size() != y.size())
			error("LeastSquare: the input vector must have same size\n");

		double t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0;
		for (unsigned i = 0; i<x.size(); ++i)
		{
			t1 += x[i] * x[i];
			t2 += x[i];
			t3 += x[i] * y[i];
			t4 += y[i];
			t5 += y[i] * y[i];
		}

		a = (t3*x.size() - t2 * t4) / (t1*x.size() - t2 * t2);
		//b = (t4 - a*t2) / x.size();  
		b = (t1*t4 - t2 * t3) / (t1*x.size() - t2 * t2);
		double r = (x.size()*t3 - t2 * t4) / (sqrt(x.size()*t1 - t2 * t2)*sqrt(x.size()*t5 - t4 * t4));
		r_2 = r * r;
		/*
		double average_x = t2 / x.size();
		double average_y = t4 / x.size();
		double t5 = 0, t6 = 0, t7 = 0;
		for (unsigned i = 0; i < x.size(); ++i) {
			double dx = (x[i] - average_x);
			double dy = (y[i] - average_y);
			t5 += dx * dy;
			t6 += dx * dx;
			t7 += dy * dy;
		}*/
	}

	double getY(const double x) const
	{
		return a * x + b;
	}

	double GetSlope() {
		return a;
	}
	double GetIntercept() {
		return b;
	}
	double GetR() {
		return r_2;
	}
};

#endif

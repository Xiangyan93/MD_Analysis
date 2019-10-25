#ifndef XYFUNC_h
#define XYFUNC_h
// vector++;
void VectorPlusOne(std::vector <unsigned> &state, const std::vector<unsigned> scale)
{
	state[0] += 1;
	for (unsigned i = 0;i < state.size();++i) {
		if (state[i] == scale[i]) {
			state[i] = 0;
			state[i + 1] += 1;
		}
	}
}
void right_fprintf(FILE *fp, std::string line, unsigned n) {
	if (n > 20) {
		error("function: right_fprintf(FILE *fp, string line, unsigned n) can be used only for n <=20\n");
	}
	std::string temp = line;
	temp.insert(0, "                    ", n - temp.size());
	fprintf(fp, "%s", temp.c_str());
}
/*double atof(std::string s)*/
/*{*/
/*return atof(s.c_str());*/
/*}*/
//judge whether all elements in a vector is diffrent
template <class Type>
bool IsAllDiff(std::vector<Type> value)
{
  for(unsigned i=0;i<value.size();++i){
    for(unsigned j=i+1;j<value.size();++j){
      if(value[i]==value[j])
        return false;
    }
  }
  return true;
}
bool IsOnlyOneTrue(unsigned num, ...) {
	va_list ap;
	va_start(ap, num);
	unsigned k = 0;
	for (unsigned i = 0;i < num;++i) {
		bool temp=va_arg(ap, int);
		if (temp) k++;
	}
	va_end(ap);
	if (k == 1) return true;
	else return false;
}
//square function
template <class Type>
Type square(Type value) {
	Type s = value*value;
	return s;
}
//judge whether a data can be found in a vector
template <class Type>
bool IsInside(Type in, std::vector<Type> value)
{
  for(unsigned i=0;i<value.size();++i){
    if(in==value[i])
      return true;
  }
  return false;
}
template <class Type>
bool IsInside(Type in, std::vector<Type> value, unsigned &a)
{
  for(unsigned i=0;i<value.size();++i){
    if(in==value[i]){
      a=i;
      return true;
    }
  }
  return false;
}

//
std::string HeadSpace(std::string s, unsigned length) {
	if (s.length() > length) {
		printf("%s,%d\n", s.c_str(), length);
		error("In function std::string HeadSpace(string s, int length), the length of string s must small than int length\n");
        return 0;
	}
	else {
		std::string info;
		unsigned l = length - s.length();
		for (unsigned i = 0; i < l; ++i) info += " ";
		info += s;
		return info;
	}
}
std::string TailSpace(std::string s, unsigned length) {
	if (s.length() > length) {
		printf("%s,%d\n", s.c_str(), length);
		error("In function std::string TailSpace(string s, int length), the length of string s must small than int length\n");
        return 0;
	}
	else {
		std::string info = s;
		unsigned l = length - s.length();
		for (unsigned i = 0; i < l; ++i) info += " ";
		return info;
	}
}
//get the length of a integer
unsigned GetLength(unsigned num) {
	unsigned l=1;
	while (num > 10) {
		num /= 10;
		l++;
	}
	return l;
}
//get the minimum value of a vector
template <class Type>
Type GetMin(std::vector <Type> value)
{
  Type min=value[0];
  for(unsigned i=1;i<value.size();++i){
    if(value[i]<min)
      min = value[i];
  }
  return min;
} 
//get the minimum value of a vector, and the position of the minimum value
template <class Type>
Type GetMin(std::vector <Type> value,unsigned &a)
{
  Type min=value[0];
  a=0;
  for(unsigned i=1;i<value.size();++i){
    if(value[i]<min){
      min = value[i];
      a=i;
    }
  }
  return min;
}
//get the minimum value of a series of double type number
double GetMinDouble(unsigned num, ...) {
	va_list ap;
	va_start(ap, num);
	double min = va_arg(ap, double);
	for (unsigned i = 1;i < num;++i) {
		double temp = va_arg(ap, double);
		if (temp < min)
			min = temp;
	}
	return min;
}
//get the minimum value of a series of int type number
int GetMinInt(unsigned num, ...) {
	va_list ap;
	va_start(ap, num);
	int min = va_arg(ap, int);
	for (unsigned i = 1;i < num;++i) {
		int temp = va_arg(ap, int);
		if (temp < min)
			min = temp;
	}
	return min;
}
//get the maximum value of a vector
template <class Type>
Type GetMax(std::vector <Type> value)
{
  Type max=value[0];
  for(unsigned i=1;i<value.size();++i){
    if(value[i]>max)
      max = value[i];
  }
  return max;
}
//get the maximum value of a vector, and the position of the maximum value
template <class Type>
Type GetMax(std::vector <Type> value,unsigned &a)
{
  Type max=value[0];
  a=0;
  for(unsigned i=1;i<value.size();++i){
    if(value[i]>max){
      max = value[i];
      a=i;
    }
  }
  return max;
}
//get product
template <class Type>
Type GetProduct(std::vector <Type> value)
{
  Type a=1;
  for(unsigned i=0;i<value.size();++i){
    a *= value[i];
  }
  return a;
}
//get sum
template <class Type>
Type GetSum(std::vector <Type> value)
{
	Type a = 0;
	for (unsigned i = 0;i<value.size();++i) {
		a += value[i];
	}
	return a;
}
//get average
std::vector <double> GetAverage(std::vector <std::vector <double> > v) {
	std::vector <double> temp(v[0].size(), 0);
	for (unsigned i = 0; i < temp.size(); ++i) {
		for (unsigned j = 0; j < v.size(); ++j) {
			temp[i] += v[j][i];
		}
		temp[i] /= v.size();
	}
	return temp;
}
double GetAverage(std::vector <double> value)
{
  double a=0.;
  for(unsigned i=0;i<value.size();++i){
      a += value[i];
  }
  return a/value.size();
}
//get standard deviation
double GetSTD(std::vector <double> value)
{
  double sum=0.;
  for(unsigned i=0;i<value.size();++i){
    sum += value[i];
  }
  double average=sum/value.size();
  double ebar=0.;
  for(unsigned i=0;i<value.size();++i){
    double dv = value[i]-average;
    ebar += dv*dv;
  }
  ebar /= value.size()-1;
  return sqrt(ebar);
}

#endif

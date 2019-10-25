#pragma once
//split a vector using split symbol "pattern"; return a vector of string
std::vector<std::string> split(std::string str, std::string pattern)
{
	std::vector<std::string> ret;
	if (pattern.empty()) return ret;
	size_t start = 0, index = str.find_first_of(pattern, 0);
	while(index!=str.npos) {
	  if (start != index)
		  ret.push_back(str.substr(start, index - start));
	  start = index + 1;
	  index = str.find_first_of(pattern, start);
	}
	if (!str.substr(start).empty())
		ret.push_back(str.substr(start));
	return ret;
}

//itoa
std::string itoa(const unsigned n)
{
	std::stringstream newstr;
	newstr << n;
	return newstr.str();
}
std::string itoa(const unsigned long long n)
{
	std::stringstream newstr;
	newstr << n;
	return newstr.str();
}
//atof
std::vector <double> atof(std::vector <std::string> s)
{
  std::vector <double> a;
  for(unsigned i=0;i<s.size();++i){
    a.push_back(atof(s[i].c_str()));
  }
  return a;
}
//atoi
std::vector <unsigned> atoi(std::vector <std::string> s)
{
  std::vector <unsigned> a;
  for(unsigned i=0;i<s.size();++i){
    a.push_back(atoi(s[i].c_str()));
  }
  return a;
}

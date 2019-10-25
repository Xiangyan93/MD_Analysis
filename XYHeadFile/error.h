#pragma once
void error(std::string error_info)
{
  printf("%s\n",error_info.c_str());
  exit(0);
}
void error(std::string error_info, FILE *log_file)
{
	fprintf(log_file,"%s\n", error_info.c_str());
	exit(0);
}

#pragma once
#include <string>
#include <fstream>

using namespace std;

void errlog(string err_msg) {
	ofstream logfile("err.log");
	logfile << err_msg;
	logfile.close();
}
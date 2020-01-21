#pragma once

#include "stdafx.h"

class PhongException : public std::exception {
public:
	PhongException(const std::string &msg);
	const char *what();

private:
	std::string _msg;
};

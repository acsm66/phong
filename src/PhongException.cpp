#include "stdafx.h"
#include "PhongException.h"

PhongException::PhongException(const std::string &msg) : _msg(msg) {}

const char *PhongException::what() {
	if (_msg.empty()) {
		return "Erro generico";
	}
	return _msg.c_str();
}

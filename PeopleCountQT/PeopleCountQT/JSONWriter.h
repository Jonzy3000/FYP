#pragma once

#include <iostream>
#include "json.h"
#include <fstream>
#include <memory>
#include "qmessagebox.h"
using JSONLib = nlohmann::json;

class JSONWriter {
public:
	static void saveJson(std::string fileName, const JSONLib& jsonObj) {
		std::ofstream o(fileName);
		o << std::setw(4) << jsonObj << std::endl;
	}
};
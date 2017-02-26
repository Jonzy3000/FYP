#pragma once

#include <iostream>
#include "CalibrationOptions.h"
#include "json.h"
#include <fstream>
#include <memory>
#include "qmessagebox.h"

using JSONLib = nlohmann::json;

class JSONReader {
public:
	static const JSONLib readJson(std::string fileName) {
		std::ifstream file(fileName);
		JSONLib json;
		try {
			file >> json;
		}
		catch (std::exception e) {
			QMessageBox(QMessageBox::Warning, "title", e.what());
		}
		return json;
	}
};

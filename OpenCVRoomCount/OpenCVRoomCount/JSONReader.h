#pragma once
#include <iostream>
#include "ConfigOptions.h"
#include "json.h"
#include <fstream>
#include <memory>

class JSONReader {
public:
	JSONReader(std::string fileName) {
		auto json = readJson(fileName);
		populateConfigOptions(json);
	}

	const JSONLib readJson(std::string fileName) {
		std::ifstream file(fileName);
		JSONLib json;
		file >> json;
		return json;
	}

	void populateConfigOptions(const JSONLib& json) {
		pConfigOptions = std::make_shared<ConfigOptions>(json);
	}

	std::shared_ptr<ConfigOptions> getConfigOptions() {
		return pConfigOptions;
	}
private:
	std::shared_ptr<ConfigOptions> pConfigOptions;
};

#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <filesystem>

using std::string;
namespace fs = std::filesystem;

/* CS6210_TASK: Create your data structure here for storing spec from the config file */
struct MapReduceSpec {
	unsigned int n_workers;
	std::vector<string> worker_ipaddr_ports;
	std::vector<string> input_files;
	string output_dir;
	unsigned int n_output_files;
	unsigned int map_kilobytes;
	string user_id;
};


/* CS6210_TASK: Populate MapReduceSpec data structure with the specification from the config file */
/**
 * Reads the `config_file` and sets the `mr_spec` with the config values.
 * @returns false if an error occurs
 */
inline bool read_mr_spec_from_config_file(const std::string& config_filename, MapReduceSpec& mr_spec) {
	std::ifstream file(config_filename);
	if (!file.is_open()) {
		std::cerr << "Cannot open the config file: " << config_filename << std::endl;
		return false;
	}

	string line;
	while (std::getline(file, line)) {
		try {
			line = trim(line);
			if (line.length() == 0) {
				continue;
			}
			if (line[0] == ';' || line[0] == '#') { // comment
				continue;
			}
			string key; string value;
			split(line, "=", &key, &value);
			key = trim(key); value = trim(value);
			
			// determine key
			if (key == "n_workers") {
				mr_spec.n_workers = std::stoi(value);
			} else if (key == "worker_ipaddr_ports") {
				mr_spec.worker_ipaddr_ports = comma_split(value);
			} else if (key == "input_files") {
				mr_spec.input_files = comma_split(value);
			} else if (key == "output_dir") {
				mr_spec.output_dir = value;
			} else if (key == "n_output_files") {
				mr_spec.n_output_files = std::stoi(value);
			} else if (key == "map_kilobytes") {
				mr_spec.map_kilobytes = std::stoi(value);
			} else if (key == "user_id") {
				mr_spec.user_id = value;
			} else {
				std::cerr << "WARNING: " << config_filename << " contains unrecognized key '" << key << "'" << std::endl;
			}
		} catch (const std::exception& e) {
			std::cerr << "WARNING: " << config_filename << ": Failed to parse " << line << " with error: " << e.what() << ". Skipping..." << std::endl;
		} catch (...) {
			std::cerr << "WARNING: " << config_filename << ": Failed to parse " << line << ". Skipping..." << std::endl;
		}
	}
	return true;
}


/* CS6210_TASK: validate the specification read from the config file */
/** Check that required values are defined and valid.
 * @returns false if mr_spec config is invalid
 */
inline bool validate_mr_spec(const MapReduceSpec& mr_spec) {
	bool valid = true; // allows printing errors all at once

	// not testing if workers are reachable
	bool valid_worker = mr_spec.n_workers > 0 && mr_spec.worker_ipaddr_ports.size() == mr_spec.n_workers;
	if (!valid_worker) {
		std::cerr << "Invalid n_workers and or worker_ipaddr_ports size\n";
	}
	valid &= valid_worker;

	for (auto file : mr_spec.input_files) {
		bool exists = fs::exists(file);
		if (!exists) {
			std::cerr << "File " << file << " does not exist\n";
		}
		valid &= exists;
	}

	if (mr_spec.n_output_files <= 0) {
		std::cerr << "Invalid value for n_output_files\n";
		valid = false;
	}

	if (mr_spec.map_kilobytes <= 0) {
		std::cerr << "Invalid value for map_kilobytes\n";
		valid = false;
	}

	if (mr_spec.user_id.empty()) {
		std::cerr << "user_id is empty\n";
		valid = false;
	}

	return valid;
}

// helpers
/** removes whitespace from start and end */
static string trim(const string s) {
	const string whitespace = " \t\n\r\f\v";
	size_t start = s.find_first_not_of(whitespace);
	if (start == string::npos) {
		return "";
	}

	size_t end = s.find_last_not_of(whitespace);
	return s.substr(start, (end - start + 1));
}

/** splits the input string on the first sub string and sets segment to the first substring 
 * and remainder to the rest of the string.
 * @returns false when sub is not found in input
 * */
static bool split(const string& input, const string& sub, string* segment, string* remainder) {
	size_t i = input.find(sub);
	if (i == string::npos) {
		return false;
	}
	*segment = input.substr(0, i);
	*remainder = input.substr(i+sub.length());
	return true;
}

/** Splits a string with comma separated into a vector */
static std::vector<string> comma_split(const string& input) {
	std::vector<string> values;
	string head;
	string remainder = input;
	while (split(remainder, ",", &head, &remainder)) {
		values.push_back(head);
	}
	values.push_back(remainder);
	return values;
}

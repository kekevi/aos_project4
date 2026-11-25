#pragma once

#include <vector>
#include <string>
#include "mapreduce_spec.h"

using std::string;
namespace fs = std::filesystem;

struct FileSlice {
     string path; // absolute path to a file
     size_t offset; // # bytes from beginning of file to read from
     size_t size; // max
};

/* CS6210_TASK: Create your own data structure here, where you can hold information about file splits,
     that your master would use for its own bookkeeping and to convey the tasks to the workers for mapping */
struct FileShard {
     std::vector<FileSlice> slices;
};


/* CS6210_TASK: Create fileshards from the list of input files, map_kilobytes etc. using mr_spec you populated  */ 
inline bool shard_files(const MapReduceSpec& mr_spec, std::vector<FileShard>& fileShards) {
     /* tasks:
     1. essentially combine all of the input files into one long file
     2. start offsetting from the singular file, dividing it into subfiles every map_kilobytes size
     3. create the files in the <output>/tmp dir (or tmp?)
     */

     auto& input_files = mr_spec.input_files;
     auto& output_dir = mr_spec.output_dir;
     int map_kilobytes = mr_spec.map_kilobytes;

     for (auto file : input_files) {
          try {
               fileShards.push_back();
          } catch (...) {
               std::cerr << "Failed to shard file " << file;
               return false;
          }
     }

	return true;
}

/**
 * Opens the file and returns the bytes offset of the first newline before 
 * (start_offset + bytes) into the file. 
 */
size_t find_newline_before(size_t bytes, const string& file, size_t start_offset) {
     const size_t file_size = fs::file_size(file);
     if (start_offset > file_size) {
          return file_size;
     }

     
}
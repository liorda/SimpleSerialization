#pragma once

#include <fstream>
#include <vector>
#include <memory>

#include "Types.h" // needed only for Base (specifically its name member) - could be refactored into ISerializable

struct OutArchive
{
	OutArchive(const char* sFileName);
	~OutArchive();
	void write(const std::vector<std::shared_ptr<Base>>& input);
	template <typename T>
	void write_member(const char* name, const T& t)
	{
		stream << name << " : " << t << "\n";
	}
private:
	std::fstream stream;
};

struct InArchive
{
	InArchive(const char* sFileName);
	~InArchive();
	void read(std::vector<std::shared_ptr<Base>>& output);
	template <typename T>
	void read_member(const char* name, T& t)
	{
		// TODO currently we rely on the stream pointer and read the members
		// in an orderly fashion, but since we pass the member name here as
		// well, we could also implement a full read, and then select name
		// from the table
		std::string line, sep;
		stream >> line >> sep >> t;
		if (name != line)
			throw std::runtime_error("member name mismatch!");
	}
private:
	std::fstream stream;
};

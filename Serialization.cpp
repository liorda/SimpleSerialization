#include "Serialization.h"

constexpr static const char* magic = "Archive version 1";

OutArchive::OutArchive(const char* sFileName) : stream(sFileName, std::fstream::out)
{
	if (!stream.is_open())
		throw std::runtime_error(std::string("could not open output archive ") + sFileName);
}

OutArchive::~OutArchive()
{
}

void OutArchive::write(const std::vector<std::shared_ptr<Base>>& input)
{
	stream << magic << "\n\n";
	for (auto obj : input)
	{
		stream << obj->name << "\n";
		obj->write(*this);
		stream << "\n";
	}
}

InArchive::InArchive(const char* sFileName) : stream(sFileName, std::fstream::in)
{
	if (!stream.is_open())
		throw std::runtime_error(std::string("could not open input archive ") + sFileName);
}

InArchive::~InArchive()
{
}

void InArchive::read(std::vector<std::shared_ptr<Base>>& output)
{
	std::string line;
	std::getline(stream, line);
	if (line != magic)
		throw std::runtime_error("input archive signature mismatch!");
	std::getline(stream, line); // crunch separator line
	while (std::getline(stream, line))
	{
		if (line.empty())
			continue;
		Base* newObj = g_TypesAllocators[line]();
		newObj->read(*this);
		output.push_back(std::shared_ptr<Base>(newObj));
	}
}

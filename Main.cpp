#include <string>
#include <vector>
#include <memory>
#include <fstream>

#include "Types.h"
#include "Serialization.h"

int main(int argc, char* argv[])
{
	std::vector<std::shared_ptr<Base>> objects;
	objects.push_back(std::make_shared<Point>(1.0f, 2.0f));
	objects.push_back(std::make_shared<Point>(50.0f, 12.0f));
	objects.push_back(std::make_shared<Circle>(0.0f, 0.0f, 10));

	// serialize
	{
		OutArchive write_archive("out.dat");
		write_archive.write(objects);
	}
	
	std::vector<std::shared_ptr<Base>> loaded_objects;
	// deserialize
	{
		InArchive read_archive("out.dat");
		read_archive.read(loaded_objects);
	}

	return 0;
}

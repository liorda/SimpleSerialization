#include "Types.h"
#include "Serialization.h"
#include <functional>

std::map<std::string, std::function<Base*()>> g_TypesAllocators =
{
	{ "Base", []() { return new Base("Base"); } },
	{ "Point", []() { return new Point(0.0f, 0.0f); } },
	{ "Circle", []() { return new Circle(0.0f, 0.0f, 0); } }
};

Base::Base(const char* sName) : name(sName)
{
}

void Base::write(OutArchive& archive)
{
}

void Base::read(InArchive& archive)
{
}

Point::Point(float x_, float y_) : Base("Point"), x(x_), y(y_)
{
}

Point::Point(float x_, float y_, const char* sName) : Base(sName), x(x_), y(y_)
{
}

void Point::write(OutArchive& archive)
{
	__super::write(archive);
	archive.write_member("x", x);
	archive.write_member("y", x);
}

void Point::read(InArchive& archive)
{
	__super::read(archive);
	archive.read_member("x", x);
	archive.read_member("y", y);
}

Circle::Circle(float x_, float y_, int r_) : Point(x_, y_, "Circle"), r(r_)
{
}

void Circle::write(OutArchive& archive)
{
	__super::write(archive);
	archive.write_member("r", r);
}

void Circle::read(InArchive& archive)
{
	__super::read(archive);
	archive.read_member("r", r);
}

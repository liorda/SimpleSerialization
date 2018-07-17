#pragma once

#include <string>
#include <map>
#include <functional>

struct InArchive;
struct OutArchive;

class Base;
extern std::map<std::string, std::function<Base*()>> g_TypesAllocators;

class Base
{
public:
	Base(const char* sName);

protected:
	std::string name;

	// ******** serialization ********
protected:
	virtual void write(OutArchive& archive);
	virtual void read(InArchive& archive);
	friend struct InArchive;
	friend struct OutArchive;
	// ******** serialization ********
};

class Point : public Base
{
public:
	Point(float x_, float y_);
	Point(float x_, float y_, const char* sName);
protected:
	float x;
	float y;

	// ******** serialization ********
protected:
	virtual void write(OutArchive& archive) override;
	virtual void read(InArchive& archive) override;
	friend struct InArchive;
	friend struct OutArchive;
	// ******** serialization ********
};

class Circle : public Point
{
public:
	Circle(float x_, float y_, int r_);
private:
	int r;

	// ******** serialization ********
protected:
	virtual void write(OutArchive& archive) override;
	virtual void read(InArchive& archive) override;
	friend struct InArchive;
	friend struct OutArchive;
	// ******** serialization ********
};

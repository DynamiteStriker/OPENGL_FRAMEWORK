#include "CBaseObject.h"

CBaseObject::CBaseObject() :
	position(0,0,0),
	scale(1,1,1),
	rotation(0,0,0),
	name("no name has been set"),
	parentObj(nullptr),
	objectMesh(nullptr)
{

	//print out object has been created in the console
	auto Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout << this;
	SetConsoleTextAttribute(Handle, 10);
	std::cout << " Created" << std::endl;
	SetConsoleTextAttribute(Handle, 7);

}

CBaseObject::CBaseObject(std::string n) :
	position(0, 0, 0),
	scale(1, 1, 1),
	rotation(0, 0, 0),
	name(n),
	parentObj(nullptr),
	objectMesh(nullptr)
{
	//print out object has been created in the console
	auto Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout << this;
	SetConsoleTextAttribute(Handle, 10);
	std::cout << " Created" << std::endl;
	SetConsoleTextAttribute(Handle, 7);

}

CBaseObject::CBaseObject(const CBaseObject& obj)
{
	//print out object 
	auto Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout << this;
	SetConsoleTextAttribute(Handle, 10);
	std::cout << " COPIED!" << std::endl;
	SetConsoleTextAttribute(Handle, 7);
}

CBaseObject::~CBaseObject()
{
	//print out object has been created in the console
	auto Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout << this;
	SetConsoleTextAttribute(Handle, 12);
	std::cout << " Deleted" << std::endl;
	SetConsoleTextAttribute(Handle, 7);

}
void CBaseObject::Init()
{
	//print out object has been created in the console
	auto Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout << this;
	SetConsoleTextAttribute(Handle, 14);
	std::cout << " Initialised" << std::endl;
	SetConsoleTextAttribute(Handle, 7);
	
}

void CBaseObject::Update(float dt)
{

	for (CBaseObject* obj : childObj)
	{
		obj->Update(dt);
	}
}

void CBaseObject::Render()
{
	if(objectMesh != nullptr)
		objectMesh->Render();
	
	for (CBaseObject* obj : childObj)
	{
		obj->Render();
	}
}

void CBaseObject::Render(Mesh* mesh)
{

}

void CBaseObject::SetPosition(Vector3f pos)
{
	this->position = pos;
}

void CBaseObject::SetScale(Vector3f scale)
{
	this->scale = scale;
}

void CBaseObject::SetScale(float scale)
{
	this->scale = Vector3f(scale,scale,scale);
}

void CBaseObject::setRotation(Vector3f rot)
{
	this->rotation = rot;
}

Vector3f CBaseObject::GetPosition()
{
	return this->position;
}

Vector3f CBaseObject::GetScale()
{
	return this->scale;
}

float CBaseObject::GetScalef()
{
	return this->scale[0];
}

Vector3f CBaseObject::GetRotation()
{
	return this->rotation;
}

void CBaseObject::SetParentObj(CBaseObject* obj)
{
	this->parentObj = obj;
}

std::ostream& operator<<(std::ostream& os, CBaseObject* obj)
{
	auto Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout << " Object ";
	SetConsoleTextAttribute(Handle, 11);
	std::cout << obj->name;
	SetConsoleTextAttribute(Handle, 7);

	return os;
}

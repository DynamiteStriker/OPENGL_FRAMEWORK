#ifndef _CBASEOBJECT_H
#define _CBASEOBJECT_H

#include <Eigen/Dense>
#include <iostream>
#include <windows.h>
#include <list>
#include "Mesh.h"
using namespace Eigen;
class CBaseObject
{
public:
	CBaseObject();
	CBaseObject(std::string);
	//copy constructor
	CBaseObject(const CBaseObject& obj);
	~CBaseObject();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render();
	virtual void Render(Mesh* mesh);
	void SetPosition(Vector3f pos);
	void SetScale(Vector3f scale);
	void SetScale(float scale);
	void setRotation(Vector3f rot);

	Vector3f GetPosition();
	Vector3f GetScale();
	float	 GetScalef();
	Vector3f GetRotation();

	void SetParentObj(CBaseObject* obj);
	Mesh* objectMesh;
	
	
protected:

	CBaseObject* parentObj;
	std::list<CBaseObject*> childObj;
	
	Vector3f position = Vector3f(0,0,0);
	Vector3f scale = Vector3f(1, 1, 1);
	Vector3f rotation = Vector3f(0, 0, 0);

	std::string name;
	
	friend std::ostream& operator<< (std::ostream&, CBaseObject* obj);
};

#endif

#ifndef _CSceneBase_H
#define _CSceneBase_H

#include "CBaseObject.h"
#include "MeshBuilder.h"

class CSceneBase :
    public CBaseObject
{
	

public:
	CSceneBase();
	CSceneBase(std::string);
	~CSceneBase();

	//Enums for geometry
	enum GEOMETRY_TYPE
	{
		GEO_QUAD,
		NUM_GEOMETRY //THIS ONE IS ALWAYS LAST
	};


public:
	void Init() override;
	void Update(float dt) override;
	void Render() override;
	
	void SetShaderProgram(unsigned int id);

protected:

	CBaseObject* CreateObject(std::string name, GEOMETRY_TYPE type);
	Mesh* meshList[NUM_GEOMETRY];
	unsigned int m_shaderProgramID;

	CBaseObject* testObj;
};

#endif


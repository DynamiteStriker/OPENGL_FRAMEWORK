#include "CSceneBase.h"

CSceneBase::CSceneBase(): CBaseObject()
{
}

CSceneBase::CSceneBase(std::string name): CBaseObject(name)
{
	
}

CSceneBase::~CSceneBase()
{
	for (CBaseObject* obj : childObj)
	{//delete all objects in the scene
		delete obj;
	}
}

void CSceneBase::Init()
{
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("QUAD", Color(1.f, 0.f, 0.f, 1), 1.f);
	testObj = CreateObject("testQuad", GEO_QUAD);

	CBaseObject::Init();
}

void CSceneBase::Update(float dt)
{
	CBaseObject::Update(dt);
}

void CSceneBase::Render()
{
	CBaseObject::Render();
}

void CSceneBase::SetShaderProgram(unsigned int id)
{
	m_shaderProgramID = id;
}

CBaseObject* CSceneBase::CreateObject(std::string name, GEOMETRY_TYPE type)
{

	CBaseObject* obj;
	obj = new CBaseObject(name);
	obj->objectMesh = meshList[type];

	obj->SetParentObj(this);
	this->childObj.push_back(obj);

	obj->Init();

	return obj;
}

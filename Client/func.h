#pragma once

class CObject;

void createObject(CObject* _pObj, GROUP_TYPE _eGroup);
void deleteObject(CObject* _pObj);
void changeScene(SCENE_TYPE _eNext);

template<typename T>
void safeDeleteVec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
		{
			delete _vec[i];
		}
	}
	_vec.clear();
}
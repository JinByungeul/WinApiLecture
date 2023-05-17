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

template<typename T1, typename T2>
void safeDeleteMap(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin();

	for (; iter != _map.end(); ++iter)
	{
		if (nullptr != iter->second)
		{
			delete iter->second;
		}
	}
	_map.clear();
}
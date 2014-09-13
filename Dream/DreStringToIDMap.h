/////////////////////////////
// date: 2014/9/9 13:09
// author: zoulei
//////////////////////////////

#ifndef __DRESTRINGTOID_H__
#define __DRESTRINGTOID_H__

#include "DreContainer.h"
#include "DreException.h"

namespace dream
{
	template<class T>
	class StringToIDMap
	{
	public:
		/// 
		void Insert(string name, T id)
		{
#if DREAM_DEBUG
			for (auto ite = mSTIMap.begin(); ite != mSTIMap.end(); ++ ite)
			{
				DreAssert(ite->second != id, "");
			}
#endif
			mSTIMap.insert(make_pair<string, T>(std::move(name), std::move(id)));
		}

		void Remove(string name)
		{
			STIMapIte ite = mSTIMap.find(name);
			if (ite != mSTIMap.end()){
				mSTIMap.erase(ite);
			}
		}

		T StringToID(string name) {
			STIMapIte ite = mSTIMap.find(name);
			DreAssert(ite != mSTIMap.end(), "找不到相应的 string - id 映射");

			return ite->second;
		}

		string IDToString(T id) {
			for (auto ite = mSTIMap.begin(); ite != mSTIMap.end(); ++ite)
			{
				if (ite->second == id)
				{
					return ite->first;
				}
			}

			DreAssert(false, "找不到相应的 string - id 映射");
		}

	private:
		typedef map<string, T>					STIMap;
		typedef STIMap::iterator				STIMapIte;

		STIMap									mSTIMap;
	};

}

#endif	// end of __DRESTRINGTOID_H__
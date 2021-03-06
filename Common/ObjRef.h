#pragma once


#include <NovelCVLib\Common\debug.h>
#include <NovelCVLib\Common\Object.h>



namespace Ncpp
{
	
	template<class T>
	class ObjRef : public ObjectFriend
	{
	public:
		ObjRef()
		{
			m_pObj = nullptr;
		}

		ObjRef(T * a_pObj)
		{
			m_pObj = a_pObj;
			ObjRef<T>::AddObjectRef(m_pObj);
		}

		ObjRef(const ObjRef & a_objRef)
		{
			m_pObj = a_objRef.m_pObj;
			ObjRef<T>::AddObjectRef(m_pObj);
		}

		~ObjRef()
		{
			ObjRef<T>::ReleaseObject(m_pObj);
		}

		void operator = (const ObjRef<T> & a_objRef)
		{
			*this = a_objRef.m_pObj;
		}

		void operator = (T * a_pObj)
		{
			ObjRef<T>::AddObjectRef(a_pObj);
			ObjRef<T>::ReleaseObject(m_pObj);
			m_pObj = a_pObj;
		}

		T * operator -> (void)
		{
			return m_pObj;
		}

		operator T * (void)
		{
			return m_pObj;
		}

		T * AsPtr()
		{
			return m_pObj;
		}

	protected:

		static void AddObjectRef(T * a_pObj)
		{
			if (nullptr != a_pObj)
			{
				ObjectFriend::AddObjectRef(a_pObj);
			}
		}

		static void ReleaseObject(T * a_pObj)
		{
			if (nullptr != a_pObj)
			{
				ObjectFriend::ReleaseObject(a_pObj);

				if (0 == ObjectFriend::GetObjectRefCount(a_pObj))
				{
					KillObj<T>(a_pObj);
				}
			}
		}

	protected:
		T * m_pObj;
	};

}

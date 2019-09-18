// Copyright (c) 2013-2019 7Mersenne All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

namespace Septem
{

	/**
	 * Singleton Template
	 * first init when user first call T::Get()
	 * The private pointer cannot be deleted in main() of program
	 * Get() is Thread-Safe
	 * Inherit sample:
	 * class TClassname : public TSingleton<TClassname> {xxx};
	 * get instance : TClassname::Get();
	 */
	template<typename T>
	//class SEPTEMCORE_API TSingleton :£º SEPTEMCORE_API cannot use in template
	class TSingleton
	{
	public:
		// thread safe; singleton will init when first call get()
		static T* Get();
		// thread safe; singleton will init when first call getRef()
		static T& GetRef();

		// danger call, but fast
		static T* Singleton();
		// danger call, but fast
		static T& SingletonRef();

	protected:
		static T* pSingleton;
		static FCriticalSection mCriticalSection;

	private:
		TSingleton()
		{
			check(nullptr == pSingleton && "Singleton can't create 2 object!");
			pSingleton = static_cast<T*>(this);
		}
	public:
		virtual ~TSingleton()
		{
			pSingleton = nullptr;
		}
	};

	template<typename T>
	inline T * TSingleton<T>::Get()
	{
		if (nullptr == pSingleton) {
			FScopeLock lockSingleton(&mCriticalSection);
			pSingleton = new T();
		}

		return pSingleton;
	}

	template<typename T>
	inline T & TSingleton<T>::GetRef()
	{
		if (nullptr == pSingleton) {
			FScopeLock lockSingleton(&mCriticalSection);
			pSingleton = new T();
		}

		return *pSingleton;
	}

	template<typename T>
	inline T * TSingleton<T>::Singleton()
	{
		return pSingleton;
	}

	template<typename T>
	inline T & TSingleton<T>::SingletonRef()
	{
		check(pSingleton);
		return *pSingleton;
	}

	//-----------------------------------------------------------------------------
	// static values
	//-----------------------------------------------------------------------------

	template<typename T>
	T* TSingleton<T>::pSingleton = nullptr;

	template<typename T>
	FCriticalSection TSingleton<T>::mCriticalSection;
}
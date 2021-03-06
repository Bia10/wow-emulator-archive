// (c) AbyssX Group
#if !defined(SINGLETON_H)
#define SINGLETON_H

//! Scott Bilas' Singleton implementation, with proper casting mod.
template <class T> class Singleton
{
	public:
		//! Constructor: Sets the static pointer.
		Singleton()
		{
			msSingleton = static_cast<T *>(this);
		}
		//! Destructor: Sets the static pointer to NULL, just in case.
		~Singleton()
		{
			msSingleton = 0x00;
		}
		//! GetSingleton(): Returns a reference of the class.
		static T &GetSingleton(void)
		{
			return *msSingleton;
		}
		//! GetSingletonPtr(): Returns a pointer to the class.
		static T *GetSingletonPtr(void)
		{
			return msSingleton;
		}

	private:
		//! msSingleton: The static variable which holds the pointer to the singleton.
		static T *msSingleton;
};

//! Define the following for any class that inherits from Singleton.
//template <class T> T *Singleton<T>::msSingleton = 0;

#endif

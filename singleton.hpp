/*************************************************************************************************
Copyright 2014 Nicolas AUBRY

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*************************************************************************************************/

#ifndef				__SINGLETON_HPP__
#define				__SINGLETON_HPP__

template <typename T>
class				Singleton
{		
private :
	static T*		_instance;

private:
	Singleton(const Singleton&);
	Singleton&		operator=(const Singleton&);

protected :
	Singleton() {}
	~Singleton() {}

public :
	static T&		getInstance()
	{
		if (!_instance)
			_instance = new T;
		return *_instance;
	}

	static void		destroy()
	{
		if (_instance)
			delete _instance;
		_instance = NULL;
	}
};

template <typename T> 
T*					Singleton<T>::_instance = NULL;

#endif
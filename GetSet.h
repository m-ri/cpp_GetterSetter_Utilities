#pragma once


#include<functional>

#include<iostream>


using namespace std;

template<typename T>
class GetSet {
private:
	T item;
	//bool _useDefaultGetSet = false;
	std::function<T(T &)> _getterFunction = nullptr;// [](T& currentItem)-> T& {return currentItem; };
	std::function<void(T &, T const &)> _setterFunction = nullptr;// [](T& currentItem, T newValue) {curr = newValue; };
	
	//COMMENT line below, if you want to have copy constructor
	GetSet(const GetSet<T>& src) = delete;
	
public:
	//DE-COMMENT lines below, if you want to have copy constructor and assignement
	/*GetSet(const GetSet<T>& src) {
		*this = src.factory_copyValueGetterSetter();
	}
	GetSet<T>&   operator=(GetSet<T>  & src) {
		if (this != &src) {
			try {
			//	if(this->item!=nullptr) delete this->item
			}
			catch (...) {}
			*this = src.factory_copyValueGetterSetter();
		}
		return *this;
	}
	*/

	GetSet() :item(T()) {}
	GetSet(T tt) :item(tt) {}
	GetSet(T *tt) :item(*tt){}
	GetSet(GetSet<T>&& src) :
		item(std::move(src.item)), 
		_getterFunction(std::move(src._getterFunction)),_setterFunction(std::move(src._setterFunction)) {}
	void setGetter(std::function<T (T &)> getterFunction) { _getterFunction = getterFunction; }
	void setSetter(std::function<void(T &, T const &)> setterFunction) { _setterFunction = setterFunction; }

	//operator T&() {
	operator T() {
		if (_getterFunction != nullptr ) {
			return _getterFunction(item);
		}
		else {
			return item;
		}
	}
	GetSet<T>&   operator=(const T  & new_value) {
		if (_setterFunction != nullptr ) {
			_setterFunction(item, new_value);
		}else {
			this->item = new_value;
		}
		return *this;
	}
	GetSet<T>&   operator=(GetSet<T>  && src) {		
		*this = std::move(src);		
		return nullptr;
	}
	
	GetSet<T> factory_copyValue(){
		GetSet<T> retObj;
		retObj.item = T(item);
		return retObj;
	}
	GetSet<T> factory_copyValueGetterSetter(){
		GetSet<T> retObj;
		retObj.item = T(this->item);
		retObj._getterFunction = this->_getterFunction;
		retObj._setterFunction = this->_setterFunction;
		return retObj;
	}
/*	GetSet<T>&   GetSet<T>::operator=(T  && new_value) {
		if (_setterFunction != nullptr) {
			_setterFunction(item, std::move(new_value));
		}
		else {
			this->item =std::move(new_value);
		}
		return *this;
	}*/


	friend std::ostream& operator<< (std::ostream& stream, GetSet<T>& getSet) {
		//T &aus = getSet;//recall the getter
		T aus = getSet;//recall the getter
		return stream << aus;
	}
	friend std::istream& operator >> (std::istream& stream, GetSet<T>& getSet) {
		T aus;
		stream >> aus;
		getSet = std::move(aus);
		return stream;
	}


};

//ccAlgorithms2
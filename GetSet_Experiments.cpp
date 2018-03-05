#pragma once

#include "GetSet.h"

#include<string>
#include<iostream>

using namespace std;

//*
int main() {
	(new GetSet_Experiments)->test();

	std::cout << "Press [ENTER} to exit" << std::endl;
	string ret;
	std::cin >> ret;
	return 0;
}
//*/

class GetSet_Experiments {



public:
	void test() {
		
		testInteger();
		testString();
		testMove();
		testCopy();
		

	}
	void testInteger() {
		std::cout << "-----------------" << std::endl;
		std::cout << "START testInteger" << std::endl;

		GetSet<int> t(3);
		cout << t << endl;//expected 3
		t = 5;
		cout << t << endl;//expected 5
		t.setGetter([](int& currentItem)-> int {return currentItem * 10; });
		cout << t << endl;//expected 5*10=50

		t.setSetter([](int& currentItem, int newValue) {currentItem = newValue * 3; });
		t = 6;
		cout << t << endl;//expected 6*10*3=180
		t.setGetter(nullptr);
		cout << t << endl;//expected 6*3=18

		std::cout << "END testInteger" << std::endl << std::endl;
	}
	void testString() {
		std::cout << "-----------------" << std::endl;
		std::cout << "START testString" << std::endl;



		GetSet<string> t("aaa");
		cout << t << endl;//expected 'aaa'

		t.setSetter([](auto& currItem, auto newItem) {currItem = "(Setter) " + newItem; });
		t.setGetter([](auto& currItem) ->auto {return currItem + " (Getter)"; });

		t = "bbb";
		cout << t << endl;//expected '(Setter) bbb (Getter)'
		cout << ((string)t) << endl;//expected '(Setter) bbb (Getter)'

		std::cout << "END testString" << std::endl << std::endl;
	}
	void testMove() {
		std::cout << "-----------------" << std::endl;
		std::cout << "START testMove" << std::endl;

		GetSet<int> t(3);
		t.setGetter([](int& currentItem)-> int {return currentItem * 10; });
		cout << t << endl;//expected 30

		GetSet<int> t2 = std::move(t);
		cout << t2 << endl;//expected 30

		std::cout << "END testMove" << std::endl << std::endl;
	}
	void testCopy() {
		std::cout << "-----------------" << std::endl;
		std::cout << "START testCopy" << std::endl;

		GetSet<int> t(3);
		t.setGetter([](int& currentItem)-> int {return currentItem * 10; });
		cout << t << endl;//expected 30

						  // GetSet<int> t2 = std::move(t); : this is NOT allowed
		GetSet<int> t2 = (int)t;//I'm only interested about value(returned through getter)
		cout << t2 << endl;//expected 3*10

		GetSet<int> t3 = t.factory_copyValue();//I'm only interested about value
		cout << t3 << endl;//expected 3

		GetSet<int> t4 = t.factory_copyValueGetterSetter();//I'm  interested about value and getter/setter
		cout << t4 << endl;//expected 30

		std::cout << "END testCopy" << std::endl << std::endl;
	}
	

	/*class TempClass {
	public:
	int a;
	};
	void testClass() {
	std::cout << "-----------------" << std::endl;
	std::cout << "START testString" << std::endl;

	TempClass *a = new TempClass();
	a->a = 5;

	GetSet<TempClass> gs(*a);
	TempClass &b = gs;
	b.a = 6;

	TempClass c = gs;
	cout << c.a << endl;

	cout << ((TempClass)gs).a;
	}*/
};
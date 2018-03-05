# cpp_GetterSetter_Utilities
A class which help you to manage getter/setter in cpp projects. You can trasparently add/delete these modifiers on existings variables, without big changes in the code

GetSet.h contains the library, while GetSet_Experiments.cpp provides some examples (ranging from trivial examples with integers and strings, to advanced usage with copy and move constructors).

Basic example
```
#include "GetSet.h"

GetSet<int> positiveVariable(3);
t.setGetter([](int& currentItem)-> int {return max(currentItem ,0); });
positiveVariable.setSetter([](int& currentItem, int newValue) {
        if(newValue>=0)currentItem=newValue;
        else currentItem=currentItem;/* throw std::exception("Added negative value");*/ ; 
    });
    
t=5;
t=-10;
cout<<t;//output: 5
```


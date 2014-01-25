#pragma once

template <typename ModelT> class IModelFactory {
public:
	virtual ~IModelFactory() { }
	
	virtual ModelT* getModel() = 0;
};
// Model.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "ModelFactory.h"

logcc::model::IModelFactory* create_model_factory() {
	return ModelFactory::GetInstance();
}

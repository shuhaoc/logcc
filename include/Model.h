#pragma once

#include "IModelFactory.h"

logcc::model::IModelFactory* create_model_factory();

typedef logcc::model::IModelFactory* (*create_model_factory_t)();
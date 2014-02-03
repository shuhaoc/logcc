#pragma once

template <typename ModelT> class IModelAware {
public:
	IModelAware() : model(nullptr) { }

	virtual ~IModelAware() { }

	void setModel(ModelT* model) {
		this->model = model;
	}

	ModelT* getModel() const {
		return model;
	}

private:
	ModelT* model;
};
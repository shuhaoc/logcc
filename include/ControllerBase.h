#pragma once

typedef CDocument BasicViewData;

class ControllerBase {
public:
	const BasicViewData* getViewData() const { return viewData; }

	void setViewData(const BasicViewData* viewData) { this->viewData = viewData; }

private:
	const BasicViewData* viewData;
};
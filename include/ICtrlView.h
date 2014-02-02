#pragma once

struct ICtrlView {
	virtual tstring getCriteria() = 0;
	tstring criteria;
};
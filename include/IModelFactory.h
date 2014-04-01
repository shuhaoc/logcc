#pragma once

class ILogQuery;
class IPatternService;

namespace logcc {
namespace model {

class IModelFactory {
public:
	virtual ~IModelFactory() { }

	virtual ILogQuery* CreateLogQuery() const = 0;

	virtual IPatternService* CreatePatternService() const = 0;
};

} // namespace logcc
} // namespace model

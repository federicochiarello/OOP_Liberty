#ifndef GLOBALENUMS_H
#define GLOBALENUMS_H

#include <string>
#include <map>

enum TaskType {
	TASK = 1,
	TASK_CONTAINER,
	TASK_PRIORITY,
	TASK_PRIORITY_CONTAINER
};

static std::map<std::string, TaskType> task_type_map =
{
	{"TASK", TASK},
	{"TASK_CONTAINER", TASK_CONTAINER},
	{"TASK_PRIORITY", TASK_PRIORITY},
	{"TASK_PRIORITY_CONTAINER", TASK_PRIORITY_CONTAINER}
};

#endif // GLOBALENUMS_H

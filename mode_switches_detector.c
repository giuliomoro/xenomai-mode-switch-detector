#include <stdio.h>
#include <task.h>
#include <error.h>

void taskLoop(void* arg)
{
	while(1)
	{
		rt_printf("Run\n");
		rt_task_sleep(1000000000);
	}
}

int main(){
	const char* task_name = "test-task";
	RT_TASK task;
	int ret = rt_task_bind(&task, task_name, TM_NONBLOCK);
	if(ret != 0)
	{
		fprintf(stderr, "%s(%d). Task '%s' not running\n", strerror(-ret), ret, task_name);
		RT_TASK task;
		printf("Creating task\n");
		rt_task_create(&task, task_name, 0, 40, T_JOINABLE);
		rt_task_start(&task, &taskLoop, NULL);
		printf("Starting task\n");

		while(rt_task_bind(&task, task_name, TM_NONBLOCK) == 0)
		{
			static int count = 0;
			if(count++ % 10000 == 0)
				rt_printf("task alive\n");
			rt_task_sleep(100000);
		}
		return ret;
	}
	RT_TASK_INFO info;
	rt_task_inquire(&task, &info);
	int msw = info.stat.msw;
	printf("modeswitches: %d\n", msw);
	return 0;
}

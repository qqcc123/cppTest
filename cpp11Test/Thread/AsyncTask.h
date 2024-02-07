#pragma once

class AsyncTask
{
public:
	AsyncTask();
	
	~AsyncTask() = default;

	void testAsyncTask();

	void task_lambda();

	void task_bind();

	void task_thread();
};


//@author Liu Yukang
#pragma once
#include <functional>
#include "context.h"
#include "utils.h"

namespace tinyco
{

	enum coStatus
	{
		READY = 0,
		RUNNING,
		WAITING,
		DEAD
	};

	class Schedule;

	class Coroutine
	{
	public:
		Coroutine(Schedule*, std::function<void()>&&);
		Coroutine(Schedule*, std::function<void()>&);
		~Coroutine();

		DISALLOW_COPY_MOVE_AND_ASSIGN(Coroutine);

		//�ָ����е�ǰЭ��
		void resume(bool isFirstCo = false);

		//��ͣ���е�ǰЭ��
		void yield();

		//���и�Э�̵ĺ���
		void startFunc() { coFunc_(); };

		//��ȡ��Э�̵�������
		Context* getCtx() { return &ctx_; }

	private:

		std::function<void()> coFunc_;

		Schedule* pMySchedule_;

		int status_;

		Context ctx_;

	};

}
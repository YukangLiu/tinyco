//@author Liu Yukang
#pragma once
#include <queue>
#include <mutex>
#include "context.h"

#include "coroutine.h"

//����һ����Э��
#define co_go(func) netco::Schedule::getSchedule()->goNewCo(func)

//��ͣ��ǰЭ��
#define co_yield() netco::Schedule::getSchedule()->resumeAnotherCoroutine()

namespace netco
{

	class Schedule
	{
	public:
		DISALLOW_COPY_MOVE_AND_ASSIGN(Schedule);

		//��ȡ��ǰЭ�̵���
		static Schedule* getSchedule();

		//����һ����Э�̣���Э�̵ĺ�����func
		void goNewCo(std::function<void()>&& func);
		void goNewCo(std::function<void()>& func);

		//�ָ�������һ��Э��
		void resumeAnotherCoroutine();

		//�����ǰ�������е�Э��
		void killCurCo();

		//��ȡ��һ�����е�Э��
		Coroutine* getLastCoroutine() { return pLastCoroutine_; };

		//��ȡ��ǰ�������е�Э��
		Coroutine* getCurRunningCo() { return pCurCoroutine_; };

		Context* getMainCtx() { return &mainCtx_; }

	private:
		Schedule();
		~Schedule();

		//�ָ�����ָ��Э��
		void resume(Coroutine*);

		static Schedule* scheduler_;

		static std::mutex initMutex_;

		bool isFirstGo_;

		//FIFO queue
		std::queue<Coroutine*> coroutines_;

		Coroutine* pLastCoroutine_;

		Coroutine* pCurCoroutine_;

		Context mainCtx_;

	};

}
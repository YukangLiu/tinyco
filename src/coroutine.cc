//@author Liu Yukang
#include "coroutine.h"
#include "schedule.h"
#include "parameter.h"

using namespace tinyco;

static void coWrapFunc(Schedule* sche)
{
	sche->getCurRunningCo()->startFunc();
	sche->killCurCo();
	sche->resumeAnotherCoroutine();
}

Coroutine::Coroutine(Schedule* pMySchedule, std::function<void()>&& func)
	: coFunc_(std::move(func)), pMySchedule_(pMySchedule), status_(DEAD)//, ctx_(stack_, parameter::coroutineStackSize)
{
	status_ = READY;
}

Coroutine::Coroutine(Schedule* pMySchedule, std::function<void()>& func)
	: coFunc_(func), pMySchedule_(pMySchedule), status_(DEAD)//, ctx_(stack_, parameter::coroutineStackSize)
{
	status_ = READY;
}

Coroutine::~Coroutine()
{
}

void Coroutine::resume(bool isFirstCo)
{
	Coroutine* pLastCo = pMySchedule_->getLastCoroutine();
	switch (status_)
	{
	case READY:
        status_ = RUNNING;
		ctx_.makeContext((void (*)(void)) coWrapFunc, pMySchedule_);
		if (isFirstCo)
		{
			ctx_.swapToMe(pMySchedule_->getMainCtx());
		}
		else
		{
			ctx_.swapToMe(pLastCo ? pLastCo->getCtx() : nullptr);
		}
		break;

	case WAITING:
		status_ = RUNNING;
		ctx_.swapToMe(pLastCo ? pLastCo->getCtx() : nullptr);
		break;

	default:

		break;
	}
}

void Coroutine::yield()
{
	status_ = WAITING;
}
//
//  animation_function.cpp
//  Engine
//
//  Created by krzysp on 01/01/2022.
//

#include "value_animator.hpp"
#include "scripting_engine.hpp"
#include "engine.hpp"
#include "time.hpp"

using namespace engine;

ValueAnimator
    ::ValueAnimator(
        std::unique_ptr<CallableCurveLamba> curve
      , int delay
      , double seconds
      , std::function<void(ValueAnimatorI*)> callabackFunctionStart
      , std::function<void(ValueAnimatorI*, float)> callabackFunctionUpdate
      , std::function<void(ValueAnimatorI*)> callbackFunctionEnd
)
    : ValueAnimatorI(nullptr, delay, seconds, callabackFunctionStart, callabackFunctionUpdate, callbackFunctionEnd)
    ,  MemoryI()
    , m_engineProvider(ENGINE().getProvider())
    , m_time(ENGINE().getTime())
    , m_secondsDelay(delay)
    , m_secondsTotal(seconds)
    , m_secondsStart(-1)
    , m_val(curve->GetMin())
    , m_startFunc(callabackFunctionStart)
    , m_updateFunc(callabackFunctionUpdate)
    , m_endFunc(callbackFunctionEnd)
    , m_isStopped(true)
    , m_context(nullptr)
{
    m_curve = std::move(curve);
}

ValueAnimator::~ValueAnimator()
{
    FreeContext();
    printf("ValueAnimator released\n");
}

void ValueAnimator::FreeContext()
{
    if (m_context != nullptr)
    {
        free(m_context); m_context = nullptr;
    }
}

void ValueAnimator::Start()
{
    if (m_startFunc != nullptr)
    {   m_startFunc(this);
    }
    
    m_secondsStart = m_time.GetFrameStartSec();
    m_isStopped = false;
    ENGINE().getPeriodicUpdatesManager().Add(this);
    this->Keep();
}

void ValueAnimator::Stop()
{
    m_isStopped = true;
    ENGINE().getPeriodicUpdatesManager().Remove(this);

    if (m_animatableFinishL != nullptr)
    {
        m_animatableFinishL(this);
    }

    if (m_endFunc != nullptr)
    {
        m_endFunc(this);
    }
    
    this->Release();
}

float ValueAnimator::GetValue()
{
    return m_val;
}

void ValueAnimator::CallbackExecute()
{
    if (m_updateFunc != nullptr)
    {
        m_updateFunc(this, m_val);
    }
}

void ValueAnimator::ReleaseMem()
{
    if (!m_isStopped) { Stop(); };
    MemoryI::FreeMem();
}

void ValueAnimator::Update()
{
    double diffSeconds = MAX(m_time.GetFrameStartSec() - m_secondsStart - m_secondsDelay, 0);
    double progress = diffSeconds / m_secondsTotal;

    m_val = m_curve->f(progress);
    printf("val = %f\n", m_val);
    CallbackExecute();

    if (diffSeconds >= m_secondsTotal)
    {
        Stop();
    }
}

void ValueAnimator::SetFunctionUpdate(std::function<void(ValueAnimatorI*, float)> f)
{
    m_updateFunc = f;
}

void ValueAnimator::SetFunctionFinish(std::function<void(ValueAnimatorI*)> f)
{
    m_endFunc = f;
}

void ValueAnimator::SetContext(void* context)
{
    FreeContext();
    m_context = context;
}

void *ValueAnimator::GetContext()
{
    return m_context;
}

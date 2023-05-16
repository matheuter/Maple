#ifndef _PROCESSOR_H
#define _PROCESSOR_H

#include "actor.h"
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

class ActorProcessor
{
public:
    ActorProcessor();
    ~ActorProcessor();

public:
    using ActorMap = std::unordered_map<std::string, Actor *>;

    enum StatusType { SUCESS, FAULT, ERROR, DEFAULT };

public:
    template<typename... Args>
    void invoke(const std::string &route, Args... args) noexcept{
        if (m_actorMap->find(route) != m_actorMap->end()) {
            (*m_actorMap)[route]->invoke(std::forward<Args>(args)...);
            m_processorStatus = StatusType::SUCESS;
        } else {
            m_processorStatus = StatusType::FAULT;
        }
    }

    template<typename R, typename... Args>
    R invoke(const std::string &route, Args... args) noexcept{
        if (m_actorMap->find(route) != m_actorMap->end()) {
            m_processorStatus = StatusType::SUCESS;
            return (*m_actorMap)[route]->invoke<R, Args...>(std::forward<Args>(args)...);
        } else {
            m_processorStatus = StatusType::FAULT;
            return NULL;
        }
    }
    void set(const std::string &name, ActorProcessor *processor);
    ActorProcessor *get(const std::string &name) const;

public:
    void registerActor(const std::string &route, Actor *actor);
    void unregisterActor(const std::string &route);

    StatusType processorStatus() const;

private:
    ActorMap *m_actorMap;
    StatusType m_processorStatus;

private:
    ActorProcessor(ActorProcessor &&) = delete;
    ActorProcessor &operator=(const ActorProcessor &) = delete;
};

#endif // EVENTPROCESSOR_H

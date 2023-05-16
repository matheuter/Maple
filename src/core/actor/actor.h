#ifndef _ACTOR_H_
#define _ACTOR_H_

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <tuple>
#include <utility>

template<typename T>
struct function_traits;

template<typename ReturnType, typename... Args>
struct function_traits<ReturnType(Args...)>
{
    enum { value = sizeof...(Args) };
    using tuple_type = std::tuple<std::remove_cv_t<std::remove_reference_t<Args>>...>;

    template<std::size_t N, typename = typename std::enable_if<(N < value)>::type>
    using args = typename std::tuple_element<N, std::tuple<Args...>>;

    using return_type = ReturnType;

    template<std::size_t N>
    struct arguments{
        static_assert(N < value, "[error]:invalid parameter index.");
        using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
    };
};

template<typename ReturnType, typename... Args>
struct function_traits<ReturnType (*)(Args...)> : function_traits<ReturnType(Args...)>
{};

template<typename ReturnType, typename... Args>
struct function_traits<std::function<ReturnType(Args...)>> : function_traits<ReturnType(Args...)>
{};

template<typename ReturnType, typename ClassType, typename... Args>
struct function_traits<ReturnType (ClassType::*)(Args...)> : function_traits<ReturnType(Args...)>
{};

template<typename ReturnType, typename ClassType, typename... Args>
struct function_traits<ReturnType (ClassType::*)(Args...) const>
    : function_traits<ReturnType(Args...)>
{};

template<typename ReturnType, typename ClassType, typename... Args>
struct function_traits<ReturnType (ClassType::*)(Args...) volatile>
    : function_traits<ReturnType(Args...)>
{};

template<typename ReturnType, typename ClassType, typename... Args>
struct function_traits<ReturnType (ClassType::*)(Args...) const volatile>
    : function_traits<ReturnType(Args...)>
{};

template<typename Callable>
struct function_traits : function_traits<decltype(&Callable::operator())>
{};

struct invoker{
    template<typename Function, typename ThisType>
    static inline void apply(const Function &func, ThisType *thisType, void *bl, void *result){
        using tuple_type = typename function_traits<Function>::tuple_type;
        const tuple_type *tp = static_cast<tuple_type *>(bl);
        call(func, thisType, *tp, result);
    }

    template<typename Function, typename ThisType, typename... Args>
    static typename std::enable_if< std::is_void<typename function_traits<Function>::return_type>::value>::type
    call(const Function &f, ThisType *thisType, const std::tuple<Args...> &tp, void *){
        call_helper(f, thisType, std::make_index_sequence<function_traits<Function>::value>{}, tp);
    }

    template<typename Function, typename ThisType, typename... Args>
    static typename std::enable_if<!std::is_void<typename function_traits<Function>::return_type>::value>::type
    call(const Function &f, ThisType *thisType, const std::tuple<Args...> &tp, void *result){
        auto r = call_helper(f, thisType, std::make_index_sequence<function_traits<Function>::value>{}, tp);
        *(decltype(r) *) result = r;
    }

    template<typename Function, typename ThisType, size_t... I, typename... Args>
    static auto call_helper(const Function &f, ThisType *thisType, const std::index_sequence<I...> &h, const std::tuple<Args...> &tup){
        return (thisType->*f)(std::get<I>(tup)...);
    }

    template<typename Function>
    static inline void apply(const Function &func, void *bl, void *result){
        using tuple_type = typename function_traits<Function>::tuple_type;
        const tuple_type *tp = static_cast<tuple_type *>(bl);
        call(func, *tp, result);
    }

    template<typename Function, typename... Args>
    static typename std::enable_if< std::is_void<typename function_traits<Function>::return_type>::value>::type
    call(const Function &f, const std::tuple<Args...> &tp, void *){
        call_helper(f, std::make_index_sequence<function_traits<Function>::value>{}, tp);
    }

    template<typename Function, typename... Args>
    static typename std::enable_if< !std::is_void<typename function_traits<Function>::return_type>::value>::type
    call(const Function &f, const std::tuple<Args...> &tp, void *result){
        auto r = call_helper(f, std::make_index_sequence<function_traits<Function>::value>{}, tp);
        *(decltype(r) *) result = r;
    }

    template<typename Function, size_t... I, typename... Args>
    static auto call_helper(const Function &f, const std::index_sequence<I...> &h, const std::tuple<Args...> &tup){
        return f(std::get<I>(tup)...);
    }
};

class Actor : public std::enable_shared_from_this<Actor>
{
public:
    using Ptr = std::shared_ptr<Actor>;
    using FunctionWapper = std::function<void(void *, void *)>;

public:
    Actor() {}
    ~Actor() {}

    template<typename Function>
    void registerFunction(Function function_any) noexcept{
        m_invokeFunctionWapper = {std::bind(&invoker::apply<Function>, function_any, std::placeholders::_1, std::placeholders::_2)};
    }

    template<typename Function, typename ThisType>
    void registerFunction(Function function, ThisType *p) noexcept{
        m_invokeFunctionWapper = {std::bind(&invoker::apply<Function, ThisType>, function, p, std::placeholders::_1, std::placeholders::_2)};
    }

    template<typename... Args>
    void invoke(Args... args) const noexcept{
        auto args_tuple = std::make_tuple(std::forward<Args>(args)...);
        m_invokeFunctionWapper(&args_tuple, nullptr);
    }

    template<typename R, typename... Args>
    R invoke(Args... args) const noexcept{
        auto args_tuple = std::make_tuple(std::forward<Args>(args)...);
        R returnValue;
        m_invokeFunctionWapper(&args_tuple, &returnValue);
        return returnValue;
    }

private:
    FunctionWapper m_invokeFunctionWapper;
};

#ifdef __MSVC__ && NO_ACTOR_REGISTER_WITH_MACRO

#define REGISTER_FUNCTION(processor, identify, function) \
    do { \
        Actor *actor = new Actor(); \
        actor->registerFunction(##function); \
        processor->registerActor(##identify, actor); \
    } while (0);

#define REGISTER_METHOD_FUNCTION(processor, identify, function, this) \
    do { \
        Actor *actor = new Actor(); \
        actor->registerFunction(##function, ##this); \
        processor->registerActor(STR(identify), actor); \
    } while (0);
#else

template<typename ActorProcessor, typename Function>
inline void REGISTER_FUNCTION(ActorProcessor *processor, const std::string &identify, Function func)
{
    Actor *actor = new Actor();
    actor->registerFunction(func);
    processor->registerActor(identify, actor);
}

template<typename ActorProcessor, typename Function, typename ClassPointerType>
inline void REGISTER_METHOD_FUNCTION(ActorProcessor *processor, const std::string &identify, Function func, ClassPointerType thisPointer)
{
    Actor *actor = new Actor();
    actor->registerFunction(func, thisPointer);
    processor->registerActor(identify, actor);
}
#endif // end of define __MSVC__

#endif // end of

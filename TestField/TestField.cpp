#include <zengine/zengine.hpp>
#include <typeinfo>
#include <typeindex>
#include <type_traits>

class EventBase : public ze::Event
{
public:

	virtual std::string toString() const override
	{
		return "EventBase";
	}
};

class EventDerived : public EventBase
{
public:

	virtual std::string toString() const override
	{
		return "EventDerived";
	}
};

int main()
{
	ze::EventBus bus;
	ze::EventHandler<EventBase> handler([](EventBase& event)
	{
		std::cout << "1" << std::endl;
		event.cancel();
	});

	ze::EventHandler<EventDerived> handler2([](EventDerived& event)
	{
		std::cout << "2" << std::endl;
	});

	bus.pushEvent<EventDerived>();
	bus.subscribe(&handler);
	bus.subscribe(&handler2);
	bus.dispatchEvents();

	return 0;
}

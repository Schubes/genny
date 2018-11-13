#ifndef HEADER_F86B8CA3_F0C0_4973_9FC8_3875A76D7610
#define HEADER_F86B8CA3_F0C0_4973_9FC8_3875A76D7610

#include <gennylib/Actor.hpp>
#include <gennylib/PhaseLoop.hpp>
#include <gennylib/context.hpp>

namespace genny::actor {

/**
 * MultiCollectionQuery is an actor that performs updates across parameterizable number of
 * collections. Updates are performed in a loop using {@code PhaseLoop} and each iteration picks a
 * random collection to update. The actor records the latency of each update, and the total number
 * of documents updated.
 */
class MultiCollectionQuery : public Actor {

public:
    explicit MultiCollectionQuery(ActorContext& context, const unsigned int thread);
    ~MultiCollectionQuery() = default;

    void run() override;

    static ActorVector producer(ActorContext& context);

private:
    struct PhaseConfig;
    std::mt19937_64 _rng;
    metrics::Timer _queryTimer;
    metrics::Counter _documentCount;
    mongocxx::pool::entry _client;
    PhaseLoop<PhaseConfig> _loop;
};

}  // namespace genny::actor

#endif  // HEADER_F86B8CA3_F0C0_4973_9FC8_3875A76D7610

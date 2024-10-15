#pragma once

#include <vector>

#include "../../utils/ILogPathGetter.hpp"
#include "../../utils/Logger.cpp"
#include "../AbstractGenerator.cpp"
#include "../instructions/InstructionHandler.cpp"
#include "IOrderFetcher.cpp"

class FetchHandler : public ILogPathGetter
{
   public:
    FetchHandler() { Logger.SetLogPathGetter(this); }
    ~FetchHandler()
    {
        Logger.SetLogPathGetter(nullptr);
        for (auto fetcher : fetcherList)
        {
            delete fetcher;
        }
    }

    void Fetch(AbstractGenerator* generator)
    {
        if (fetcherDepth >= fetcherList.size())
        {
            Logger.Log("FetchDepth is greater than fetcherList size", Logger::ERROR);
            generator->SetCurrentOrder(Order::Empty());
            return;
        }

        auto queueIterator = fetcherList.begin() + fetcherDepth;
        IOrderFetcher* fetcher = *queueIterator;
        Order order = fetcher->Next();

        if (fetcher->IsEmpty())
        {
            fetcherList.erase(queueIterator);

            if (fetcher != nullptr) delete fetcher;
        }

        generator->SetCurrentOrder(order);
        generator->IncrementPhase();

        return;
    }

    void IncrementFetcherDepth()
    {
        Logger.Log("Incrementing fetcher depth", Logger::DEBUG);
        fetcherDepth++;
    }

    void DecrementFetcherDepth()
    {
        Logger.Log("Decrementing fetcher depth", Logger::DEBUG);
        fetcherDepth--;
    }

    void PutInFront(IOrderFetcher* fetcher)
    {
        if (fetcher->IsEmpty())
        {
            delete fetcher;
            return;
        }

        fetcherList.insert(fetcherList.begin() + fetcherDepth, fetcher);
    }

    bool IsDone() { return fetcherList.empty(); }

    virtual std::string GetLogPath() override
    {
        if (fetcherList.empty()) return "";

        std::string path = fetcherList[0]->GetLastOrderLog();

        for (size_t i = 1; i < fetcherList.size(); i++)
        {
            path += "->" + fetcherList[i]->GetLastOrderLog();
        }

        return path;
    }

   private:
    unsigned int fetcherDepth = 0;
    std::vector<IOrderFetcher*> fetcherList;
};
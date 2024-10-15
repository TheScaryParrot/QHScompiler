#pragma once

#include "../utils/InputFile.cpp"
#include "AbstractGenerator.cpp"
#include "decode/DecodeHandler.cpp"
#include "execute/ExecuteHandler.cpp"
#include "fetch/FetchHandler.cpp"
#include "fetch/InputFileFetcher.cpp"
#include "fetch/OrderQueueFetcher.cpp"

class Generator : public AbstractGenerator
{
   public:
    Generator(InputFile* file) { this->fetchHandler.PutInFront(new InputFileFetcher(file)); }

    AssemblyCode* Generate()
    {
        unsigned int phaseCounter = 0;

        while (!fetchHandler.IsDone() /* && phaseCounter < 100000 */)
        {
            ExecuteCurrentPhase();
            phaseCounter++;
        }

        /*if (phaseCounter >= 100000)
        {
            Logger.Log("Generator reached phase limit of 100000", Logger::ERROR);
            Logger.Log("Final phase was " + std::to_string(GetCurrentPhase()), Logger::ERROR);
        }*/

        return this->assemblyCode;
    }

    virtual void ExecuteCurrentPhase()
    {
        switch (this->GetCurrentPhase())
        {
            case GeneratorPhases::FETCH:
                fetchHandler.Fetch(this);
                break;
            case GeneratorPhases::DECODE:
                decodeHandler.Decode(this);
                break;
            case GeneratorPhases::EXECUTE:
                executeHandler.Execute(this);
                break;
            default:
                Logger.Log("Generator doesn't know what to do with GeneratorPhase at index: " +
                               std::to_string(GetCurrentPhase()) + ". Setting phase to FETCH",
                           Logger.ERROR);
                SetCurrentPhase(GeneratorPhases::FETCH);
                break;
        }
    }

    virtual void IncrementFetchDepth() override { fetchHandler.IncrementFetcherDepth(); }
    virtual void DecrementFetchDepth() override { fetchHandler.DecrementFetcherDepth(); }

    virtual void EnterComment() override { decodeHandler.EnterComment(); }
    virtual void ExitComment() override { decodeHandler.ExitComment(); }
    virtual void IncrementOrderQueueDepth() override { decodeHandler.IncrementOrderQueueDepthCounter(); }
    virtual void DecrementOrderQueueDepth() override { decodeHandler.DecrementOrderQueueDepthCounter(); }
    virtual unsigned int GetOrderQueueDepth() override { return decodeHandler.GetOrderQueueDepth(); }
    virtual bool IsOrderQueueActive() override { return GetOrderQueueDepth() > 0; }

    virtual void PutInFront(Order order) override
    {
        std::shared_ptr<OrderQueue> orderQueue = std::make_shared<OrderQueue>(order);
        fetchHandler.PutInFront(new OrderQueueFetcher(orderQueue));
    }
    virtual void PutInFront(std::shared_ptr<OrderQueue> orderQueue) override
    {
        fetchHandler.PutInFront(new OrderQueueFetcher(orderQueue));
    }
    virtual void PutInFront(InputFile* file) override { fetchHandler.PutInFront(new InputFileFetcher(file)); }

    virtual Order DequeueFromOrderQueue() override { return decodeHandler.DequeueFromOrderQueue(); }
    virtual void EnqueueInOrderQueue(Order order) override { decodeHandler.EnqueueInOrderQueue(order); }
    virtual void EnqueueInOrderQueueFront(Order order) override { decodeHandler.EnqueueInOrderQueueFront(order); }
    virtual OrderQueue GetOrderQueueCopy() override { return decodeHandler.GetOrderQueueCopy(); }
    virtual OrderQueue* DequeueWholeOrderQueue() override { return decodeHandler.DequeueWholeOrderQueue(); }

   private:
    FetchHandler fetchHandler = FetchHandler();
    DecodeHandler decodeHandler = DecodeHandler();
    ExecuteHandler executeHandler = ExecuteHandler();
};
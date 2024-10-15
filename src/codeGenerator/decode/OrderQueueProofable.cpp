#pragma once

class OrderQueueProofable
{
   private:
    bool orderQueueProof = false;

   public:
    virtual bool IsOrderQueueProof() { return this->orderQueueProof; }
    virtual void SetOrderQueueProof(bool codeStackProof) { this->orderQueueProof = codeStackProof; }
};
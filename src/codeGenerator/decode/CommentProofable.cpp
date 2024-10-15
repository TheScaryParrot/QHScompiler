#pragma once

class CommentProofable
{
   private:
    bool commentProof = false;

   public:
    bool IsCommentProof() { return this->commentProof; }
    void SetCommentProof(bool commentProof) { this->commentProof = commentProof; }
};
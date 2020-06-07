//
// Created by Dell on 03/06/2020.
//

#define LEAF_SUB_TREE_SIZE 1
#define LEAF_HEIGHT 0
#define INVALID_HEIGHTS_BALANCE_A 2
#define INVALID_HEIGHTS_BALANCE_B (-2)
#define EMPTY_NODE_HEIGHT (-1)

#ifndef SOUNDCLOUD_WET2_AVLRANKTREE_H
#define SOUNDCLOUD_WET2_AVLRANKTREE_H

#include <iostream>

using std::exception;

template <class Key, class Data>
class AVLRankTree{

public:

    class AVLNode{

        Key key;
        Data data;
        AVLNode* father;
        AVLNode* rightSon;
        AVLNode* leftSon;
        AVLNode* next;
        AVLNode* previous;
        int height;
        int subTreeSize;

    public:

        explicit AVLNode() = delete;
        AVLNode(AVLNode &node) = delete;
        AVLNode(Key &key,Data &data,AVLNode* father,AVLNode* rightSon,AVLNode* leftSon,AVLNode* next,
                AVLNode* previous,int height=LEAF_HEIGHT, int subTreeSize=LEAF_SUB_TREE_SIZE):
                key(key),data(data),father(father),rightSon(rightSon),leftSon(leftSon),next(next),previous(previous),height(height),
                subTreeSize(subTreeSize){}
        ~AVLNode() = default;
        const Key& getKey() const{
            return key;
        }
        Data& getData(){
            return data;
        }
        AVLNode* getNext() const {
            return next;
        }
        AVLNode* getPrevious() const {
            return previous;
        }
        friend bool operator>(AVLNode &node1,AVLNode &node2){
            return  node1.key>node2.key;
        }
        friend bool operator<(AVLNode &node1,AVLNode &node2){
            return  node1.key<node2.key;
        }
        friend bool operator==(AVLNode &node1,AVLNode &node2){
            return  node1.key==node2.key;
        }

        friend class AVLRankTree;
    };

private:

    AVLNode* root;

    void deleteTreePostorder (AVLNode* root){
        if (root== nullptr) return;
        deleteTreePostorder(root->leftSon);
        deleteTreePostorder(root->rightSon);
        delete(root);
    }

    void printTreeInorder (AVLNode* root){
        int leftSonHeight,rightSonHeight;
        if (root== nullptr) return;
        printTreeInorder(root->leftSon);
        if (root->leftSon== nullptr) leftSonHeight=EMPTY_NODE_HEIGHT;
        else leftSonHeight=root->leftSon->height;
        if (root->rightSon== nullptr) rightSonHeight=EMPTY_NODE_HEIGHT;
        else rightSonHeight=root->rightSon->height;
        printf("%d BF: %d Height: %d SubTreeSize: %d\n",root->key,
               leftSonHeight-rightSonHeight,root->height,root->subTreeSize);
        if (leftSonHeight-rightSonHeight>=2||leftSonHeight-rightSonHeight<=-2)
            printf("ERROR!!!!!!!!!!!!!!!!!!!!!! \n");
        if (root->subTreeSize<1)
            printf("ERROR!!!!!!!!!!!!!!!!!!!!!! \n");
        printTreeInorder(root->rightSon);
    }

    void printTreePostorder (AVLNode* root){
        int leftSonHeight,rightSonHeight;
        if (root== nullptr) return;
        printTreeInorder(root->leftSon);
        printTreeInorder(root->rightSon);
        if (root->leftSon== nullptr) leftSonHeight=EMPTY_NODE_HEIGHT;
        else leftSonHeight=root->leftSon->height;
        if (root->rightSon== nullptr) rightSonHeight=EMPTY_NODE_HEIGHT;
        else rightSonHeight=root->rightSon->height;
        printf("%d BF: %d Height: %d \n",root->key,
               leftSonHeight-rightSonHeight,root->height);
        if (leftSonHeight-rightSonHeight>=2||leftSonHeight-rightSonHeight<=-2)
            printf("ERROR!!!!!!!!!!!!!!!!!!!!!! \n");
    }

    void printTreeInfoInorder(AVLNode* root){
        int leftSonKey,rightSonKey,fatherKey;
        if (root== nullptr) return;
        printTreeInfoInorder(root->leftSon);
        if (root->father== nullptr) fatherKey=-1;
        else fatherKey=root->father->key;
        if (root->leftSon== nullptr) leftSonKey=-1;
        else leftSonKey=root->leftSon->key;
        if (root->rightSon== nullptr) rightSonKey=-1;
        else rightSonKey=root->rightSon->key;
        printf("root key: %d,left son key: %d,right son key: %d,father key: %d \n",
               root->key,leftSonKey,rightSonKey,fatherKey);
        printTreeInfoInorder(root->rightSon);
    }

    void printKeysBackwardsInorder(AVLNode* max){
        AVLNode* current = max;
        while (current!= nullptr){
            printf("current key: %d \n",current->getKey());
            current = current->previous;
        }
    }

    void updateHeightsAndSubTreeSizes(AVLNode* startNode){
        AVLNode* current = startNode;
        int leftSonHeight,rightSonHeight;
        while (current!= nullptr){
            if (current->leftSon== nullptr) leftSonHeight=EMPTY_NODE_HEIGHT;
            else leftSonHeight=current->leftSon->height;
            if (current->rightSon== nullptr) rightSonHeight=EMPTY_NODE_HEIGHT;
            else rightSonHeight=current->rightSon->height;
            if (leftSonHeight>rightSonHeight){
                current->height=leftSonHeight+1;
            }
            else current->height=rightSonHeight+1;
            current->subTreeSize = 0;
            if (current->rightSon!= nullptr) current->subTreeSize += current->rightSon->subTreeSize;
            if (current->leftSon!= nullptr) current->subTreeSize += current->leftSon->subTreeSize;
            current->subTreeSize++;
            current=current->father;
        }
    }

    AVLNode* findByRank(int index, AVLNode* root){
        if (root== nullptr) return nullptr;
        if (root->leftSon != nullptr){
            if (root->leftSon->subTreeSize == index-1) return root;
            else if (root->leftSon->subTreeSize > index-1) return findByRank(index,root->leftSon);
            else return findByRank(index-root->leftSon->subTreeSize-1,root->rightSon);
        }
        if (index==1) return root;
        return findByRank(index-1,root->rightSon);
    }

    void roll (AVLNode* startNode){
        AVLNode* current=startNode;
        int leftSonHeight,rightSonHeight,leftSonRightSonHeight,leftSonLeftSonHeight,
                rightSonLeftSonHeight,rightSonRightSonHeight;
        while (current!= nullptr){
            if (current->leftSon== nullptr) leftSonHeight=EMPTY_NODE_HEIGHT;
            else leftSonHeight=current->leftSon->height;
            if (current->rightSon== nullptr) rightSonHeight=EMPTY_NODE_HEIGHT;
            else rightSonHeight=current->rightSon->height;
            if (current->leftSon== nullptr||current->leftSon->leftSon== nullptr) leftSonLeftSonHeight=EMPTY_NODE_HEIGHT;
            else leftSonLeftSonHeight=current->leftSon->leftSon->height;
            if (current->leftSon== nullptr||current->leftSon->rightSon== nullptr) leftSonRightSonHeight=EMPTY_NODE_HEIGHT;
            else leftSonRightSonHeight=current->leftSon->rightSon->height;
            if (current->rightSon== nullptr||current->rightSon->leftSon== nullptr) rightSonLeftSonHeight=EMPTY_NODE_HEIGHT;
            else rightSonLeftSonHeight=current->rightSon->leftSon->height;
            if (current->rightSon== nullptr||current->rightSon->rightSon== nullptr) rightSonRightSonHeight=EMPTY_NODE_HEIGHT;
            else rightSonRightSonHeight=current->rightSon->rightSon->height;
            if (leftSonHeight-rightSonHeight>=INVALID_HEIGHTS_BALANCE_A){
                if (leftSonLeftSonHeight-leftSonRightSonHeight==-1)
                    current=LRroll(current)->father;
                else if (leftSonLeftSonHeight-leftSonRightSonHeight>=0)
                    current=LLroll(current)->father;
                continue;
            }
            if (leftSonHeight-rightSonHeight<=INVALID_HEIGHTS_BALANCE_B){
                if (rightSonLeftSonHeight-rightSonRightSonHeight<=0)
                    current=RRroll(current)->father;
                else if (rightSonLeftSonHeight-rightSonRightSonHeight==1)
                    current=RLroll(current)->father;
                continue;
            }
            current=current->father;
        }
    }

    AVLNode* RRroll(AVLNode* problemNode){

        //printf("RR on %d \n",problemNode->key);

        int problemNodeLeftSonHeight,problemNodeRightSonHeight,BRightSonHeight,BLeftSonHeight,
                problemNodeFatherRightSonHeight,problemNodeFatherLeftSonHeight,
                problemNodeLeftSonLeftSonHeight,problemNodeLeftSonRightSonHeight,
                problemNodeRightSonLeftSonHeight,problemNodeRightSonRightSonHeight;
        AVLNode* problemNodeFather= problemNode->father;
        AVLNode* B=problemNode->rightSon;
        AVLNode* BL=problemNode->rightSon->leftSon;

        B->leftSon=problemNode;
        B->father=problemNode->father;
        if (problemNode->father!= nullptr){
            if (problemNode->key>problemNode->father->key)
                problemNode->father->rightSon=B;
            else problemNode->father->leftSon=B;
        }
        problemNode->father=B;
        if (B->father== nullptr)
            root=B;
        problemNode->rightSon=BL;
        if (BL!= nullptr){
            BL->father=problemNode;
        }

        problemNode->subTreeSize = 0;
        if (problemNode->rightSon!= nullptr) problemNode->subTreeSize += problemNode->rightSon->subTreeSize;
        if (problemNode->leftSon!= nullptr) problemNode->subTreeSize += problemNode->leftSon->subTreeSize;
        problemNode->subTreeSize++;
        B->subTreeSize = 0;
        if (B->leftSon!= nullptr) B->subTreeSize += B->leftSon->subTreeSize;
        if (B->rightSon!= nullptr) B->subTreeSize += B->rightSon->subTreeSize;
        B->subTreeSize++;

        if (problemNode->leftSon== nullptr) problemNodeLeftSonHeight=EMPTY_NODE_HEIGHT;
        else problemNodeLeftSonHeight=problemNode->leftSon->height;
        if (problemNode->rightSon== nullptr) problemNodeRightSonHeight=EMPTY_NODE_HEIGHT;
        else problemNodeRightSonHeight=problemNode->rightSon->height;

        if (problemNodeLeftSonHeight>problemNodeRightSonHeight){
            problemNode->height=problemNodeLeftSonHeight+1;
        } else problemNode->height=problemNodeRightSonHeight+1;

        if (B->leftSon== nullptr) BLeftSonHeight=EMPTY_NODE_HEIGHT;
        else BLeftSonHeight=B->leftSon->height;
        if (B->rightSon== nullptr) BRightSonHeight=EMPTY_NODE_HEIGHT;
        else BRightSonHeight=B->rightSon->height;

        if (BLeftSonHeight>BRightSonHeight){
            B->height=BLeftSonHeight+1;
        } else B->height=BRightSonHeight+1;

        if (problemNodeFather== nullptr||problemNodeFather->rightSon== nullptr) problemNodeFatherRightSonHeight=EMPTY_NODE_HEIGHT;
        else problemNodeFatherRightSonHeight=problemNodeFather->rightSon->height;
        if (problemNodeFather== nullptr||problemNodeFather->leftSon== nullptr) problemNodeFatherLeftSonHeight=EMPTY_NODE_HEIGHT;
        else problemNodeFatherLeftSonHeight=problemNodeFather->leftSon->height;

        if (problemNodeFather!= nullptr){
            if (problemNodeFatherLeftSonHeight>problemNodeFatherRightSonHeight){
                problemNodeFather->height=problemNodeFatherLeftSonHeight+1;
            } else problemNodeFather->height=problemNodeFatherRightSonHeight+1;
            updateHeightsAndSubTreeSizes(problemNodeFather->father);
        }

        if (problemNode->leftSon== nullptr||problemNode->leftSon->leftSon== nullptr)
            problemNodeLeftSonLeftSonHeight=EMPTY_NODE_HEIGHT;
        else problemNodeLeftSonLeftSonHeight=problemNode->leftSon->leftSon->height;
        if (problemNode->leftSon== nullptr||problemNode->leftSon->rightSon== nullptr)
            problemNodeLeftSonRightSonHeight=EMPTY_NODE_HEIGHT;
        else problemNodeLeftSonRightSonHeight=problemNode->leftSon->rightSon->height;
        if (problemNode->rightSon== nullptr||problemNode->rightSon->leftSon== nullptr)
            problemNodeRightSonLeftSonHeight=EMPTY_NODE_HEIGHT;
        else problemNodeRightSonLeftSonHeight=problemNode->rightSon->leftSon->height;
        if (problemNode->rightSon== nullptr||problemNode->rightSon->rightSon== nullptr)
            problemNodeRightSonRightSonHeight=EMPTY_NODE_HEIGHT;
        else problemNodeRightSonRightSonHeight=problemNode->rightSon->rightSon->height;

        //printf("%d new BF: %d \n",problemNode->key,problemNodeLeftSonHeight-problemNodeRightSonHeight);

        if (problemNodeLeftSonHeight-problemNodeRightSonHeight>=INVALID_HEIGHTS_BALANCE_A){
            if (problemNodeLeftSonLeftSonHeight-problemNodeLeftSonRightSonHeight==-1)
                LRroll(problemNode);
            else if (problemNodeLeftSonLeftSonHeight-problemNodeLeftSonRightSonHeight>=0)
                LLroll(problemNode);
        }
        if (problemNodeLeftSonHeight-problemNodeRightSonHeight<=INVALID_HEIGHTS_BALANCE_B){
            if (problemNodeRightSonLeftSonHeight-problemNodeRightSonRightSonHeight<=0)
                RRroll(problemNode);
            else if (problemNodeRightSonLeftSonHeight-problemNodeRightSonRightSonHeight==1)
                RLroll(problemNode);
        }

        return B;

    };

    AVLNode* LLroll(AVLNode* problemNode){

        //printf("LL on %d \n",problemNode->key);

        int problemNodeLeftSonHeight,problemNodeRightSonHeight,ARightSonHeight,ALeftSonHeight,
                problemNodeFatherRightSonHeight,problemNodeFatherLeftSonHeight,
                problemNodeLeftSonLeftSonHeight,problemNodeLeftSonRightSonHeight,
                problemNodeRightSonLeftSonHeight,problemNodeRightSonRightSonHeight;
        AVLNode* problemNodeFather= problemNode->father;
        AVLNode* A=problemNode->leftSon;
        AVLNode* AR=problemNode->leftSon->rightSon;

        A->rightSon=problemNode;
        A->father= problemNode->father;
        if (problemNode->father!= nullptr){
            if (problemNode->key>problemNode->father->key)
                problemNode->father->rightSon=A;
            else problemNode->father->leftSon=A;
        }
        problemNode->father=A;
        if (A->father== nullptr)
            root=A;
        problemNode->leftSon=AR;
        if (AR!= nullptr){
            AR->father=problemNode;
        }

        problemNode->subTreeSize = 0;
        if (problemNode->rightSon!= nullptr) problemNode->subTreeSize += problemNode->rightSon->subTreeSize;
        if (problemNode->leftSon!= nullptr) problemNode->subTreeSize += problemNode->leftSon->subTreeSize;
        problemNode->subTreeSize++;
        A->subTreeSize = 0;
        if (A->leftSon!= nullptr) A->subTreeSize += A->leftSon->subTreeSize;
        if (A->rightSon!= nullptr) A->subTreeSize += A->rightSon->subTreeSize;
        A->subTreeSize++;

        if (problemNode->leftSon== nullptr) problemNodeLeftSonHeight=EMPTY_NODE_HEIGHT;
        else problemNodeLeftSonHeight=problemNode->leftSon->height;
        if (problemNode->rightSon== nullptr) problemNodeRightSonHeight=EMPTY_NODE_HEIGHT;
        else problemNodeRightSonHeight=problemNode->rightSon->height;

        if (problemNodeLeftSonHeight>problemNodeRightSonHeight){
            problemNode->height=problemNodeLeftSonHeight+1;
        } else problemNode->height=problemNodeRightSonHeight+1;

        if (A->leftSon== nullptr) ALeftSonHeight=EMPTY_NODE_HEIGHT;
        else ALeftSonHeight=A->leftSon->height;
        if (A->rightSon== nullptr) ARightSonHeight=EMPTY_NODE_HEIGHT;
        else ARightSonHeight=A->rightSon->height;

        if (ALeftSonHeight>ARightSonHeight){
            A->height=ALeftSonHeight+1;
        } else A->height=ARightSonHeight+1;

        if (problemNodeFather== nullptr||problemNodeFather->rightSon== nullptr) problemNodeFatherRightSonHeight=EMPTY_NODE_HEIGHT;
        else problemNodeFatherRightSonHeight=problemNodeFather->rightSon->height;
        if (problemNodeFather== nullptr||problemNodeFather->leftSon== nullptr) problemNodeFatherLeftSonHeight=EMPTY_NODE_HEIGHT;
        else problemNodeFatherLeftSonHeight=problemNodeFather->leftSon->height;

        if (problemNodeFather!= nullptr){
            if (problemNodeFatherLeftSonHeight>problemNodeFatherRightSonHeight){
                problemNodeFather->height=problemNodeFatherLeftSonHeight+1;
            } else problemNodeFather->height=problemNodeFatherRightSonHeight+1;
            updateHeightsAndSubTreeSizes(problemNodeFather->father);
        }

        if (problemNode->leftSon== nullptr||problemNode->leftSon->leftSon== nullptr)
            problemNodeLeftSonLeftSonHeight=EMPTY_NODE_HEIGHT;
        else problemNodeLeftSonLeftSonHeight=problemNode->leftSon->leftSon->height;
        if (problemNode->leftSon== nullptr||problemNode->leftSon->rightSon== nullptr)
            problemNodeLeftSonRightSonHeight=EMPTY_NODE_HEIGHT;
        else problemNodeLeftSonRightSonHeight=problemNode->leftSon->rightSon->height;
        if (problemNode->rightSon== nullptr||problemNode->rightSon->leftSon== nullptr)
            problemNodeRightSonLeftSonHeight=EMPTY_NODE_HEIGHT;
        else problemNodeRightSonLeftSonHeight=problemNode->rightSon->leftSon->height;
        if (problemNode->rightSon== nullptr||problemNode->rightSon->rightSon== nullptr)
            problemNodeRightSonRightSonHeight=EMPTY_NODE_HEIGHT;
        else problemNodeRightSonRightSonHeight=problemNode->rightSon->rightSon->height;

        //printf("%d new BF: %d \n",problemNode->key,problemNodeLeftSonHeight-problemNodeRightSonHeight);

        if (problemNodeLeftSonHeight-problemNodeRightSonHeight>=INVALID_HEIGHTS_BALANCE_A){
            if (problemNodeLeftSonLeftSonHeight-problemNodeLeftSonRightSonHeight==-1)
                LRroll(problemNode);
            else if (problemNodeLeftSonLeftSonHeight-problemNodeLeftSonRightSonHeight>=0)
                LLroll(problemNode);
        }
        if (problemNodeLeftSonHeight-problemNodeRightSonHeight<=INVALID_HEIGHTS_BALANCE_B){
            if (problemNodeRightSonLeftSonHeight-problemNodeRightSonRightSonHeight<=0)
                RRroll(problemNode);
            else if (problemNodeRightSonLeftSonHeight-problemNodeRightSonRightSonHeight==1)
                RLroll(problemNode);
        }

        return A;

    };

    AVLNode* LRroll(AVLNode* problemNode){
        RRroll(problemNode->leftSon);
        return LLroll(problemNode);
    };

    AVLNode* RLroll(AVLNode* problemNode){
        LLroll(problemNode->rightSon);
        return RRroll(problemNode);
    };

public:

    explicit AVLRankTree(){
        root = nullptr;
    };

    explicit AVLRankTree(AVLNode* root):root(root){}

    AVLRankTree (const AVLRankTree &avlRankTree)= default;

    ~AVLRankTree(){
        deleteTreePostorder(root);
    };

    AVLNode* getRoot() {
        return root;
    }

    AVLNode* insert(Key &key,Data &data){
        if (root== nullptr){
            root=new AVLNode(key, data, nullptr, nullptr, nullptr, nullptr,
                             nullptr);
            return root;
        }
        AVLNode* newAvlNode= nullptr;
        AVLNode* current = root;
        while (current!= nullptr){
            if (current->key==key)
                throw AlreadyExist_AVLtree();
            if (current->key<key) {
                if (current->rightSon==nullptr){
                    newAvlNode=new AVLNode(key, data, current, nullptr, nullptr,
                                           nullptr, nullptr);
                    current->rightSon=newAvlNode;
                    if (current->father!= nullptr){
                        if (current->father->leftSon==current){
                            current->father->previous = newAvlNode;
                            newAvlNode->next = current->father;
                        }
                        else {
                            newAvlNode->next = current->next;
                            if (current->next!= nullptr)
                                current->next->previous = newAvlNode;
                        }
                    }
                    current->next = newAvlNode;
                    newAvlNode->previous = current;
                    break;
                }
                current=current->rightSon;
            }
            else {
                if (current->leftSon== nullptr){
                    newAvlNode =new AVLNode(key, data, current, nullptr, nullptr,
                                            nullptr, nullptr);
                    current->leftSon=newAvlNode;
                    if (current->father!= nullptr){
                        if (current->father->rightSon==current){
                            current->father->next = newAvlNode;
                            newAvlNode->previous = current->father;
                        }
                        else {
                            newAvlNode->previous = current->previous;
                            if (current->previous!= nullptr)
                                current->previous->next = newAvlNode;
                        }
                    }
                    current->previous = newAvlNode;
                    newAvlNode->next = current;
                    break;
                }
                current=current->leftSon;
            }
        }
        updateHeightsAndSubTreeSizes(current);
        roll(current);
        return newAvlNode;
    }

    void erase(Key &key){
        AVLNode* current = root;
        AVLNode* connectionNode;
        while (current!= nullptr){
            if (current->key==key){
                // updating next and previous properties
                if (current->previous!= nullptr)
                    current->previous->next = current->next;
                if (current->next!= nullptr)
                    current->next->previous = current->previous;
                // if the erased node has a father
                if (current->father!= nullptr){
                    // if the erased node has a left son
                    if (current->leftSon!= nullptr){
                        connectionNode=current->leftSon;
                        while (connectionNode->rightSon!= nullptr)
                            connectionNode=connectionNode->rightSon;
                        if (current->father->key>current->key)
                            current->father->leftSon=current->leftSon;
                        else if (current->father->key<current->key)
                            current->father->rightSon=current->leftSon;
                        current->leftSon->father=current->father;
                        connectionNode->rightSon=current->rightSon;
                        if (current->rightSon!= nullptr){
                            current->rightSon->father=connectionNode;
                        }
                        updateHeightsAndSubTreeSizes(connectionNode);
                        roll(connectionNode);
                    }
                        //if the erased node has no left son
                    else {
                        //connecting the erase node father to the erased node right son
                        if (current->father->key>current->key)
                            current->father->leftSon=current->rightSon;
                        else if (current->father->key<current->key)
                            current->father->rightSon=current->rightSon;
                        //if the erased node right son is null then update the
                        //heights and roll from the erased node father else from
                        //the erased node right son (and make the erased node father
                        //the erased node right son father
                        if (current->rightSon!= nullptr)
                            current->rightSon->father=current->father;
                        updateHeightsAndSubTreeSizes(current->father);
                        roll(current->father);

                    }
                }
                    // if the erased node has no father
                else {
                    // if the erased node has a left son
                    if (current->leftSon!= nullptr){
                        connectionNode=current->leftSon;
                        while (connectionNode->rightSon!= nullptr)
                            connectionNode=connectionNode->rightSon;
                        root=current->leftSon;
                        current->leftSon->father= nullptr;
                        connectionNode->rightSon=current->rightSon;
                        if (current->rightSon!= nullptr){
                            current->rightSon->father=connectionNode;
                        }
                        updateHeightsAndSubTreeSizes(connectionNode);
                        roll(connectionNode);
                    }
                        // if the erased node has no left son
                    else {
                        root=current->rightSon;
                        if (current->rightSon!= nullptr){
                            current->rightSon->father= nullptr;
                        }
                    }
                }
                delete(current);
                return;
            }
            if (current->key<key)
                current=current->rightSon;
            else current=current->leftSon;
        }
        throw NotFound_AVLtree();
    }

    AVLNode* find (Key &key){
        AVLNode* current = root;
        while (current!= nullptr){
            if (current->key==key)
                return current;
            if (current->key<key)
                current=current->rightSon;
            else current=current->leftSon;
        }
        throw NotFound_AVLtree();
    }

    AVLNode* select (int index){
        return findByRank(index,root);
    }

    void printTree (){
        printTreeInorder(root);
        printf("\n");
    }

    void treeClear (){
        deleteTreePostorder(root);
        root= nullptr;
    }

    AVLNode* findMaxNode(){
        if (root== nullptr)
            return nullptr;
        AVLNode* current = root;
        while (current->rightSon!= nullptr)
            current = current->rightSon;
        return current;
    }

    class NotFound_AVLtree : public exception{};
    class BadParameters_AVLtree : public  exception{};
    class AlreadyExist_AVLtree : public exception{};

};

#endif //SOUNDCLOUD_WET2_AVLRANKTREE_H

#include "gtest/gtest.h"
#include <cstring>
#include "aux_functions.h"
#define _USE_MATH_DEFINES
#include "math.h"

extern "C"
{
    #include <time.h>
    #include <stdlib.h>
    #include "../src/Aux_Func.h"
}


TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);

    // Inicializações do Projeto

    // Randomiza, eventualmente.
    srand((unsigned int) time(NULL));
}


TEST(TestcreateOneFr52Deck, TestMatchFr52Deck) {
    ListCardNodePtr expectedDeck = NULL;
    ListCardNodePtr actualDeck = NULL;

    createOneFr52Deck(&actualDeck);
    ReadFileOfOneFr52Deck(&expectedDeck);
    ASSERT_TRUE(ListMatch(actualDeck, expectedDeck));
}


TEST(TestshuffleOneFr52Deck, TestShuffleFr52DeckListMatch) {
    ListCardNodePtr expectedDeck = NULL;
    ListCardNodePtr actualDeck = NULL;

    ReadFileOfOneFr52Deck(&actualDeck);
    shuffle(&actualDeck);
    
    readFileOfShuffledFr52Deck(&expectedDeck);
    ASSERT_TRUE(ListMatch(actualDeck, expectedDeck));
}

TEST(TestshuffleOneFr52Deck, TestShuffleFr52DeckNodeAddressMismatch) {
    ListCardNodePtr expectedDeck = NULL;
    ListCardNodePtr actualDeck = NULL;

    int i;
    int actualAddressSeq[53] = { 0 };
    int expectedAddressSeq[53] = { 0 };

    for (i = 0; i < 53; i++) {
        expectedAddressSeq[i] = rand() + 1;
    }

    ListCardNodePtr actualAddressSeqPtr;
    ListCardNodePtr expectedAddressSeqPtr;

    ReadFileOfOneFr52Deck(&actualDeck);
    actualAddressSeqPtr = actualDeck;
    for (i = 0; actualAddressSeqPtr != NULL && i < 52; i++) {
        actualAddressSeq[i] = (int)actualAddressSeqPtr;
        actualAddressSeqPtr = actualAddressSeqPtr->nextPtr;
    }
    actualAddressSeq[i] = (int)actualAddressSeqPtr;

    shuffle(&actualDeck);
    expectedAddressSeqPtr = actualDeck;
    for (i = 0; expectedAddressSeqPtr != NULL && i < 52; i++) {
        expectedAddressSeq[i] = (int)expectedAddressSeqPtr;
        expectedAddressSeqPtr = expectedAddressSeqPtr->nextPtr;
    }
    expectedAddressSeq[i] = (int)expectedAddressSeqPtr;

    // Verifica se os nós foram trocados
    ASSERT_TRUE(ListNodeAddressesArrayMismatch(actualAddressSeq, expectedAddressSeq));
}

TEST(TestshuffleOneFr52Deck, TestShuffleFr52DeckEmptyDeck) {
    ListCardNodePtr expectedDeck = NULL;
    ListCardNodePtr actualDeck = NULL;

    ReadFileOfOneFr52Deck(&actualDeck);
    shuffle(&actualDeck);

    readFileOfShuffledFr52Deck(&expectedDeck);
    // Verifica se algum dos ponteiros é nulo
    ASSERT_TRUE(NullPointerTest(actualDeck, expectedDeck));
}

TEST(Test_isDeckEmpty, isDeckEmptyTestEmptyDeck) {
    ListCardNodePtr expectedDeck = NULL;

    EXPECT_TRUE(isDeckEmpty(expectedDeck));

}

TEST(Test_isDeckEmpty, isDeckEmptyTestNotEmptyDeck) {
    ListCardNodePtr expectedDeck = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    expectedDeck->nextPtr = NULL;
    expectedDeck->card.face = face[0];
    expectedDeck->card.face_number = 1;
    expectedDeck->card.suit = suit[3];
    expectedDeck->card.suit_number = 4;

    EXPECT_FALSE(isDeckEmpty(expectedDeck));

}

TEST(Test_popFromDeck, popFromOneElementDeckTestEmptyDeck) {
    ListCardNodePtr rebuiltExpectedDeck = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    *rebuiltExpectedDeck = { face[0], suit[3], 1, 4, NULL };
    ListCardNodePtr actualDeck = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    *actualDeck = { face[0], suit[3], 1, 4, NULL };
    ListCardNodePtr expectedDeck = NULL;
    ListCardNodePtr rebuiltActualDeck = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    Card actualCard = { 0 };
    *rebuiltActualDeck = { actualCard, NULL };
    popFromDeck(&actualDeck);
    ASSERT_TRUE(ListMatch(actualDeck, expectedDeck));

}

TEST(Test_popFromDeck, popFromOneElementDeckTestOneElementRebuiltDeck) {
    ListCardNodePtr rebuiltExpectedDeck = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    *rebuiltExpectedDeck = { face[0], suit[3], 1, 4, NULL };
    ListCardNodePtr actualDeck = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    *actualDeck = { face[0], suit[3], 1, 4, NULL };
    ListCardNodePtr expectedDeck = NULL;
    ListCardNodePtr rebuiltActualDeck = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    Card actualCard = { 0 };
    *rebuiltActualDeck = { actualCard, NULL };
    actualCard = popFromDeck(&actualDeck);
    *rebuiltActualDeck = { actualCard, NULL };
    ASSERT_TRUE(ListMatch(rebuiltActualDeck, rebuiltExpectedDeck));
}

TEST(Test_popFromDeck, popFromOneFr52DeckTestRebuiltDeck) {
    ListCardNodePtr expectedDeck;
    ListCardNodePtr actualDeck;
    ReadFileOfOneFr52Deck(&actualDeck);
    ReadFileOfOneFr52Deck(&expectedDeck);
    ListCardNodePtr rebuiltActualDeck = NULL;
    Card actualCard = { 0 };
    ListCardNodePtr newNode = NULL;

    while (actualDeck != NULL) {
        newNode = (ListCardNodePtr)malloc(sizeof(ListCardNode));
        actualCard = popFromDeck(&actualDeck);
        newNode->card = actualCard;
        newNode->nextPtr = rebuiltActualDeck;
        rebuiltActualDeck = newNode;
    }

    while (rebuiltActualDeck != NULL) {
        newNode = (ListCardNodePtr)malloc(sizeof(ListCardNode));
        actualCard = popFromDeck(&rebuiltActualDeck);
        newNode->card = actualCard;
        newNode->nextPtr = actualDeck;
        actualDeck = newNode;
    }

    ASSERT_TRUE(ListMatch(actualDeck, expectedDeck));
}

TEST(Test_dequeueFromDeck, dequeueFromOneElementDeckTestEmptyDeck) {
    ListCardNodePtr actualDeckHead = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    ListCardNodePtr actualDeckTail = actualDeckHead;
    *actualDeckHead = { face[0], suit[3], 1, 4, NULL };
    ListCardNodePtr expectedDeckHead = NULL, expectedDeckTail = NULL;
    
    dequeueFromDeck(&actualDeckHead, &actualDeckTail);
    ASSERT_TRUE(ListMatch(actualDeckHead, expectedDeckHead));
    ASSERT_TRUE(ListMatch(actualDeckTail, expectedDeckTail));

}

TEST(Test_dequeueFromDeck, dequeueFromOneElementDeckTestOneElementRebuiltDeck) {
    ListCardNodePtr actualDeckTail = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    ListCardNodePtr actualDeckHead = actualDeckTail;
    *actualDeckTail = { face[0], suit[3], 1, 4, NULL };

    ListCardNodePtr rebuiltExpectedDeckTail = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    ListCardNodePtr rebuiltExpectedDeckHead = rebuiltExpectedDeckTail;
    *rebuiltExpectedDeckTail = { face[0], suit[3], 1, 4, NULL };
    
    ListCardNodePtr rebuiltActualDeckTail = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    ListCardNodePtr rebuiltActualDeckHead = rebuiltActualDeckTail;
    Card actualCard = { 0 };
    *rebuiltActualDeckTail = { actualCard, NULL };

    actualCard = dequeueFromDeck(&actualDeckHead, &actualDeckTail);
    *rebuiltActualDeckTail = { actualCard, NULL };
    ASSERT_TRUE(ListMatch(rebuiltActualDeckHead, rebuiltExpectedDeckHead));
}

TEST(Test_dequeueFromDeck, dequeueFromTwoElementDeckTestPointersForOneElementDeck) {
    ListCardNodePtr actualDeckTail = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    ListCardNodePtr actualDeckHead = actualDeckTail;
    *actualDeckTail = { face[0], suit[3], 1, 4, NULL };

    ListCardNodePtr actualNewNode = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    *actualNewNode = { face[12], suit[3], 13, 4, NULL };
    actualDeckTail->nextPtr = actualNewNode;
    actualDeckTail = actualNewNode;

    ListCardNodePtr expectedDeckHead = actualDeckHead->nextPtr, expectedDeckTail = actualDeckTail;

    dequeueFromDeck(&actualDeckHead, &actualDeckTail);
    ASSERT_TRUE(ListMatch(actualDeckHead, expectedDeckHead));
    ASSERT_TRUE(ListMatch(actualDeckTail, expectedDeckTail));

}

TEST(Test_dequeueFromDeck, dequeueFromTwoElementDeckTestOneElementDeck) {
    ListCardNodePtr actualDeckTail = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    ListCardNodePtr actualDeckHead = actualDeckTail;
    *actualDeckTail = { face[0], suit[3], 1, 4, NULL };

    ListCardNodePtr actualNewNode = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    *actualNewNode = { face[12], suit[3], 13, 4, NULL };
    actualDeckTail->nextPtr = actualNewNode;
    actualDeckTail = actualNewNode;

    ListCardNodePtr expectedDeckHead = actualDeckHead->nextPtr, expectedDeckTail = actualDeckTail;

    dequeueFromDeck(&actualDeckHead, &actualDeckTail);
    
    ASSERT_TRUE(ListMatch(actualDeckHead, expectedDeckHead));

}

TEST(Test_dequeueFromDeck, dequeueFromTwoElementDeckTestOneElementNewDeck) {
    ListCardNodePtr actualDeckTail = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    ListCardNodePtr actualDeckHead = actualDeckTail;
    *actualDeckTail = { face[0], suit[3], 1, 4, NULL };

    ListCardNodePtr actualNewNode = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    *actualNewNode = { face[12], suit[3], 13, 4, NULL };
    actualDeckTail->nextPtr = actualNewNode;
    actualDeckTail = actualNewNode;

    ListCardNodePtr expectedDeckHead = actualDeckHead->nextPtr, expectedDeckTail = actualDeckTail;

    ListCardNodePtr actualNewDeckTail = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    ListCardNodePtr actualNewDeckHead = actualNewDeckTail;
    actualNewDeckTail->card = dequeueFromDeck(&actualDeckHead, &actualDeckTail);
    actualNewDeckTail->nextPtr = NULL;

    ListCardNodePtr expectedNewDeckTail = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    ListCardNodePtr expectedNewDeckHead = expectedNewDeckTail;
    *expectedNewDeckTail = { face[0], suit[3], 1, 4, NULL };

    ASSERT_TRUE(ListMatch(actualNewDeckHead, expectedNewDeckHead));

}

TEST(Test_dequeueFromDeck, dequeueAllElementsFromOneFr52DeckTestRebuiltDeck) {
    ListCardNodePtr expectedDeck;
    ListCardNodePtr actualDeck, actualDeckHead, actualDeckTail;
    ReadFileOfOneFr52Deck(&actualDeck);
    // Find Tail
    actualDeckHead = actualDeckTail = actualDeck;
    while (actualDeck != NULL) {
        actualDeckTail = actualDeck;
        actualDeck = actualDeck->nextPtr;
    }
    ReadFileOfOneFr52Deck(&expectedDeck);
    ListCardNodePtr rebuiltActualDeck = NULL, fairy = NULL;
    Card actualCard = { 0 };
    ListCardNodePtr newNode = NULL;

    while (actualDeckHead != NULL) {
        newNode = (ListCardNodePtr)malloc(sizeof(ListCardNode));
        actualCard = dequeueFromDeck(&actualDeckHead, &actualDeckTail);
        newNode->card = actualCard;
        newNode->nextPtr = NULL;
        if (rebuiltActualDeck == NULL) {
            rebuiltActualDeck = newNode;
            fairy = rebuiltActualDeck;
        }
        else {
            fairy->nextPtr = newNode;
            fairy = newNode;
        }
    }

    ASSERT_TRUE(ListMatch(rebuiltActualDeck, expectedDeck));
}

TEST(Test_enqueueOnDeck, enqueueOnEmptyQueueTestSingleElementQueue) {
    Card card = { face[0], suit[3], 1, 4 };
    ListCardNodePtr expectecDeckTail = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    ListCardNodePtr expectedDeckHead = expectecDeckTail;
    *expectecDeckTail = { card, NULL };

    ListCardNodePtr actualDeckHead = NULL, actualDeckTail;
    enqueueOnDeck(&actualDeckHead, &actualDeckTail, card);

    ASSERT_TRUE(ListMatch(actualDeckHead, expectedDeckHead));

}

TEST(Test_enqueueOnDeck, enqueueOnEmptyQueueTestPointersForSingleElementQueue) {
    Card card = { face[0], suit[3], 1, 4 };
    ListCardNodePtr expectecDeckTail = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    ListCardNodePtr expectedDeckHead = expectecDeckTail;
    *expectecDeckTail = { card, NULL };

    ListCardNodePtr actualDeckHead = NULL, actualDeckTail;
    enqueueOnDeck(&actualDeckHead, &actualDeckTail, card);

    ASSERT_TRUE(ListMatch(actualDeckHead, actualDeckTail));

}

TEST(Test_enqueueOnDeck, enqueueOnSingleQueueTestDualElementQueue) {
    Card card = { face[0], suit[3], 1, 4 };
    ListCardNodePtr expectedDeckTail = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    ListCardNodePtr expectedDeckHead = expectedDeckTail;
    *expectedDeckTail = { card, NULL };
    ListCardNodePtr newNode = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    *newNode = { face[5], suit[2], 6, 3, NULL };
    expectedDeckTail->nextPtr = newNode;
    expectedDeckTail = newNode;

    ListCardNodePtr actualDeckTail = (ListCardNodePtr)malloc(sizeof(ListCardNode));
    ListCardNodePtr actualDeckHead = actualDeckTail;
    *actualDeckTail = { face[0], suit[3], 1, 4, NULL };
    card = { face[5], suit[2], 6, 3 };

    enqueueOnDeck(&actualDeckHead, &actualDeckTail, card);

    ASSERT_TRUE(ListMatch(actualDeckHead, expectedDeckHead));

}

TEST(Test_enqueueOnDeck, enqueueAllElementsFromOneShuffledFr52Deck) {
    ListCardNodePtr expectedDeck, expectedDeckPtr;
    ListCardNodePtr actualDeckHead = NULL, actualDeckTail;
    Card card;
    readFileOfShuffledFr52Deck(&expectedDeck);
    expectedDeckPtr = expectedDeck;
    while (expectedDeckPtr != NULL) {
        card = expectedDeckPtr->card;
        expectedDeckPtr = expectedDeckPtr->nextPtr;
        enqueueOnDeck(&actualDeckHead, &actualDeckTail, card);
    }
    ASSERT_TRUE(ListMatch(actualDeckHead, expectedDeck));
}

TEST(insertThreeHandNode, TestIOr) {
    ListCardNodePtr actualDeckHead = NULL, actualDeckTail;
    Card card = { face[0], suit[3], 1, 4 };
    TreeCardNodePtr myTree = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    myTree->card = card;

    TreeCardNodePtr leaf = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[2], suit[3], 3, 4 };
    leaf->card = card;
    leaf->leftPtr = leaf->rightPtr = NULL;
    myTree->rightPtr = leaf;

    leaf = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[0], suit[0], 1, 1 };
    leaf->card = card;
    leaf->leftPtr = leaf->rightPtr = NULL;
    myTree->leftPtr = leaf;

    IOrd(myTree, &actualDeckHead, &actualDeckTail);
}

TEST(insertThreeHandNode, insertOneElementIntoTheTree) {
    ListCardNodePtr expectedDeckHead = NULL, expectedDeckTail;
    Card card = { face[0], suit[3], 1, 4 };
    TreeCardNodePtr myTree = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    myTree->card = card;
    myTree->leftPtr = myTree->rightPtr = NULL;
    IOrd(myTree, &expectedDeckHead, &expectedDeckTail);

    ListCardNodePtr actualDeckHead = NULL, actualDeckTail;
    TreeCardNodePtr yourTree = NULL;
    insertTreeHandNode(&yourTree, card);
    IOrd(yourTree, &actualDeckHead, &actualDeckTail);

    ASSERT_TRUE(ListMatch(actualDeckHead, expectedDeckHead));
}

TEST(insertThreeHandNode, insertThreeElementsIntoTheTree) {
    ListCardNodePtr expectedDeckHead = NULL, expectedDeckTail;
    Card card = { face[0], suit[3], 1, 4 };
    TreeCardNodePtr myTree = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    myTree->card = card;

    TreeCardNodePtr yourTree = NULL;
    insertTreeHandNode(&yourTree, card);

    TreeCardNodePtr leaf = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[2], suit[3], 3, 4 };
    leaf->card = card;
    leaf->leftPtr = leaf->rightPtr = NULL;
    myTree->rightPtr = leaf;

    insertTreeHandNode(&yourTree, card);

    leaf = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[0], suit[0], 1, 1 };
    leaf->card = card;
    leaf->leftPtr = leaf->rightPtr = NULL;
    myTree->leftPtr = leaf;

    insertTreeHandNode(&yourTree, card);

    IOrd(myTree, &expectedDeckHead, &expectedDeckTail);

    ListCardNodePtr actualDeckHead = NULL, actualDeckTail;
    IOrd(yourTree, &actualDeckHead, &actualDeckTail);

    ASSERT_TRUE(ListMatch(actualDeckHead, expectedDeckHead));
}

TEST(insertThreeHandNode, insertSixFullyDifferentElementsIntoTheTree) {
    ListCardNodePtr expectedDeckHead = NULL, expectedDeckTail;
    Card card = { face[0], suit[2], 1, 3 }; // Ás de paus
    TreeCardNodePtr myTree = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    myTree->card = card;

    TreeCardNodePtr leaf1, leaf2, leaf3, leaf4, leaf5, leaf6;

    TreeCardNodePtr yourTree = NULL;
    insertTreeHandNode(&yourTree, card);

    leaf1 = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[2], suit[3], 3, 4 }; // Três de espadas
    leaf1->card = card;
    
    myTree->rightPtr = leaf1;

    insertTreeHandNode(&yourTree, card);

    leaf3 = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[3], suit[2], 4, 3 }; // Quatro de paus
    leaf3->card = card;
    leaf3->leftPtr = leaf3->rightPtr = NULL;
    leaf1->leftPtr = leaf3;

    insertTreeHandNode(&yourTree, card);

    leaf4 = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[8], suit[3], 9, 4 }; // Nove de espadas
    leaf4->card = card;
    leaf4->leftPtr = leaf4->rightPtr = NULL;
    leaf1->rightPtr = leaf4;

    insertTreeHandNode(&yourTree, card);

    leaf2 = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[10], suit[1], 11, 2 }; // valete de ouro
    leaf2->card = card;
    myTree->leftPtr = leaf2;

    insertTreeHandNode(&yourTree, card);

    leaf5 = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[4], suit[0], 5, 1 }; // cinco de copas
    leaf5->card = card;
    leaf5->leftPtr = leaf5->rightPtr = NULL;
    leaf2->leftPtr = leaf5;

    insertTreeHandNode(&yourTree, card);

    leaf6 = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[12], suit[1], 13, 2 }; // rei de ouro
    leaf6->card = card;
    leaf6->leftPtr = leaf6->rightPtr = NULL;
    leaf2->rightPtr = leaf6;

    insertTreeHandNode(&yourTree, card);

    IOrd(myTree, &expectedDeckHead, &expectedDeckTail);

    ListCardNodePtr actualDeckHead = NULL, actualDeckTail;
    IOrd(yourTree, &actualDeckHead, &actualDeckTail);

    ASSERT_TRUE(ListMatch(actualDeckHead, expectedDeckHead));
}

TEST(insertThreeHandNode, insertSixFullyDifferentElementsAndTryOneEqualIntoTheTree) {
    ListCardNodePtr expectedDeckHead = NULL, expectedDeckTail;
    Card card = { face[0], suit[2], 1, 3 }; // Ás de paus
    TreeCardNodePtr myTree = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    myTree->card = card;

    TreeCardNodePtr leaf1, leaf2, leaf3, leaf4, leaf5, leaf6;

    TreeCardNodePtr yourTree = NULL;
    insertTreeHandNode(&yourTree, card);

    leaf1 = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[2], suit[3], 3, 4 }; // Três de espadas
    leaf1->card = card;

    myTree->rightPtr = leaf1;

    insertTreeHandNode(&yourTree, card);

    leaf3 = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[3], suit[2], 4, 3 }; // Quatro de paus
    leaf3->card = card;
    leaf3->leftPtr = leaf3->rightPtr = NULL;
    leaf1->leftPtr = leaf3;

    insertTreeHandNode(&yourTree, card);

    leaf4 = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[8], suit[3], 9, 4 }; // Nove de espadas
    leaf4->card = card;
    leaf4->leftPtr = leaf4->rightPtr = NULL;
    leaf1->rightPtr = leaf4;

    insertTreeHandNode(&yourTree, card);

    leaf2 = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[10], suit[1], 11, 2 }; // valete de ouro
    leaf2->card = card;
    myTree->leftPtr = leaf2;

    insertTreeHandNode(&yourTree, card);

    leaf5 = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[4], suit[0], 5, 1 }; // cinco de copas
    leaf5->card = card;
    leaf5->leftPtr = leaf5->rightPtr = NULL;
    leaf2->leftPtr = leaf5;

    insertTreeHandNode(&yourTree, card);

    leaf6 = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[12], suit[1], 13, 2 }; // rei de ouro
    leaf6->card = card;
    leaf6->leftPtr = leaf6->rightPtr = NULL;
    leaf2->rightPtr = leaf6;

    insertTreeHandNode(&yourTree, card);

    card = { face[10], suit[1], 11, 2 }; // valete de ouro
    insertTreeHandNode(&yourTree, card);

    IOrd(myTree, &expectedDeckHead, &expectedDeckTail);

    ListCardNodePtr actualDeckHead = NULL, actualDeckTail;
    IOrd(yourTree, &actualDeckHead, &actualDeckTail);

    ASSERT_TRUE(ListMatch(actualDeckHead, expectedDeckHead));
}

TEST(insertThreeHandNode, insertSixDifferentElementsAndTryThreeEqualIntoTheTree) {
    ListCardNodePtr expectedDeckHead = NULL, expectedDeckTail;
    Card card = { face[0], suit[2], 1, 3 }; // Ás de paus
    TreeCardNodePtr myTree = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    myTree->card = card;

    TreeCardNodePtr leaf1, leaf2, leaf3, leaf4, leaf5, leaf6;

    TreeCardNodePtr yourTree = NULL;
    insertTreeHandNode(&yourTree, card);

    leaf1 = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[2], suit[3], 3, 4 }; // Três de espadas
    leaf1->card = card;

    myTree->rightPtr = leaf1;

    insertTreeHandNode(&yourTree, card);

    leaf3 = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[3], suit[2], 4, 3 }; // Quatro de paus
    leaf3->card = card;
    leaf3->leftPtr = leaf3->rightPtr = NULL;
    leaf1->leftPtr = leaf3;

    insertTreeHandNode(&yourTree, card);

    leaf4 = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[8], suit[3], 9, 4 }; // Nove de espadas
    leaf4->card = card;
    leaf4->leftPtr = leaf4->rightPtr = NULL;
    leaf1->rightPtr = leaf4;

    insertTreeHandNode(&yourTree, card);

    leaf2 = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[10], suit[0], 11, 1 }; // valete de copas
    leaf2->card = card;
    myTree->leftPtr = leaf2;

    insertTreeHandNode(&yourTree, card);

    leaf5 = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[4], suit[0], 5, 1 }; // cinco de copas
    leaf5->card = card;
    leaf5->leftPtr = leaf5->rightPtr = NULL;
    leaf2->leftPtr = leaf5;

    insertTreeHandNode(&yourTree, card);

    leaf6 = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[12], suit[1], 13, 2 }; // rei de ouro
    leaf6->card = card;
    leaf6->leftPtr = leaf6->rightPtr = NULL;
    leaf2->rightPtr = leaf6;

    insertTreeHandNode(&yourTree, card);

    card = { face[10], suit[0], 11, 1 }; // valete de copas
    insertTreeHandNode(&yourTree, card);
    card = { face[8], suit[3], 9, 4 }; // Nove de espadas
    insertTreeHandNode(&yourTree, card);
    card = { face[12], suit[1], 13, 2 }; // rei de ouro
    insertTreeHandNode(&yourTree, card);

    IOrd(myTree, &expectedDeckHead, &expectedDeckTail);

    ListCardNodePtr actualDeckHead = NULL, actualDeckTail;
    IOrd(yourTree, &actualDeckHead, &actualDeckTail);

    ASSERT_TRUE(ListMatch(actualDeckHead, expectedDeckHead));
}

TEST(insertThreeHandNode, insertFourDifferentElementsToFormAnUmbalancedTree) {
    ListCardNodePtr expectedDeckHead = NULL, expectedDeckTail;
    Card card = { face[0], suit[0], 1, 1 }; // Ás de copas
    TreeCardNodePtr myTree = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    myTree->card = card;

    TreeCardNodePtr leaf1, leaf3, leaf4;

    TreeCardNodePtr yourTree = NULL;
    insertTreeHandNode(&yourTree, card);

    leaf1 = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[2], suit[2], 3, 3}; // Três de paus
    leaf1->card = card;

    myTree->rightPtr = leaf1;

    insertTreeHandNode(&yourTree, card);

    leaf3 = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[3], suit[1], 4, 2 }; // Quatro de ouro
    leaf3->card = card;
    leaf3->leftPtr = leaf3->rightPtr = NULL;
    leaf1->leftPtr = leaf3;

    insertTreeHandNode(&yourTree, card);

    leaf4 = (TreeCardNodePtr)malloc(sizeof(TreeCardNode));
    card = { face[8], suit[3], 9, 4 }; // Nove de espadas
    leaf4->card = card;
    leaf4->leftPtr = leaf4->rightPtr = NULL;
    leaf1->rightPtr = leaf4;

    insertTreeHandNode(&yourTree, card);

    myTree->leftPtr = NULL;

    IOrd(myTree, &expectedDeckHead, &expectedDeckTail);

    ListCardNodePtr actualDeckHead = NULL, actualDeckTail;
    IOrd(yourTree, &actualDeckHead, &actualDeckTail);

    ASSERT_TRUE(ListMatch(actualDeckHead, expectedDeckHead));
}

TEST(insertThreeHandNode, insertShuffled52FrDeckElementsIntoTheTree) {
    ListCardNodePtr orderedDeck = NULL;
    ReadFileOfOneFr52Deck(&orderedDeck);

    ListCardNodePtr shuffledDeck = NULL;
    readFileOfShuffledFr52Deck(&shuffledDeck);

    TreeCardNodePtr yourTree = NULL;
    ListCardNodePtr shuffledPtr = shuffledDeck;
    Card card;
    while (shuffledPtr != NULL) {
        card = shuffledPtr->card;
        insertTreeHandNode(&yourTree, card);
        shuffledPtr = shuffledPtr->nextPtr;
    }

    ListCardNodePtr actualDeckHead = NULL, actualDeckTail;
    IOrd(yourTree, &actualDeckHead, &actualDeckTail);

    ASSERT_TRUE(ListMatch(actualDeckHead, orderedDeck));
}
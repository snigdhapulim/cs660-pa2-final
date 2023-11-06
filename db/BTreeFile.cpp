#include <db/BTreeFile.h>
#include "db/BufferPool.h"
#include "db/Database.h"

using namespace db;

BTreeLeafPage *BTreeFile::findLeafPage(TransactionId tid, PagesMap &dirtypages, BTreePageId *pid, Permissions perm,
                                       const Field *f) {
    // TODO pa2.2: implement
    // BTreePage *currentPage = nullptr;
    //  BTreeLeafPage *leafPage = nullptr;
    //   BTreePageId *currentPageId=nullptr;

    // Start at the root of the B+ tree and traverse the tree
    //   while (true) {
    //   currentPage = static_cast<BTreePage *>(getPage(tid, dirtypages, pid , Permissions::READ_ONLY));

    // Check if we've reached a leaf page
    //  if (pid->getType() == BTreePageType::LEAF) {
    // Cast to BTreeLeafPage and return
//    leafPage = static_cast<BTreeLeafPage *>(currentPage);
    //   break;
    //   }
    //  BTreePageId *nextPid;


    // Find the appropriate child page using the IndexPredicate
    //   const IndexPredicate indexPredicate(Op::EQUALS, f);
    //   BTreePageId *childPid = currentPage->(indexPredicate);

    // Update the current page ID for the next iteration
    //   pid = childPid;
    //  }

    // Add the dirty pages to the list of dirty pages
//  dirtypages[pid] = leafPage;

    // return leafPage;

    return nullptr;
}

BTreeLeafPage *BTreeFile::splitLeafPage(TransactionId tid, PagesMap &dirtypages, BTreeLeafPage *page, const Field *field) {
    // TODO pa2.3: implement
    return nullptr;
}

BTreeInternalPage *BTreeFile::splitInternalPage(TransactionId tid, PagesMap &dirtypages, BTreeInternalPage *page,
                                                Field *field) {
    // TODO pa2.3: implement
    return nullptr;
}

void BTreeFile::stealFromLeafPage(BTreeLeafPage *page, BTreeLeafPage *sibling, BTreeInternalPage *parent,
                                  BTreeEntry *entry, bool isRightSibling) {
    // TODO pa2.4: implement (BONUS)
}

void BTreeFile::stealFromLeftInternalPage(TransactionId tid, PagesMap &dirtypages, BTreeInternalPage *page,
                                          BTreeInternalPage *leftSibling, BTreeInternalPage *parent,
                                          BTreeEntry *parentEntry) {
    // TODO pa2.4: implement (BONUS)
}

void BTreeFile::stealFromRightInternalPage(TransactionId tid, PagesMap &dirtypages, BTreeInternalPage *page,
                                           BTreeInternalPage *rightSibling, BTreeInternalPage *parent,
                                           BTreeEntry *parentEntry) {
    // TODO pa2.4: implement (BONUS)
}

void BTreeFile::mergeLeafPages(TransactionId tid, PagesMap &dirtypages, BTreeLeafPage *leftPage,
                               BTreeLeafPage *rightPage, BTreeInternalPage *parent, BTreeEntry *parentEntry) {
    // TODO pa2.4: implement (BONUS)
}

void BTreeFile::mergeInternalPages(TransactionId tid, PagesMap &dirtypages, BTreeInternalPage *leftPage,
                                   BTreeInternalPage *rightPage, BTreeInternalPage *parent, BTreeEntry *parentEntry) {
    // TODO pa2.4: implement (BONUS)
}

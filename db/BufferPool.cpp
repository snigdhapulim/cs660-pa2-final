#include <db/BufferPool.h>
#include <db/Database.h>
#include "db/SkeletonFile.h"

using namespace db;

void BufferPool::evictPage() {
    // TODO pa2.1: implement
    // If the pool is empty, nothing to evict
    if (pages.empty()) return;

    // Iterate over pages
    for (auto it = pages.begin(); it != pages.end(); ++it) {
        // If the page is dirty, write to disk
        if (it->second->isDirty()) {
            flushPage(&it->second->getId());
        }
        // Remove the page from the buffer pool
        pages.erase(it);
        // Evict only one page per call
        return;
    }
}

void BufferPool::flushAllPages() {
    // TODO pa2.1: implement
    for(auto &pair : pages) {
        flushPage(pair.first);
    }
}

void BufferPool::discardPage(const PageId *pid) {
    // TODO pa2.1: implement
    auto it = pages.find(pid);
    if (it != pages.end()) {
        // Remove the page from the PagesMap
        pages.erase(it);
    }
}

void BufferPool::flushPage(const PageId *pid) {
    // TODO pa2.1: implement

    auto it = pages.find(pid);
    if(it != pages.end()) {
        Page *page = it->second;
        if(page->isDirty()) {
            // Assuming we have a method to write a page to disk.
            // Write this page's data to disk.
            // This would involve filesystem operations.
            // writePageToDisk(page->getId(), page->getPageData());
            DbFile* file = Database::getCatalog().getDatabaseFile(pid->getTableId());

            // Call the writePage function of the file to write to disk
            file->writePage(page);
            page->markDirty(std::nullopt);
        }
    }
}

void BufferPool::flushPages(const TransactionId &tid) {
    // TODO pa2.1: implement
    for(auto &pair : pages) {
        Page *page = pair.second;
        if(page->isDirty() && page->isDirty() == tid) {
            flushPage(&(pair.second->getId()));
        }
    }
}

void BufferPool::insertTuple(const TransactionId &tid, int tableId, Tuple *t) {
    // TODO pa2.3: implement
}

void BufferPool::deleteTuple(const TransactionId &tid, Tuple *t) {
    // TODO pa2.3: implement
}

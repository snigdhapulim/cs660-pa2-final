#include <db/BufferPool.h>
#include <db/Database.h>
#include "db/SkeletonFile.h"
#include "db/BTreeLeafPage.h"


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

    PageId *pid = const_cast<PageId *>(t->getRecordId()->getPageId());
    Page *page = this->getPage( pid);

    // Try to insert the tuple into the page.
    if (page != nullptr) {
        // Cast the page to a BTreeLeafPage since we're dealing with B-Trees.
        BTreeLeafPage *leafPage = dynamic_cast<BTreeLeafPage*>(page);
        if (leafPage != nullptr) {
            // Insert the tuple.
            try {
                leafPage->deleteTuple(t); // Assume deleteTuple throws an exception on failure.

                // Mark the page as dirty instead of flushing it immediately.
                page->markDirty(tid); // This method should be implemented to mark the page as dirty.
            } catch (const std::exception &e) {
                throw std::runtime_error("Insertion failed: No space on page");
            }
        } else {
            throw std::runtime_error("Page is not a BTreeLeafPage");
        }
    } else {
        throw std::runtime_error("Page not found in BufferPool");
    }

}

void BufferPool::deleteTuple(const TransactionId &tid, Tuple *t) {
    // TODO pa2.3: implement
    PageId *pid = const_cast<PageId *>(t->getRecordId()->getPageId());  // Assume getRecordId().getPageId() returns a PageId, not a pointer.
    Page *page = this->getPage(pid); // Permissions assumed to be a part of method signature.

    // Try to delete the tuple from the page.
    if (page != nullptr) {
        // Cast the page to a BTreeLeafPage.
        BTreeLeafPage *leafPage = dynamic_cast<BTreeLeafPage*>(page);
        if (leafPage != nullptr) {
            // Delete the tuple.
            try {
                leafPage->deleteTuple(t); // Assume deleteTuple throws an exception on failure.

                // Mark the page as dirty instead of flushing it immediately.
                page->markDirty(tid); // This method should be implemented to mark the page as dirty.
            } catch (const std::exception &e) {
                // Handle the exception if deleteTuple fails and throws an exception.
                throw std::runtime_error("Deletion failed: ");
            }
        } else {
            throw std::runtime_error("Page is not a BTreeLeafPage");
        }
    } else {
        throw std::runtime_error("Page not found in BufferPool");
    }
}

## Buffer Pool Operations Brief

### Eviction Policy
A First-In-First-Out (FIFO) policy is employed for page eviction. The eviction mechanism removes the earliest page loaded into the buffer that has not yet been evicted. If the page is dirty, it is flushed to disk before eviction.

### Method Implementations
`evictPage`: Adhering to FIFO, this method evicts the oldest page from the pool after potentially flushing it to disk if it is dirty.

`flushAllPages`: Executes a disk flush for all dirty pages in the buffer pool without evicting them.

`discardPage`: Discards a specific page by PageId from the pool, without flushing it to disk.

`flushPage`: Flushes a given page to disk if it's dirty and marks it as not dirty.

`flushPages`: Flushes pages associated with a specific transaction ID, ensuring data integrity for transactions.

### Eviction Strategy Commentary
The FIFO approach is straightforward but may not be optimal for all workloads. A more sophisticated system might use an LRU (Least Recently Used) or LFU (Least Frequently Used) strategy, which could potentially enhance performance by considering the access patterns and frequency of page usage.

The FIFO eviction policy is implemented, with other operations designed to flush pages without eviction as per the specifications. Although the FIFO method is basic, it serves the foundational needs of the assignment. Future work could explore more advanced eviction policies like LRU or LFU for improved efficiency.






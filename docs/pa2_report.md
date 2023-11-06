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

## Exercise 2: Find Leaf Page Implementation

### Predicate and IndexPredicate Class Implementations
Predicate Class:
The Predicate class serves as a base class for creating a comparison operation that can be applied to the entries of the tree.

Implemented Methods:
`Predicate::Predicate`:
This is the constructor that initializes the predicate with the necessary operands and comparison operation.

`Predicate::getField`:
Retrieves the field index of the table on which the predicate will operate.

`Predicate::getOp`:
Returns the comparison operator of the predicate.

`Predicate::getOperand`:
Obtains the operand against which the table field values will be compared.

`Predicate::filter`:
Applies the predicate to a given value to determine if it meets the condition.

IndexPredicate Class:
IndexPredicate is a specialized version of Predicate that is tailored for index entries.

Implemented Methods:
`IndexPredicate::IndexPredicate`:
The constructor initializes the index predicate with the specific field and value for comparison.

`IndexPredicate::getField and IndexPredicate::getOp`:
These methods override the Predicate class methods, providing field and operator specific to index entries.

`IndexPredicate::operator==`:
Overloads the equality operator to compare two IndexPredicate objects for equality.

std::hash<IndexPredicate> Specialization:
A specialization of std::hash is implemented for IndexPredicate to allow its objects to be used in hash-based containers like unordered_map.

Implemented Method:
`std::hash<IndexPredicate>::operator()`: Defines the hash function for IndexPredicate objects.
`BTreeFile::findLeafPage`is a critical method responsible for navigating the B+ tree to find the leaf page corresponding to a given key.

### Key Features Implemented:
Traversal from the root to the correct leaf by comparing entry keys using IndexPredicate.
Handling cases where the key is not provided by moving to the left-most child to find the left-most leaf page.
Fetching pages from the buffer pool with appropriate permission levels (READ_ONLY for internal pages, specific permissions for leaf pages).
Utilization of the `BTreeFile::getPage` wrapper function to track dirty pages.




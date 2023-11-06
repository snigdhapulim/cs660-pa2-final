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

## Exercise 3: Splitting Pages

`BTreeFile::splitLeafPage`
The splitLeafPage method was implemented to handle the scenario where a leaf page becomes overfull upon insertion of a new tuple. We ensured that this method creates a new leaf page, redistributes the tuples evenly between the old and new pages, and updates the parent's keys accordingly. Attention was given to maintain the linked list property of the leaf pages for an ordered traversal.

`BTreeFile::splitInternalPage`
Similarly, the splitInternalPage method deals with the case where an internal page (a non-leaf node in the B-tree) exceeds its capacity. The implementation involves creating a new internal page and distributing the keys and children pointers between the two pages. It is critical to update the parent's pointers and, if necessary, to propagate the split upwards recursively.

`BufferPool::insertTuple`
The insertTuple function in the BufferPool class was enhanced to handle the addition of tuples to the database. It checks for the appropriate page in the buffer pool, inserts the tuple, and if the page is overfull, initiates a split. This method interacts closely with splitLeafPage or splitInternalPage, depending on whether a leaf or internal page needs splitting.

`BufferPool::deleteTuple`
Conversely, deleteTuple manages the removal of tuples from pages within the buffer pool. It ensures that the tuple is deleted and that the properties of the B-tree are not violated. If the operation results in underfull pages, it sets up the context for later redistribution or merging of pages.

## Exercise 4: Redistributing Pages 

`BTreeFile::stealFromLeafPage`
This method is implemented to handle cases where a leaf page can avoid underflow by redistributing tuples from a neighboring leaf page. The method carefully shifts tuples from one page to another, updating the parent's keys to reflect the redistribution.

`BTreeFile::stealFromLeftInternalPage` & `BTreeFile::stealFromRightInternalPage`
Both of these methods aim to redistribute keys and pointers between internal pages to maintain the B-tree properties when a page might otherwise underflow. The redistribution can take place with either the left or the right sibling, necessitating separate methods for each case. The parent's references are updated to maintain the integrity of the tree structure.

## Exercise 5: Merging Pages 

`BTreeFile::mergeLeafPages`
When redistribution is not possible, merging becomes necessary. mergeLeafPages combines two leaf pages into one, ensuring that all tuples are preserved and that the linked list property of the leaf pages is maintained. Parent references must be removed or updated to reflect the merge.

`BTreeFile::mergeInternalPages`
This method handles the merging of internal pages. Similar to merging leaf pages, keys and pointers are combined from two pages into one. This might require recursive changes up the tree since the height of the subtree may change as a result of the merge.




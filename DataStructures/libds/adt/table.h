#pragma once

#include <libds/adt/abstract_data_type.h>
#include <libds/amt/implicit_sequence.h>
#include <libds/amt/explicit_hierarchy.h>
#include <functional>
#include <random>


namespace ds::adt {

    template <typename K, typename T>
    struct TableItem
    {
        K key_;
        T data_;
        ImplicitList<T>* elements_;

        bool operator==(const TableItem<K, T>& other) const
        {
            return key_ == other.key_ && data_ == other.data_;
        }

        bool operator!=(const TableItem<K, T>& other) const
        {
            return !(*this == other);
        }
    };

    template <typename K, typename T>
    using TabItem = TableItem<K, T>;

    //----------

    template <typename K, typename T>
    class Table :
        virtual public ADT
    {
    public:
        virtual void insert(K key, T data) = 0;
        virtual T& find(K key);
        virtual bool tryFind(K key, T*& data) = 0;
        virtual bool contains(K key);
        virtual T remove(K key) = 0;
    };

    //----------

    template <typename K, typename T, typename SequenceType>
    class SequenceTable :
        public Table<K, T>,
        public ADS<TabItem<K, T>>
    {
    public:
        SequenceTable();
        SequenceTable(const SequenceTable& other);

        bool tryFind(K key, T*& data) override;

    public:
        using BlockType = typename SequenceType::BlockType;
        using IteratorType = typename SequenceType::IteratorType;

        virtual BlockType* findBlockWithKey(K key) = 0;

        IteratorType begin();
        IteratorType end();

    protected:
        SequenceType* getSequence();
    };

    //----------

    template <typename K, typename T, typename SequenceType>
    class UnsortedSequenceTable :
        public SequenceTable<K, T, SequenceType>
    {
    protected:
        typename SequenceType::BlockType* findBlockWithKey(K key) override;
    };

    template <typename K, typename T, typename SequenceType>
    using UnsortedSTab = UnsortedSequenceTable<K, T, SequenceType>;

    //----------

    template <typename K, typename T>
    class UnsortedImplicitSequenceTable :
        public UnsortedSequenceTable<K, T, amt::IS<TabItem<K, T>>>
    {
    public:
        void insert(K key, T data) override;
        T remove(K key) override;

    private:
        using BlockType = typename amt::IS<TabItem<K, T>>::BlockType;
    };

    template <typename K, typename T>
    using UnsortedISTab = UnsortedImplicitSequenceTable<K, T>;

    //----------

    template <typename K, typename T>
    class UnsortedExplicitSequenceTable :
        public UnsortedSequenceTable<K, T, amt::SinglyLS<TabItem<K, T>>>
    {
    public:
        void insert(K key, T data) override;
        T remove(K key) override;

    private:
        using BlockType = typename amt::SinglyLS<TabItem<K, T>>::BlockType;
    };

    template <typename K, typename T>
    using UnsortedESTab = UnsortedExplicitSequenceTable<K, T>;

    //----------

    template <typename K, typename T>
    class SortedSequenceTable :
        public SequenceTable<K, T, amt::IS<TabItem<K, T>>>
    {
    public:
        void insert(K key, T data) override;
        T remove(K key) override;

    protected:
        using BlockType = typename amt::IS<TabItem<K, T>>::BlockType;

        BlockType* findBlockWithKey(K key) override;

    private:
        bool tryFindBlockWithKey(K key, size_t firstIndex, size_t lastIndex, BlockType*& lastBlock);
    };

    template <typename K, typename T>
    using SortedSTab = SortedSequenceTable<K, T>;

    //----------

    template <typename K, typename T>
    class HashTable :
        public Table<K, T>,
        public AUMS<TabItem<K, T>>
    {
    public:
        using HashFunctionType = std::function<size_t(K)>;

    public:
        HashTable();
        HashTable(const HashTable& other);
        HashTable(HashFunctionType hashFunction, size_t capacity);
        ~HashTable();

        ADT& assign(const ADT& other) override;
        bool equals(const ADT& other) override;
        void clear() override;
        size_t size() const override;
        bool isEmpty() const override;

        void insert(K key, T data) override;
        bool tryFind(K key, T*& data) override;
        T remove(K key) override;

    private:
        using SynonymTable = UnsortedESTab<K, T>;
        using SynonymTableIterator = typename SynonymTable::IteratorType;
        using PrimaryRegionIterator = typename amt::IS<SynonymTable*>::IteratorType;

    private:
        static const size_t CAPACITY = 100;

    private:
        amt::IS<SynonymTable*>* primaryRegion_;
        HashFunctionType hashFunction_;
        size_t size_;

    public:
        class HashTableIterator
        {
        public:
            HashTableIterator(PrimaryRegionIterator* tablesFirst, PrimaryRegionIterator* tablesLast);
            HashTableIterator(const HashTableIterator& other);
            ~HashTableIterator();
            HashTableIterator& operator++();
            HashTableIterator operator++(int);
            bool operator==(const HashTableIterator& other) const;
            bool operator!=(const HashTableIterator& other) const;
            TabItem<K, T>& operator*();

        private:
            PrimaryRegionIterator* tablesCurrent_;
            PrimaryRegionIterator* tablesLast_;
            SynonymTableIterator* synonymIterator_;
        };
        using IteratorType = HashTableIterator;

        HashTableIterator begin() const
        {
            return HashTableIterator(new PrimaryRegionIterator(primaryRegion_->begin()), new PrimaryRegionIterator(primaryRegion_->end()));
        }

        HashTableIterator end() const
        {
            return HashTableIterator(new PrimaryRegionIterator(primaryRegion_->end()), new PrimaryRegionIterator(primaryRegion_->end()));
        }
    };

    //----------

    template <typename K, typename T, typename BlockType>
    class GeneralBinarySearchTree :
        public Table<K, T>,
        public ADS<TabItem<K, T>>
    {
    public:
        using IteratorType = typename amt::BinaryEH<BlockType>::IteratorType;

    public:
        GeneralBinarySearchTree();
        GeneralBinarySearchTree(const GeneralBinarySearchTree& other);
        ~GeneralBinarySearchTree();

        size_t size() const override;
        bool isEmpty() const override;
        void clear() override;

        void insertWithDuplicities(K key, T data);
        bool tryFindWithDuplicities(K key, T*& data, ImplicitList<T>*& other_elements);

        void insert(K key, T data) override;
        bool tryFind(K key, T*& data) override;
        T remove(K key) override;

        IteratorType begin() const;
        IteratorType end() const;

    protected:
        using BVSNodeType = typename amt::BinaryEH<BlockType>::BlockType;

        amt::BinaryEH<BlockType>* getHierarchy() const;

        virtual void removeNode(BVSNodeType* node);
        virtual void balanceTree(BVSNodeType* node) { }

        bool tryFindNodeWithKey(K key, BVSNodeType*& node) const;

        void rotateLeft(BVSNodeType* node);
        void rotateRight(BVSNodeType* node);

    private:
        size_t size_;
    };

    //----------

    template <typename K, typename T>
    class BinarySearchTree :
        public GeneralBinarySearchTree<K, T, TabItem<K, T>>
    {
    };

    //----------

    template <typename K, typename T>
    struct TreapItem :
        public TabItem<K, T>
    {
        int priority_;
    };

    template <typename K, typename T>
    class Treap :
        public GeneralBinarySearchTree<K, T, TreapItem<K, T>>
    {
    public:
        Treap();

    protected:
        using BVSNodeType = typename GeneralBinarySearchTree<K, T, TreapItem<K, T>>::BVSNodeType;

        void removeNode(BVSNodeType* node) override;
        void balanceTree(BVSNodeType* node) override;

    private:
        // generator cisel
        std::default_random_engine rng_;
    };

    //----------

    template<typename K, typename T>
    T& Table<K, T>::find(K key)
    {
        T* data = nullptr;
        if (!this->tryFind(key, data))
        {
            throw std::out_of_range("No such key!");
        }
        return *data;
    }

    template<typename K, typename T>
    bool Table<K, T>::contains(K key)
    {
        T* data = nullptr;
        return this->tryFind(key, data);
    }

    //----------

    template<typename K, typename T, typename SequenceType>
    SequenceTable<K, T, SequenceType>::SequenceTable() :
        ADS<TabItem<K, T>>(new SequenceType())
    {
    }

    template<typename K, typename T, typename SequenceType>
    SequenceTable<K, T, SequenceType>::SequenceTable(const SequenceTable& other) :
        ADS<TabItem<K, T>>(new SequenceType(), other)
    {
    }

    template<typename K, typename T, typename SequenceType>
    bool SequenceTable<K, T, SequenceType>::tryFind(K key, T*& data)
    {
        BlockType* blockWithKey = this->findBlockWithKey(key);
        if (blockWithKey == nullptr)
        {
            return false;
        }
        data = &blockWithKey->data_.data_;
        return true;
    }

    template <typename K, typename T, typename SequenceType>
    auto SequenceTable<K, T, SequenceType>::begin() -> IteratorType
    {
        return this->getSequence()->begin();
    }

    template <typename K, typename T, typename SequenceType>
    auto SequenceTable<K, T, SequenceType>::end() -> IteratorType
    {
        return this->getSequence()->end();
    }

    template<typename K, typename T, typename SequenceType>
    SequenceType* SequenceTable<K, T, SequenceType>::getSequence()
    {
        return dynamic_cast<SequenceType*>(this->memoryStructure_);
    }

    //----------

    template<typename K, typename T, typename SequenceType>
    typename SequenceType::BlockType* UnsortedSequenceTable<K, T, SequenceType>::findBlockWithKey(K key)
    {
        return this->getSequence()->findBlockWithProperty([&key](typename SequenceType::BlockType* b) ->bool
            {
                return b->data_.key_ == key;
            });
    }

    //----------

    template<typename K, typename T>
    void UnsortedImplicitSequenceTable<K, T>::insert(K key, T data)
    {
        if (this->contains(key))
        {
            throw std::logic_error("Table already contains element associated with given key!");
        }

        TabItem<K, T>& tableItem = this->getSequence()->insertLast().data_;
        tableItem.key_ = key;
        tableItem.data_ = data;
    }

    template<typename K, typename T>
    T UnsortedImplicitSequenceTable<K, T>::remove(K key)
    {
        BlockType* blockWithKey = this->findBlockWithKey(key);

        if (blockWithKey == nullptr)
        {
            throw std::out_of_range("No such key!");
        }

        T result = blockWithKey->data_.data_;
        BlockType* lastBlock = this->getSequence()->accessLast();
        if (blockWithKey != lastBlock)
        {
            std::swap(blockWithKey->data_, lastBlock->data_);
        }
        this->getSequence()->removeLast();
        return result;
    }

    //----------

    template<typename K, typename T>
    void UnsortedExplicitSequenceTable<K, T>::insert(K key, T data)
    {
        if (this->contains(key))
        {
            throw std::logic_error("Table already contains element associated with given key!");
        }

        TabItem<K, T>& tableItem = this->getSequence()->insertFirst().data_;
        tableItem.key_ = key;
        tableItem.data_ = data;
    }

    template<typename K, typename T>
    T UnsortedExplicitSequenceTable<K, T>::remove(K key)
    {
        BlockType* blockWithKey = this->findBlockWithKey(key);

        if (blockWithKey == nullptr)
        {
            throw std::out_of_range("No such key!");
        }

        T result = blockWithKey->data_.data_;
        BlockType* firstBlock = this->getSequence()->accessFirst();
        if (blockWithKey != firstBlock)
        {
            using std::swap;
            swap(blockWithKey->data_, firstBlock->data_);
        }
        this->getSequence()->removeFirst();
        return result;
    }

    //----------


    template<typename K, typename T>
    void SortedSequenceTable<K, T>::insert(K key, T data)
    {
        TabItem<K, T>* tableItem;

        if (this->isEmpty())
        {
            tableItem = &this->getSequence()->insertFirst().data_;
        }
        else
        {
            BlockType* blok = nullptr;
            if (this->tryFindBlockWithKey(key, 0, this->size(), blok))
            {
                throw std::logic_error("Duplicate key!");
            }
            tableItem = key > blok->data_.key_
                ? &this->getSequence()->insertAfter(*blok).data_
                : &this->getSequence()->insertBefore(*blok).data_;
        }

        tableItem->key_ = key;
        tableItem->data_ = data;
    }

    template<typename K, typename T>
    T SortedSequenceTable<K, T>::remove(K key)
    {
        BlockType* blockWithKey = nullptr;
        if (!this->tryFindBlockWithKey(key, 0, this->size(), blockWithKey))
        {
            throw std::out_of_range("No such key!");
        }

        T result = blockWithKey->data_.data_;
        if (this->getSequence()->accessFirst() == blockWithKey)
        {
            this->getSequence()->removeFirst();
        }
        else
        {
            this->getSequence()->removeNext(*this->getSequence()->accessPrevious(*blockWithKey));
        }
        return result;
    }

    template<typename K, typename T>
    auto SortedSequenceTable<K, T>::findBlockWithKey(K key) -> BlockType*
    {
        BlockType* blockWithKey = nullptr;
        return this->tryFindBlockWithKey(key, 0, this->size(), blockWithKey)
            ? blockWithKey
            : nullptr;
    }

    template<typename K, typename T>
    bool SortedSequenceTable<K, T>::tryFindBlockWithKey(K key, size_t firstIndex, size_t lastIndex, BlockType*& lastBlock)
    {
        if (this->isEmpty())
        {
            lastBlock = nullptr;
            return false;
        }

        size_t midIndex = firstIndex;
        while (firstIndex < lastIndex)
        {
            midIndex = firstIndex + (lastIndex - firstIndex) / 2;
            lastBlock = this->getSequence()->access(midIndex);

            if (lastBlock->data_.key_ < key)
            {
                firstIndex = midIndex + 1;
            }
            else if (lastBlock->data_.key_ > key)
            {
                lastIndex = midIndex;
            }
            else
            {
                break;
            }
        }

        lastBlock = this->getSequence()->access(midIndex);
        return lastBlock->data_.key_ == key;
    }

    //----------

    template<typename K, typename T>
    HashTable<K, T>::HashTable() :
        HashTable([](K key) { return std::hash<K>()(key); }, CAPACITY)
    {
    }

    template <typename K, typename T>
    HashTable<K, T>::HashTable(const HashTable& other) :
        primaryRegion_(new amt::IS<SynonymTable*>(other.primaryRegion_->size(), true)),
        hashFunction_(other.hashFunction_),
        size_(0)
    {
        assign(other);
    }

    template<typename K, typename T>
    HashTable<K, T>::HashTable(HashFunctionType hashFunction, size_t capacity) :
        primaryRegion_(new amt::IS<SynonymTable*>(capacity, true)),
        hashFunction_(hashFunction),
        size_(0)
    {
    }

    template <typename K, typename T>
    HashTable<K, T>::~HashTable()
    {
        this->clear();
        delete primaryRegion_;
    }

    template <typename K, typename T>
    ADT& HashTable<K, T>::assign(const ADT& other)
    {
        if (this != &other)
        {
            const HashTable& otherTable = dynamic_cast<const HashTable&>(other);
            this->clear();
            for (TabItem<K, T>& otherItem : otherTable)
            {
                this->insert(otherItem.key_, otherItem.data_);
            }
        }

        return *this;
    }

    template <typename K, typename T>
    bool HashTable<K, T>::equals(const ADT& other)
    {
        if (this == &other) { return true; }
        if (this->size() != other.size()) { return false; }

        const HashTable& otherTable = dynamic_cast<const HashTable&>(other);
        for (TabItem<K, T>& otherItem : otherTable)
        {
            T* otherData = nullptr;
            if (!this->tryFind(otherItem.key_, otherData) || *otherData != otherItem.data_)
            {
                return false;
            }
        }
        return true;
    }

    template <typename K, typename T>
    void HashTable<K, T>::clear()
    {
        size_ = 0;
        primaryRegion_->processAllBlocksForward([](typename amt::IS<SynonymTable*>::BlockType* blokSynoným)
            {
                delete blokSynoným->data_;
                blokSynoným->data_ = nullptr;
            });
    }

    template <typename K, typename T>
    size_t HashTable<K, T>::size() const
    {
        return size_;
    }

    template <typename K, typename T>
    bool HashTable<K, T>::isEmpty() const
    {
        return size() == 0;
    }

    template <typename K, typename T>
    void HashTable<K, T>::insert(K key, T data)
    {
        int index = hashFunction_(key) % primaryRegion_->size();
        SynonymTable* synonyms = primaryRegion_->access(index)->data_;

        if (synonyms == nullptr)
        {
            synonyms = new SynonymTable();
            primaryRegion_->access(index)->data_ = synonyms;
        }

        synonyms->insert(key, data);
        ++this->size_;
    }

    template <typename K, typename T>
    bool HashTable<K, T>::tryFind(K key, T*& data)
    {
        int index = hashFunction_(key) % primaryRegion_->size();
        SynonymTable* synonyms = primaryRegion_->access(index)->data_;

        if (synonyms == nullptr)
        {
            return false;
        }

        return synonyms->tryFind(key, data);
    }

    template <typename K, typename T>
    T HashTable<K, T>::remove(K key)
    {
        int index = hashFunction_(key) % primaryRegion_->size();
        SynonymTable* synonyms = primaryRegion_->access(index)->data_;

        if (synonyms == nullptr)
        {
            this->error("HashTable<K, T>::remove Item with key does not exist");
        }

        T block = synonyms->remove(key);
        if (synonyms->isEmpty())
        {
            delete synonyms;
            primaryRegion_->access(index)->data_ = nullptr;
        }
        --this->size_;
        return block;
    }

    template <typename K, typename T>
    HashTable<K, T>::HashTableIterator::HashTableIterator
    (PrimaryRegionIterator* tablesFirst, PrimaryRegionIterator* tablesLast) :
        tablesCurrent_(tablesFirst),
        tablesLast_(tablesLast)
    {
        while (*tablesCurrent_ != *tablesLast_ && **tablesCurrent_ == nullptr)
        {
            ++(*tablesCurrent_);
        }
        synonymIterator_ = *tablesCurrent_ != *tablesLast_
            ? new SynonymTableIterator((**tablesCurrent_)->begin())
            : nullptr;
    }

    template <typename K, typename T>
    HashTable<K, T>::HashTableIterator::HashTableIterator
    (const HashTableIterator& other) :
        tablesCurrent_(new PrimaryRegionIterator(*other.tablesCurrent_)),
        tablesLast_(new PrimaryRegionIterator(*other.tablesLast_)),
        synonymIterator_(other.synonymIterator_ != nullptr
            ? new SynonymTableIterator(*other.synonymIterator_)
            : nullptr

        )
    {
    }

    template <typename K, typename T>
    HashTable<K, T>::HashTableIterator::~HashTableIterator()
    {
        delete tablesCurrent_;
        delete tablesLast_;
        delete synonymIterator_;
    }

    template <typename K, typename T>
    auto HashTable<K, T>::HashTableIterator::operator++() -> HashTableIterator&
    {
        //TODO nefunguje
        ++synonymIterator_;

        auto last_el = SynonymTableIterator((**tablesCurrent_)->end());

        if (*synonymIterator_ == last_el)
        {
            do
            {
                ++tablesCurrent_;
            } while (*tablesCurrent_ != *tablesLast_ && **tablesCurrent_ == nullptr);

            delete synonymIterator_;
            synonymIterator_ = nullptr;

            if (*tablesCurrent_ != *tablesLast_)
            {
                synonymIterator_ = new SynonymTableIterator((**tablesCurrent_)->begin());
            }
        }

        return *this;
    }

    template <typename K, typename T>
    auto HashTable<K, T>::HashTableIterator::operator++(int) -> HashTableIterator
    {
        HashTableIterator tmp(*this);
        operator++();
        return tmp;
    }

    template <typename K, typename T>
    bool HashTable<K, T>::HashTableIterator::operator==(const HashTableIterator& other) const
    {
        return synonymIterator_ == other.synonymIterator_ ||
            (synonymIterator_ != nullptr &&
                other.synonymIterator_ != nullptr &&
                *synonymIterator_ == *(other.synonymIterator_));
    }

    template <typename K, typename T>
    bool HashTable<K, T>::HashTableIterator::operator!=(const HashTableIterator& other) const
    {
        return !(*this == other);
    }

    template <typename K, typename T>
    TabItem<K, T>& HashTable<K, T>::HashTableIterator::operator*()
    {
        return (**synonymIterator_);
    }

    //----------

    template<typename K, typename T, typename BlockType>
    GeneralBinarySearchTree<K, T, BlockType>::GeneralBinarySearchTree() :
        ADS<TabItem<K, T>>(new amt::BinaryEH<BlockType>()),
        size_(0)
    {
    }

    template<typename K, typename T, typename BlockType>
    GeneralBinarySearchTree<K, T, BlockType>::GeneralBinarySearchTree(const GeneralBinarySearchTree& other) :
        ADS<TabItem<K, T>>(new amt::BinaryEH<BlockType>(), other),
        size_(other.size_)
    {
    }

    template<typename K, typename T, typename BlockType>
    GeneralBinarySearchTree<K, T, BlockType>::~GeneralBinarySearchTree()
    {
        size_ = 0;

    }

    template<typename K, typename T, typename BlockType>
    size_t GeneralBinarySearchTree<K, T, BlockType>::size() const
    {
        return size_;
    }

    template<typename K, typename T, typename BlockType>
    bool GeneralBinarySearchTree<K, T, BlockType>::isEmpty() const
    {
        return size_ == 0;
    }

    template <typename K, typename T, typename BlockType>
    void GeneralBinarySearchTree<K, T, BlockType>::clear()
    {
        this->getHierarchy()->clear();
        this->size_ = 0;
    }

    // Specialna metoda pre vkladanie prvkov s rovnakym klucom
    template<typename K, typename T, typename BlockType>
    void GeneralBinarySearchTree<K, T, BlockType>::insertWithDuplicities(K key, T data)
    {
        BVSNodeType* node = nullptr;

        if (this->tryFindNodeWithKey(key, node))
        {
           (*node).data_.elements_->insertLast(data);
        }
        else if (node != nullptr)
        {
            BVSNodeType* newNode = key > node->data_.key_
                ? &this->getHierarchy()->insertRightSon(*node)
                : &this->getHierarchy()->insertLeftSon(*node);

            newNode->data_ = { key,data, new ImplicitList<T> };
            this->size_++;
            this->balanceTree(newNode);
        }
        else
        {
            this->getHierarchy()->emplaceRoot().data_ = { key,data, new ImplicitList<T> };
            this->size_++;
        }
    }

    // Specialna metoda pre najdenie prvkov s rovnakym klucom
    template<typename K, typename T, typename BlockType>
    bool GeneralBinarySearchTree<K, T, BlockType>::tryFindWithDuplicities(K key, T*& data, ImplicitList<T>*& other_elements)
    {
        BVSNodeType* nodeWithKey = nullptr;
        if (!this->tryFindNodeWithKey(key, nodeWithKey))
        {
            return false;
        }
        data = &nodeWithKey->data_.data_;
        other_elements = nodeWithKey->data_.elements_;
        return true;
    }



    template<typename K, typename T, typename BlockType>
    void GeneralBinarySearchTree<K, T, BlockType>::insert(K key, T data)
    {
        //BVSNodeType* newNode = nullptr;
        //if (this->isEmpty())
        //{
        //    newNode = &this->getHierarchy()->emplaceRoot();
        //}
        //else
        //{
        //    BVSNodeType* parent = nullptr;
        //    if (this->tryFindNodeWithKey(key, parent))
        //    {
        //        throw std::logic_error("Table already contains an element associated with given key!");
        //    }
        //    newNode = key > parent->data_.key_
        //        ? &this->getHierarchy()->insertRightSon(*parent)
        //        : &this->getHierarchy()->insertLeftSon(*parent);
        //}

        //newNode->data_.key_ = key;
        //newNode->data_.data_ = data;

        //++size_;
        //this->balanceTree(newNode);


        BVSNodeType* node = nullptr;

        if (this->tryFindNodeWithKey(key, node))
        {
            this->error("GeneralBinarySearchTree<K, T, BlockType>::insert(K key, T data) : Key already exists in table!");
        }
        else if (node != nullptr)
        {
            BVSNodeType* newNode =  key > node->data_.key_
                ? &this->getHierarchy()->insertRightSon(*node)
                : &this->getHierarchy()->insertLeftSon(*node);

            newNode->data_ = { key,data };
            this->size_++;
            this->balanceTree(newNode);
        }
        else
        {
            this->getHierarchy()->emplaceRoot().data_ = { key,data };
            this->size_++;
        }

    }

    template<typename K, typename T, typename BlockType>
    bool GeneralBinarySearchTree<K, T, BlockType>::tryFind(K key, T*& data)
    {
        BVSNodeType* nodeWithKey = nullptr;
        if (!this->tryFindNodeWithKey(key, nodeWithKey))
        {
            return false;
        }
        data = &nodeWithKey->data_.data_;
        return true;
    }

    template<typename K, typename T, typename BlockType>
    T GeneralBinarySearchTree<K, T, BlockType>::remove(K key)
    {
        BVSNodeType* nodeWithKey = nullptr;
        if (!this->tryFindNodeWithKey(key, nodeWithKey))
        {
            throw std::out_of_range("No such key!");
        }

        T result = nodeWithKey->data_.data_;
        this->removeNode(nodeWithKey);
        size_--;
        return result;
    }

    template <typename K, typename T, typename BlockType>
    auto GeneralBinarySearchTree<K, T, BlockType>::begin() const -> IteratorType
    {
        return this->getHierarchy()->begin();
    }

    template <typename K, typename T, typename BlockType>
    auto GeneralBinarySearchTree<K, T, BlockType>::end() const -> IteratorType
    {
        return this->getHierarchy()->end();
    }

    template<typename K, typename T, typename BlockType>
    amt::BinaryEH<BlockType>* GeneralBinarySearchTree<K, T, BlockType>::getHierarchy() const
    {
        return dynamic_cast<amt::BinaryEH<BlockType>*>(this->memoryStructure_);
    }

    template<typename K, typename T, typename BlockType>
    void GeneralBinarySearchTree<K, T, BlockType>::removeNode(BVSNodeType* node)
    {
        BVSNodeType* parent = static_cast<ds::amt::BinaryExplicitHierarchyBlock<BlockType>*>(node->parent_);


        switch (getHierarchy()->degree(*node))
        {
        case 0:
        {
            if (getHierarchy()->isRoot(*node))
            {
                getHierarchy()->clear();
            }
            else
            {
                if (getHierarchy()->isLeftSon(*node))
                {
                    getHierarchy()->removeLeftSon(*parent);
                }
                else
                {
                    getHierarchy()->removeRightSon(*parent);
                }
            }
        }
        break;
        case 1:
        {
            BVSNodeType* son = getHierarchy()->hasLeftSon(*node) ? node->left_ : node->right_;
            if (node->left_ == son)
            {
                getHierarchy()->changeLeftSon(*node, nullptr);
            }
            else
            {
                getHierarchy()->changeRightSon(*node, nullptr);
            }

            if (getHierarchy()->isRoot(*node))
            {
                getHierarchy()->clear();
                getHierarchy()->changeRoot(son);
            }
            else
            {
                if (parent->left_ == node)
                {
                    getHierarchy()->removeLeftSon(*parent);
                    getHierarchy()->changeLeftSon(*parent, son);
                }
                else
                {
                    getHierarchy()->removeRightSon(*parent);
                    getHierarchy()->changeRightSon(*parent, son);
                }
            }
        }
        break;
        case 2:
        {
            BVSNodeType* previous_inorder = node->left_;
            while (getHierarchy()->hasRightSon(*previous_inorder))
            {
                previous_inorder = previous_inorder->right_;
            }
            std::swap(node->data_, previous_inorder->data_);
            removeNode(previous_inorder);
        }
        break;
        }
    }

    template<typename K, typename T, typename BlockType>
    bool GeneralBinarySearchTree<K, T, BlockType>::tryFindNodeWithKey(K key, BVSNodeType*& node) const
    {
        BVSNodeType* cur = this->getHierarchy()->accessRoot();

        while (cur != nullptr)
        {
            if (key == cur->data_.key_)
            {
                node = cur;
                return true;
            }
            else if (key < cur->data_.key_)
            {
                BVSNodeType* lSon = this->getHierarchy()->accessLeftSon(*cur);
                if (lSon != nullptr)
                {
                    cur = this->getHierarchy()->accessLeftSon(*cur);
                }
                else
                {
                    node = cur;
                    return false;
                }
            }
            else
            {
                BVSNodeType* rSon = this->getHierarchy()->accessRightSon(*cur);
                if (rSon != nullptr)
                {
                    cur = this->getHierarchy()->accessRightSon(*cur);
                }
                else
                {
                    node = cur;
                    return false;
                }
            }
        }
        node = nullptr;
        return false;
    }

    template<typename K, typename T, typename BlockType>
    void GeneralBinarySearchTree<K, T, BlockType>::rotateLeft(BVSNodeType* node)
    {
        BVSNodeType* left_son = node->left_;
        BVSNodeType* parent = static_cast<ds::amt::BinaryExplicitHierarchyBlock<BlockType>*>(node->parent_);
        BVSNodeType* grand_parent = static_cast<ds::amt::BinaryExplicitHierarchyBlock<BlockType>*>(parent->parent_);

        this->getHierarchy()->changeRightSon(*parent, nullptr);
        this->getHierarchy()->changeLeftSon(*node, nullptr);

        if (grand_parent != nullptr)
        {
            if (grand_parent->left_ == parent)
            {
                this->getHierarchy()->changeLeftSon(*grand_parent, node);
            }
            else
            {
                this->getHierarchy()->changeRightSon(*grand_parent, node);
            }
        } else
        {
            this->getHierarchy()->changeRoot(node);
        }

        this->getHierarchy()->changeRightSon(*parent, left_son);
        this->getHierarchy()->changeLeftSon(*node, parent);
    }

    template<typename K, typename T, typename BlockType>
    void GeneralBinarySearchTree<K, T, BlockType>::rotateRight(BVSNodeType* node)
    {
        BVSNodeType* right_son = node->right_;
        BVSNodeType* parent = static_cast<ds::amt::BinaryExplicitHierarchyBlock<BlockType>*>(node->parent_);
        BVSNodeType* grand_parent = static_cast<ds::amt::BinaryExplicitHierarchyBlock<BlockType>*>(parent->parent_);

        this->getHierarchy()->changeLeftSon(*parent, nullptr);
        this->getHierarchy()->changeRightSon(*node, nullptr);

        if (grand_parent != nullptr)
        {
            if (grand_parent->left_ == parent)
            {
                this->getHierarchy()->changeLeftSon(*grand_parent, node);
            }
            else
            {
                this->getHierarchy()->changeRightSon(*grand_parent, node);
            }
        }
        else
        {
            this->getHierarchy()->changeRoot(node);
        }
        this->getHierarchy()->changeLeftSon(*parent, right_son);
        this->getHierarchy()->changeRightSon(*node, parent);
    }

    //----------

    template<typename K, typename T>
    Treap<K, T>::Treap() :
        rng_(std::rand())
    {
    }

    template<typename K, typename T>
    void Treap<K, T>::removeNode(BVSNodeType* node)
    {
        node->data_.priority_ = (std::numeric_limits<int>::max)();
        while (this->getHierarchy()->degree(*node) == 2)
        {
            BVSNodeType* left_son = node->left_;
            BVSNodeType* right_son = node->right_;

            if (left_son->data_.priority_ < right_son->data_.priority_)
            {
                this->rotateRight(left_son);
            }
            else
            {
                this->rotateLeft(right_son);
            }
        }
        GeneralBinarySearchTree<K, T, TreapItem<K, T>>::removeNode(node);
    }

    template<typename K, typename T>
    void Treap<K, T>::balanceTree(BVSNodeType* node)
    {
        // rozdelenie generovania
        std::uniform_int_distribution<int> random_key_dist((std::numeric_limits<int>::min)(), (std::numeric_limits<int>::max)());
        int priority = random_key_dist(rng_);
        node->data_.priority_ = priority;

        BVSNodeType* parent = static_cast<BVSNodeType*>(node->parent_);

        while (parent != nullptr && parent->data_.priority_ > node->data_.priority_)
        {
	        if (parent->left_ == node)
	        {
                this->rotateRight(node);
	        } else
	        {
                this->rotateLeft(node);
	        }
            parent = static_cast<BVSNodeType*>(node->parent_);
        }
    }
}
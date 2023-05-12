#pragma once
#include <libds/adt/list.h>
#include <complexities/complexity_analyzer.h>
#include <random>
#include <libds/adt/table.h>

namespace ds::utils
{
    template<class Table>
    class TableAnalyzer : public ComplexityAnalyzer<Table>
    {
    public:
        explicit TableAnalyzer(const std::string& name);

    protected:
        void beforeOperation(Table& table) override;
        void afterReplication(Table& table) override;

    private:
        void insertNElements(Table& table, size_t n);

    private:
        ds::adt::ImplicitList<int> list_;
        ds::adt::ImplicitList<int> insert_keys_;
        std::default_random_engine indexRnd_;
        std::default_random_engine indexRnd2_;
        std::default_random_engine keyRnd_;
        std::default_random_engine keyRnd2_;
    protected:
        int key_;
        int insert_key_;
    };

    template<class Table>
    class TableFindAnalyzer: public TableAnalyzer<Table>
    {
    public:
        explicit TableFindAnalyzer(const std::string& name);

    protected:
        void executeOperation(Table& table) override;
    };


    template<class Table>
    class TableInsertAnalyzer : public TableAnalyzer<Table>
    {
    public:
        explicit TableInsertAnalyzer(const std::string& name);

    protected:
        void executeOperation(Table& table) override;
    };





    class TablesAnalyzer : public CompositeAnalyzer
    {
    public:
        TablesAnalyzer() :
            CompositeAnalyzer("Tables")
        {
            this->addAnalyzer(std::make_unique<TableInsertAnalyzer<ds::adt::Treap<int, int>>>("treap-insert"));
            this->addAnalyzer(std::make_unique<TableFindAnalyzer<ds::adt::Treap<int, int>>>("treap-find"));

            this->addAnalyzer(std::make_unique<TableInsertAnalyzer<ds::adt::SortedSequenceTable<int, int>>>("sortedSequenceTable-insert"));
            this->addAnalyzer(std::make_unique<TableFindAnalyzer<ds::adt::SortedSequenceTable<int, int>>>("sortedSequenceTable-find"));
        }
    };

    template<class Table>
    inline TableAnalyzer<Table>::TableAnalyzer(const std::string& name) :
        ComplexityAnalyzer<Table>(name, [this](Table& table, size_t n)
            {
                this->insertNElements(table, n);
            }),
				list_(),
                insert_keys_(),
                indexRnd_(std::random_device()()),
                indexRnd2_(std::random_device()()),
                keyRnd_(std::random_device()()),
                keyRnd2_(std::random_device()()),
                key_(0),
				insert_key_(0)
    {
    }
            template<class Table>
            inline void TableAnalyzer<Table>::beforeOperation(Table& table)
            {
                std::uniform_int_distribution<size_t> indexDist(0, this->list_.size() - 1);
                std::uniform_int_distribution<size_t> indexDist2(0, this->insert_keys_.size() - 1);

                size_t list_index = indexDist(indexRnd_);
                size_t insert_index = indexDist2(indexRnd2_);

                this->key_ = this->list_.access(list_index);
                this->insert_key_ = this->insert_keys_.access(insert_index);

                this->list_.remove(list_index);
                this->insert_keys_.remove(insert_index);

            }
            template<class Table>
            inline void TableAnalyzer<Table>::afterReplication(Table& table)
            {
                this->list_.clear();
                this->insert_keys_.clear();
            }
           
            template<class Table>
            inline void TableAnalyzer<Table>::insertNElements(Table& table, size_t n)
            {

                std::uniform_int_distribution<int> keyDist(INT_MIN, 0);

				
                // Naplnenie tabulky s datami a udrzanie si indexov v tabulke
                for (size_t i = 0; i < n; i++)
                {
                    int key = keyDist(this->keyRnd_);

                    int data = key;

                    try
                    {
                        table.insert(key, data);
                        this->list_.insertLast(key);
                    }
                    catch (...)
                    {
                        i--;
                    }
                }

                std::uniform_int_distribution<int> keyDist2(1, INT_MAX - 1);

				// Naplnenie zoznamu indexov, ktore sa v tabulke este nenachadzaju

                for (size_t i = 0; i < n; i++)
                {
                    int* block = nullptr;
                    int key = keyDist2(this->keyRnd2_);
                    if (!table.tryFind(key, block))
                    {
                        this->insert_keys_.insertLast(key);
                    } else
                    {
                        i--;
                    }
                }
            }

            template <class Table>
            TableFindAnalyzer<Table>::TableFindAnalyzer(const std::string& name):
				TableAnalyzer<Table>(name)
            {
            }

            template <class Table>
            void TableFindAnalyzer<Table>::executeOperation(Table& table)
            {
                table.find(this->key_);
            }

            template <class Table>
            TableInsertAnalyzer<Table>::TableInsertAnalyzer(const std::string& name):
				TableAnalyzer<Table>(name)
            {
            }

            template <class Table>
            void TableInsertAnalyzer<Table>::executeOperation(Table& table)
            {
                table.insert(this->insert_key_, this->key_);
            }
}

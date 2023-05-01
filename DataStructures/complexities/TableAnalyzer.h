#pragma once

#include <complexities/complexity_analyzer.h>
#include <iterator>
#include <list>
#include <random>
#include <vector>

namespace ds::utils
{
    /**
     * @brief Common base for list analyzers.
     */
    template<class Table>
    class TableAnalyzer : public ComplexityAnalyzer<Table>
    {
    public:
        explicit TableAnalyzer(const std::string& name);

    protected:
        void beforeOperation(Table& structure) override;
        void executeOperation(Table& structure) override;
    private:
        void insert_n_elements(Table& table, size_t n);

    private:
        std::default_random_engine rngKey_;
        std::default_random_engine rngData_;
        size_t key;
        // int data_;
    };

    template <class Table>
    void TableAnalyzer<Table>::beforeOperation(Table& structure)
    {

    }

    template <class Table>
    void TableAnalyzer<Table>::executeOperation(Table& structure)
    {
        structure.contains(this->key);
    }

    template <class Table>
    void TableAnalyzer<Table>::insert_n_elements(Table& table, size_t n)
    {
    }
}

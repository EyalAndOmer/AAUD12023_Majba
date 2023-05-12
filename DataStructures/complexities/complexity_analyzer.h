#pragma once

#include <chrono>
#include <filesystem>
#include <fstream>
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>
#include <iostream>

namespace ds::utils
{
    /**
     *  @brief Analyzer with a name.
     */
    class Analyzer
    {
    public:
        explicit Analyzer(std::string name);
        virtual ~Analyzer() = default;
        virtual void analyze() = 0;
        virtual void setOutputDirectory(std::string path) = 0;
        virtual void setReplicationCount(size_t count) = 0;
        virtual void setStepSize(size_t size) = 0;
        virtual void setStepCount(size_t count) = 0;
        [[nodiscard]] const std::string& getName() const;

    private:
        std::string name_;
    };

    /**
     *  @brief Container of analyzers.
     */
    class CompositeAnalyzer : public Analyzer
    {
    public:
        explicit CompositeAnalyzer(const std::string& name);
        void analyze() override;
        void setOutputDirectory(std::string path) override;
        void setReplicationCount(size_t count) override;
        void setStepSize(size_t size) override;
        void setStepCount(size_t count) override;
        void addAnalyzer(std::unique_ptr<Analyzer> analyzer);
        [[nodiscard]] const std::vector<std::unique_ptr<Analyzer>>& getAnalyzers() const;

    private:
        std::vector<std::unique_ptr<Analyzer>> analyzers_;
    };

    /**
     *  @brief Specific analyzer.
     */
    class LeafAnalyzer : public Analyzer
    {
    public:
        explicit LeafAnalyzer(const std::string& name);
        void setOutputDirectory(std::string path) override;
        void setReplicationCount(size_t count) override;
        void setStepSize(size_t size) override;
        void setStepCount(size_t count) override;
        [[nodiscard]] std::filesystem::path getOutputPath() const;
        [[nodiscard]] bool wasSuccessful() const;

    protected:
        void resetSuccess();
        void setSuccess();
        [[nodiscard]] size_t getReplicationCount() const;
        [[nodiscard]] size_t getStepSize() const;
        [[nodiscard]] size_t getStepCount() const;

    private:
        static const size_t DEFAULT_REPLICATION_COUNT = 100;
        static const size_t DEFAULT_STEP_SIZE = 10000;
        static const size_t DEFAULT_STEP_COUNT = 10;

    private:
        std::string outputDir_;
        size_t replicationCount_;
        size_t stepSize_;
        size_t stepCount_;
        bool wasSuccessful_;
    };

    /**
     *  @brief Universal analyzer of an operation of any structure.
     */
    template<class Structure>
    class ComplexityAnalyzer : public LeafAnalyzer
    {
    public:
        void analyze() override;
        void analyze(Structure structurePrototype);

    protected:
        ComplexityAnalyzer(
            const std::string& name,
            std::function<void(Structure&, size_t)> insertN
        );

        virtual void beforeOperation(Structure& structure) {};
        virtual void executeOperation(Structure& structure) = 0;
        virtual void afterOperation(Structure& structure) {};
        virtual void beforReplication(Structure& structure) {};
        virtual void afterReplication(Structure& structure) {};


    private:
        using duration_t = std::chrono::nanoseconds;

    private:
        void saveToCsvFile(const std::map<size_t, std::vector<duration_t>>& data) const;

    private:
        std::function<void(Structure&, size_t)> insertN_;
    };

    template <class Structure>
    ComplexityAnalyzer<Structure>::ComplexityAnalyzer(
        const std::string& name,
        std::function<void(Structure&, size_t)> insertN
    ) :
        LeafAnalyzer(name),
        insertN_(insertN)
    {
    }

    template <class Structure>
    void ComplexityAnalyzer<Structure>::analyze()
    {
        if constexpr (std::is_default_constructible_v<Structure>)
        {
            this->analyze(Structure());
        }
        else
        {
            throw std::runtime_error("Structure is not default constructible. Use the other overload.");
        }
    }

    // T1
    template<class Structure>
    void ComplexityAnalyzer<Structure>::analyze(Structure structurePrototype)
    {
        // resetovanie success
        resetSuccess();

        // Mapa na uchovanie hodnot merani, vector kvoli zapisu vsetkych replikacii, keby chcem len jednu dam
        // primitivny typ
        std::map<size_t, std::vector<duration_t>> data;

        // Idem pocet replikacii
        for (int replikacia = 0; replikacia < getReplicationCount(); ++replikacia) {
            // V kazdej replikacii vytvorim strukturu
            Structure structure(structurePrototype);
            this->beforReplication(structure);
            // Pre danu strukturu idem robit merania cez vsetky kroky
            // Pre prazdnu strukturu je beh zbytovny, pre remove aj zly, cize ideme od step = 1
            for (int step = 1; step <= getStepCount(); ++step) {
                // Urci pocet kolko musis vlozit
                // step * getStepSize() je max pocet prvkov
                // structure.size() aktualny pocet prvkov
                size_t insert_count = step * getStepSize() - structure.size();
                // Naplnenie cez lambda funkciu
                insertN_(structure, insert_count);

                // Akcie pred samotnou operaciou
                beforeOperation(structure);

                // Zaciatok merania casu, high_resolution_clock su najpresnejsie hodiny
                auto start_time = std::chrono::high_resolution_clock::now();
                // Samotna operacia
                executeOperation(structure);

                // Zmeranie casu po operacii
                auto duration = std::chrono::high_resolution_clock::now() - start_time;

                // Po samotnej operacii
                afterOperation(structure);

                // Zapisanie do suboru
                // Dve moznosti zapisu
                // Prva je zapisovat neustale do suboru, ktory sa bude stale otvarat a zatvarat, dlhe trvanie
                // Druhe riesenie je vkladat do lokalnej premennej a potom zapisat do suboru naraz

                // Zapisanie samotneho casu do mapy
                data[step * getStepSize()].push_back(duration);
            }
            this->afterReplication(structure);

            std::cout << "Replication " << replikacia << "/" << getReplicationCount() << '\n';
        }

        saveToCsvFile(data);
        // Nastavenie success na true
        setSuccess();
    }

    template <class Structure>
    void ComplexityAnalyzer<Structure>::saveToCsvFile(const std::map<size_t, std::vector<duration_t>>& data) const {
        constexpr char Separator = ';';
        auto path = this->getOutputPath();
        std::ofstream ost(path);
        if (!ost.is_open())
        {
            throw std::runtime_error("Failed to open output file.");
        }

        const size_t rowCount = data.begin()->second.size();
        const size_t lastSize = (--data.end())->first;

        for (const auto& [size, durations] : data)
        {
            ost << size << (size != lastSize ? Separator : '\n');
        }

        for (int i = 0; i < rowCount; ++i)
        {
            for (const auto& [size, durations] : data)
            {
                ost << data.at(size)[i].count() << (size != lastSize ? Separator : '\n');
            }
        }
        ost.close();
    }
}

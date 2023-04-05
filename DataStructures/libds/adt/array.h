#pragma once

#include <libds/adt/abstract_data_type.h>
#include <libds/amt/implicit_sequence.h>

namespace ds::adt {

    class Dimension
    {
    public:
        Dimension();
        Dimension(int base, size_t size);
        Dimension(const Dimension& other);

        int getBase() const;
        size_t getSize() const;

        bool operator==(const Dimension& other) const;
        bool operator!=(const Dimension& other) const;
        Dimension& operator=(const Dimension& other);

    private:
        int base_;
        size_t size_;
    };

    //----------

    template <typename T>
    class Array :
        public ADS<T>
    {
    public:
        using IteratorType = typename amt::IS<T>::IteratorType;

    public:
        Array(size_t size);
        Array(Dimension dimension);
        Array(const Array<T>& other);
        ~Array();

        ADT& assign(const ADT& other) override;
        void clear() override;
        bool isEmpty() const override;
        bool equals(const ADT& other) override;

        size_t size() const override;
        int getBase() const;
        T access(size_t index) const;
        void set(T element, size_t index);

        IteratorType begin();
        IteratorType end();

    private:
        bool validateIndex(size_t index) const;
        size_t mapIndex(size_t index) const;
        amt::IS<T>* getSequence() const;

    private:
        size_t base_;
    };

    //----------

    template <typename T>
    class Matrix :
        public ADS<T>
    {
    public:
        Matrix(size_t size1, size_t size2);
        Matrix(Dimension dimension1, Dimension dimension2);
        Matrix(const Matrix& other);
        ~Matrix();

        ADT& assign(const ADT& other) override;
        void clear() override;
        size_t size() const override;
        bool isEmpty() const override;
        bool equals(const ADT& other) override;
        Dimension getDimension1() const;
        Dimension getDimension2() const;

        T access(size_t index1, size_t index2) const;
        void set(T element, size_t index1, size_t index2);

    private:
        bool validateIndices(size_t index1, size_t index2) const;
        size_t mapIndices(size_t index1, size_t index2) const;
        amt::IS<T>* getSequence() const;

    private:
        Dimension dimension1_;
        Dimension dimension2_;
    };

    //----------

    inline Dimension::Dimension() :
        Dimension(0, 0)
    {
    }

    inline Dimension::Dimension(int base, size_t size) :
        base_(base),
        size_(size)
    {
    }

    inline Dimension::Dimension(const Dimension& other) :
        base_(other.base_),
        size_(other.size_)
    {
    }

    inline int Dimension::getBase() const
    {
        return base_;
    }

    inline size_t Dimension::getSize() const
    {
        return size_;
    }

    inline bool Dimension::operator==(const Dimension& other) const
    {
        return base_ == other.base_ && size_ == other.size_;
    }

    inline bool Dimension::operator!=(const Dimension& other) const
    {
        return !(*this == other);
    }

    inline Dimension& Dimension::operator=(const Dimension& other)
    {
        base_ = other.base_;
        size_ = other.size_;
        return *this;
    }

    //----------

    template<typename T>
    Array<T>::Array(size_t size) :
        Array(Dimension(0, size))
    {
    }

    template<typename T>
    Array<T>::Array(Dimension dimension) :
        ADS<T>(new amt::IS<T>(dimension.getSize(), true)),
        base_(dimension.getBase())
    {
    }

    template<typename T>
    Array<T>::Array(const Array<T>& other) :
        ADS<T>(new amt::IS<T>(), other),
        base_(other.base_)
    {
    }

    template<typename T>
    Array<T>::~Array() = default;

    template<typename T>
    ADT& Array<T>::assign(const ADT& other)
    {
        // dynamic cast sa da pouzit ako instanceof v jave
        // ako je mozne davat const do dynamic cast a co tam robi to &
        auto other_arr = dynamic_cast<const Array<T>&>(other);

        if (base_ != other_arr.base_ || this->size() != other_arr.size())
        {
            throw std::exception("Array::assign: Dimension of arrays don't match");
        }

        ADS<T>::assign(other);

        return *this;
    }

    template<typename T>
    void Array<T>::clear()
    {
        this->error("Array can't be cleared!");
    }

    template<typename T>
    size_t Array<T>::size() const
    {
        return this->getSequence()->size();
    }

    template<typename T>
    int Array<T>::getBase() const
    {
        return base_;
    }

    template<typename T>
    bool Array<T>::isEmpty() const
    {
        return this->size() == 0;
    }

    template<typename T>
    bool Array<T>::equals(const ADT& other)
    {
        const Array<T>& otherArray = dynamic_cast<const Array<T>&>(other);
        return base_ == otherArray.base_ && ADS<T>::equals(other);
    }

    template<typename T>
    T Array<T>::access(size_t index) const
    {
        if (!validateIndex(index))
        {
            throw std::exception("Array<T>::access: Bad index");
        }

        return this->getSequence()->access(this->mapIndex(index))->data_;
    }

    template<typename T>
    void Array<T>::set(T element, size_t index)
    {
        if (!validateIndex(index))
        {
            throw std::exception("Array<T>::set: Bad index");
        }

    	this->getSequence()->access(this->mapIndex(index))->data_ = element;
    }

    template <typename T>
    auto Array<T>::begin() -> IteratorType
    {
        return this->memoryStructure_->begin();
    }

    template <typename T>
    auto Array<T>::end() -> IteratorType
    {
        return this->memoryStructure_->end();
    }

    template<typename T>
    amt::IS<T>* Array<T>::getSequence() const
    {
        return dynamic_cast<amt::IS<T>*>(this->memoryStructure_);
    }

    template<typename T>
    bool Array<T>::validateIndex(size_t index) const
    {
        return index >= base_ && index < base_ + size();
    }

    template<typename T>
    size_t Array<T>::mapIndex(size_t index) const
    {
        return index - base_;
    }

    //----------

    template<typename T>
    Matrix<T>::Matrix(size_t size1, size_t size2) :
        Matrix<T>(Dimension(0, size1), Dimension(0, size2))
    {
    }

    template<typename T>
    Matrix<T>::Matrix(Dimension dimension1, Dimension dimension2) :
        ADS<T>(new amt::IS<T>(dimension1.getSize() * dimension2.getSize(), true)),
        dimension1_(dimension1),
        dimension2_(dimension2)
    {
    }

    template<typename T>
    Matrix<T>::Matrix(const Matrix<T>& other) :
        ADS<T>(new amt::IS<T>(), other),
    dimension1_(other.dimension1_),
    dimension2_(other.dimension2_)
    {
    }

    template<typename T>
    Matrix<T>::~Matrix() = default;

    template<typename T>
    ADT& Matrix<T>::assign(const ADT& other)
    {
        const Matrix<T>& otherMatrix = dynamic_cast<const Matrix<T>&>(other);
        if (dimension1_ != otherMatrix.dimension1_ || dimension2_ != otherMatrix.dimension2_)
        {
            this->error("Matrix dimensions are different!");
        }
        ADS<T>::assign(otherMatrix);
        return *this;
    }

    template<typename T>
    void Matrix<T>::clear()
    {
        this->error("Matrix can't be cleared!");
    }

    template<typename T>
    size_t Matrix<T>::size() const
    {
        return dimension1_.getSize() * dimension2_.getSize();
    }

    template<typename T>
    bool Matrix<T>::isEmpty() const
    {
        return false;
    }

    template<typename T>
    bool Matrix<T>::equals(const ADT& other)
    {
        const auto& otherMatrix = dynamic_cast<const Matrix<T>&>(other);
        return dimension1_ == otherMatrix.dimension1_ &&
               dimension2_ == otherMatrix.dimension2_ &&
               ADS<T>::equals(other);
    }

    template <typename T>
    Dimension Matrix<T>::getDimension1() const
    {
        return dimension1_;
    }

    template <typename T>
    Dimension Matrix<T>::getDimension2() const
    {
        return dimension2_;
    }

    template<typename T>
    T Matrix<T>::access(size_t index1, size_t index2) const
    {
        if (!validateIndices(index1, index2))
        {
            throw std::exception("Matrix<T>::access: bad index");
        }
        size_t mapped_index = mapIndices(index1, index2);
        return this->getSequence()->access(mapped_index)->data_;
    }
    template<typename T>
    void Matrix<T>::set(T element, size_t index1, size_t index2)
    {
        if (!validateIndices(index1, index2))
        {
            throw std::exception("Matrix<T>::access: bad index");
        }
        size_t mapped_index = mapIndices(index1, index2);
    	this->getSequence()->access(mapped_index)->data_ = element;
    }

    template<typename T>
    bool Matrix<T>::validateIndices(size_t index1, size_t index2) const
    {
        return (index1 >= dimension1_.getBase() && index1 < dimension1_.getBase() + dimension1_.getSize()) &&
            (index2 >= dimension2_.getBase() && index2 < dimension2_.getBase() + dimension2_.getSize());
    }

    template<typename T>
    size_t Matrix<T>::mapIndices(size_t index1, size_t index2) const
    {
        return (index1 - dimension1_.getBase()) * dimension2_.getSize() + (index2 - dimension2_.getBase());
    }

    template<typename T>
    amt::IS<T>* Matrix<T>::getSequence() const
    {
        return dynamic_cast<amt::IS<T>*>(this->memoryStructure_);
    }
}
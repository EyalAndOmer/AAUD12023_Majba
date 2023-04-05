#pragma once

#include <libds/mm/memory_manager.h>
#include <libds/mm/memory_omanip.h>
#include <libds/constants.h>
#include <cstdlib>
#include <cstring>
#include <ostream>
#include <algorithm>
#include <iostream>

namespace ds::mm {

	template<typename BlockType>
	class CompactMemoryManager : public MemoryManager<BlockType> {
	public:
		CompactMemoryManager();
		explicit CompactMemoryManager(size_t size);
		CompactMemoryManager(const CompactMemoryManager<BlockType>& other);
		~CompactMemoryManager() override;

		BlockType* allocateMemory() override;
		BlockType* allocateMemoryAt(size_t index);
		void releaseMemory(BlockType* pointer) override;
		void releaseMemoryAt(size_t index);
		void releaseMemory();

		[[nodiscard]] size_t getCapacity() const;

		CompactMemoryManager<BlockType>& assign(const CompactMemoryManager<BlockType>& other);
		void changeCapacity(size_t newCapacity);
		void shrinkMemory();
		void clear();
		bool equals(const CompactMemoryManager<BlockType>& other) const;
		void* calculateAddress(const BlockType& data);
		size_t calculateIndex(const BlockType& data);
		BlockType& getBlockAt(size_t index);
		void swap(size_t index1, size_t index2);

		void print(std::ostream& os);

	private:
		[[nodiscard]] size_t getAllocatedBlocksSize() const;
		[[nodiscard]] size_t getAllocatedCapacitySize() const;

	private:
		// Zaciatok alokovanej pamate
		BlockType* base_;
		// koniec alokovanej pamate
		BlockType* end_;
		// koniec priradenej pamate
		BlockType* limit_;

		static const size_t INIT_SIZE = 4;
	};

	template<typename BlockType>
	CompactMemoryManager<BlockType>::CompactMemoryManager() :
		CompactMemoryManager(INIT_SIZE)
	{
	}

	template<typename BlockType>
	CompactMemoryManager<BlockType>::CompactMemoryManager(size_t size) :
		base_(static_cast<BlockType*>(std::calloc(size, sizeof(BlockType)))),
		end_(base_),
		limit_(base_ + size)
	{
	}

	template<typename BlockType>
	CompactMemoryManager<BlockType>::CompactMemoryManager(const CompactMemoryManager<BlockType>& other) :
		CompactMemoryManager(other.getAllocatedBlockCount())
	{
		assign(other);
	}

	template<typename BlockType>
	CompactMemoryManager<BlockType>::~CompactMemoryManager()
	{
		// Uvolni pamat
		CompactMemoryManager<BlockType>::releaseMemory(base_);
		// Vrat pamat
		std::free(base_);

		base_ = nullptr;
		end_ = nullptr;
		limit_ = nullptr;
	}

	template<typename BlockType>
	BlockType* CompactMemoryManager<BlockType>::allocateMemory()
	{
		return allocateMemoryAt(end_ - base_);
	}

	template<typename BlockType>
	BlockType* CompactMemoryManager<BlockType>::allocateMemoryAt(size_t index)
	{
		if (end_ == limit_) {
			// Dali sme linearnu expanznu strategiu o dvojnasobok
			changeCapacity(2 * this->getAllocatedBlockCount());
		}

		// memmove mozem pouzit ked sa bloky prekryvaju
		// memcpy mozem pouzit ked sa bloky neprekryvaju
		if (end_ - base_ > index) {
			std::memmove(base_ + index + 1, base_ + index, (end_ - base_ - index) * sizeof(BlockType));
		}
		++this->allocatedBlockCount_;
		++end_;

		// Placement new nam dava moznost urcit si velkost pamate, keby dame new tak to riesi OS
//        return new (base_ + index) BlockType();
		return placement_new(base_ + index);
	}

	template<typename BlockType>
	void CompactMemoryManager<BlockType>::releaseMemory(BlockType* pointer)
	{
		BlockType* p = pointer;

		while (p != end_) {
			// explicitne zavolanie destruktora
			p->~BlockType();
			++p;
		}
		end_ = pointer;
		this->allocatedBlockCount_ = end_ - base_;
		// Rozdiel medzi tymto a this je ze c++ podporuje viacnasobnu dedicnost
		// keby obaja predkovia maju atribut s rovnakym menom tak sa zavolaju obidva, takto iba ten co chcem
//        MemoryManager<BlockType>::allocatedBlockCount_ = end_ - base_;
	}

	template<typename BlockType>
	void CompactMemoryManager<BlockType>::releaseMemoryAt(size_t index)
	{
		// Zavolaj destruktor na dane pamatove miesto
		getBlockAt(index).~BlockType();

		std::memmove(base_ + index, base_ + index + 1, (end_ - base_ - index - 1) * sizeof(BlockType));
		--end_;
		--this->allocatedBlockCount_;
	}

	template<typename BlockType>
	void CompactMemoryManager<BlockType>::releaseMemory()
	{
		releaseMemory(end_ - 1);
	}

	template<typename BlockType>
	size_t CompactMemoryManager<BlockType>::getCapacity() const
	{
		return limit_ - base_;
	}

	template<typename BlockType>
	CompactMemoryManager<BlockType>& CompactMemoryManager<BlockType>::assign(const CompactMemoryManager<BlockType>& other) {
		if (this != &other) {
			releaseMemory(base_);
			this->allocatedBlockCount_ = other.allocatedBlockCount_;
			// Sposobi, ze skopirujem iba pamat, ktoru other realne pouziva
			void* new_base = std::realloc(base_, other.getAllocatedCapacitySize());
			// realloc vracia nullptr pri nedostasku pamate
			if (new_base == nullptr) {
				throw std::bad_alloc();
			}

			base_ = static_cast<BlockType*>(new_base);
			end_ = base_ + this->allocatedBlockCount_;
			limit_ = base_ + (other.limit_ - other.base_);

			// Co by sa stalo keby urobim memcpy ?
			// Other ktory kopirujem moze obsahovat smerniky na ine objekty
			// Ked urobim memcpy tak sa mi prekopiruje blok po bloku, a s blokom sa mi aj smerniky skopiruju
			// Vznikol by SHALLOW COPY
			// Pri volani destruktora sa mi pri destruktore zmazu objekty na ktore mam smerniky
			// A other sa snane nekonzistentny

			for (size_t i = 0; i < other.getAllocatedBlockCount(); ++i) {
				placement_copy(base_ + i, *(other.base_ + i));
			}
			//            std::memcpy(base_, other.base_, other.getAllocatedBlocksSize());
		}
		return *this;
	}

	template<typename BlockType>
	void CompactMemoryManager<BlockType>::shrinkMemory()
	{
		size_t new_capacity = static_cast<size_t>(end_ - base_);

		if (new_capacity < CompactMemoryManager<BlockType>::INIT_SIZE)
		{
			new_capacity = CompactMemoryManager<BlockType>::INIT_SIZE;
		}

		changeCapacity(new_capacity);
	}

	template<typename BlockType>
	void CompactMemoryManager<BlockType>::changeCapacity(size_t newCapacity)
	{
		if (newCapacity == getCapacity()) {
			return;
		}
		if (newCapacity < this->getAllocatedBlockCount()) {
			releaseMemory(base_ + newCapacity);
		}

		void* new_base = std::realloc(base_, newCapacity * sizeof(BlockType));

		if (new_base == nullptr) {
			throw std::bad_alloc();
		}

		// Static cast je urceny presne na toto
		base_ = static_cast<BlockType*>(new_base);
		end_ = base_ + this->getAllocatedBlockCount();
		limit_ = base_ + newCapacity;
	}

	template<typename BlockType>
	void CompactMemoryManager<BlockType>::clear()
	{
		releaseMemory(base_);
	}

	template<typename BlockType>
	bool CompactMemoryManager<BlockType>::equals(const CompactMemoryManager<BlockType>& other) const
	{
		return (this == &other) ||
			(
				// Funkcia memcmp porovnava bitovo dva bloky pamate, ktore maju rovnaku velkost
				// Funkcia vracia 0 ak su bloky rovnake, 1 ake je blok vacsi, -1 ak je blok mensi
				// memcpy sa pozera iba na adresy blokov, nie na smerniky ake ma, robi SHALLOW porovnavanie
				// Ak by sme chceli DEEP porovnavanie tak zavolame comapre nad blokmi samotnymi
				this->allocatedBlockCount_ == other.allocatedBlockCount_ &&
				std::memcmp(base_, other.base_, this->getAllocatedBlocksSize()) == 0
				);
	}

	template<typename BlockType>
	void* CompactMemoryManager<BlockType>::calculateAddress(const BlockType& data)
	{
		BlockType* p = base_;
		while (p != end_ && p != &data) {
			// lepsi je ++p ako p++
			++p;
		}

		if (p == end_) {
			return nullptr;
		}

		return p;
	}

	template<typename BlockType>
	size_t CompactMemoryManager<BlockType>::calculateIndex(const BlockType& data)
	{
		if (&data <= end_ && &data >= base_) {
			return &data - base_;
		}
		// V prirucke je -1, ale pouzivame konstantu
		return INVALID_INDEX;
	}

	template<typename BlockType>
	BlockType& CompactMemoryManager<BlockType>::getBlockAt(size_t index)
	{
		return *(base_ + index);
	}

	template<typename BlockType>
	void CompactMemoryManager<BlockType>::swap(size_t index1, size_t index2)
	{
		std::swap(getBlockAt(index1), getBlockAt(index2));
	}

	template<typename BlockType>
	size_t CompactMemoryManager<BlockType>::getAllocatedBlocksSize() const
	{
		return (end_ - base_) * sizeof(BlockType);
	}

	template<typename BlockType>
	size_t CompactMemoryManager<BlockType>::getAllocatedCapacitySize() const
	{
		return (limit_ - base_) * sizeof(BlockType);
	}

	template<typename BlockType>
	void CompactMemoryManager<BlockType>::print(std::ostream& os)
	{
		os << "first = " << base_ << std::endl;
		os << "last = " << end_ << std::endl;
		os << "limit = " << limit_ << std::endl;
		os << "block size = " << sizeof(BlockType) << "B" << std::endl;

		BlockType* ptr = base_;
		while (ptr != limit_) {
			std::cout << ptr;
			os << PtrPrintBin<BlockType>(ptr);

			if (ptr == base_) {
				os << "<- first";
			}
			else if (ptr == end_) {
				os << "<- last";
			}
			os << std::endl;
			ptr++;
		}

		os << limit_ << "|<- limit" << std::endl;
	}

}
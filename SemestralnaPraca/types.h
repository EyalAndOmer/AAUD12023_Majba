#include <libds/adt/list.h>
#include <libds/adt/tree.h>

template<typename T>
using ImplicitList = ds::adt::GeneralList<T, ds::amt::ImplicitSequence<T>>;

template<typename T>
using ExplicitList = ds::adt::GeneralList<T, ds::amt::ExplicitSequence<T>>;

template<typename T>
using MultiwayTree = ds::adt::GeneralTree<T, ds::amt::MultiWayExplicitHierarchy<T>>;

template<typename T>
using ExplicitBinaryTree = ds::adt::GeneralTree<T, ds::amt::BinaryExplicitHierarchy<T>>;

enum UCType
{
	republika,
	kraj,
	okres,
	obec
};
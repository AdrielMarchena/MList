#pragma once
#include <string>
#include <unordered_map>

#ifndef MAX_NUMBER_OF_FIELDS

#define MAX_NUMBER_OF_FIELDS 32

#endif

//Don't touch it
static std::unordered_map<std::string, int> mlist_s_TypeDictionary;
static int mlist_s_enumCounter = 0;

static const int GetEnumType(const std::string& stringName)
{
	if (mlist_s_TypeDictionary.find(stringName) == mlist_s_TypeDictionary.end())
		return -1;
	return mlist_s_TypeDictionary[stringName];
}

struct Type {
	std::string stringName;
	int enumValue;
	size_t size;
};

template<typename T> 
static Type* GetType()
{
	return nullptr;
}

#define DEFINE_TYPE(TYPE) \
template<>\
static Type* GetType<TYPE>() {\
	static Type type;\
	type.stringName = #TYPE;\
	type.size = sizeof(TYPE);\
	type.enumValue = __COUNTER__;\
	static bool once = [&](){ mlist_s_enumCounter++; return true; }();\
	mlist_s_TypeDictionary[type.stringName] = type.enumValue;\
	return &type;\
}\

struct Field {
	Type* type;
	std::string name;
	size_t offset;
};

// MAX_NUMBER_OF_FIELDS is arbitrarily large
struct Class {
	std::array<Field, MAX_NUMBER_OF_FIELDS> fields;
};

template<typename T>
static Class* GetClass() { return nullptr; }

#define BEGIN_ATTRIBUTES_FOR(CLASS)  \
template<> \
static Class* GetClass<CLASS>() { \
  using ClassType = CLASS; \
  static Class localClass; \
  enum { BASE = __COUNTER__ }; \

#define DEFINE_MEMBER(NAME)  \
  enum { NAME##Index = __COUNTER__ - BASE - 1}; \
  localClass.fields[NAME##Index].type = GetType<decltype(ClassType::NAME)>();\
  localClass.fields[NAME##Index].name = { #NAME };  \
  localClass.fields[NAME##Index].offset = offsetof(ClassType, NAME);\

#define END_ATTRIBUTES \
  return &localClass; \
}\

DEFINE_TYPE(std::string);
DEFINE_TYPE(uint8_t);
DEFINE_TYPE(int8_t);
DEFINE_TYPE(uint16_t);
DEFINE_TYPE(int16_t);
DEFINE_TYPE(uint32_t);
DEFINE_TYPE(int32_t);
DEFINE_TYPE(uint64_t);
DEFINE_TYPE(int64_t);

#define FRIEND_FOR_REFLECTION(CLASS) \
static friend Class* ::GetClass<CLASS>();\
static friend Type* ::GetType<CLASS>()

#define FORWARD_DECLARATION(CLASS) \
template<>\
static Type* GetType<CLASS>();\
template<>\
static Class* GetClass<CLASS>()
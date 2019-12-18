#ifndef LOOREFLECT_GENERATOR_H
#define LOOREFLECT_GENERATOR_H
#include "looreflect.h"

namespace loo
{
	class Generator
	{
		FILE *out;
		ClassDef *cdef;
		std::vector<std::uint32_t> meta_data;
	public:
		Generator(ClassDef *classDef, const std::vector<QByteArray> &metaTypes, const std::unordered_map<QByteArray, QByteArray> &knownQObjectClasses, const std::unordered_map<QByteArray, QByteArray> &knownGadgets, FILE *outfile = 0);
		void generateCode();//core
	private:
		bool registerableMetaType(const QByteArray &propertyType);
		void registerClassInfoStrings();
		void generateClassInfos();
		void registerFunctionStrings(const std::vector<FunctionDef> &list);
		void registerByteArrayVector(const std::vector<QByteArray> &list);
		void generateFunctions(const std::vector<FunctionDef> &list, const char *functype, int type, int &paramsIndex);
		void generateFunctionRevisions(const std::vector<FunctionDef> &list, const char *functype);
		void generateFunctionParameters(const std::vector<FunctionDef> &list, const char *functype);
		void generateTypeInfo(const QByteArray &typeName, bool allowEmptyName = false);
		void registerEnumStrings();
		void generateEnums(int index);
		void registerPropertyStrings();
		void generateProperties();
		void generateMetacall();
		void generateStaticMetacall();
		void generateSignal(FunctionDef *def, int index);
		void generatePluginMetaData();
		std::multimap<QByteArray, int> automaticPropertyMetaTypesHelper();
		std::unordered_map<int, std::multimap<QByteArray, int> > methodsWithAutomaticTypesHelper(const std::vector<FunctionDef> &methodList);

		void strreg(const QByteArray &); // registers a string
		int stridx(const QByteArray &); // returns a string's id
		std::vector<QByteArray> strings;
		QByteArray purestSuperClass;
		std::vector<QByteArray> metaTypes;
		std::unordered_map<QByteArray, QByteArray> knownQObjectClasses;
		std::unordered_map/*QHash*/<QByteArray, QByteArray> knownGadgets;
	};
}

#endif
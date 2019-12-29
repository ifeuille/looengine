/* ========================================================================= */
/* Copyright (C) 2017-2018 Arvid Gerstmann. All rights reserved.             */
/* ========================================================================= */

#ifndef LOOREFLECT_ENUMVALUE_GENERATOR_HPP
#define LOOREFLECT_ENUMVALUE_GENERATOR_HPP
#pragma once

#include "annotations.h"
#include "utils.h"

inline raw_ostream &operator<<(raw_ostream &os, PropertyAnnotations &p) {
  return os;
}

/* ========================================================================= */
/* Field Generator                                                           */
/* ========================================================================= */
struct EnumConstantGenerator {
  ASTContext *const ctx;
  SmallString<64> fieldName;
  SmallString<64> typeName;
  raw_svector_ostream fieldNameOs{fieldName};
  raw_svector_ostream TypeNameOs{typeName};
  StringRef const type;
  std::string const fieldPrefix;

  explicit EnumConstantGenerator(ASTContext *context, StringRef const &parentType,
                              StringRef const &prefix)
      : ctx(context), type(parentType), fieldPrefix(prefix) {}

  void Generate(unsigned i, EnumConstantDecl const *e,
                PropertyAnnotations &annotations, raw_ostream &os) {
    fieldName.clear();
    typeName.clear();

    e->printName(fieldNameOs);
    GetRealTypeName(ctx, e->getType(), TypeNameOs);

    auto prefix = [&]() -> raw_ostream & {
      return os << fieldPrefix << "[" << i << "]";
    };

    os << "\n/* EnumConstant " << (i + 1) << " */\n";
    prefix() << ".m_index = " << i << ";\n";
    prefix() << ".m_value = " << e->getInitVal().getSExtValue() << ";\n";
    prefix() << ".m_name = \"" << fieldName << "\";\n";
    if (annotations.hasTagName) {
      prefix() << ".m_tagName = \"" << annotations.tagName << "\";\n";
    } else {
      prefix() << ".m_tagName = \"" << fieldName << "\";\n";
    }
    prefix() << ".m_flags = " << annotations.Flags() << ";\n";
    // prefix() << ".m_qualifier = " << GenerateQualifier(ctx, e->getType()) <<
    // ";\n";
    if (type != typeName)
      /* prefix() << ".m_type = TypeResolver<" << typeName << ">::Get();\n";
       */
      prefix() << ".m_type = GetType<" << typeName << ">();\n";
    else
      prefix() << ".m_type = nullptr;\n";
  }
};

#endif /* METAREFLECT_FIELD_GENERATOR_HPP */

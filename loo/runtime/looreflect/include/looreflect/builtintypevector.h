#ifndef LOOREFLECT_TEMPLATES_VECTOR_H
#define LOOREFLECT_TEMPLATES_VECTOR_H
#pragma once
#include "looreflect/declclass.h"
#ifndef __LOOREFLECT__

#include <string>
#include <vector>

namespace looreflect {
namespace detail {

/* ========================================================================= */
/* Vector                                                                    */
/* ========================================================================= */
template <class VecT> struct LooVectorClass : public LooClassTemplate {
  using LooClassTemplate::LooClassTemplate;

  virtual void visit(void const *instance, LooClassVisitor *visitor,
                     size_t filter = LooField::kFlagsSerialized,
                     unsigned depth = 0) const noexcept {
    if (instance == nullptr) {
      visitor->primitive(this, nullptr);
      return;
    }

    LooType const *type = LooGetType<typename VecT::value_type>();
    VecT const *vec = (VecT const *)instance;

    visitor->array_begin(this, depth, vec->size());
    std::size_t i = 0;
    for (auto const &e : *vec) {
      visitor->array_element(type, depth + 1, i++);

      if (type->is_class()) {
        Class const *c = (LooClass const *)type;
        c->visit(&e, visitor, filter, depth + 1);
      } else {
        visitor->primitive(type, &e);
      }
    }
    visitor->array_end(this, depth);
  }
};

template <class T>
inline LooClass const *LooGetClassImpl(LooClassTag<std::vector<T>>) noexcept {
  static LooClassBuilder<T, 0, 0, 1> reflected([](auto self) {
    self->templateArgs[0].tag = LooTemplateArgument::Tag::Type;
    self->templateArgs[0].type = LooGetType<T>();
  });
  static LooVectorClass<std::vector<T>> cache(
      sizeof(std::vector<T>), Hash("std::vector<T>"), nullptr, /* BASECLASS */
      reflected.fields, reflected.fields + reflected.numFields,
      reflected.functions, reflected.functions + reflected.numFunctions,
      "std::vector<T>", Class::kFlagsNull, reflected.templateArgs,
      reflected.templateArgs + reflected.numTemplateArgs);
  return &cache;
}

template <class T>
inline LooType const *LooGetTypeImpl(LooTypeTag<std::vector<T>>) noexcept {
  return LooGetClassImpl(LooClassTag<std::vector<T>>{});
}


} 
}


#endif 
#endif

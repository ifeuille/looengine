
#ifndef LOOREFLECT_TEMPLATES_STRING_H
#define LOOREFLECT_TEMPLATES_STRING_H
#pragma once
#include "looreflect/declclass.h"
#ifndef __LOOREFLECT__

#include <string>
#include <vector>

namespace looreflect {
namespace detail {


/* ========================================================================= */
/* String                                                                    */
/* ========================================================================= */
class LooStringClass : public LooClass {
  using LooClass::LooClass;

  virtual void visit(void const *instance, LooClassVisitor *visitor,
                     size_t filter = LooField::kFlagsSerialized,
                     unsigned depth = 0) const noexcept {
	  LOO_UNUSED (filter);
	  LOO_UNUSED (depth);
    if (instance == nullptr) {
      visitor->string(this, nullptr);
      return;
    }

    std::string const *str = (std::string const *)instance;
    char const *s = str->c_str();
    visitor->string(this, &s);
  }
};

inline LooClass const *LooGetClassImpl(LooClassTag<std::string>) noexcept {
	static LooClassBuilder<std::string, 0, 0, 0> reflected ([](auto self) {LOO_UNUSED (self); });
  static LooClass cache(
      sizeof(std::string), Hash("std::string"), nullptr, /* BASECLASS */
      reflected.fields, reflected.fields + reflected.numFields,
      reflected.functions, reflected.functions + reflected.numFunctions,
      "std::string", LooClass::kFlagsNull);
  return &cache;
}

inline LooType const *LooGetTypeImpl(LooTypeTag<std::string>) noexcept {
  return LooGetClassImpl(LooClassTag<std::string>{});
}

} /* namespace detail */
} /* namespace looreflect */

#endif
#endif 

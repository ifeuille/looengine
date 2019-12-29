#include <stdio.h>

#include "annotations.h"
#include "loofinder.h"
#include "utils.h"

static llvm::cl::OptionCategory g_ToolCategory("looreflect options");

int main(int argc, const char **argv) {
  /* Parse command-line options. */
  CommonOptionsParser optionsParser(argc, argv, g_ToolCategory);
  ClangTool tool(optionsParser.getCompilations(),
                 optionsParser.getSourcePathList());

#if 0
    auto &db = optionsParser.getCompilations();
    for (auto &cmd : db.getAllCompileCommands()) {
        printf("CommandLine:");
        for (auto &opt : cmd.CommandLine)
            printf(" %s", opt.c_str());
        printf("\n");
        printf("File: %s\n", cmd.Filename.c_str());
        printf("Directory: %s\n", cmd.Directory.c_str());
        printf("Output: %s\n", cmd.Output.c_str());
    }
#endif

  /* The classFinder class is invoked as callback. */
  LooFinder classFinder;
  MatchFinder finder;

  /* Search for all records (class/struct) with an 'annotate' attribute. */
  static DeclarationMatcher const classMatcher =
      cxxRecordDecl(decl().bind("id"), hasAttr(attr::Annotate));
  finder.addMatcher(classMatcher, &classFinder);

  /* Search for all fields with an 'annotate' attribute. */
  static DeclarationMatcher const propertyMatcher =
      fieldDecl(decl().bind("id"), hasAttr(attr::Annotate));
  finder.addMatcher(propertyMatcher, &classFinder);

  /* Search for all functions with an 'annotate' attribute. */
  static DeclarationMatcher const functionMatcher =
      functionDecl(decl().bind("id"), hasAttr(attr::Annotate));
  finder.addMatcher(functionMatcher, &classFinder);

  static DeclarationMatcher const enumMatcher =
      enumDecl(decl().bind("id"), hasAttr(attr::Annotate));
  static DeclarationMatcher const enumConstantMatcher =
      enumConstantDecl(decl().bind("id"), hasAttr(attr::Annotate));

  finder.addMatcher(enumMatcher, &classFinder);
  finder.addMatcher(enumConstantMatcher, &classFinder);

  return tool.run(newFrontendActionFactory(&finder).get());
}

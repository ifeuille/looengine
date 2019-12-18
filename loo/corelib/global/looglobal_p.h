
// #ifndef LOOGLOBAL_P_H
// #define LOOGLOBAL_P_H

// //
// //  W A R N I N G
// //  -------------
// //
// // This file is not part of the Qt API.  It exists purely as an
// // implementation detail.  This header file may change from version to
// // version without notice, or even be removed.
// //
// // We mean it.
// //

// #include "looglobal.h"
// #include "looglobal_p.h"      // include self to avoid syncqt warning - no-op

// // #include <LooCore/private/looconfig_p.h>
// // #include <LooCore/private/lootcore-config_p.h>

// #if defined(__cplusplus)
// #if !LOO_HAS_BUILTIN(__builtin_available)
// #include <initializer_list>
// #include <LooCore/private/loooperatingsystemversion_p.h>
// #include <LooCore/looversionnumber.h>

// LOO_BEGIN_NAMESPACE

// struct loo_clang_builtin_available_os_version_data {
//     LooOperatingSystemVersion::OSType type;
//     const char *version;
// };

// static inline bool qt_clang_builtin_available(
//     const std::initializer_list<qt_clang_builtin_available_os_version_data> &versions)
// {
//     for (auto it = versions.begin(); it != versions.end(); ++it) {
//         if (currentType() == it->type) {
//             const auto current = QOperatingSystemVersion::current();
//             return QVersionNumber(
//                 current.majorVersion(),
//                 current.minorVersion(),
//                 current.microVersion()) >= QVersionNumber::fromString(
//                     QString::fromLatin1(it->version));
//         }
//     }

//     // Result is true if the platform is not any of the checked ones; this matches behavior of
//     // LLVM __builtin_available and @available constructs
//     return true;
// }

// LOO_END_NAMESPACE

// #define QT_AVAILABLE_OS_VER(os, ver) \
//     QT_PREPEND_NAMESPACE(qt_clang_builtin_available_os_version_data){\
//         QT_PREPEND_NAMESPACE(QOperatingSystemVersion)::os, #ver}
// #define QT_AVAILABLE_CAT(L, R) QT_AVAILABLE_CAT_(L, R)
// #define QT_AVAILABLE_CAT_(L, R) L ## R
// #define QT_AVAILABLE_EXPAND(...) QT_AVAILABLE_OS_VER(__VA_ARGS__)
// #define QT_AVAILABLE_SPLIT(os_ver) QT_AVAILABLE_EXPAND(QT_AVAILABLE_CAT(QT_AVAILABLE_SPLIT_, os_ver))
// #define QT_AVAILABLE_SPLIT_macOS MacOS,
// #define QT_AVAILABLE_SPLIT_iOS IOS,
// #define QT_AVAILABLE_SPLIT_tvOS TvOS,
// #define QT_AVAILABLE_SPLIT_watchOS WatchOS,
// #define QT_BUILTIN_AVAILABLE0(e) \
//     QT_PREPEND_NAMESPACE(qt_clang_builtin_available)({})
// #define QT_BUILTIN_AVAILABLE1(a, e) \
//     QT_PREPEND_NAMESPACE(qt_clang_builtin_available)({QT_AVAILABLE_SPLIT(a)})
// #define QT_BUILTIN_AVAILABLE2(a, b, e) \
//     QT_PREPEND_NAMESPACE(qt_clang_builtin_available)({QT_AVAILABLE_SPLIT(a), \
//                                                       QT_AVAILABLE_SPLIT(b)})
// #define QT_BUILTIN_AVAILABLE3(a, b, c, e) \
//     QT_PREPEND_NAMESPACE(qt_clang_builtin_available)({QT_AVAILABLE_SPLIT(a), \
//                                                       QT_AVAILABLE_SPLIT(b), \
//                                                       QT_AVAILABLE_SPLIT(c)})
// #define QT_BUILTIN_AVAILABLE4(a, b, c, d, e) \
//     QT_PREPEND_NAMESPACE(qt_clang_builtin_available)({QT_AVAILABLE_SPLIT(a), \
//                                                       QT_AVAILABLE_SPLIT(b), \
//                                                       QT_AVAILABLE_SPLIT(c), \
//                                                       QT_AVAILABLE_SPLIT(d)})
// #define QT_BUILTIN_AVAILABLE_ARG(arg0, arg1, arg2, arg3, arg4, arg5, ...) arg5
// #define QT_BUILTIN_AVAILABLE_CHOOSER(...) QT_BUILTIN_AVAILABLE_ARG(__VA_ARGS__, \
//     QT_BUILTIN_AVAILABLE4, \
//     QT_BUILTIN_AVAILABLE3, \
//     QT_BUILTIN_AVAILABLE2, \
//     QT_BUILTIN_AVAILABLE1, \
//     QT_BUILTIN_AVAILABLE0, )
// #define __builtin_available(...) QT_BUILTIN_AVAILABLE_CHOOSER(__VA_ARGS__)(__VA_ARGS__)
// #endif // !QT_HAS_BUILTIN(__builtin_available)
// #endif // defined(__cplusplus)

// #endif // QGLOBAL_P_H


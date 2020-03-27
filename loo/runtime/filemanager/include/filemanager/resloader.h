
#ifndef LE_CORE_RESLOADER_HPP
#define LE_CORE_RESLOADER_HPP

#pragma once
#include "filemanager/dllexporter.h"
#include "global/global.h"
#include <istream>
#include <string>
#include <vector>
#if defined(LOO_COMPILER_CLANGC2)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter" // Ignore unused parameter 'x', 'alloc'
#pragma clang diagnostic ignored "-Wunused-variable" // Ignore unused variable (mpl_assertion_in_line_xxx) in boost
#endif
#include "global/extstd/readerwriterqueue.h"
#if defined(LE_COMPILER_CLANGC2)
#pragma clang diagnostic pop
#endif
#include "filemanager/residentifier.h"
#include "global/thread.h"
#include "global/extstd/noncopyable.h"
#include "filemanager/package.h"
#if defined(LOO_PLATFORM_ANDROID)
struct AAsset;
struct android_app;
#endif

namespace loo
{
	namespace fm
	{
		class FILEMANAGER_EXPORT ResLoadingDesc : loo::noncopyable
		{
		public:
			virtual ~ResLoadingDesc ()
			{
			}

			virtual uint64_t Type () const = 0;

			virtual bool StateLess () const = 0;

			virtual std::shared_ptr<void> CreateResource ()
			{
				return std::shared_ptr<void> ();
			}
			virtual void SubThreadStage () = 0;
			virtual void MainThreadStage () = 0;

			virtual bool HasSubThreadStage () const = 0;

			virtual bool Match (ResLoadingDesc const & rhs) const = 0;
			virtual void CopyDataFrom (ResLoadingDesc const & rhs) = 0;
			virtual std::shared_ptr<void> CloneResourceFrom (std::shared_ptr<void> const & resource) = 0;

			virtual std::shared_ptr<void> Resource () const = 0;
		};
		typedef std::shared_ptr<ResLoadingDesc> ResLoadingDescPtr;

		class FILEMANAGER_EXPORT ResLoader : loo::noncopyable
		{
		public:
			ResLoader ();
			~ResLoader ();

			static ResLoader& Instance ();
			static void Destroy ();
			void Init (
				loo::global::thread_pool& threadpool
#ifdef LOO_PLATFORM_ANDROID
				,android_app* state_
#endif
			);

			void Suspend ();
			void Resume ();

			void AddPath (nonstd::string_view phy_path);
			void DelPath (nonstd::string_view phy_path);
			bool IsInPath (nonstd::string_view phy_path);
			std::string const & LocalFolder () const
			{
				return local_path_;
			}

			void Mount (nonstd::string_view virtual_path, nonstd::string_view phy_path);
			void Unmount (nonstd::string_view virtual_path, nonstd::string_view phy_path);

			ResIdentifierPtr Open (nonstd::string_view name);
			std::string Locate (nonstd::string_view name);
			uint64_t Timestamp (nonstd::string_view name);
			std::string AbsPath (nonstd::string_view path);

			std::shared_ptr<void> SyncQuery (ResLoadingDescPtr const & res_desc);
			std::shared_ptr<void> ASyncQuery (ResLoadingDescPtr const & res_desc);
			void Unload (std::shared_ptr<void> const & res);

			template <typename T>
			std::shared_ptr<T> SyncQueryT (ResLoadingDescPtr const & res_desc)
			{
				return std::static_pointer_cast<T>(this->SyncQuery (res_desc));
			}

			template <typename T>
			std::shared_ptr<T> ASyncQueryT (ResLoadingDescPtr const & res_desc)
			{
				return std::static_pointer_cast<T>(this->ASyncQuery (res_desc));
			}

			template <typename T>
			void Unload (std::shared_ptr<T> const & res)
			{
				this->Unload (std::static_pointer_cast<void>(res));
			}

			void Update ();

		private:
			std::string RealPath (nonstd::string_view path);
			std::string RealPath (nonstd::string_view path,
				std::string& package_path, std::string& password, std::string& path_in_package);
			void DecomposePackageName (nonstd::string_view path,
				std::string& package_path, std::string& password, std::string& path_in_package);

			void AddLoadedResource (ResLoadingDescPtr const & res_desc, std::shared_ptr<void> const & res);
			std::shared_ptr<void> FindMatchLoadedResource (ResLoadingDescPtr const & res_desc);
			void RemoveUnrefResources ();

			void LoadingThreadFunc ();

#if defined(LOO_PLATFORM_ANDROID)
			AAsset* LocateFileAndroid (nonstd::string_view name);
#elif defined(LOO_PLATFORM_IOS)
			std::string LocateFileIOS (nonstd::string_view name);
#elif defined(LOO_PLATFORM_WINDOWS_STORE)
			std::string LocateFileWinRT (nonstd::string_view name);
#endif
		private:
			static std::unique_ptr<ResLoader> res_loader_instance_;

			enum LoadingStatus
			{
				LS_Loading,
				LS_Complete,
				LS_CanBeRemoved
			};

			std::string exe_path_;
			std::string local_path_;
			std::vector<std::tuple<uint64_t, uint32_t, std::string, PackagePtr>> paths_;
			std::mutex paths_mutex_;

			std::mutex loaded_mutex_;
			std::mutex loading_mutex_;
			std::vector<std::pair<ResLoadingDescPtr, std::weak_ptr<void>>> loaded_res_;
			std::vector<std::pair<ResLoadingDescPtr, std::shared_ptr<volatile LoadingStatus>>> loading_res_;
			moodycamel::ReaderWriterQueue< std::pair<ResLoadingDescPtr, std::shared_ptr<volatile LoadingStatus>>, 1024> loading_res_queue_;
			/*boost::lockfree::spsc_queue<std::pair<ResLoadingDescPtr, std::shared_ptr<volatile LoadingStatus>>,
				boost::lockfree::capacity<1024>> loading_res_queue_;*/

			std::unique_ptr<loo::global::joiner<void>> loading_thread_;
			volatile bool quit_;

#ifdef LOO_PLATFORM_ANDROID
			 android_app* state;
#endif
		};
	}
}

#endif			// LE_CORE_RESLOADER_HPP


#pragma once


#include "vkfg/vulkan/debugger/vlocaldebugger.h"

namespace loo
{
	namespace vkfg
	{

		//
		// Debugger
		//

		class VDebugger
		{
			// types
		private:
			using BatchGraph = VLocalDebugger::BatchGraph;


			// variables
		private:
			mutable Array<String>		_fullDump;
			mutable Array<BatchGraph>	_graphs;


			// methods
		public:
			VDebugger ();

			void AddBatchDump (String &&);
			void GetFrameDump (OUT String &) const;

			void AddBatchGraph (BatchGraph &&);
			void GetGraphDump (OUT String &) const;
		};


	}
}
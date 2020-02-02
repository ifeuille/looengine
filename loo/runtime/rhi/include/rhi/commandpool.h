#ifndef LOO_RHI_COMMANDPOOL_H
#define LOO_RHI_COMMANDPOOL_H
#pragma once
#include "rhi/dllexporter.h"
#include "global/global.h"

namespace loo
{
	namespace rhi
	{
		class RHIQueue;
		class RHI_EXPORT RHICommandPool
		{
		public:
			RHICommandPool (RHIQueue* InQueue):queue(InQueue){}
			virtual ~RHICommandPool () {}

			virtual LOOResult ResetCommandPool () {	return LOO_SUCCESS;}

		private:
			RHIQueue* queue;
		};
	}
}

#endif
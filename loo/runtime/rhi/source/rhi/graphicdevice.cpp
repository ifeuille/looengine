#include "rhi/graphicdevice.h"
#include "rhi/queue.h"

loo::rhi::GraphicDevice* GGraphicDevice = NULL;

loo::rhi::RHIQueue * loo::rhi::GraphicDevice::GetDeviceQueue (uint32 queueFamilyIndex, uint32 queueIndex)
{
	auto it = queuesMap.find (queueFamilyIndex);
	if (it == queuesMap.end ())
	{
		return nullptr;
	}
	auto itt = it->second.find (queueIndex);
	if (itt == it->second.end ())
	{
		return nullptr;
	}
	return itt->second;
}

void loo::rhi::GraphicDevice::PushQueue (uint32 queueFamilyIndex, uint32 queueIndex, RHIQueue* queue)
{
	if (!queue)return;
	auto it = queuesMap.find (queueFamilyIndex);
	if (it == queuesMap.end ())
	{
		std::unordered_map<uint32/*queueIndex*/, RHIQueue*> queueMap;
		queueMap.insert (std::make_pair(queueIndex, queue));
		queuesMap.insert (std::make_pair(queueFamilyIndex, queueMap));
		return;
	}
	queuesMap[queueFamilyIndex][queueIndex] = queue;
}

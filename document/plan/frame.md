



1.frame

solution:multiples dlls + multi exe



global(header only):global(type,harwar define)

public:looreflect(独立),

RHI(渲染抽象层),

logger(独立),

ecs system(header only独立),

render graph(pipeline 抽象层，只依赖RHI)

core:

memory mgr,math,container,event mgr,plugin mgr

hal:

threadmgr : 协程,thread,signals,multicore support,job queue,batches

resourcemanager,

input manager:mouse,keyboard,joysticks,gamepads

timemanager:



第三方：

lua(也许可以嵌入),physical，sound



2.utils

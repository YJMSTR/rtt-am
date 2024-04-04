#include <am.h>
#include <klib.h>
#include <rtthread.h>

static rt_ubase_t ctx_from, ctx_to;

static Context* ev_handler(Event e, Context *c) {
  switch (e.event) {
    case EVENT_YIELD:
      ctx_from = (rt_ubase_t)(&c);
      Context *ctxto = *(Context **)ctx_to;
      return ctxto;
    case EVENT_IRQ_TIMER:
      return c;
    default: printf("Unhandled event ID = %d\n", e.event); assert(0);
  }
  return c;
}

void __am_cte_init() {
  cte_init(ev_handler);
}

void rt_hw_context_switch_to(rt_ubase_t to) {
  // Context *c = *(Context **)to;
  // struct rt_thread *thread = rt_thread_self();
  ctx_to = to;
  yield();
  assert(0);
}

void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to) {
  *(Context **)from = rt_thread_self()->sp;
  ctx_to = to;
  yield();
  assert(0);
}

void rt_hw_context_switch_interrupt(void *context, rt_ubase_t from, rt_ubase_t to, struct rt_thread *to_thread) {
  assert(0);
}

void wrapper_func(void *tentry, void *parameter, void *texit) {
  ((void (*)(void *))tentry)(parameter);
  ((void (*)())texit)();
}

rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter, rt_uint8_t *stack_addr, void *texit) {
  rt_uint8_t *addr = (rt_uint8_t *)(stack_addr - ((uintptr_t)stack_addr) % sizeof(Context));
  rt_uint8_t *ctx_addr = (addr - sizeof(Context));
  Context *ctx = (Context *)ctx_addr;
  ctx->mepc = (uintptr_t)wrapper_func;
  ctx->gpr[10] = (uintptr_t)tentry;
  ctx->gpr[11] = (uintptr_t)parameter;
  ctx->gpr[12] = (uintptr_t)texit;

  return ctx_addr;
}

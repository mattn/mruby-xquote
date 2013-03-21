#include <mruby.h>
#include <mruby/string.h>
#include <unistd.h>

static mrb_value
mrb_backtick(mrb_state *mrb, mrb_value self) {
  char* str;
  char* out = "";

  mrb_get_args(mrb, "z", &str);
  return mrb_str_new_cstr(mrb, out);
}

/*********************************************************
 * register
 *********************************************************/

void
mrb_mruby_backtick_gem_init(mrb_state* mrb) {
  mrb_define_class_method(mrb, mrb->kernel_module, "backtick", mrb_backtick, ARGS_REQ(1));
}

void
mrb_mruby_backtick_gem_final(mrb_state* mrb) {
}

/* vim:set et ts=2 sts=2 sw=2 tw=0: */
